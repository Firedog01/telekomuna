import java.io.*;
import java.net.*;

public class Receiver {
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public void start(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        clientSocket = serverSocket.accept();
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        while(!clientSocket.isClosed()) {
            String msg = in.readLine();
            Huffman h = new Huffman(msg, "dictionary.txt");
            System.out.println("Received: " + msg);
            System.out.println("Decoded: " + h.message);
            out.println("ACK");
        }
    }

    public void stop() throws IOException {
        in.close();
        out.close();
        clientSocket.close();
        serverSocket.close();
    }
}
