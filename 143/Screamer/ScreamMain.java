import java.applet.Applet;
import java.applet.AudioClip;
import java.io.*;
import java.net.URL;

import javax.sound.*;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;

import sun.applet.Main;


public class ScreamMain {

	public static void main(String[] args) throws FileNotFoundException {
		
		String sound = "scream.wav";
		//playAudioClip(sound, true);
		playSound(sound);
		System.out.println("played fag");
		
	}
	
	public static synchronized void playSound(final String url) {
		  new Thread(new Runnable() {
		  // The wrapper thread is unnecessary, unless it blocks on the
		  // Clip finishing; see comments.
		    public void run() {
		      try {
		        Clip clip = AudioSystem.getClip();
		        AudioInputStream inputStream = AudioSystem.getAudioInputStream(
		          Main.class.getResourceAsStream("/path/to/sounds/" + url));
		        clip.open(inputStream);
		        clip.start(); 
		      } catch (Exception e) {
		        System.err.println(e.getMessage());
		      }
		    }
		  }).start();
		}
	
//	private static AudioClip playAudioClip(String filename, boolean loop) {
//		URL url = ClassLoader.getSystemResource(filename);
//		AudioClip clip = null;
//		try {
//			clip = Applet.newAudioClip(url);
//			if (loop) {
//				clip.loop();
//			} else {
//				clip.play();
//			}
//		} catch (NullPointerException e) {
//			//if (CONSOLE_OUTPUT) {
//				System.out.println("Error: Unable to load audio clip");
//			//}
//		}
//
//		return clip;
//	}
	
}
