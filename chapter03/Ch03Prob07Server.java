import java.net.*;
import java.io.*;
import java.util.Random;


public class Ch03Prob07Server
{
    public static void main(String[] args) {
        try {
            String[] Haiku = {
                "An old silent pond\nA frog jumps into the pond—\nSplash! Silence again.",
                "A world of dew,\nAnd within every dewdrop\nA world of struggle.",
                "The light of a candle\nIs transferred to another candle—\nSpring twilight",
                "I write, erase, rewrite\nErase again, and then\nA poppy blooms."
            };

            ServerSocket sock = new ServerSocket(5575);
            
            while (true) {
                Socket client = sock.accept();
                Random randNum = new Random();
                String TodayQuote = Haiku[randNum.nextInt(Haiku.length)];

                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
                pout.println(TodayQuote);

                client.close();
            }
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}

