import java.awt.*;

public class Rabbit extends Critter {
	
	private int steps;
	private boolean hungry;
	
	public Rabbit(){
		steps = 0;
		hungry = true;
	}

	public Color getColor(){
		return Color.DARK_GRAY;
	}
	
	public Direction getMove() {
		steps++;
		if (steps % 6 == 1 || steps % 6 == 2) {
			return Direction.NORTH;
		} else if (steps % 6 == 3 || steps % 6 == 4) {
			return Direction.SOUTH;
		} else {
			return Direction.EAST;
		}
	}
	
	public Attack fight(String opponent){
		if ("V<>^".contains(opponent)) {
			return Attack.SCRATCH;
		} else {
			return Attack.ROAR;
		}
	}
	
	public boolean eat() {
		if (hungry) {
			hungry = !hungry; //oh my
		}
		return !hungry;
	}
	
	public String toString() {
		return "v";
	}

}