/* Stefan Dierauf March 2013
 * TA: Molly Yoder
 * Node for QuestionTree class
 */


public class QuestionNode {
	public String data;
	public QuestionNode left; 
	public QuestionNode right; 

	//constructs the QuestionNode if only given a string
	public QuestionNode(String data) {
		this(data, null, null);
	}
	
	//constructs the QuestionNode with the given data, left, and right QuestionNodes
	public QuestionNode(String data, QuestionNode left, QuestionNode right) {
		this.data = data;
		this.left = left;
		this.right = right;
	}
	
 
 }
