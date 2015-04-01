import java.io.*;
import java.util.Locale;
import java.util.StringTokenizer;

public class torus_ma_maxs2 {
    private final InputReader reader;
    private final OutputWriter writer;

    public torus_ma_maxs2(InputReader reader, OutputWriter writer) {
        this.reader = reader;
        this.writer = writer;
    }

    public static void main(String[] args) {
        InputReader reader = new InputReader(System.in);
        OutputWriter writer = new OutputWriter(System.out);
        new torus_ma_maxs2(reader, writer).run();
        writer.writer.flush();
    }

    boolean go(char dir) {
        writer.printf("%c\n", dir);
        writer.writer.flush();
        String s = reader.next();
        return (s.equals("Y") || s.equals("E"));
    }

    public void run() {
        final int N = 300;
        for (int i = 0; i < N; i += 2) {
            for (int j = 0; j < N - 1; j++)
                if (go('R'))
                    return;
            if (go('D'))
                return;
            for (int j = 0; j < N - 1; j++)
                if (go('L'))
                    return;
            if (go('D'))
                return;
        }
        throw new AssertionError();
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

