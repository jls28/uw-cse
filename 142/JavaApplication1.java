public class JavaApplication1 {
    public static final int boxSize=6;
    public static int zipcode=97201;
    public static int twentyfive=25;
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("hello world");
        
        triangle();
        doThings();
        drawDiamond();
      
    }
    public static void doThings() {
        System.out.println("time to do some math");
        
        double zipcodeMath;
        System.out.println("My zipcode is: "+zipcode);
        zipcodeMath = zipcode*zipcode-5000+zipcode;
        System.out.println("If i take my zipcode, multiply it by itself, suptract 5000, and add my zipcode, I get: " +zipcodeMath);
        System.out.println("I am now adding 25 to my zipcode");
        zipcode=zipcode+twentyfive;
        System.out.println(zipcode);
    }
    public static void doSomeLoops(){ //we are going to doThings() five times
        System.out.println("Let's do some loops");
        for (int i = 0; i < 5; i++) {
            doThings();
            
        }
        
    }
    public static void triangle(){
    // Prints the following output
	// *
	// **
	// ***
	// ****
	// *****
        for (int line = 1; line <= 5; line++) {
			for (int j = 1; j <= line; j++) {
				System.out.print("*");
			}
			System.out.println();
		}
        for (int line = 1; line <= 5; line++) {
			for (int j = 1; j <= line; j++) {
				System.out.print(line);
			}
			System.out.println();
		}
        for (int i = 1; i <= 10; i++) {
            System.out.println(i+" squared is: "+(i*i));
            
        }
        System.out.println("let's make some patterns");
        
        for (int i = 0; i < 3; i++) {
            System.out.println("a  -  a");
            typeB();
            System.out.println("  c-     c");
            typeB();
        }
        System.out.println("now we are going to print the first six y-int of  5x-17");
        for (int count = 0; count < 6; count++) {
            System.out.println("5 times "+count+" minus 17 equals:");
            System.out.println(5*count-17);
            
        }
        System.out.println("now we are going to draw a box of stars based on a size variable");
        System.out.println("The box scalar is: " +boxSize);
        printEnd();
        printMiddle();
        printEnd();
        
        
    }
    public static void printEnd(){
        System.out.print("+");
        for (int i = 1; i <= 4*boxSize; i++) {
            System.out.print("* ");
        }
        System.out.println("+");
    
        
    }
    public static void printMiddle(){
        for (int i = 0; i < boxSize*4; i++) {
            System.out.print("*");
            for (int spaces = 0; spaces < boxSize*4; spaces++) {
                System.out.print("  ");
                
            }
            System.out.println("*");
            
        }
    }
    public static void typeB(){
        System.out.println(" b -    b");
}
    public static void drawDiamond() {
        System.out.println("this will draw an ascii diamond");
        System.out.println("boxSize will be equal to the radius");
        printBoxsizeSpaces();
        System.out.print("*");
        printBoxsizeSpaces();
    }
    public static void printBoxsizeSpaces(){
        for (int diamond = 0; diamond < boxSize; diamond++) {
            System.out.print(" ");
            
        }
        
    }
}
