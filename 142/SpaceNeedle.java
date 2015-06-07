/*
Stefan Dierauf October 2012
Prints ASCII Art of the Space Needle
Based on a size constant called SCALAR
*/
public class SpaceNeedle {
   
   public static final int SCALAR = 8;
   
   public static void main (String[] args){
      //the whole space needle breaks down into five distinct parts
		//Each part is given a letter, A through E
		//Some parts repeat
      printA(); //the top
      printB();
      printC();
      printD();
      
      printA();//the middle
      printE();
      
      printB();//the base
      printC();
      
   }
   
   //the top spike of the space needle. also part of the structure.
   public static void printA(){
      for (int row = 1; row <= SCALAR; row++){
         printLoop(3*SCALAR, " "); //print white space
         System.out.print("||");
         System.out.println();
      }
   }
   
   
   //I realized that I only needed one forloop 
	//for the whole program after I started making one for printing whitepsace. 
	//Hence, printLoop.
   //the only thing that changes is the test and the string printed for each forloop
   public static void printLoop(int test, String str){
      for (int line = 1; line <= test; line++) {
         System.out.print(str);
      }
      
   }
   
   //the "roof" of the space needle. also the base
   public static void printB(){
      for (int row = 1; row <= SCALAR; row++){
         printLoop(-3*row + SCALAR*3, " ");//print white space
         System.out.print("__/");
         printLoop(3*row-3, ":");
         System.out.print("||");
         printLoop(3*row-3, ":");
         System.out.print("\\__");
         System.out.println();
      }
   }
   
   //the middle "filling" of the space needle top.
   public static void printC() {
      System.out.print("|");
      printLoop(6*SCALAR, "\"");
      System.out.print("|");
      System.out.println();
      
   }
   
   //the lower half of the top of the space needle
   public static void printD() {
      for (int row = 1; row <= SCALAR; row++) {
         printLoop(2*row - 2, " ");//print white
         System.out.print("\\_");
         printLoop(-2*row + (SCALAR*3+1), "/\\");
         System.out.print("_/");
         System.out.println();
      }
      
   }
   
   
   //prints the main middle structure of the space needle
   public static void printE() {
      for (int row = 1; row <= SCALAR*SCALAR; row++){
         printLoop(SCALAR*3-(1+SCALAR-2), " ");//print white
         System.out.print("|");
         printLoop(SCALAR - 2, "%");
         System.out.print("||");
         printLoop(SCALAR - 2, "%");
         System.out.print("|");
         System.out.println();
         
      }
   }
   
}
