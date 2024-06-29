program seilaoquefaz;
type tipo_vetor = array[1..200] of longint;
var v: tipo_vetor; n, b, decimal: longint;

function ConverterBase(var v: tipo_vetor; x, tam: longint): longint;
  var s, i, base: longint;
  begin
    base:= 1;
    s:= 0;
    for i:=tam downto 1 do
      begin
	s:= s + v[i]*base;
	base:= base*x;
      end;
      ConverterBase:= s;    
  end;

function VerificarVetor(var v: tipo_vetor; x, tam: longint): boolean;
  var i: longint;
  begin	 
    VerificarVetor:= true;
    for i:= 1 to tam do
      begin
	if v[i] > x then
	  VerificarVetor:= false;
      end;
  end;


procedure LerVetor(var v: tipo_vetor; tam: longint);
  var i: longint;
  begin
    for i:= 1 to tam do
      read(v[i]);
  end;

begin
  read(b);
  read(n);
  LerVetor(v, n);
  if VerificarVetor(v, b, n) then
    begin
      decimal:= ConverterBase(v, b, n);
      writeln(decimal);
    end
  else
    writeln(-1);
end.
