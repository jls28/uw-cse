/* Stefan Dierauf Oct 2012
This program takes in dna strings
and outputs information about them. */

import java.util.*;
import java.io.*;

public class DNA {

	public static final int MIN_NUM_CODONS = 5; 
	public static final double PERCENT_OF_CG = 30;
	public static final int UNIQUE_NUCLEOTIDES = 4;
	public static final int NUC_PER_CODON = 3;
	
	public static void main(String[] args) throws FileNotFoundException{
		
		Scanner console = new Scanner(System.in);
		
		printHeader();
		
		System.out.print("Input file name? ");
		File input = new File(console.next());
		
		System.out.print("Output file name? ");
		PrintStream out = new PrintStream(console.next());
		
		Scanner fileScan = new Scanner(input);
	
		while (fileScan.hasNextLine()) {
			String regionName = fileScan.nextLine();
			String nucleotides = fileScan.nextLine().toUpperCase();
			int[] nucCount = new int[UNIQUE_NUCLEOTIDES + 1]; //includes '-'
			countNucs(nucleotides, nucCount);
			double[] massPercent = new double[UNIQUE_NUCLEOTIDES + 1];
			double totalMass = Math.round(calcMassPercentage(nucCount, massPercent) * 10.0) / 10.0;
			String nucNoDashes = removeDashes(nucleotides);
			String[] codonSet = new String[(nucNoDashes.length() / NUC_PER_CODON)];
			listCodons(codonSet, nucNoDashes);
			boolean isProtein = checkIfProtein(codonSet, massPercent); 
			printData(out, regionName, nucleotides, nucCount, massPercent, totalMass, codonSet, isProtein);
		}
	}
	
	//prints the output per dna string
	public static void printData(PrintStream out, String regionName, String nucleotides, 
	int[] nucCount, double[] massPercent, double totalMass,  String[] codonSet, boolean isProtein) {
		out.println("Region Name: " + regionName);
		out.println("Nucleotides: " + nucleotides);
		out.println("Nuc. Counts: " + Arrays.toString(Arrays.copyOf(nucCount, UNIQUE_NUCLEOTIDES)));
		out.println("Total Mass%: " + Arrays.toString(Arrays.copyOf(massPercent, UNIQUE_NUCLEOTIDES)) + 
		" of " + totalMass);
		out.println("Codons List: " + Arrays.toString(codonSet));
		String proteinText = "NO";
		if (isProtein) {
			proteinText = "YES";
		}
		out.println("Is Protein?: " + proteinText);
		out.println();
	}
	
	//prints the information in the console about the program. 
	public static void printHeader() {
		System.out.println("This program reports information about DNA");
		System.out.println("nucleotide sequences that may encode proteins.");
	}
	
	//sums up the number of individual nucleotides in a strand including the junk dna
	public static void countNucs(String nucleotides, int[] nucCount) {
		for (int i = 0; i < nucleotides.length(); i++) {
			if (nucleotides.toLowerCase().charAt(i) == 'a') {
				nucCount[0]++;
			}else if (nucleotides.toLowerCase().charAt(i) == 'c') {
				nucCount[1]++;
			}else if (nucleotides.toLowerCase().charAt(i) == 'g') {
				nucCount[2]++;
			}else if (nucleotides.toLowerCase().charAt(i) == 't') {
				nucCount[3]++;
			}else{
				nucCount[4]++;
			}
		}
	}
	
	//calculates the mass percentages of each nucleotide, including junk dna
	public static double calcMassPercentage(int nucCount[], double massPercentage[]) {
		double totalMass = 0;
		double[] masses = {135.128, 111.103, 151.128, 125.107, 100.0};
		for (int i = 0; i < nucCount.length; i++){
			totalMass += nucCount[i] * masses [i];
		}
		for (int i = 0; i < massPercentage.length; i++) {
			massPercentage[i] = Math.round(((masses[i] * nucCount[i]) / totalMass) * 100 * 10.0) / 10.0 ;
		}
		return totalMass;	
	}
	
	//removes dashes from a string, intended for nucleotide string
	public static String removeDashes(String nucleotides) {
		String nucNoDashes = "";
		for (int i = 0; i < nucleotides.length(); i++) {
			if (!(nucleotides.charAt(i) == '-')) {
				nucNoDashes = nucNoDashes + nucleotides.charAt(i);
			}
		}
		return nucNoDashes;
	}
	
	//breaks string into 3's and saves them into array
	public static void listCodons(String[] codonSet, String nucNoDashes) { 
		String codon = ""; 
		for (int i = 0; i < nucNoDashes.length(); i++) {
			if (codon.length() < NUC_PER_CODON - 1) {
				codon = codon + nucNoDashes.charAt(i);
			}else {
				codon = codon + nucNoDashes.charAt(i);
				codonSet[i / NUC_PER_CODON] = codon;
				codon = "";
			}
		}
	}
	
	//checks if dna strand is a protein based on specifications
	public static boolean checkIfProtein(String[] codonSet, double[] massPercent){
		return (codonSet[0].equals("ATG") && checkIfValidStopCodon(codonSet) 
		&& codonSet.length >= MIN_NUM_CODONS && checkMassPercentageOfGC(massPercent));
	}
	
	//boolean casting for checkIfProtein (so I dont go crazy)
	public static boolean checkIfValidStopCodon(String[] codonSet) {
		return codonSet[codonSet.length - 1].equals("TAA") || 
		codonSet[codonSet.length - 1].equals("TAG") || 
		codonSet[codonSet.length - 1].equals("TGA");
	}
	
	//boolean casting for checkIfProtein (so I dont go crazy)
	public static boolean checkMassPercentageOfGC(double[] massPercent) {
		return (massPercent[1] + massPercent[2] >= PERCENT_OF_CG);
	}
}