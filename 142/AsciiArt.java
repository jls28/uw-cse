/*
Stefan Dierauf October 2012
Prints ASCII Art of a box
Based on a size constant called BOX_SIZE
also prints BOX_SIZE just incase you don't know
*/
public class AsciiArt {

	 public static final int BOX_SIZE = 10;
    //This will draw some ascii art
    public static void main(String[] args) {
	 
	 System.out.println("The box scalar is: " + BOX_SIZE + " * 4");
	 printEnd();
	 printMiddle();
	 printEnd();
       
    }
	 
	 public static void printEnd(){
        System.out.print("+");
        for (int i = 1; i <= 4*BOX_SIZE; i++) {
            System.out.print("* ");
        }
        System.out.println("+");
    
        
    }
    public static void printMiddle(){
        for (int i = 0; i < BOX_SIZE*4; i++) {
            System.out.print("*");
            for (int spaces = 0; spaces < BOX_SIZE*4; spaces++) {
                System.out.print("  ");
                
            }
            System.out.println("*");
            
        }
    }
}
