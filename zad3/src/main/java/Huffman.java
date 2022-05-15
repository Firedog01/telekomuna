import java.io.*;
import java.util.*;

public class Huffman {

    HashMap <Character, String> dictionary = new HashMap<>(); // Used during encoding
    HashMap <String, Character> decodeDictionary = new HashMap<>(); // Used during decoding
    String message;

    // Contructor that creates dictionary for given message
    Huffman(String message){
        this.message = message;
        HashMap< Character, Integer > occurences = new HashMap <> (); //tworzymy mapę, która przechowa ilość wystąpień dla każdego znaku
        for (char c: message.toCharArray()) { //następnie zliczamy je w pętli
            if (occurences.containsKey(c)) {
                occurences.put(c, occurences.get(c) + 1);
            } else {
                occurences.put(c, 1);
            }
        }
        BinaryTreeComparator nc = new BinaryTreeComparator(); //tworzymy instancję pomocniczej klasy
        PriorityQueue < BinaryTree > nodes = new PriorityQueue<>(occurences.size(), nc); //korzystamy z PriorityQueue - w uproszczeniu jest to lista, która zadba, aby nasze elementy były zawsze posortowane; korzysta ona z naszego Comparatora
        for (Map.Entry< Character, Integer > entry: occurences.entrySet()) { //zamieniamy znaki i ich ilość wystąpień na liście, a następnie dodajemy je do utworzonej listy
            BinaryTree n = new BinaryTree(entry.getKey(), entry.getValue());
            nodes.add(n);
        }
        BinaryTree rootBinaryTree = null; //zmienna pomocnicza przechowująca korzeń drzewa - finalnie ma być on liściem przechowującym wartość równą długości wpisanego wyrazu
        while (nodes.size() > 1) { //dopóki na liście nie pozostał jeden element(korzeń)

            BinaryTree n1 = nodes.peek(); //pobieramy najmniejszy element z listy
            nodes.poll(); //a następnie go usuwamy
            BinaryTree n2 = nodes.peek(); //ponownie pobieramy najmniejszy element z listy
            nodes.poll(); //i ponownie go usuwamy; w ten sposób pobraliśmy dwa najmniejsze elementy z listy
            BinaryTree parent = new BinaryTree(n1.getValue() + n2.getValue()); //tworzymy liść, który będzie przechowywał powyższe elementy
            if(n1.getValue() == n2.getValue() && !n1.isLeaf()) { //jeżeli oba liście mają tą samą wartość, a jeden z nich jest kontenerem, to powinien on być traktowany jako większy element
                BinaryTree pom = n1; //dlatego w takiej sytuacji podmieniamy wartości
                n1 = n2;
                n2 = pom;
            }
            rootBinaryTree = parent; // ustawiamy go tymczasowo jako korzeń
            parent.left = n1; // mniejszy element ustawamy jako jego lewe dziecko
            parent.right = n2;// większy jako jego prawe dziecko
            nodes.add(parent); //następnie dodajemy rodzica jako samodzielny element do listy
        }
        encodeValues(rootBinaryTree, "");
    }

    Huffman(String encodedMessage, String path) throws IOException {
        File dictFile = new File(path);
        BufferedReader dictReader = new BufferedReader(new FileReader(dictFile));
        String str;
        while ((str = dictReader.readLine()) != null) {
            decodeDictionary.put(str.substring(2), str.toCharArray()[0]);
        }

        // Decoding here
        String buf = "";
        StringBuilder msg = new StringBuilder();
        for(char c : encodedMessage.toCharArray()) {
            buf += c;
            //System.out.println(buf);
            if(decodeDictionary.containsKey(buf)) {
                msg.append(decodeDictionary.get(buf));
                buf = "";
            }
        }
        message = msg.toString();
    }

    private void encodeValues(BinaryTree node, String txt) { //tworzymy rekurencyjną funkcję, która nada liścią odpowiednie wartości
        if (node == null) {
            return;
        }
        if (node.getCharacter() != null) { //jeżeli liść posiada swój znak
            dictionary.put(node.getCharacter(), txt); //dodajemy jego zakodowaną wartość do tablicy
        }
        encodeValues(node.left, txt + "0"); //wywołujemy funkcję rekurencyjnie
        encodeValues(node.right,txt + "1"); //dla obu dzieci; w ten sposób całemu drzewu zostanie przypisana wartość
    }

    public String getCode(Character c) {
        return dictionary.get(c);
    }

    public String getEncoded() {
        StringBuilder ret = new StringBuilder();
        for(char c : message.toCharArray()) {
            ret.append(dictionary.get(c));
        }
        return ret.toString();
    }

    public String dictionaryToString() {
        StringBuilder ret = new StringBuilder();
        for(Character code : dictionary.keySet()) {
            ret.append(code)
                    .append(" ")
                    .append(dictionary.get(code))
                    .append('\n');
        }
        return ret.toString();
    }

}
