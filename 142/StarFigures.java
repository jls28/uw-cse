public class StarFigures{
	public static void main(String[] args) {
	//this will print three figures
	figureOne();
	figureTwo();
	figureThree();
	}
	
	public static void blockA() {
		System.out.println("*****");
	}
	
	public static void blockB() {
		System.out.println(" * * ");
	}
	
	//prints a blank line
	public static void blockC() {
		System.out.println();
	}	
	
	public static void blockD() {
		System.out.println("  *  ");
	}
	
	//prints a 2x5 block shape
	public static void blockAA(){
		blockA();
		blockA();
	}
	
	//prints an X shape
	public static void blockBDB(){
		blockB();
		blockD();
		blockB();
	}
	
	//prints the first figure
	public static void figureOne() {
		blockAA();
		blockBDB();
		blockC();
	}
	
	//prints the second shape
	public static void figureTwo() {
		blockAA();
		blockBDB();
		blockAA();
		blockC();
	}
	
	//prints the thrid shape
	public static void figureThree() {
		blockD();
		blockD();
		blockD();
		blockAA();
		blockBDB();
	}
}
