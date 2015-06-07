// This testing program stub creates a queue of HTML tags 
// in a valid sequence.
// You may use this as a starting point for testing
// your removeAll method.
import java.util.*;

public class HtmlValidatorTest {
	public static void main(String[] args) {
		
		Queue<HtmlTag> tags = new LinkedList<HtmlTag>();
		tags.add(new HtmlTag("html", true)); 
		tags.add(new HtmlTag("p", true)); 
		tags.add(new HtmlTag("i", true)); 
		tags.add(new HtmlTag("b", true));      
		tags.add(new HtmlTag("b", false));     
		tags.add(new HtmlTag("i", false));
		tags.add(new HtmlTag("p", false));
		tags.add(new HtmlTag("br"));           
		tags.add(new HtmlTag("html", false));
		
		//check if nothing is removed
		Queue<HtmlTag> checkRemoveNothing = new LinkedList<HtmlTag>();
		checkRemoveNothing.add(new HtmlTag("html", true)); 
		checkRemoveNothing.add(new HtmlTag("p", true)); 
		checkRemoveNothing.add(new HtmlTag("i", true)); 
		checkRemoveNothing.add(new HtmlTag("b", true));      
		checkRemoveNothing.add(new HtmlTag("b", false));     
		checkRemoveNothing.add(new HtmlTag("i", false));
		checkRemoveNothing.add(new HtmlTag("p", false));
		checkRemoveNothing.add(new HtmlTag("br"));           
		checkRemoveNothing.add(new HtmlTag("html", false));
		
		//check if <b> and </b> elements are removed
		Queue<HtmlTag> checkRemoveSomething = new LinkedList<HtmlTag>();
		checkRemoveSomething.add(new HtmlTag("html", true)); 
		checkRemoveSomething.add(new HtmlTag("p", true)); 
		checkRemoveSomething.add(new HtmlTag("i", true));
		checkRemoveSomething.add(new HtmlTag("i", false));
		checkRemoveSomething.add(new HtmlTag("p", false));
		checkRemoveSomething.add(new HtmlTag("br"));           
		checkRemoveSomething.add(new HtmlTag("html", false));
		
		HtmlValidator validator = new HtmlValidator(tags);
		
		
		//Case: remove a tag that is not there
		validator.removeAll("ul");
		if (matches(tags, checkRemoveNothing)) {
			System.out.println("Remove nonpresent tag case passed");
		} else {
			System.out.println("Remove nonpresent tag case FAILED");
		}
		
		//Case: remove a tag that is there
		validator.removeAll("b"); 
		if (matches(tags, checkRemoveNothing)) {
			System.out.println("Remove valid tag case passed");
		} else {
			System.out.println("Remove valid tag case FAILED");
		}
		
		//Case: .removeAll is passed in null
		System.out.println("If the program now throws an IllegalArgumentException, " +
				"then the remove null case is passed");
		validator.removeAll(null);
		
		
	}
	
	//checks if both queues passed in match each other
	//throws NullPointerException if null passed in
	public static boolean matches(Queue<HtmlTag> q, Queue<HtmlTag> check) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			if (!q.element().equals(check.element())) {
				return false;
			}
		}
		return true;	
	}
}
