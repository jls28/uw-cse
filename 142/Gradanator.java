/*
Stefan Dierauf Oct 2012
This program prompts the user for their grades
and outputs a final grade
a la the gradanator
*/
import java.util.*;

public class Gradanator {
   
   public static void main (String[] args){
      
      Scanner s = new Scanner(System.in);
      
      header();
      
      double midtermGrade = promptUser(s, "Midterm:");
      double finalGrade = promptUser(s, "Final:");
      double homeworkGrade = promptUser(s, "Homework:");
      double endGrade = midtermGrade + finalGrade + homeworkGrade;
      
      footer(endGrade);
      
   }
   
   //prints the top part of the program
   public static void header() {
      System.out.println("This program reads exam/homework scores" +
      "\nand reports your overall course grade.");
      System.out.println();
   }
   
	//begins the prompt for either type of work
	//decided to put the code for each further prompt in their own method
	//makes it easier to read
	//reduces redundancy so weight isn't asked for twice
   public static double promptUser(Scanner s, String work){
      System.out.println(work);
      System.out.print("Weight (0-100)? ");
      int weight = s.nextInt();
      if (work.equals("Homework:")){
			return homeworkPrompt(s, weight); //calls prompt for homework and returns the weighted score
      } else {
         return testsPrompt(s, weight); //calls prompt for other work and returns the weighted score
      }
   }
	
	//further prompt for homework type
	public static double homeworkPrompt(Scanner s, int weight){
		System.out.print("Number of assignments? ");
      int numberAssignments = s.nextInt();
      int hwScore = 0;
      int hwMax = 0;
      for (int i = 1; i <= numberAssignments; i++){
         System.out.print("Assignment " + i + " score and max? ");
         hwScore += s.nextInt();
         hwMax += s.nextInt();
      }
      System.out.print("How many sections did you attend? ");
      int numberSections = Math.min(s.nextInt() * 3, 20);
   	hwMax += 20;  
	   hwScore = Math.min(hwScore + numberSections, hwMax);
      System.out.println("Section points = " + numberSections + " / 20");
      return gradeMath(hwScore, hwMax, weight);
	
	}
	
	//further prompt for other kinds of tests returns the weighted score
	public static double testsPrompt(Scanner s, int weight){
		System.out.print("Score earned? ");
      int midtermScore = s.nextInt();
      System.out.print("Were scores shifted (1=yes, 2=no)? ");
      int midtermShifted = s.nextInt();
      int midtermShift = 0;
      if (midtermShifted == 1){
         System.out.print("Shift amount? ");
         midtermShift = s.nextInt();
      } else {}
      int shiftedSum = Math.min((midtermScore + midtermShift),100);
      return gradeMath(shiftedSum, 100, weight);
	
	}
	
	//does the calculation for the end of each prompt and returns a weighted score
   public static double gradeMath (int sum, int maxSum, int weight) {
      System.out.println("Total points = " + sum + " / " + maxSum);
      double weightedScore = Math.round(sum * weight * 10.0 / maxSum) / 10.0;
      System.out.println("Weighted score = " + weightedScore + " / " + weight);
      System.out.println();
      return weightedScore;
      
   }
   
	//prints the footer of the program,containing the gpa and a custom message based on gpa
   public static void footer(double endGrade) {
      double gpa = 0;
      String customMessage = " ";
      if (endGrade >= 85) {
         gpa = 3.0;
         customMessage = "You sure are a smartypants!";
      } else if (endGrade >= 75) {
         gpa = 2.0;
         customMessage = "You are almost a smartypants!";
         
      } else if (endGrade >= 60) {
         gpa = 0.7;
         customMessage = "You are almost almost a smartypants!";
      } else if (endGrade < 60) {
         gpa = 0.0;
         customMessage = "At least it's not negative!";
      }
      System.out.println("Overall percentage = " + endGrade);
      System.out.println("Your grade will be at least: " + gpa);
      System.out.println(customMessage);
   }
   
   
}