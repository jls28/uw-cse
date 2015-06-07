/* Stefan Dierauf 2013
 * Makes 3d points and vectors less of a headache
 * WARNING: contains spaghetti and unoptimized code.
 * "-/" means square root. 
 */

import java.util.*;

public class DistanceFormula {
	
	public static void main(String[] args) throws InterruptedException {
		Scanner input = new Scanner(System.in);
		System.out.println("Distance calculator between points(2d or 3d)");
		String word = "";
		ArrayList<point3d> points = new ArrayList<point3d>();
		System.out.println("Make a (n)ew point, (c)lear, (e)xit, (solve <indexes of points>) to get as much info as possible for the given points");
		System.out.println("or put a point in x, y, z form");
		while (!word.equals("e")){
			System.out.println();
			System.out.print("Saved points: " + points + "  ");
			String next = input.nextLine();
			if (next.equals("c")) {
				points.clear();
			}
			if (next.equals("n")) { //create a new point
				points.add(newPoint(input));
			} else if (next.contains("solve")) { //solve for given points
				String[] indexes = next.substring(6).split(" ");
				int first = Integer.parseInt(indexes[0]);
				int second = Integer.parseInt(indexes[1]);
				if (indexes.length > 2) {
					int third = Integer.parseInt(indexes[2]);
					points.get(first).solve(points.get(second), points.get(third));
				}
				points.get(first).solve(points.get(second));
			} else if (next.contains(",")) { //stick in a new point
				points.add(new point3d(next));	
			} else if (next.contains("g")) {
				System.out.print("Installing Gentoo");
				while (true) {
					System.out.print(".");
					Thread.sleep(500);
				}
			}
			word = next;	
		}
	}
	
	//tediously makes a new point
	public static point3d newPoint(Scanner input) {
		System.out.println("Make a new point");
		System.out.print("x: ");
		double x = input.nextDouble();
		System.out.print("y; ");
		double y = input.nextDouble();
		System.out.print("z: ");
		double z = input.nextDouble();
		return new point3d(x, y, z);
	}
	
	//point class
	public static class point3d {
		public double x;
		public double y;
		public double z;
		private String constructor;
		
		//2d points
		public point3d(double x, double y) {
			this(x, y, 0.0);
		}
		
		//tedious constructor
		public point3d(double x, double y, double z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
		
		//pre: string is in "3, 4, 5" format (or 3.1, 4.2, 5.3 format)
		public point3d(String data) {
			constructor = data;
			String[] nums = data.split(", ");
			this.x = Double.parseDouble(nums[0]);
			this.y = Double.parseDouble(nums[1]);
			this.z = Double.parseDouble(nums[2]);
		}
		
		//distance formula with another point
		public double distance(point3d other) {
			double answer = Math.pow(x - other.x, 2) + Math.pow(y - other.y, 2) 
					+ Math.pow(z - other.z, 2);
			return Math.sqrt(answer);
		}
		
		//solves stuff
		public void solve(point3d second) {
			System.out.println("distance: " + distance(second) + " or  -/" + Math.pow(distance(second), 2));
			System.out.print("first = centroid of sphere and second = point on surface: "); sphereCenterAndPoint(second);
			System.out.println("If both points are endpoints of a sphere, equation is: " + sphereEndpoints(second));
			solveVectors(second);
		}
		
		//solves vector stuff
		public void solveVectors(point3d other) {
			System.out.println("------Vectors------");
			System.out.println("Converting points to vectors... (assuming points are 0-based vectors)");
			vector v1 = new vector(this.constructor);
			vector v2 = new vector(other.constructor);
			System.out.println(v1);
			System.out.println(v2);
			v1.add(v2);
			v1.subtract(v2);
			v1.compAB(v2);
			v1.crossProduct(v2);
		}
		
		//solves stuff with more than one other point
		public void solve(point3d second, point3d third) {
			//plane containing the points (probably requires vectors)
		}
		
		//solves sphere endpoints question
		public String sphereEndpoints(point3d other) {
			//find radius
			//find center
			double A = (this.x + other.x) / 2;
			double B = (this.y + other.y) / 2;
			double C = (this.z + other.z) / 2;
			double radiusSquared = sqr(distance(other)); //not div by 4
			return "(x - " + A + ")^2 " + " + (y - " + B + ")^2 + (z - " + C + ")^2 = " + radiusSquared + "/4" ;
			
		}
		
		public void sphereCenterAndPoint(point3d point) {
			System.out.println("(x-" + x + ")^2 + (y-" + y + ")^2 + (z-" + z + ")^2 = " + sqr(distance(point)));
		}
		
		//math.pow(a, 2) takes too long to type
		double sqr(double a) {
			return Math.pow(a, 2);
		}
		
		//should probably go in vectors class
		public double length() {
			return distance(new point3d(0.0, 0.0, 0.0));
		}
		
		//#yolo
		public String toString() {
			return "(" + x + ", " + y + ", " + z + ")";
		}
	
	}
	
	//vectors are just points with a cooler toString
	//and vector specific methods
	public static class vector extends point3d {
		
		private double magnitude;
		
		public vector(String data) {
			super(data);
			magnitude = length();
		}
		
		public vector (double x, double y, double z) {
			super(x, y, z);
			magnitude = length();
		}
		
		public void add(vector other) {
			vector added = new vector(x + other.x, y + other.y, z + other.z);
			System.out.print("sum: ");
			System.out.println(added);
		}
		
		public void compAB(vector other) {
			double dot = dotProduct(other);
			System.out.println("comp_aB: " + dot + " /  magnitude of a"); 
		}
		
		public void subtract(vector other) {
			vector subtracted  = new vector(x - other.x, y - other.y, z - other.z);
			System.out.print("difference: ");
			System.out.println(subtracted);
		}
		
		public double dotProduct(vector other) {
			System.out.print("Dot product: ");
			double dot = x * other.x + y * other.y + z * other.z;
			System.out.print("= " + dot + " --");
			double theta = dot / (this.magnitude * other.magnitude);
			double acos = Math.acos(theta) * 180/Math.PI;
			double rad = acos / (180/Math.PI);
			double radNoPi = rad / Math.PI;
			System.out.println("Angle between: " + acos + " degrees or " + rad + " radians (" + radNoPi + "*pi)"  );
			return dot;//fill
		}
		
		public void crossProduct(vector other) {
			System.out.print("Cross product: ");
			//oh fuck here we go
			double first = y * other.z - z * other.y;
			double second = x * other.z - z * other.x;
			double third = x * other.y - other.x * y;
			vector cross = new vector(first, -second, third);
			System.out.println(cross); //fill
		}
		
		public String toString() {
			return x + "i + " + y + "j + " + z +"k, magnitude: -/" + sqr(magnitude);  
		}
		
		
		
	}
}

	


