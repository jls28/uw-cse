import java.util.*;

public class Cheetah extends Critter {
	private int neededFood;
	private boolean east;
	private int foodCounter;
	
	public Cheetah(int food) {
		neededFood = food;
		east = food % 2 == 0;
	}
	
	public boolean eat() {
		foodCounter++;
		east = !east;
		return true;
	}
	
	public Attack fight(String opponent) {
		if (foodCounter >= neededFood) {
			foodCounter = 0;
			return Attack.POUNCE;
		} else {
			return Attack.FORFEIT;
		}
	}
	
	public Direction getMove() {
		if(east) {
			return Direction.EAST;
		} else {
			return Direction.SOUTH;
		}
	}
}