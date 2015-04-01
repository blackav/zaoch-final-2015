import java.io.*;
import java.util.Locale;
import java.util.StringTokenizer;

public class torus_ma_ssqrts {
    private final InputReader reader;
    private final OutputWriter writer;

    public torus_ma_ssqrts(InputReader reader, OutputWriter writer) {
        this.reader = reader;
        this.writer = writer;
    }

    public static void main(String[] args) {
        InputReader reader = new InputReader(System.in);
        OutputWriter writer = new OutputWriter(System.out);
        new torus_ma_ssqrts(reader, writer).run();
        writer.writer.flush();
    }

    boolean go(char dir) {
        writer.printf("%c\n", dir);
        writer.writer.flush();
        String s = reader.next();
        return (s.equals("Y") || s.equals("E"));
    }

    public void run() {
        for (int i = 1; ; i++) {
            int a = 1 << i;
            int b = a * a;
            for (int j = 0; j < a / 2; j++)
            {
                for (int t = 0; t < b - 1; t++)
                    if (go('U'))
                        return;
                if (go('R'))
                    return;
                for (int t = 0; t < b - 1; t++)
                    if (go('D'))
                        return;
                if (go('R'))
                    return;
            }
            for (int j = 0; j < (b - a) / 2; j++)
            {
                for (int t = 0; t < a - 1; t++)
                    if (go('U'))
                        return;
                if (go('R'))
                    return;
                for (int t = 0; t < a - 1; t++)
                    if (go('D'))
                        return;
                if (go('R'))
                    return;
            }
        }
    }


    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }

    static class OutputWriter {
        public PrintWriter writer;

        OutputWriter(OutputStream stream) {
            writer = new PrintWriter(stream);
        }

        public void printf(String format, Object... args) {
            writer.print(String.format(Locale.ENGLISH, format, args));
        }
    }
}

