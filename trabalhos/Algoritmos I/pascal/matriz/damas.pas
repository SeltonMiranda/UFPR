program d;
CONST MAX = 8;
type matriz = array[1..MAX,1..MAX] of longint;
var m: matriz;

procedure pecaqueficam(var m: matriz);
var i, j, cont: longint;
begin
  cont:= 0;
  for i:= 1 to MAX do
    begin
      for j:= 1 to MAX do
	begin
	  if m[i,j] = -1 then
	    begin
	      if  (j=1) then
		begin
		  if m[i+1,j+1] = -1 then
		    begin
		      cont:= cont + 1;
		      write(i,'-',j,' ');
		    end;
		end
	      else if (j = MAX) then
		begin
		  if m[i+1,j-1] = -1 then
		    begin
		      cont:= cont + 1;
		      write(i,'-',j,' ');
		    end;
		end
	      else
		begin
		  if (m[i+1,j+1]=-1) and (m[i+1,j-1]=-1) then
		    begin
		      cont:= cont + 1;
		      write(i,'-',j,' ');
		    end;
		end;
	    end;
    	end;
    end;

    if cont = 0 then
      write(0,' ');
end;

procedure pecaquemove(var m: matriz);
var i, j, cont: longint;
begin
  cont:= 0;
  for i:= 1 to MAX do
    begin
      for j:= 1 to MAX do
	begin
	  if m[i,j] = -1 then
	    begin
	      if  (j=1) then
		begin
		  if m[i+1,j+1] = 0 then
		    begin
		      cont:= cont + 1;
		      write(i,'-',j,' ');
		    end;
		end
	      else if (j = MAX) then
		begin
		  if m[i+1,j-1] = 0 then
		    begin
		      cont:= cont + 1;
		      write(i,'-',j,' ');
		    end;
		end
	      else 
		begin
		  if (m[i+1,j+1]= -1) and (m[i+1,j-1]= 0) then
		    begin
		      cont:= cont + 1;
		      write(i,'-',j,' ');
		    end
		  else if (m[i+1,j+1]= 0) and (m[i+1,j-1]=-1) then
		    begin
		      cont:= cont + 1;
		      write(i,'-',j,' ');
		    end
		  else if (m[i+1,j+1]= 0) and (m[i+1,j-1]= 0) then
		      begin
			cont:= cont + 1;
			write(i,'-',j,' ');
		      end;
		end;
	    end;
	end;
    end;

    if cont = 0 then
      write(0,' ');
end;

procedure pecaquetomam(var m: matriz);
var i, j, cont: longint;
begin
  cont:= 0;
  for i:= 1 to MAX do
    begin
      for j:= 1 to MAX do
	begin
	  if m[i,j]= -1 then
	    begin
	      if (m[i+1,j+1] = 1) and (m[i+2,j+2]=0) then
		begin
		  cont:= cont + 1;
		  write(i,'-',j,' ');
		end
	      else if (m[i+1,j-1]=1) and (m[i+2,j-2]=0) then
		  begin
		    cont:= cont + 1;
		    write(i,'-',j,' ');
		  end;
	    end;
    	end;
    end;
    if cont = 0 then
      write(0,' ');
end;

procedure lermatriz(var m: matriz);
var i, j: longint;
begin
  for i:=1 to MAX do
    for j:= 1 to MAX do
      read(m[i,j]);
end;


begin
  lermatriz(m);

  write('tomar: ');
  pecaquetomam(m);
  writeln();

  write('mover: ');
  pecaquemove(m);
  writeln();

  write('ficar: ');
  pecaqueficam(m);
end.
