#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>
#include <stdint.h>

#include <likwid.h>

#include "utils.h"
// o que mudar

// montaSL
// alocar mem alinhada (sizeof(real_t *))
// verificar se n é pot de 2, se for somar um padding
// percorrer o vetor de maior tamanho uma vez só(mais externo) (vai ter que mudar o preenchimento de outras coisas)

// eliminacao de gauss
// retrossub -> loop unrolling (criar um vetor de 4 somas e fazer o unroll depois subtrair no final) fator 4

/////////////////////////////////////////////////////////////////////////////////////
//   AJUSTE DE CURVAS
/////////////////////////////////////////////////////////////////////////////////////
void montaSLOtm(double **A, double *b, int n, long long int p, double *x, double *y)
{
  n--; // n é a ordem do SL, tem que diminuir para representar o grau do polinomio

  A[0][0] = (real_t)p;
  // laco sobre p é o mais externo porque este eh o vetor com mais elementos desta forma minimizamos o cache miss
  for (int i = 0; i < p; i++)
  {
    real_t powX;
    b[0] += y[i];
    // calcula primeira linha de a e o vetor b
    powX = 1.0;
    for (int j = 1 j <= n; j++)
    {
      powX *= x[i];
      A[0][j] += powX;
      b[j] += powX * y[i];
    }

    // calcula ultima coluna de a
    for (int k = 1; k <= n; k++)
    {
      powX *= x[i];
      A[0][n] += powX;
    }

    // preenche os espacos restantes da matriz a
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < n; j++)
        a[i][j] = a[i - 1][j - 1];
  }
}

void montaSL(double **A, double *b, int n, long long int p, double *x, double *y)
{
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
    {
      A[i][j] = 0.0;
      for (long long int k = 0; k < p; ++k)
      {
        A[i][j] += pow(x[k], i + j);
      }
    }

  for (int i = 0; i < n; ++i)
  {
    b[i] = 0.0;
    for (long long int k = 0; k < p; ++k)
      b[i] += pow(x[k], i) * y[k];
  }
}

void eliminacaoGauss(double **A, double *b, int n)
{
  for (int i = 0; i < n; ++i)
  {
    int iMax = i;
    for (int k = i + 1; k < n; ++k)
      if (A[k][i] > A[iMax][i])
        iMax = k;

    if (iMax != i)
    {
      double *tmp, aux;
      tmp = A[i];
      A[i] = A[iMax];
      A[iMax] = tmp;

      aux = b[i];
      b[i] = b[iMax];
      b[iMax] = aux;
    }

    for (int k = i + 1; k < n; ++k)
    {
      double m = A[k][i] / A[i][i];
      A[k][i] = 0.0;

      for (int j = i + 1; j < n; ++j)
        A[k][j] -= A[i][j] * m;

      b[k] -= b[i] * m;
    }
  }
}

void retrossubs(double **A, double *b, double *x, int n)
{
  for (int i = n - 1; i >= 0; --i)
  {
    x[i] = b[i];

    for (int j = i + 1; j < n; ++j)
      x[i] -= A[i][j] * x[j];

    x[i] /= A[i][i];
  }
}

double Pol(double x, int G, double *alpha)
{
  double Px = alpha[0];
  for (int i = 1; i <= G; ++i)
    Px += alpha[i] * pow(x, i);

  return Px;
}

void *aligned_malloc(size_t bytes)
{
}

int main()
{

  int G, g;           // G -> grau do polinomio
  long long int P, p; // P -> no. de pontos
  string_t marker;

  scanf("%d %lld", &G, &P);
  p = P;     // quantidade de pontos
  g = G + 1; // tamanho do SL (G + 1)

  double *x = (double *)malloc(sizeof(double) * p);
  double *y = (double *)malloc(sizeof(double) * p);

  // ler numeros
  for (long long int i = 0; i < p; ++i)
    scanf("%lf %lf", x + i, y + i);

  double **A = (double **)malloc(sizeof(double *) * g);
  for (int i = 0; i < g; ++i)
    A[i] = (double *)malloc(sizeof(double) * g);

  double *b = (double *)malloc(sizeof(double) * g);
  double *alpha = (double *)malloc(sizeof(double) * g); // coeficientes ajuste

  LIKWID_MARKER_INIT;

  // (A) Gera SL
  marker = markerName("SL", p);
  LIKWID_MARKER_START(marker);
  double tSL = timestamp();
  montaSL(A, b, g, p, x, y);
  tSL = timestamp() - tSL;
  LIKWID_MARKER_STOP(marker);
  free(marker);

  // (B) Resolve SL
  marker = markerName("EG", p);
  LIKWID_MARKER_START(marker);
  double tEG = timestamp();
  eliminacaoGauss(A, b, g);
  retrossubs(A, b, alpha, g);
  tEG = timestamp() - tEG;
  LIKWID_MARKER_STOP(marker);
  free(marker);

  LIKWID_MARKER_CLOSE;

  // Imprime coeficientes
  for (int i = 0; i < g; ++i)
    printf("%1.15e ", alpha[i]);
  puts("");

  // Imprime resíduos
  for (long long int i = 0; i < p; ++i)
    printf("%1.15e ", fabs(y[i] - Pol(x[i], G, alpha)));
  puts("");

  // Imprime os tempos
  printf("%lld %1.10e %1.10e\n", P, tSL, tEG);

  return 0;
}
