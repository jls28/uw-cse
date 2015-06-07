/* Stefan Dierauf Jan 2013
 * TA: Molly Yoder
 * Manages a collection of "Assassins" who are playing Assassin
 */

import java.util.*;

public class AssassinManager {
	private AssassinNode front;
	private AssassinNode graveyard;
	
	//constructs the AssassinManager
	public AssassinManager(ArrayList<String> names) {
		if (names == null || names.size() == 0) {
			throw new IllegalArgumentException();
		}
		front = null;
		graveyard = null;
		for (int i = names.size()-1; i >= 0; i--) {
			AssassinNode temp = new AssassinNode(names.get(i), front);
			front = temp;
		}
	}

	//returns true if the game is over and false if it is not over. 
	public boolean isGameOver() {
		int count = 0;
		AssassinNode current = front;
		while (current != null) {
			count++;
			current = current.next;
		}
		return count == 1;
	}

	//returns the name of the winner as a string if the game is over 
	//and returns null if it's not over
	public String winner() {
		if (isGameOver()) {
			return front.name;
		}
		return null;
	}
	
	//prints the graveyard list as long as it contains something
	public void printGraveyard() {
		if (graveyard != null) {
			AssassinNode current = graveyard;
			while (current != null) {
				System.out.println("  " + current.name + " was killed by " + current.killer);
				current = current.next;
			}
		}
	}
		
	//prints the current "assassins" in the game and who they are killing
	public void printKillRing() {
		String first = front.name;
		AssassinNode current = front;
		while (current.next != null) {
			String result = "  ";
			result += current.name + " is stalking " + current.next.name;
			System.out.println(result);
			current = current.next;
		}
		System.out.println("  " + current.name + " is stalking " + first);
	}

	//returns true if the graveyard contains the name or false if it doesnt.
	public boolean graveyardContains(String name) {
		AssassinNode current = graveyard;
		while (current != null) {
			if (current.name.equalsIgnoreCase(name)) {
				return true;
			}
			current = current.next;
		}
		return false;
	}
	
	//returns true if the kill ring contains the name or false if it doesnt.
	public boolean killRingContains(String name) {
		AssassinNode current = front;
		while (current != null) {
			if (current.name.equalsIgnoreCase(name)) {
				return true;
			}
			current = current.next;
		}
		return false;
	}

	//"kills" the corresponding person in the kill ring if they exist
	//if the game is over, throws IllegalStateException
	//if they don't exist, throws IllegalArgumentException
	public void kill(String name) {
		if (isGameOver()) {
			throw new IllegalStateException();
		}
		if (!killRingContains(name)) {
			throw new IllegalArgumentException();
		}
		AssassinNode current = front;
		if (front.name.equalsIgnoreCase(name)) {
			while(current.next != null) {
				current = current.next;
			}
			AssassinNode temp = front;
			front = front.next;
			temp.killer = current.name;
			temp.next = graveyard;
			graveyard = temp;
			
		} else {
			while (!current.next.name.equalsIgnoreCase(name)) {
				current = current.next;
			}
			AssassinNode temp = current.next;
			current.next = current.next.next;
			temp.killer = current.name;
			temp.next = graveyard;
			graveyard = temp;
		}
	}
}
