/* Stefan Dierauf 2013
 * TA: Molly Yoder
 * HtmlValidator class for the second homework
 * Validates tags in an .html document or other kinds of 
 * "tagged" documents
 */

import java.util.*;


public class HtmlValidator {
	
	private Queue<HtmlTag> data;

	//Saves the queue of HtmlTags passed in into a new queue
	public HtmlValidator(Queue<HtmlTag> tags) {
		data = tags;
	}

	//creates an new empty queue if no HtmlTags are passed in 
	public HtmlValidator() {
		 data = new LinkedList<HtmlTag>();
	}

	//adds a tag to the queue
	//throws IllegalArgumentException if null passed in
	public void addTag(HtmlTag tag) {
		if (tag == null) {
			throw new IllegalArgumentException();
		}
		data.add(tag);	
	}

	//returns the tags stored in the queue
	public Queue<HtmlTag> getTags() {
		return data;
	}

	//removes all tags containing the element passed in
	//throws IllegalArgumentException if null passed in
	public void removeAll(String element) {
		if (element == null) {
			throw new IllegalArgumentException();
		}
		int size = data.size();
		for (int i = 0; i < size; i++) {
			HtmlTag t = data.remove();
			if (!(t.getElement().equals(element))) {
				data.add(t);
			}
		}	
	}
	
	//prints correct indentation for the validate() method
	private void printTag(int indent, HtmlTag t) {
		for (int j = 0; j < indent; j++) {
			System.out.print("    ");
		}
		System.out.println(t);
	}

	//Checks html tags, outputs errors where unexpected tags are and where unclosed tags are
	public void validate() {
		int size = data.size();
		int indent = -1;
		Stack<HtmlTag> s = new Stack<HtmlTag>();
		for (int i = 0; i < size; i++) {
			HtmlTag t = data.remove();
			if (t.isSelfClosing()) {
				if(t.isOpenTag()) {
					indent++;
					printTag(indent, t);
					indent--;
				} else {
					System.out.println("ERROR unexpected tag: " + t);
				}
			} else if (t.isOpenTag()) {
				indent++;
				printTag(indent, t);
				s.push(t);
			} else {
				if (!t.matches(s.peek())) {
					System.out.println("ERROR unexpected tag: " + t);
				} else {
					printTag(indent, t);
					indent--;
					s.pop();
				}
			}
			data.add(t);	
		}
		while (!s.isEmpty()) {
			System.out.println("ERROR unclosed tag: " + s.pop());
		}
	}
}
