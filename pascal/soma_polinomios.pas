program soma_polinomios;
type
	vetor=array[0..199] of real;

procedure ler_polinomios(var p, q: vetor; var grau_p, grau_q:longint);
	var
		i: longint;
	begin
		writeln('qual o grau do polinomio p?');
		read(grau_p);
		
		     writeln('escreva os coeficientes');
		for i:= grau_p downto 0 do
		  begin	
	   	     read(p[i]);	     
		   end;

	   	writeln('qual o grau do polinomio q?');
		read(grau_q);
		
		     writeln('escreva os coeficientes');
		for i:= grau_q downto 0 do
		  begin	
	   	     read(q[i]);	     
		   end;	      
	end;

procedure somar(var p, q, s: vetor; var grau_p, grau_q, grau_s: longint);
	var
	   i, menorgrau: longint;
	begin
	    if grau_p > grau_q then
	      begin
		  grau_s:= grau_p;
	          menorgrau:= grau_q;

		  for i:= menorgrau + 1 to grau_s do
			begin
			  s[i]:= p[i];
			end;	  
	      end	    
      	     else
		 begin
		     grau_s:= grau_q;
	             menorgrau:= grau_p;
	             for i:= menorgrau + 1 to grau_s do
		         s[i]:= q[i];	     
		 end;	 
	    
	    for i:= 0 to menorgrau do
	        s[i]:= p[i] + q[i];	    
	end;

procedure escrever_polinomios(var p, q, s: vetor; var g1, g2 , g3: longint);
	var
		i: longint;
	begin
		writeln('aqui esta o polinomio p:');
		for i:= g1 downto 0 do
			write(' ',p[i]:0:0);
		writeln();
		
		writeln('aqui esta o polinomio q:');
		for i:= g2 downto 0 do
			write(' ',q[i]:0:0);
		writeln();

		writeln('aqui esta a soma dos polinomios:');
		for i:= g3 downto 0 do
			write(' ',s[i]:0:0);
			writeln();
	end;

var
	grau_p, grau_q, grau_s: longint;
	p, q, s: vetor;	
begin
	ler_polinomios(p , q, grau_p, grau_q);
	somar(p, q, s, grau_p, grau_q, grau_s);
	escrever_polinomios(p, q , s, grau_p, grau_q, grau_s);
end.
