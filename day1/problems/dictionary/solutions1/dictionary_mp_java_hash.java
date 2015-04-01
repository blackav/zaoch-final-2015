import java.io.*;

public class dictionary_mp_java_hash {
    private static final int P = 17239;
    private static final int M = (int) 1e9 + 7;
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        new dictionary_mp_java_hash().run();
        out.close();
    }

    void print(int start, int n, char s[]) {
        for (int i = 0; i < n; ++i)
            out.print(s[start + i]);
        out.println();
    }

    public void run() throws IOException {
        final int l = Integer.parseInt(rd.readLine());
        final char s[] = rd.readLine().toCharArray();
        final int n = s.length, used[] = new int[n + 1];
        long h[] = new long[n + 1], ppow[] = new long[n + 1];
        final boolean bad[] = new boolean[n + 1];
        ppow[0] = 1;
        for (int i = 0; i < n; ++i) {
            h[i + 1] = (h[i] * P + s[i]) % M;
            ppow[i + 1] = (ppow[i] * P) % M;
        }
        for (int len_a = 1; len_a <= l; ++len_a) {
            if (bad[len_a]) continue;
            int start = len_a;
            long hvalue = h[len_a];
            while ((start + len_a <= n) && ((h[start + len_a] - h[start] * ppow[len_a] - hvalue) % M == 0)) {
                start += len_a;
                bad[start] = true;
            }
            if (start == n) {
                out.println(1);
                print(0, len_a, s);
                return;
            }
        }
        for (int len_a = 1; len_a <= l; ++len_a) {
            if (bad[len_a]) continue;
            int start = len_a;
            long hvalue_a = h[len_a];
            while ((h[start + len_a] - h[start] * ppow[len_a] - hvalue_a) % M == 0)
                start += len_a;
            for (int len_b = 1; len_b <= l; ++len_b) {
                int pos = start + len_b;
                long hvalue_b = h[start + len_b] - h[start] * ppow[len_b];
                while ((pos < n) && (used[pos] != len_a)) {
                    used[pos] = len_a;
                    if (pos + len_a <= n) {
                        long hvalue_cur_a = h[pos + len_a] - h[pos] * ppow[len_a];
                        if ((hvalue_cur_a - hvalue_a) % M == 0) {
                            pos += len_a;
                            continue;
                        }
                    }
                    if (pos + len_b <= n) {
                        long hvalue_cur_b = h[pos + len_b] - h[pos] * ppow[len_b];
                        if ((hvalue_cur_b - hvalue_b) % M == 0) {
                            pos += len_b;
                            continue;
                        }
                    }
                    break;
                }
                if (pos == n) {
                    out.println(2);
                    print(0, len_a, s);
                    print(start, len_b, s);
                    return;
                }
            }
        }
        out.print("3\na\nb\nc\n");
    }
}
