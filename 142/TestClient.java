import java.util.*;

public class TestClient {

	public static void main(String[] args) {
	
		int[] a = {1, 4, 7, 10, 13, 10, 13, 10, 7, 4};
		
		System.out.println(sameGap(a));
	
	}
	
	public static boolean sameGap(int[] a){
		int gap = Math.abs(a[0] - a[1]);
	
}