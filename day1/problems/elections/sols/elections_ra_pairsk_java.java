import java.io.*;
import java.util.*;
public class elections_ra_pairsk_java {
  int maxn = 50000;
  int[][] g = new int[maxn][];
  long[] dp1 = new long[maxn];
  long[] dp2 = new long[maxn];
  long[] one = new long[maxn];
  long[] xx = new long[maxn];
  int[] szv = new int[maxn];
  class Point {
    long x;
    int y;
    Point() {
    }
    Point(long _x, int _y) {
      x = _x;
      y = _y;
    }
  }
  ArrayList<Point> f = new ArrayList<Point>();

  void factorize(long n) {
    for (long i = 2; i * i <= n; i++) {
      int cnt = 0;
      while (n % i == 0) {
        n /= i;
        cnt++;
      }
      if (cnt > 0) {
        f.add(new Point(i, cnt));
      }
    }
    if (n > 1) {
      f.add(new Point(n, 1));
    }
  }

  void reserve(int stp1, int rs, long x, int i) {
    if (i == f.size()) {
      g[stp1] = new int[(rs + 1) / 2]; 
      xx[stp1] = x;
      dp1[stp1] = one[stp1] = (x + 1) / 2;
      return;
    }
    int S = f.get(i).y;  
    stp1 *= (S + 1);  
    for (int v1 = 0; v1 <= S; v1++, x *= f.get(i).x) {    
      reserve(stp1 + v1, rs * (v1 + 1), x, i + 1);
    }
  }

  void construct_edges(int stp1, int stp2, int i) {
    if (i == f.size()) {
      if (xx[stp1] <= xx[stp2 - stp1]) {
        g[stp2][szv[stp2]++] = stp1;
      }
      return;
    }
    int S = f.get(i).y;
    stp1 *= (S + 1);
    stp2 *= (S + 1);  
    for (int v1 = 0; v1 <= S; v1++) {
      for (int v2 = v1; v2 <= S; v2++) {
        construct_edges(stp1 + v1, stp2 + v2, i + 1);
      }
    }
  }

  public static void main(String[] args) throws IOException {
    new elections_ra_pairsk_java().run();
  }

  public void run() throws IOException {
    Scanner sc = new Scanner(System.in);
    PrintWriter pw = new PrintWriter(System.out);
    long n = sc.nextLong();
    int k = sc.nextInt();
    long inf = n + 1;
    factorize(n);    
    reserve(0, 1, 1, 0);
    construct_edges(0, 0, 0);
    int v1 = 0;
    for (Point p : f) {
      v1 = v1 * (p.y + 1) + p.y;
    }
    for (int i = 0; i < k - 1; i++) {
      long val;    
      for (int j = 0; j <= v1; j++) {
        dp2[j] = inf;
        for (int it : g[j]) {
          if (dp2[j] > (val = one[it] * dp1[j - it])) {
            dp2[j] = val;
          }
        }
      }
      long[] temp = dp1;
      dp1 = dp2;
      dp2 = temp;
    }
    pw.println(dp1[v1]);
    sc.close();
    pw.close();
  }
}
