import java.io.*;
import java.util.*;

public class Product {
	
	public static void main(String[] args) throws FileNotFoundException{
		
		Scanner s = new Scanner(new File("poo.txt"));
		ArrayList<Integer> a = new ArrayList<Integer>();
		while (s.hasNext()) {
			a.add(s.nextInt());
		}
		//System.out.println(a);
		long max = 0;
		int index = 0;
		for (int i = 0; i < a.size() - 63; i++) {
			int num = a.get(i) * a.get(i + 21) * a.get(i + 42) * a.get(i + 63);
			if (num > max) {
				max = num;
			}
		}
		for (int i = 3; i < a.size() - 76; i++) {
			int num = a.get(i) * a.get(i + 19) *a.get(i + 38) * a.get(i + 57);
			if (num > max) {
				max = num;
			}
		}
		System.out.println(max);
	}

}
