program teste;
type vetor = array[1..100] of integer;
    matriz = array[1..100,1..100] of integer;
var
  n, i: integer; 
  m: matriz;

function isInMatrix(var v:vetor; element, n: integer):boolean;
var i: integer;
begin
  isInMatrix:= false;
  for i:= 1 to n do
    if v[i] = element then
      isInMatrix:= true;
end;

function verifyMatrix(var m: matriz; n: integer): integer;
var i, j: integer;
    founded: boolean;
begin
  for i:= 1 to n do
    begin
      for j:= 2 to n do
        if isInMatrix(m[j], m[1,i], n) then
          founded:= true
        else founded:= false;
      
        if (cont = n) and founded then
          verifyMatrix:= m[1,j];

    end;
end;

procedure sortRows(var v:vetor; n: integer);
var i, j, leastPos, switch: integer;
begin
  for i:= 1 to n-1 do
    begin
      leastPos:= i;
      for j:= i+1 to n do
        if v[j] > v[leastPos] then
          leastPos:= j;

      switch:= v[leastPos];
      v[leastPos]:= v[i];
      v[i]:= switch;
    end;
end;

procedure readMatrix(var m: matriz; n: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to n do
      read(m[i,j]);
end;

begin
  read(n);
  readMatrix(m, n);

  for i:= 1 to n do
    sortRows(m[i], n);

  writeln(verifyMatrix(m,n));
end.
