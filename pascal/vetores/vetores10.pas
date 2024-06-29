program questao;
type vetor = array[1..200] of longint;
var v: vetor; tam_v, n, posi: longint;

procedure ler_vetor(var v: vetor; var tam: longint);
    var i, n: longint;
    begin
        i:= 1;
        read(n);
        while n<> 0 do
            begin
                v[i]:= n;
                i:= i + 1;
                read(n);
            end;
        tam:= i - 1;
    end;
    
function pertence (var v: vetor; tam, x: longint): boolean;
    var i: longint;
    begin
        v[tam + 1]:= x;
        i:= 1;
        while (v[i]<> x) do
                i:= i + 1;

        if i > tam then
            pertence:= false
        else
            pertence:= true;
    end;

function acharposi(var v: vetor; tam, x: longint): longint;
    var  i: longint;
    begin
        v[tam + 1]:= x;
        i:= 1;
        while (v[i]<> x) do
                i:= i + 1;

	if i <= tam then
	  acharposi:= i
	else
	  acharposi:= 0;
  end;
    
begin
    ler_vetor(v, tam_v);
    read(n);
    while n <> 0 do
        begin
            if pertence(v, tam_v, n) then
	      begin
		posi:= acharposi(v, tam_v, n);
                writeln(posi);
	      end
            else
                writeln(0);
            read(n);    
        end;
end.
