/* Stefan Dierauf Dec 2012
Bird class that extends critter 
flies around in a square
is blue
looks like a v in the direction it's flying */

import java.awt.*;

public class Bird extends Critter {

	private int steps;
	private String bird;
	
	//starts off pointing up
	public Bird() {
		steps = 0;
		bird = "^";
	}
	
	//blue in color
	public Color getColor() {
		return Color.BLUE;
	}
	
	//Always kills ants, otherwise pounces
	public Attack fight(String opponent) {
		if (opponent.equals("%")) {
			return Attack.ROAR;
		} else {
			return Attack.POUNCE;
		}
	}
	
	//moves around perimeter of 3x3 sqaure
	//method also sets char of bird
	public Direction getMove() {
		steps++;
		int simpleSteps = steps / 4;
		if (simpleSteps % 4 == 1) {
			this.bird = "^";
			return Direction.NORTH;
		} else if (simpleSteps % 4 == 2) {
			this.bird = ">";
			return Direction.EAST;
		} else if (simpleSteps % 4 == 3) {
			this.bird = "V";
			return Direction.SOUTH;
		} 	else {
			this.bird = "<";
			return Direction.WEST;
		}
	}
	
	//returns the char the bird is set to. 
	public String toString() {
		return bird;
	}

}
