public class BinaryTree {

    private int value; //przechowywana wartość
    private Character character = null; //przechowywany znak
    public BinaryTree left = null; //lewe dziecko danego liścia
    public BinaryTree right = null; //prawe dziecko danego liścia
    public BinaryTree(char letter, int val) { //tworzymy konstruktor liścia dla znaków
        value = val;
        character = letter;
    }
    public BinaryTree(int val) { //tworzymy konstruktor dla liści będących sumą dzieci
        value = val;
    }
    public int getValue() { //funkcja zwracająca wartość liścia
        return value;
    }
    public Character getCharacter() {//funkcja zwracająca znak liścia
        return character;
    }
    public boolean isLeaf() { //funkcja zwracająca, czy liść nie jest kontenerem 
        return character != null;
    }

}
