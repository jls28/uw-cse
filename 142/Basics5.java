import java.util.Scanner;
public class Basics5
{
	public static void main(String[] args)
	{
		String ans = greetings();
		if (ans.equalsIgnoreCase("d")){
			drinkingAge();}
		else if (ans.equalsIgnoreCase("a")){
			amusementPark();}
		else {
			System.out.println("That's not a choice!");}
	}
	
	public static String greetings()
	{
		String ans;
		Scanner in= new Scanner(System.in);
		System.out.print("Why hello there, would you like to play a game?");
		ans=in.next();
		if	(!ans.equals("no")){
			System.out.println("Which game would you like to play?  [D]rinking age or [A]musement park?");
			ans=in.next();}
		else {
			System.out.println("lame.");}
		return ans;
		}
	
	public static void drinkingAge()
	{
		Scanner in= new Scanner(System.in);
		int age;
		System.out.println("How old are you?");
		age=in.nextInt();
		if (age >=  21){
		System.out.println("You can drink");}
		else {
		System.out.println("You have " +(21-age) +" years left until you can drink legally, byt you can drink illegally!");}
	}
	
	public static void amusementPark()
	{
		Scanner in= new Scanner(System.in);
		int heightfeet;
		int heightinches;
		int totalheightinches;
		int age;
		System.out.println("how tall are you (feet)?");
		heightfeet = in.nextInt();
		System.out.println("how many more inches taller are you?");
		heightinches = in.nextInt();
		System.out.println("how old are you?");
		age = in.nextInt();
		totalheightinches = ((heightfeet*12)+heightinches);
		if ((age >= 9)&&(totalheightinches >= 52)){
			System.out.println("you can ride!");}
		else {
			System.out.println("you can't ride");}
		}
}