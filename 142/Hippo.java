/* Stefan Dierauf Dec 2012
Hippo class that extends Critter class
moves in a random direction every 5 steps
eats until not hungry (amount of hunger determined on create)
*/

import java.awt.*;
import java.util.*;

public class Hippo extends Critter {
	
	private int hunger;
	private Direction dir;
	private Random generator;
	private int steps;
	private int rand;
	
	//starts off having a random amount of food it will eat before not being hungry
	public Hippo(int hunger) {
		this.hunger = hunger;
		generator = new Random();
		steps = 0;
		dir = getDir();
	}
	
	//gets a random direction
	public Direction getDir() {
		rand = generator.nextInt(4);
		if (rand == 0) {
			return Direction.NORTH;
		} else if (rand == 1) {
			return Direction.SOUTH;
		} else if (rand == 2) {
			return Direction.WEST;
		} else {
			return Direction.EAST;
		}
	}
	
	//Scratches if it is still hungry, otherwise pounces.
	public Attack fight(String opponent) {
		if (hunger > 0) {
			return Attack.SCRATCH;
		} else {
			return Attack.POUNCE;
		}
	}
	
	//eats if it is still hungry
	public boolean eat() {
		if (hunger > 0) {
			hunger--;
		}
		return (hunger > 0);
	}
	
	//moves in a random direction every five steps
	public Direction getMove() {
		if (steps % 5 == 0) {
			dir = getDir();
		}
		steps++;
		return dir;
	}
	
	//if its still hungry, Gray, otherwise it will be white. 
	public Color getColor() {
		if (hunger > 0) {
			return Color.GRAY;
		} else {
			return Color.WHITE;
		}
	}
	
	//appears as the number of hunger it is at. 
	public String toString() {
		return "" + hunger;
	}


}