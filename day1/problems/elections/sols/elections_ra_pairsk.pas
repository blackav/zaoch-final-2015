uses SysUtils;
{$R-,Q-,S-,D-,I-,L-,O+}
const maxn = 30000;
const maxe = 10000000;

const TASK = 'elections';
type ll = int64;
type int = longint;
var dp : array[0..1, 0..maxn] of ll;
    one, xx : array[0..maxn] of ll;
    szf, ke : int;
    fx : array[0..100] of ll;
    fy : array[0..100] of int;
    head : array[0..maxn] of int;
    next, en : array[0..maxe] of int;
procedure factorize(n : ll);
var i : ll;
    cnt : int;
begin
  szf := 0;
  i := 2;
  while (i * i <= n) do begin
    cnt := 0;
    while (trunc(n / i) * i = n) do begin
      n := n div i;
      inc(cnt);
    end;
    if (cnt > 0) then begin
      fx[szf] := i;
      fy[szf] := cnt;
      inc(szf);
    end;
    inc(i);
  end;
  if (n > 1) then begin
    fx[szf] := n;
    fy[szf] := 1;
    inc(szf);
  end;
end;
procedure reserve(stp1 : int; rs : int; x : ll; i : int);
var S, v1 : int;
begin
  if (i = szf) then begin    
    xx[stp1] := x;
    one[stp1] := (x + 1) div 2;
    dp[0, stp1] := one[stp1];
    exit;
  end;
  S := fy[i];  
  stp1 := stp1 * (S + 1);  
  for v1 := 0 to S do begin    
    reserve(stp1 + v1, rs * (v1 + 1), x, i + 1);
    x := x * fx[i];
  end;
end;
procedure add(x, y : int);
begin
  inc(ke);
  next[ke] := head[x];
  head[x] := ke;
  en[ke] := y;
end;
procedure construct_edges(stp1 : int; stp2 : int; i: int);
var S, v1, v2 : int;
begin
  if (i = szf) then begin    
    if (xx[stp1] <= xx[stp2 - stp1]) then begin
      add(stp2, stp1);
    end;
    exit;
  end;
  S := fy[i];  
  stp1 := stp1 * (S + 1);  
  stp2 := stp2 * (S + 1);  
  for v1 := 0 to S do begin    
    for v2 := v1 to S do begin    
      construct_edges(stp1 + v1, stp2 + v2, i + 1);
    end;
  end;
end;
var n, inf, val : ll;
//    start : TDateTime;
    k, v1, i, j, cur, ncur, bb : int;
begin        
//  start := now();
  {$ifdef home}
  assign(input, TASK + '.in');
  reset(input);
  assign(output, TASK + '.out');
  rewrite(output);
  {$endif}
  ke := 0;
  read(n, k);
  inf := n + 1;
  factorize(n);
  reserve(0, 1, 1, 0);
  construct_edges(0, 0, 0);
  v1 := 0;
  for i := 0 to szf - 1 do begin
    v1 := v1 * (fy[i] + 1) + fy[i];
  end;
  cur := 0;
  for i := 1 to k - 1 do begin
    ncur := 1 - cur;    
    for j := 0 to v1 do begin
      dp[ncur, j] := inf;
      bb := head[j];
      while (bb <> 0) do begin
        val := one[en[bb]] * dp[cur,j - en[bb]];
        if (dp[ncur,j] > val) then begin
          dp[ncur,j] := val;
        end;
        bb := next[bb];
      end;
    end;
    cur := ncur;
  end;
  writeln(dp[cur, v1]);
//  writeln(stderr, (now() - start) * 24 * 60 * 60 :0:10);
end.
