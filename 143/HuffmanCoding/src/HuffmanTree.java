/*Stefan Dierauf March 2013
 * TA Molly Yoder
 * A huffmantree for creating, encoding, and decoding text files using huffman compression
 * 
 */

import java.io.PrintStream;
import java.util.*;


public class HuffmanTree {
	private HuffmanNode overallRoot;
	private int maxChar;
	private final int NONTERMINAL = -1;

	//constructs HuffmanTree if passed array of char counts. 
	public HuffmanTree(int[] count) {
		maxChar = count.length;
		Queue<HuffmanNode> temp = new PriorityQueue<HuffmanNode>();
		for (int i = 0; i < count.length; i++) { // add all chars and their frequencies
			if (count[i] != 0) {
				temp.add(new HuffmanNode(i, count[i]));
			}
		}
		temp.add(new HuffmanNode(maxChar, 1)); //adds the EOF	
		overallRoot = buildHuffmanTree(temp);
	}

	//builds the HuffmanTree
	private HuffmanNode buildHuffmanTree(Queue<HuffmanNode> counts) {
		if (counts.size() == 1) { 
			return counts.remove(); 
		} else {
			HuffmanNode first = counts.remove();
			HuffmanNode second = counts.remove();
			int total = first.frequency + second.frequency;
			HuffmanNode combined = new HuffmanNode(NONTERMINAL, total, first, second);
			counts.add(combined);
			return buildHuffmanTree(counts);
		}
	}
	
	//constructs the HuffmanTree if passed a given code file
	public HuffmanTree(Scanner code) {
		overallRoot = new HuffmanNode(NONTERMINAL);
		while (code.hasNext()) {
			int data = Integer.parseInt(code.nextLine());
			String location = code.nextLine();
			overallRoot = add(data, location, overallRoot);
		}
	}
    
    //adds the nodes to the huffman tree
    private HuffmanNode add(int data, String location, HuffmanNode root) {
    	if (location.equals("")) {
    		return new HuffmanNode(data);
    	} else {
    		if (location.charAt(0) == '0') {
    			if (root.left == null) {
    				root.left = add(data, location.substring(1), new HuffmanNode(NONTERMINAL));
    			} else {
    				root.left = add(data, location.substring(1), root.left);
    			}
    		} else {
    			if (root.right == null) {
    				root.right = add(data, location.substring(1), new HuffmanNode(NONTERMINAL));
    			} else {
    				root.right = add(data, location.substring(1), root.right);
    			}
    		}
    		return root;
    	}
    }
	
    //decodes a file encoded with huffman compression and prints it to the given PrintStream
    public void decode(BitInputStream input, PrintStream output, int charMax) {
    	int charCode = NONTERMINAL;
    	while (charCode < charMax) {
	    	HuffmanNode temp = overallRoot;
	    	while (temp.left != null && temp.right != null) {
		    	int bit = input.readBit();
		    	if (bit == 0) {
		    		temp = temp.left;
		    	} else {
		    		temp = temp.right;
		    	}
	    	}
	    	charCode = temp.data;
	    	output.write(charCode);
    	}
    }
	

    //prints the huffman tree in pre-order fashion to the given PrintStream
	public void write(PrintStream output) {
		write(output, overallRoot, "");
	}

	//helper method for printing the huffman tree to the given PrintStream
	public void write(PrintStream output, HuffmanNode root, String encoded) {
		if (root.left == null && root.right == null) {
			output.println(root.data);
			output.println(encoded);
		} else {
			write(output, root.left, encoded + "0");
			write(output, root.right, encoded + "1");
		}
	}
	
	
	//HuffmanNode class used by HuffmanTree
	private class HuffmanNode implements Comparable<HuffmanNode> {
		public HuffmanNode left;
		public HuffmanNode right;
		public int data; // char data saved as an int
		public int frequency;
		
		//constructs a HuffmanNode if only given data
		private HuffmanNode(int data) {
			this(data, -1);
		}
		
		//constructs a HuffmanNode if given data and a frequency
		private HuffmanNode(int data, int count) {
			this(data, count, null, null);
		}
		
		//constructs a HuffmanNode if all fields are defined
		private HuffmanNode(int data, int count, HuffmanNode left, HuffmanNode right) {
			this.data = data;
			frequency = count;
			this.left = left;
			this.right = right;
		}

		//returns an int after comparing two huffman nodes
		public int compareTo(HuffmanNode other) {
			return this.frequency - other.frequency;
		}
	}
}
