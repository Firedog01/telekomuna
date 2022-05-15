import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader bfn = new BufferedReader(new InputStreamReader(System.in));
        String ipLoopback = "127.1.1.1";
        System.out.print("Choose port: ");
        String port = bfn.readLine();
        int intPort = Integer.parseInt(port);

        System.out.print("Sender or receiver? [s/r]: ");
        String input = bfn.readLine();
        if(input.equals("s") || input.equals("S")) {
            // sender
            Sender s = new Sender();
            s.startConnection(ipLoopback, intPort);
            input = bfn.readLine();
            while(!input.equals("")) {
                String res = s.sendMessage(input);
                System.out.println(res);
                input = bfn.readLine();
            }
        } else if(input.equals("r") || input.equals("R")) {
            // reciever
            Receiver r = new Receiver();
            r.start(intPort);
        } else {
            System.out.println("Incorrect option");
        }
    }
}
