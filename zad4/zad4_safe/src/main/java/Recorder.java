import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class Recorder {

    // Format of audio file
    static AudioFileFormat.Type fileType = AudioFileFormat.Type.WAVE;

    // Line from which audio data is captured
    static TargetDataLine line;

    // Defines an audio format
    private static AudioFormat getAudioFormat() {
        float sampleRate = 44100; // Próbkowanie
        int sampleSizeInBits = 32; // Kwantyzacja
        int channels = 1;
        boolean signed = true;
        boolean bigEndian = true;
        return new AudioFormat(sampleRate, sampleSizeInBits,
                channels, signed, bigEndian);
    }

    public static void start(String fileName) {
        try {
            AudioFormat format = getAudioFormat();
            DataLine.Info info = new DataLine.Info(TargetDataLine.class, format);
            File wavFile = new File("../sound_files/" + fileName + ".wav");
            // Checks if system supports the data line
            if (!AudioSystem.isLineSupported(info)) {
                System.out.println("Line not supported");
                return;
            }

            // Start capturing
            line = (TargetDataLine) AudioSystem.getLine(info);
            line.open(format);
            line.start();
            System.out.println("Start capturing...");

            // Start recording
            AudioInputStream ais = new AudioInputStream(line);
            System.out.println("Start recording...");

            // Pressing enter ends recording
            Thread stopper = new Thread(() -> {
                Scanner in = new Scanner(System.in);
                in.nextLine();
                Recorder.finish();
            });
            stopper.start();
            System.out.print("Press enter to end recording");

            AudioSystem.write(ais, fileType, wavFile);

        } catch (LineUnavailableException | IOException e) {
            e.printStackTrace();
        }
    }

    // Closes the target data line to finish capturing and recording
    private static void finish() {
        line.stop();
        line.close();
    }

}
