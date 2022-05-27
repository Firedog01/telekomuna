package tele;

import java.io.File;
import javax.sound.sampled.*;

public class Main implements LineListener {

    boolean completed;

    @Override
    public void update(LineEvent event) {
        LineEvent.Type type = event.getType();

        if (type == LineEvent.Type.START) {
            System.out.println("Playback started.");

        } else if (type == LineEvent.Type.STOP) {
            completed = true;
            System.out.println("Playback completed.");
        }
    }

    public void play() {
        try {
            File file = new File("sound_files/ncs.wav");
            AudioInputStream stream = AudioSystem.getAudioInputStream(file);
            Clip clip = AudioSystem.getClip();
            clip.addLineListener(this);
            clip.open(stream);
            clip.start();
            completed = false;

            while (!completed) {
                Thread.sleep(1000);
//                System.out.println(clip.getFramePosition());
//                System.out.println(clip.getFrameLength());
            }

            stream.close();

        } catch (Exception ex) {
            System.out.println(ex.getMessage());
        }
    }

    public static void main(String[] args) {
        Main m = new Main();
        m.play();
    }

}
