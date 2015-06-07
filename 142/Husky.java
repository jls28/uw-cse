import java.awt.*;
import java.util.*;

public class Husky extends Critter {
	//moves to perimeter, then moves around counterclockwise 
	//if detects ant, fight = roar
	//if detects bird, fight = scratches
	//if detects hippo, then roars
	//if detects stone, then pounces
	
	private int myX;
	private int myY;
	private int steps;
	private Random generator;
	private boolean override;
	private boolean packs;
	private Direction dir;
	private int rand;
	private String enemies;
	private String myChar;
	private String msg;
	
	
	
	public Husky() {
		myX = getX();
		myY = getY();
		steps = 0;
		override = true;
		dir = Direction.NORTH;
		generator = new Random();
		enemies = "V><^9876543210S%";
		myChar = "W";
		msg = "Go Huskies ";
	}
	
	public Attack fight(String opponent) {
		if (opponent.equals("%")){
			return Attack.ROAR;
		}
		if ("V><^".contains(opponent)) {
			return Attack.SCRATCH;
		}
		if ("987654321".contains(opponent)) {
			return Attack.ROAR;
		}
		if (opponent.equals("0")) {
			return Attack.SCRATCH;
		}
		if (opponent.equals("S")) {
			return Attack.POUNCE;
		}
		if (!enemies.contains(opponent)){
			return Attack.SCRATCH;
		}
		rand = generator.nextInt(3);
		if (rand == 0) {
			return Attack.SCRATCH;
		} else if (rand == 1) {
			return Attack.POUNCE;
		} else {
			return Attack.ROAR;
		} 
	}
	
	public boolean eat() {
		if (steps % 10 == 0){
			return false;
		}
		return true;
	}
	
	public boolean checkFood() {
		if (getNeighbor(Direction.WEST).equals(".")){
			dir = Direction.WEST;
			return true;
		}
		if (getNeighbor(Direction.EAST).equals(".")){
			dir = Direction.EAST;
			return true;
		}
		if (getNeighbor(Direction.NORTH).equals(".")){
			dir = Direction.NORTH;
			return true;
		}
		if (getNeighbor(Direction.SOUTH).equals(".")){
			dir = Direction.SOUTH;
			return true;
		}
		return false;
	}
	
	public void goHuskies() {
		myChar = msg.charAt(getX() % msg.length()) + " ";
	
	}
	
	public Direction getMove() {
		myX = getX();
		myY = getY();
		steps++;
		
		//if (override) {
		if (steps % 300 < 150) {
			if ((myX == 0 || myX == getWidth()-1) || (myY == 0 || myY == getHeight()-1)) {
				goHuskies();
				if (checkFood()) {
				return dir;
				}
				if (myX == 0 && myY < getHeight() -1 ) {
					return Direction.SOUTH;
				} else if (myY == getHeight()-1 && myX < getWidth()-1) {
					return Direction.EAST;
				} else if (myX == getWidth()-1 && myY > 0) {
					return Direction.NORTH;
				} else if (myX > 0 && myY == 0) {
					return Direction.WEST;
				}
			}
			if (myX < myY) {
				if (myX < getWidth() / 2){
					dir = Direction.WEST;
					return Direction.WEST;
				} else {
					dir = Direction.EAST;
					return Direction.EAST;
				}
			} else {
				if (myY < getHeight()/2) {
					dir = Direction.NORTH;
					return Direction.NORTH;
				} else {
					dir = Direction.SOUTH;
					return Direction.SOUTH;
				}
			}
		} else {
		
		return getRandomDirection();
		}

	}
	
	public Direction getRandomDirection() {
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

	
	public Color getColor() {
		if (getX() % 2 == 0) {
			return Color.MAGENTA;
		} else {
			return Color.YELLOW;
		}
	}
	
	public String toString() {
		return myChar;
	}
	
	
}