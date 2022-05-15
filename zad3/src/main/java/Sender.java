import java.io.*;
import java.net.*;

public class Sender {
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public void startConnection(String ip, int port) throws IOException {
        clientSocket = new Socket(ip, port);
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    }

    public String sendMessage(String msg) throws IOException {
        Huffman h = new Huffman(msg);
        FileWriter dictWriter = new FileWriter("dictionary.txt");
        dictWriter.write(h.dictionaryToString());
        dictWriter.close();
        out.println(h.getEncoded());
        String resp = in.readLine();
        return resp;
    }

    public void stopConnection() throws IOException {
        in.close();
        out.close();
        clientSocket.close();
    }
}
