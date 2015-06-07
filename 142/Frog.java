import java.awt.*;

public class Frog extends Critter {
	
	private int age;
	private int steps;

	public Frog(int age) {
		this.age = age;
	}
	
	public Color getColor() {
		return Color.GREEN;
	}
	
	public Direction getMove() {
		steps++;
		if (steps % age == 0) {
			return Direction.EAST;
		} else {
			return Direction.CENTER;
		}
			
	}

	public String toString() {
		return "F";
	}

}