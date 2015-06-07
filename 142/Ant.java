/* Stefan Dierauf Dec 2012
creats an ant critter that moves diagonally north east or south east,
depending on boolean passed in
always Scratches
*/

import java.awt.*;

public class Ant extends Critter {
	
	private boolean walkSouth;
	private int steps;
	
	//constructor that initiallizes walksouth
	public Ant(boolean walkSouth) {
		this.walkSouth = walkSouth;
	}
	
	//depending on walkSouth, either moves NE or SE
	public Direction getMove() {
		steps++;
		if (steps % 2 == 1) {
			if (walkSouth) {
				return Direction.SOUTH;
			} else {
				return Direction.NORTH;
			}
		} else {
			return Direction.EAST;
		}
	}
	
	//always eats
	public boolean eat() {
		return true;
	}
	
	//always scratches
	public Attack fight(String opponent){
		return Attack.SCRATCH;
	}
	
	//always red
	public Color getColor() {
		return Color.RED;
	}
	
	//represented by %
	public String toString() {
		return "%";
	}
}