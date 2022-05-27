import java.io.File;
import java.util.Scanner;

public class TUI {

    private static File [] audioFiles;
    private static final Scanner in = new Scanner(System.in);
    public static String input;

    public static void launch() {
        System.out.println("---------------\nRlay and Pecord\n---------------\nType ? for help.");
        try {
            while (true) {
                System.out.print("> ");
                input = in.nextLine();
                switch (input) {
                    case "p" -> play();
                    case "r" -> record();
                    case "q" -> System.exit(0);
                    case "?" -> System.out.println("\nCommands:\n\tp - Play audio file from list\n\tr - Record new audio file\n\tq - Quit program or submenu\t? - Get help");
                    default -> System.out.println("\nInvalid command!\n\n");
                }
            }
        } catch (Exception e) {
            System.err.println("Nieobsłużony wyjątek!");
        }
    }

    private static void play() {
        do {
            getFiles();
            listFileNames();
            System.out.print("Play > ");
            input = in.nextLine();
            if(!input.equals("q")) {
                try {
                    int id = Integer.parseInt(input);
                    Player.select(audioFiles[id-1]);
                    Player.play();
                } catch (Exception e) {
                    System.out.println("Invalid audio file!");
                }
            }
        } while (!input.equals("q"));
    }

    private static void record() {
        do {
            System.out.println("Type r to start recording!");
            System.out.print("\nRecord > ");
            input = in.nextLine();
            if(input.equals("r")) {
                try {
                    System.out.print("File name: ");
                    input = in.nextLine();
                    Recorder.start(input);
                } catch (Exception e) {
                    System.out.println("Exception occured!");
                }
            }
        } while (!input.equals("q"));
    }

    private static void getFiles() {
        File dir = new File("../sound_files");
        audioFiles = dir.listFiles();
    }

    private static void listFileNames() {
        int id = 1;
        System.out.println("\n---------------\nAll audio files\n---------------");
        for (File f : audioFiles) {
            System.out.println(id + ". " + f.getName());
            id++;
        }
        System.out.println("---------------");
    }

}
