import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;

public class Recorder {

    // record duration, in milliseconds
    static final long recordTime = 10000;	// 10 sec

    // format of audio file
    static AudioFileFormat.Type fileType = AudioFileFormat.Type.WAVE;

    // the line from which audio data is captured
    static TargetDataLine line;

    /**
     * Defines an audio format
     */
    private static AudioFormat getAudioFormat() {
        float sampleRate = 16000;
        int sampleSizeInBits = 8;
        int channels = 2;
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
            // checks if system supports the data line
            if (!AudioSystem.isLineSupported(info)) {
                System.out.println("Line not supported");
                System.exit(0);
            }
            line = (TargetDataLine) AudioSystem.getLine(info);
            line.open(format);
            line.start();	// start capturing

            System.out.println("Start capturing...");

            AudioInputStream ais = new AudioInputStream(line);

            System.out.println("Start recording...\n");

            Thread stopper = new Thread(() -> {
                try {
                    Thread.sleep(recordTime);
                } catch (InterruptedException ex) {
                    ex.printStackTrace();
                }
                Recorder.finish();
            });

            // start recording
            stopper.start();
            AudioSystem.write(ais, fileType, wavFile);

        } catch (LineUnavailableException | IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Closes the target data line to finish capturing and recording
     */
    private static void finish() {
        line.stop();
        line.close();
    }

}
