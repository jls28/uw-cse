
public class FuckYeah {
	
	public static int routes = 0;
	
	public static void main(String[] args) {
		
		int x = 4;
		int y = 4;
		latticePaths(x, y, 0, 0);
		System.out.println(routes);
		
	}
	
	public static void latticePaths(int x, int y, int currx, int curry) {
		if (!(currx > x || curry > y)) {
			if (currx == x && curry == y) {
				System.out.println("found");
				routes++;
			} else {
				latticePaths(x, y, currx + 1, curry);
				latticePaths(x, y, currx, curry + 1);
			}
		}
	}

}
