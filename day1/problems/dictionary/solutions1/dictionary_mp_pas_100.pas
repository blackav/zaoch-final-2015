{$R-,Q-,S-,D-,I-,L-,O+}
uses
	SysUtils, Math;
const
	max_n = 200010;
type
	char_array = array[1..max_n] of char;
	int_array = array[1..max_n] of longint;	
var
	s: char_array;
	z_a, z_b, used: int_array;
	bad: array[1..max_n] of boolean;
	l, n, len_a, len_b, start, pos: longint;

procedure print(start, len: longint; var s: char_array);
var
	i: longint;
begin
	for i := start to start + len - 1 do
		write(s[i]);
	writeln;
end;

procedure calc_z(start, n: longint; var s: char_array; var z: int_array);
var
	i, l, r, zvalue: longint;
begin
	z[start] := 0;
	l := 0;
	r := 0;
    for i := 1 to n do begin
        zvalue := min(z[start + i - l], max(0, r - i + 1));
        while (s[start + zvalue] = s[start + i + zvalue]) do begin
            inc(zvalue);
            l := i;
            r := i + zvalue - 1;
        end;
        z[i + start] := zvalue;
    end;
end;

begin
    readln(l);
    n := 0;
    while not eoln do begin
    	inc(n);
    	bad[n] := false;
    	used[n] := 0;
    	read(s[n]);
    end;
    calc_z(1, n, s, z_a);
    z_a[1] := l;
    for len_a := 1 to l do begin
        if (bad[len_a]) then continue;
        start := len_a + 1;
        while (z_a[start] >= len_a) do begin
            inc(start, len_a);
            bad[start] := true;
        end;
        if (start = n + 1) then begin
            writeln(1);
            print(1, len_a, s);
            halt(0);
        end;
    end;
    for len_a := 1 to l do begin
        if (bad[len_a]) then continue;
        start := len_a + 1;
        while (z_a[start] >= len_a) do
            inc(start, len_a);
        calc_z(start, n - start + 1, s, z_b);
        z_b[start] := l;
        for len_b := 1 to l do begin
            pos := start + len_b;
            while (used[pos] <> len_a) do begin
                used[pos] := len_a;
                if (z_a[pos] >= len_a) then
                    inc(pos, len_a)
                else if (z_b[pos] >= len_b) then
                    inc(pos, len_b)
                else
                    break;
            end;
            if (pos = n + 1) then begin
                writeln(2);
                print(1, len_a, s);
                print(start, len_b, s);
                halt(0);
            end;
        end;
    end;
    writeln('3');
    writeln('a');
    writeln('b');
    writeln('c');
end.
