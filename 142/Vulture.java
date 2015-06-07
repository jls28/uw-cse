/* Stefan Dierauf Dec 2012
vulture class that extends bird class
Same as bird but only eats if hungry
also black
*/

import java.awt.*;

public class Vulture extends Bird {
	
	private boolean hungry;
	
	//starts off hungry
	public Vulture() {
		hungry = true;
	}
	
	//only eats if hungry 
	public boolean eat() {
		if (hungry) {
			hungry = !hungry;
			return true;
		} else {
			return false;
		}
		
	}
	
	//when it fights, it becomes hungry again
	public Attack fight(String opponent) {
		hungry = true;
		return super.fight(opponent);
	}
	
	//Vulture is black
	public Color getColor() {
		return Color.BLACK;
	}
}