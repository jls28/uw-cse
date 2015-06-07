//figure out how many days until your birthday
import java.util.Scanner;
class Daysuntilbirthday {
	public static void main(String[] args) {
         Scanner in= new Scanner(System.in);
         
         int birth_month;
         int birth_day;
         int todays_month;
         int todays_day;
         
         System.out.println("what month were you born (numerical)?");
         birth_month = in.nextInt();
         
         System.out.println("what day were you born?");
         birth_day = in.nextInt();
         
         System.out.println("what month is it today?");
         todays_month = in.nextInt();
         
         System.out.println("what day is it today?");
         todays_day = in.nextInt();
         
			//have to set the variables to a certain number if you 
			//are doing an if statement to get that variable, otherwise 
			//java thinks the variable may never get defined and then 
			//doesn't work
         int birth_month_in_days = theForLoops(birth_month);
         int birth_day_total = 0;
             	
        /* if (birth_month==1){
            birth_month_in_days=0;
         }else if {(birth_month==2)
           } birth_month_in_days=31;
         else if (birth_month==3)
            birth_month_in_days=59;
         else if (birth_month==4)
            birth_month_in_days=90;
         else if (birth_month==5)
            birth_month_in_days=120;
         else if (birth_month==6)
            birth_month_in_days=151;
         else if (birth_month==7)
            birth_month_in_days=181;
         else if (birth_month==8)
            birth_month_in_days=212;
         else if (birth_month==9)
            birth_month_in_days=232;
         else if (birth_month==10)
            birth_month_in_days=263;
         else if (birth_month==11)
            birth_month_in_days=294;
         else if (birth_month==12)
            birth_month_in_days=324; */
           
      birth_day_total=(birth_month_in_days+birth_day);
      
      int todays_month_in_days = theForLoops(todays_month);
   	    
		 
        /* int todays_day_total;
        if (todays_month==1)
            todays_month_in_days=0;
         else if (todays_month==2)
            todays_month_in_days=31;
         else if (todays_month==3)
            todays_month_in_days=59;
         else if (todays_month==4)
            todays_month_in_days=90;
         else if (todays_month==5)
            todays_month_in_days=120;
         else if (todays_month==6)
            todays_month_in_days=151;
         else if (todays_month==7)
            todays_month_in_days=181;
         else if (todays_month==8)
            todays_month_in_days=212;
         else if (todays_month==9)
            todays_month_in_days=232;
         else if (todays_month==10)
            todays_month_in_days=263;
         else if (todays_month==11)
            todays_month_in_days=294;
         else if (todays_month==12)
            todays_month_in_days=324; */
            
            
                  
       int todays_day_total=todays_month_in_days+todays_day;
         
        int days_until;
        days_until=0;
    
         if (todays_day_total > birth_day_total)
         days_until = 365 - (todays_day_total-birth_day_total);
           else if (birth_day_total > todays_day_total)
           days_until = todays_day_total-birth_day_total;
         
         if (days_until>0)
         System.out.println("it is " +days_until +" days until your birthday!");
      	else 
      	System.out.println("happy birthday!!");
      }
	public static int theForLoops (int monthCounter){
		int days = 0;
		for (int i = 1; i < monthCounter ; i++){
			if (i % 2 == 1) {
			days += 31;
			}
			else if (i % 2 == 0 && i !=2){
			days += 30;
			}
			else{ 
			days+= 28;
         }
		
  		}
   	return days;
	} 
        
}
