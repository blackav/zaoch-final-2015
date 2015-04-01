outputtemplate := "%j-%c.eps";

beginfig(1)
  u:=2cm;
  w:=5u;
  h:=1u / 2 * 3;
  r:=h/4;
  pair S, A[], B[];
  n:=3;
  m:=3;
  S=(w/2, 2h);
  A[1]=(w / (n + 1), 1h);
  B[1]=(0, 0);
  for i=1 upto n - 1: A[i + 1] = A[i] + (w / (n + 1), 0); endfor;
  for i=1 upto n * m - 1: B[i + 1] = B[i] + (w / (n * m - 1), 0); endfor;
  for i=1 upto n:
    draw S -- A[i];
    for j=1 upto m:
      draw A[i]--B[(i - 1) * m + j];
    endfor;
  endfor;
  color c;
  c:= black;
  draw fullcircle scaled r shifted S;
  fill fullcircle scaled r shifted S withcolor c;  
  for i=1 upto n:
    c:=white;
    if (i * 2 <= n + 1): c:=black; fi;
    draw fullcircle scaled r shifted A[i];
    fill fullcircle scaled r shifted A[i] withcolor c;    
    for j=1 upto m:
      c:=white;
      if (i * 2 <= n + 1) and (j * 2 <= m + 1): c:=black; fi;
      draw fullcircle scaled r shifted B[(i - 1) * m + j];
      fill fullcircle scaled r shifted B[(i - 1) * m + j] withcolor c;
    endfor;
  endfor;


endfig;

beginfig(2)
  u:=2cm;
  w:=5u;
  h:=1u;
  r:=h/4;
  pair S, A[], B[], C[];
  n:=2;
  m:=2;
  k:=3;
  S=(w/2, 3h);
  A[1]=(w / (n + 1), 2h);
  sh:= w / (n * m + 2);
  B[1]=(sh, 1h);
  C[1]=(0, 0);  
  for i=1 upto n - 1: A[i + 1] = A[i] + (w / (n + 1), 0); endfor;
  for i=1 upto n * m - 1: B[i + 1] = B[i] + ((w - 2 * sh) / (n * m - 1), 0); endfor;
  for i=1 upto n * m * k - 1: C[i + 1] = C[i] + (w / (n * m * k - 1), 0); endfor;  
  for i=1 upto n:
    draw S -- A[i];
    for j=1 upto m:
      draw A[i]--B[(i - 1) * m + j];    
      for l=1 upto k:
        draw B[(i - 1) * m + j]--C[(i - 1) * m * k + (j - 1) * k + l];
      endfor;    
    endfor;
  endfor;
  color c;
  c:= black;
  draw fullcircle scaled r shifted S;
  fill fullcircle scaled r shifted S withcolor c;  
  for i=1 upto n:
    c:=white;
    if (i * 2 <= n + 1): c:=black; fi;
    draw fullcircle scaled r shifted A[i];
    fill fullcircle scaled r shifted A[i] withcolor c;    
    for j=1 upto m:
      c:=white;
      if (i * 2 <= n + 1) and (j * 2 <= m + 1): c:=black; fi;
      draw fullcircle scaled r shifted B[(i - 1) * m + j];
      fill fullcircle scaled r shifted B[(i - 1) * m + j] withcolor c;
      for l=1 upto k:
        c:=white;
        if (i * 2 <= n + 1) and (j * 2 <= m + 1) and (l * 2 <= k + 1): c:=black; fi;
        draw fullcircle scaled r shifted C[(i - 1) * m * k + (j - 1) * k + l];
        fill fullcircle scaled r shifted C[(i - 1) * m * k + (j - 1) * k + l] withcolor c;
      endfor;      
    endfor;
  endfor;


endfig;
