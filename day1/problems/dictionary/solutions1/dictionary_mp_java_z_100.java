import java.io.*;

public class dictionary_mp_java_z_100 {
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        new dictionary_mp_java_z_100().run();
        out.close();
    }

    int min(int a, int b) {
        return a < b ? a : b;
    }
    int max(int a, int b) {
        return a > b ? a : b;
    }

    void calc_z(int n, char s[], int z[]) {
        z[0] = 0;
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            int zvalue = min(z[i - l], max(0, r - i + 1));
            while (s[zvalue] == s[i + zvalue]) {
                zvalue++;
                l = i;
                r = i + zvalue - 1;
            }
            z[i] = zvalue;
        }
    }

    void print(int start, int n, char s[]) {
        for (int i = 0; i < n; ++i)
            out.print(s[start + i]);
        out.println();
    }

    public void run() throws IOException {
        int l = Integer.parseInt(rd.readLine());
        String tmp = rd.readLine();
        int n = tmp.length(), z_a[] = new int[n + 1], z_b[] = new int[n + 1], used[] = new int[n + 1], it = 0;
        int nz[] = new int[n + 1];
        char s[] = new char[n + 1];
        char ns[] = new char[n + 1];
        System.arraycopy(tmp.toCharArray(), 0, s, 0, n);
        boolean bad[] = new boolean[n + 1];
        calc_z(n, s, z_a);
        z_a[0] = l;
        for (int len_a = 1; len_a <= l; ++len_a) {
            if (bad[len_a]) continue;
            int start = len_a;
            while (z_a[start] >= len_a) {
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
            int start = 0;
            while (z_a[start] >= len_a)
                start += len_a;
            System.arraycopy(s, start, ns, 0, n - start);
            calc_z(n - start, ns, z_b);
            z_b[0] = l;
            ++it;
            for (int len_b = 1; len_b <= l; ++len_b) {
                int pos = start + len_b;
                while ((pos < n) && (used[pos] != it)) {
                    used[pos] = it;
                    if (z_a[pos] >= len_a)
                        pos += len_a;
                    else if (z_b[pos - start] >= len_b)
                        pos += len_b;
                    else
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
