unit racionais;

interface

type 
        Tracional = record
                num, den: integer;
                valido: boolean;
        end;

function validoRacional(var r: Tracional): boolean;
function criaRacional(num, den: integer): Tracional;
function numeradorRacional(var r: Tracional): integer;
function denominadorRacional(var r: Tracional): integer;
function sorteiaRacional(max: integer): Tracional;
function aleat(max, min: integer): integer;
function somaRacional(var r1, r2: Tracional): Tracional;
function subtraiRacional(var r1, r2: Tracional): Tracional;
function multiplicaRacional(var r1, r2: Tracional): Tracional;
function divideRacional(var r1, r2: Tracional): Tracional;
procedure imprimirRacional(var r: Tracional);
procedure simplificaRacional(var r: Tracional);

implementation

function aleat(max, min: integer): integer;
begin
        aleat := min + random(10000) mod max+1;
end;

function sorteiaRacional(max: integer): Tracional;
var
        num, den: integer;
        r: Tracional;
begin
        num := aleat(max, -max);
        den := aleat(max, -max);
        r := criaRacional(num, den);
        sorteiaRacional:= r;
end;

function validoRacional(var r: Tracional): boolean;
begin
        validoRacional := r.valido;
end;

procedure imprimirRacional(var r: Tracional);
begin
        if not validoRacional(r) then
                write('INVALIDO')
        else if r.den = 1 then
                write(r.num)
        else if r.num = 0 then
                write(0)
        else if r.num = r.den then
                write(1)
        else
                write(r.num,'/', r.den);
end;

function numeradorRacional(var r: Tracional): integer;
begin
        numeradorRacional := r.num;
end;

function denominadorRacional(var r: Tracional): integer;
begin
        denominadorRacional := r.den;
end;

function mdc(a, b: integer): integer;
begin
        if b = 0 then
                mdc := a
        else
                mdc := mdc(b, a mod b);
end;

procedure simplificaRacional(var r: Tracional);
var
        maxDiv: integer;
begin
        maxDiv := mdc(r.num, r.den);
        r.num := r.num div maxDiv;
        r.den := r.den div maxDiv;

        if r.den < 0 then
                begin
                        r.num := r.num * -1;
                        r.den := r.den * -1;
                end;
end;

function criaRacional(num, den: integer): Tracional;
var racional: Tracional;
begin
        racional.num := num;
        racional.den := den;
        racional.valido := racional.den <> 0;
        simplificaRacional(racional);
        criaRacional := racional;
end;

function somaRacional(var r1, r2: Tracional): Tracional;
var 
        soma: Tracional;
        num, den: integer;
begin
        num := r1.num * r2.den + r1.den * r2.num;
        den := r1.den * r2.den;
        soma := criaRacional(num, den);
        somaRacional := soma;
end;

function subtraiRacional(var r1, r2: Tracional): Tracional;
var 
        subtrai: Tracional;
        num, den: integer;
begin
        num := r1.num * r2.den - r1.den * r2.num;
        den := r1.den * r2.den;
        subtrai := criaRacional(num, den);
        subtraiRacional := subtrai;
end;

function multiplicaRacional(var r1, r2: Tracional): Tracional;
var
        mult: Tracional;
        num, den: integer;
begin
        num := r1.num * r2.num;
        den := r1.den * r2.den;
        mult := criaRacional(num, den);
        multiplicaRacional := mult;
end;

function divideRacional(var r1, r2: Tracional): Tracional;
var
        divi: Tracional;
        num, den: integer;
begin
        num := r1.num * r2.den;
        den := r1.den * r2.num;
        divi := criaRacional(num, den);
        divideRacional := divi;
end;

end.
