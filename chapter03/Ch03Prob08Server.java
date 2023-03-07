import java.net.*;
import java.io.*;


public class Ch03Prob08Server
{
    public static void main(String[] args) {
        try {
            ServerSocket sock = new ServerSocket(6013);

            String line;
            String back_message = "";
            
            
            Socket client = sock.accept();

            InputStream in = client.getInputStream();

            BufferedReader bin = new BufferedReader(new InputStreamReader(in));
            PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

            while ((line = bin.readLine()) != null) {
                System.out.println(line);    
                pout.println(line);
                pout.flush();
            }
            client.close();
            
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}

