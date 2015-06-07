/* Stefan Dierauf Nov 2012 
a simple program for counting the days until someone's birthday
*/

import java.util.*;

public class Birthday {

	public static void main(String[] args) {
		Scanner console = new Scanner(System.in);
		System.out.print("What is today's date (month and day)? ");
		Date todaysDate = new Date (console.nextInt(), console.nextInt());
		System.out.print("What is your birthday (month and day)? ");
		Date yourBirthday = new Date (console.nextInt(), console.nextInt());
		System.out.println("There are " + yourBirthday.daysInMonth() + " days in month #" + 
		yourBirthday.getMonth());
		if (todaysDate.equals(yourBirthday)) {
			System.out.println("Happy Birthday!");
		} else {
			System.out.println("Number of days until birthday " + yourBirthday + ": " 
			+ howMany(todaysDate, yourBirthday));
		}
	
	}
	
	public static int howMany(Date todaysDate, Date yourBirthday) {
		int todaysDateInDays = countDays(todaysDate);
		int yourBirthdayInDays = countDays(yourBirthday);
		
		if (todaysDateInDays > yourBirthdayInDays) {
			return 365 - (todaysDateInDays - yourBirthdayInDays);
      } else {
			return Math.abs(todaysDateInDays - yourBirthdayInDays);
		}
	}
	
	public static int countDays(Date theDate) {
		int days = theDate.getDay();
		for (int i = 1; i < theDate.getMonth(); i++) {
			if (i == 2) {
			days += 28;
			} else if ((i % 2 == 1 && i <= 7) || (i % 2 == 0 && i >= 8)) {
			days += 31;
			}
			else{ 
			days+= 30;
         }
  		}
		return days;
   	
	}

}
