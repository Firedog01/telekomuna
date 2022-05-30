import java.io.File;
import java.util.Scanner;


public class TUI {

    //Java console color constants
    public static final String TEXT_GREEN = "\u001B[32m";
    public static final String TEXT_BLUE = "\u001B[34m";
    public static final String TEXT_RESET = "\u001B[0m";
    public static final String TEXT_YELLOW = "\u001B[33m";
    public static final String TEXT_RED = "\u001B[31m";
    public static final String TEXT_PURPLE = "\u001B[35m";

    private static File [] audioFiles;
    private static final Scanner in = new Scanner(System.in);
    public static String input;

    public static void launch() {
        System.out.println(TEXT_PURPLE + titleAscii + TEXT_RESET + "Type ? for help.");
        try {
            while (true) {
                System.out.print(TEXT_RESET + "> " + TEXT_BLUE);
                input = in.nextLine();
                switch (input) {
                    case "p" -> play();
                    case "r" -> record();
                    case "q" -> {bye(); System.exit(0);}
                    case "?" -> System.out.println("\nCommands:\n\tp - Play audio file from list\n\tr - Record new audio file\n\tq - Quit program or submenu\n\t? - Get help");
                    default -> System.out.println(TEXT_RED + "Invalid command!" + TEXT_BLUE);
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
            System.out.print("Play" + TEXT_RESET +" > " + TEXT_YELLOW);
            input = in.nextLine();
            if(input.equals("?"))
                System.out.println("\nCommands:\n\tq - Quit submenu\n\t? - Get help");
            else if(!input.equals("q")) {
                try {
                    int id = Integer.parseInt(input);
                    Player.select(audioFiles[id - 1]);
                    Player.play();
                } catch (Exception e) {
                    System.out.println(TEXT_RED + "Invalid audio file!" + TEXT_YELLOW);
                }
            }
        } while (!input.equals("q"));
    }

    private static void record() {
        do {
            System.out.println(TEXT_GREEN + recordAscii + "\nType r to start recording\n---------------------------------------------------");
            System.out.print("Record" + TEXT_RESET + " > " + TEXT_GREEN);
            input = in.nextLine();
            switch (input) {
                case "r":
                    try {
                        System.out.print("File name: ");
                        input = in.nextLine();
                        Recorder.start(input);
                    } catch (Exception e) {
                        System.out.println("Exception occured!");
                    }
                    break;
                case "?":
                    System.out.println("\nCommands:\n\tr - Record new audio file\n\tq - Quit submenu\n\t? - Get help");
                    break;
                case "q":
                    break;
                default:
                    System.out.println(TEXT_RED + "Invalid command!" + TEXT_BLUE);
                    break;
            }

        } while (!input.equals("q"));
    }

    private static void getFiles() {
        File dir = new File("../sound_files");
        audioFiles = dir.listFiles();
    }

    private static void listFileNames() {
        int id = 1;
        System.out.println(TEXT_YELLOW + playAscii);
        for (File f : audioFiles) {
            System.out.println(id + ". " + f.getName());
            id++;
        }
        System.out.println("------------------------------");
    }

    private static void bye() {
        System.out.println(TEXT_PURPLE + byeAscii);
    }

    // Ascii art strings

    private static final String titleAscii = """
             _______  __                                                __                                                         __\s
            |       \\|  \\                                              |  \\                                                       |  \\
            | ▓▓▓▓▓▓▓\\ ▓▓ ______  __    __       ______  _______   ____| ▓▓      ______   ______   _______  ______   ______   ____| ▓▓
            | ▓▓__| ▓▓ ▓▓|      \\|  \\  |  \\     |      \\|       \\ /      ▓▓     /      \\ /      \\ /       \\/      \\ /      \\ /      ▓▓
            | ▓▓    ▓▓ ▓▓ \\▓▓▓▓▓▓\\ ▓▓  | ▓▓      \\▓▓▓▓▓▓\\ ▓▓▓▓▓▓▓\\  ▓▓▓▓▓▓▓    |  ▓▓▓▓▓▓\\  ▓▓▓▓▓▓\\  ▓▓▓▓▓▓▓  ▓▓▓▓▓▓\\  ▓▓▓▓▓▓\\  ▓▓▓▓▓▓▓
            | ▓▓▓▓▓▓▓\\ ▓▓/      ▓▓ ▓▓  | ▓▓     /      ▓▓ ▓▓  | ▓▓ ▓▓  | ▓▓    | ▓▓  | ▓▓ ▓▓    ▓▓ ▓▓     | ▓▓  | ▓▓ ▓▓   \\▓▓ ▓▓  | ▓▓
            | ▓▓  | ▓▓ ▓▓  ▓▓▓▓▓▓▓ ▓▓__/ ▓▓    |  ▓▓▓▓▓▓▓ ▓▓  | ▓▓ ▓▓__| ▓▓    | ▓▓__/ ▓▓ ▓▓▓▓▓▓▓▓ ▓▓_____| ▓▓__/ ▓▓ ▓▓     | ▓▓__| ▓▓
            | ▓▓  | ▓▓ ▓▓\\▓▓    ▓▓\\▓▓    ▓▓     \\▓▓    ▓▓ ▓▓  | ▓▓\\▓▓    ▓▓    | ▓▓    ▓▓\\▓▓     \\\\▓▓     \\\\▓▓    ▓▓ ▓▓      \\▓▓    ▓▓
             \\▓▓   \\▓▓\\▓▓ \\▓▓▓▓▓▓▓_\\▓▓▓▓▓▓▓      \\▓▓▓▓▓▓▓\\▓▓   \\▓▓ \\▓▓▓▓▓▓▓    | ▓▓▓▓▓▓▓  \\▓▓▓▓▓▓▓ \\▓▓▓▓▓▓▓ \\▓▓▓▓▓▓ \\▓▓       \\▓▓▓▓▓▓▓
                                 |  \\__| ▓▓                                    | ▓▓                                                  \s
                                  \\▓▓    ▓▓                                    | ▓▓                                                  \s
                                   \\▓▓▓▓▓▓                                      \\▓▓                                                  \s
            """;

    private static final String playAscii = """
             _______  __                  \s
            |       \\|  \\                 \s
            | ▓▓▓▓▓▓▓\\ ▓▓ ______  __    __\s
            | ▓▓__/ ▓▓ ▓▓|      \\|  \\  |  \\
            | ▓▓    ▓▓ ▓▓ \\▓▓▓▓▓▓\\ ▓▓  | ▓▓
            | ▓▓▓▓▓▓▓| ▓▓/      ▓▓ ▓▓  | ▓▓
            | ▓▓     | ▓▓  ▓▓▓▓▓▓▓ ▓▓__/ ▓▓
            | ▓▓     | ▓▓\\▓▓    ▓▓\\▓▓    ▓▓
             \\▓▓      \\▓▓ \\▓▓▓▓▓▓▓_\\▓▓▓▓▓▓▓
                                 |  \\__| ▓▓
                                  \\▓▓    ▓▓
                                   \\▓▓▓▓▓▓
            """;

    private static final String recordAscii = """
             _______                                            __\s
            |       \\                                          |  \\
            | ▓▓▓▓▓▓▓\\ ______   _______  ______   ______   ____| ▓▓
            | ▓▓__| ▓▓/      \\ /       \\/      \\ /      \\ /      ▓▓
            | ▓▓    ▓▓  ▓▓▓▓▓▓\\  ▓▓▓▓▓▓▓  ▓▓▓▓▓▓\\  ▓▓▓▓▓▓\\  ▓▓▓▓▓▓▓
            | ▓▓▓▓▓▓▓\\ ▓▓    ▓▓ ▓▓     | ▓▓  | ▓▓ ▓▓   \\▓▓ ▓▓  | ▓▓
            | ▓▓  | ▓▓ ▓▓▓▓▓▓▓▓ ▓▓_____| ▓▓__/ ▓▓ ▓▓     | ▓▓__| ▓▓
            | ▓▓  | ▓▓\\▓▓     \\\\▓▓     \\\\▓▓    ▓▓ ▓▓      \\▓▓    ▓▓
             \\▓▓   \\▓▓ \\▓▓▓▓▓▓▓ \\▓▓▓▓▓▓▓ \\▓▓▓▓▓▓ \\▓▓       \\▓▓▓▓▓▓▓
            """;

    private static final  String byeAscii = """
             __                              __\s
            |  \\                            |  \\
            | ▓▓____  __    __  ______      | ▓▓
            | ▓▓    \\|  \\  |  \\/      \\     | ▓▓
            | ▓▓▓▓▓▓▓\\ ▓▓  | ▓▓  ▓▓▓▓▓▓\\    | ▓▓
            | ▓▓  | ▓▓ ▓▓  | ▓▓ ▓▓    ▓▓     \\▓▓
            | ▓▓__/ ▓▓ ▓▓__/ ▓▓ ▓▓▓▓▓▓▓▓     __\s
            | ▓▓    ▓▓\\▓▓    ▓▓\\▓▓     \\    |  \\
             \\▓▓▓▓▓▓▓ _\\▓▓▓▓▓▓▓ \\▓▓▓▓▓▓▓     \\▓▓
                     |  \\__| ▓▓                \s
                      \\▓▓    ▓▓                \s
                       \\▓▓▓▓▓▓
                        """;
}
