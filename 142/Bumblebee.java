public class Bumblebee extends Critter {
	private int count;
	private int timer;
	public Direction getMove() {
		timer++;
		if(timer>count) {
			timer = 1;
			count++;
		}
		if (count%4 == 1) {
			return Direction.WEST;
		} else if (count % 4 == 2) {
			return Direction.SOUTH;
		} else if (count %4  == 3) {
			return Direction.EAST;
		} else {
			return Direction.NORTH;
		}
	}	
}
		
	