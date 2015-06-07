import java.util.*;

public class Thing {

	public static void main(String[] args){
		int[] list = { 1, 4, 4, 4, 6, 7, 8, 8, 8, 8, 9, 11, 11, 11, 12, 14, 14};
		System.out.println(mode(list));
	
	}
	
	public static int mode(int[] list) {
		int max = -1;
		
		for (int i = 0; i < list.length; i++){
			if (list[i]>max) {
				max = list[i];
			}
		}
		int count[] = new int[max];
		for (int i = 0; i < count.length; i++) {
			count[list[i]-1]++;
		}
		int maxCount = -1;
		for (int i = 0; i < count.length; i++){
			if (count[i] > maxCount) {
				maxCount = count[i];
			}
		}
		return Arrays.indexOf(count[maxCount]);
	
	}
}