public class AsciiArt {
public static final int HEIGHT_OF_TRIANGLE = 4;
public static final int WIDTH_IN_TRIANGLES = 8;
public static final int HEIGHT_IN_TRIANGLES = 8;
	
	public static void main(String[] args) throws InterruptedException {
		pattern();		
	}
	
	public static void triangleUp() throws InterruptedException{
		for (int i = 1; i <= HEIGHT_OF_TRIANGLE; i++) {
			for (int j = 1; j <= WIDTH_IN_TRIANGLES; j++) {
				for (int k = 1; k <= (i - 1); k++) {
					System.out.print("_");
				}
				System.out.print("\\");
				for (int k = 1; k <= (-2 * i + 2 * HEIGHT_OF_TRIANGLE); k++) {
				System.out.print("_");
				}	
				System.out.print("/");
				for (int k = 1; k <= (i - 1); k++) {
					System.out.print("_");
				}
				Thread.sleep(100);
			}
			System.out.println();
		}
	}
	
	public static void triangleDown() {
		for (int i = HEIGHT_OF_TRIANGLE; i >= 1; i--) {
			for (int j = 1; j <= WIDTH_IN_TRIANGLES; j++) {
				for (int k = 1; k <= (i - 1); k++) {
					System.out.print("_");
				}
				System.out.print("/");
				for (int k = 1; k <= (-2 * i + 2 * HEIGHT_OF_TRIANGLE); k++) {
				System.out.print("_");
				}	
				System.out.print("\\");
				for (int k = 1; k <= (i - 1); k++) {
					System.out.print("_");
				}
			}
			System.out.println();
		}
	}
		
	
	public static void pattern() throws InterruptedException{
		for (int i = 1; i <= HEIGHT_IN_TRIANGLES; i++) {
			if ((i % 2) == 0) {
			triangleUp();
			}
			else {
			triangleDown();	
			}
		}	
	}
}