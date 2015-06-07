public class Test {
	public static void main(String[] args) {
		
		/**/
		//firstQS();
		ten4();
	
	}
	
	public static void ten4() {
		for (int i = 1; i<=5; i++) {
			for (int j = 1; j<= -4*i+20; j++){
				System.out.print("/");
			}
			for (int k = 1; k<=8*i-8; k++) {
				System.out.print("*");
			}
			for (int l = 1; l<=-4*i+20; l++){
				System.out.print("\\");
			}
			System.out.println(); 
		
		}
	}
	public static void firstQS() {
		for (int i = 1; i<=2; i++) {
			for (int j=1; j <=3; j++) {
				for (int k =1; k <=4; k++) {
					System.out.print("*");
				
				}
				System.out.print("!");
			}
			System.out.println();
		
		}
	}
	
}
