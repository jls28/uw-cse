import java.util.Arrays;


public class ArraysAreFun {
	
	public static void main(String[] args) {
		int a = 4;
		int[] bob = {1, 2, 3, 4, 5};
		//bob[0] = 3;
		int[] jane = {12, 3, 4, 6};
		jane[0] = 6;
		for (int i = 0; i < bob.length - 1; i++) {
			System.out.print(bob[i] + ", ");
		}
		System.out.println(bob[bob.length-1]);
		int sum = 0;
		for (int i = 0; i < bob.length; i++) {
			System.out.println(bob[i]*jane[i]);
			sum += bob[i] * jane[i];
		}
		System.out.println(sum);
		
	}

}
