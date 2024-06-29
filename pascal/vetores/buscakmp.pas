program KMP;

procedure ComputeFailureArray(pattern: string; var failure: array of integer);
var
  m, j, i: integer;
begin
  m := Length(pattern);
  j := 0;
  failure[1] := 0;

  for i := 2 to m do
  begin
   while (j > 0) and (pattern[j + 1] <> pattern[i]) do
      j := failure[j];

    if pattern[j + 1] = pattern[i] then
      Inc(j);

    failure[i] := j;
  end;
end;

procedure KMPSearch(text, pattern: string);
var
  n, m, i, j: integer;
  failure: array of integer;
begin
  n := Length(text);
  m := Length(pattern);

  SetLength(failure, m);

  ComputeFailureArray(pattern, failure);

  i := 1;
  j := 0;

  while i <= n do
  begin
    if pattern[j + 1] = text[i] then
    begin
      Inc(i);
      Inc(j);

      if j = m then
      begin
        writeln('Padrão encontrado na posição ', i - j);
        j := failure[j];
      end;
    end
    else if j > 0 then
      j := failure[j]
    else
      Inc(i);
  end;
end;

var
  text, pattern: string;
begin
  writeln('Digite o texto:');
  readln(text);
  
  writeln('Digite o padrão a ser procurado:');
  readln(pattern);

  KMPSearch(text, pattern);
end.

