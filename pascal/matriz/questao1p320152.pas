program quest;
CONST MAX = 50;
type matrix = array[1..MAX,1..MAX] of integer;
    vector = array[1..MAX] of integer;
var n, m, size: integer; v: vector; mat: matrix;

procedure SortArray(var v: vector; size: integer);
var i, j, LeastPos, temp: integer;
begin
  for i:= 1 to size-1 do
    begin
      LeastPos:= i;
      for j:= i + 1 to size do
	if v[j] < v[LeastPos] then
	    LeastPos:= j;

	temp:= v[LeastPos];
	v[LeastPos]:= v[i];
	v[i]:= temp;
    end;
end;


procedure ReadMatrix(var mat: matrix; n, m: integer);
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to m do
      read(mat[i,j]);
end;

procedure NewArray(var mat: matrix; n, m: integer; var v: vector; var size: integer);
var i, j: integer;
begin
  size:= 0;
  for i:= 1 to n do
    begin
      for j:= 1 to m do
	begin
	  if (mat[i,j] = mat[j,i]) then 
	    begin
	      size:= size + 1;
	      v[size]:= mat[i,j];
	      mat[j,i]:= 0;
	    end;
	end;
    end;
end;

procedure printArray(var v: vector; size: integer);
var i: integer;
begin
  for i:= 1 to size do
    write(v[i],' ');
end;

begin
  read(n, m);
  ReadMatrix(mat, n, m);
  NewArray(mat, n, m, v, size);
  SortArray(v, size);
  PrintArray(v, size);
end.
