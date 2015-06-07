/* Stefan Dierauf Jan 2013
 * TA: Molly Yoder (she lifts)
 * 
 * TileManager class for Tiles homework
 * this class manages a set of tiles drawn on a drawing panel
 * tile at index 0 is at the lowest position
 */

import java.awt.Graphics;
import java.util.*;

public class TileManager {
	
	private ArrayList<Tile> data;
	private Random rand;
	
	//creates ArrayList to store data
	public TileManager() {
		data = new ArrayList<Tile>();
		rand = new Random();
	}

	//adds a tile to the panel
	public void addTile(Tile tile) {
		data.add(tile);
	}

	//redraws all tiles
	public void drawAll(Graphics g) {
		for (int i = 0; i < data.size(); i++) {
			data.get(i).draw(g);
		}	
	}
	
	//returns whether x,y is contained in the tile
	private boolean contains(int index, int x, int y) {
		Tile t = data.get(index);
		return (x >= t.getX() && x <= t.getX() + t.getWidth() 
				&& y >= t.getY() && y <= t.getY() + t.getHeight());
	}

	//deletes all tiles containing x,y
	public void deleteAll(int x, int y) {
		for (int i = 0; i < data.size(); i++) {
			if (contains(i , x, y)) {
				data.remove(i);
			}
		}
	}
	
	//gets the "highest" tile that contains x,y and returns it's index if it exists
	private int topTile(int x, int y) {
		for (int i = data.size() - 1; i > -1; i--) {
			if (contains(i, x, y)) {
				return i;
			}
		}
		return -1;
	}
	
	//gets the "lowest" tile that contains x,y and returns it's index if it exists
	private int bottomTile(int x, int y) {
		for (int i = 0; i < data.size(); i++) {
			if (contains(i, x, y)) {
				return i;
			}
		}
		return -1;
	}

	//deletes highest tile that contains x,y if it exists
	public void delete(int x, int y) {
		if (topTile(x, y) != -1) {
			data.remove(topTile(x, y));
		}
	}
	
	//lowers highest tile containing x,y to lowest position if it exists
	public void lower(int x, int y) {
		if (topTile(x, y) != -1) {
			Tile t = data.get(topTile(x, y));
			data.remove(topTile(x, y));
			data.add(0, t);		
		}	
	}

	//raises lowest tile containing x,y to highest position
	public void raise(int x, int y) {
		int index = bottomTile(x,y);
		if (index != -1) {
			Tile t = data.get(index);
			data.remove(index);
			data.add(data.size(), t);
		}
	}

	//shuffles all tiles' position and order
	public void shuffle(int width, int height) {
		Collections.shuffle(data); 
		for (int i = 0; i < data.size(); i++) {
			data.get(i).setX(rand.nextInt(width -  data.get(i).getWidth()));
			data.get(i).setY(rand.nextInt(height - data.get(i).getHeight()));
		}	
	}
}
