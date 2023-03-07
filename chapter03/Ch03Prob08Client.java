import java.net.*;
import java.io.*;

public class Ch03Prob08Client
{
    public static void main(String[] args) {
        try {
            Socket sock = new Socket("127.0.0.1", 6013);

            String line;

            PrintWriter pout = new PrintWriter(sock.getOutputStream(), true);
            pout.println("Hello World!");
            // pout.flush();
            
            InputStream in = sock.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));

            while ((line = bin.readLine()) != null) {
                System.out.println(line);
            }

            sock.close();
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}

