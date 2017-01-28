/**
 * Proiectarea Algoritmilor, 2014
 * Lab 3: Greedy si Programare Dinamica
 * Task 1: Planificarea temelor
 *
 * @author 	Sorina Sandu, Mihai Bivol, Alex Olteanu
 * @email	alexandru.olteanu@cs.pub.ro
 */

import java.io.File;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

import com.sun.xml.internal.bind.v2.runtime.unmarshaller.XsiNilLoader.Array;

public class HomeworkPlanner {

	public static final int NO_TESTS = 3;
	public int[] lastDay = new int[NO_TESTS];					// ultima zi in care se pot rezolva teme
	public Homework[][] homeworks = new Homework[NO_TESTS][];	// lista de teme

	public static void main(String[] args) {
		HomeworkPlanner hp = new HomeworkPlanner();
		hp.readData("date.in");
		hp.test();
	}

	/**
	 * for each of the tests
	 * find the longest common substring
	 */
	private void test () {
		/* for each of the tests */
		for (int test=0; test<NO_TESTS; test++) {

			System.out.print("Pentru temele ");
			printv(homeworks[test]);
			System.out.println();

			Homework[] solutie = chooseHomeworks(homeworks[test], lastDay[test]);
			int i=0;
			for (Homework h:solutie) {
				i++;
				System.out.println("Ziua "+i+": "+h);
			}

		}
	}

	/**
	 * Intoarce planificarea temelor pentru un set de task-uri
	 * @homeworks: vector cu task-urile ce trebiue rezolvate
	 * @lastDay: ultima zi in care pot fi rezolvate teme
	 */
	public boolean contains(Homework[] planning, Homework homework, int hi){
		for(int i = 0; i < hi; i++){
			Homework h = new Homework(planning[i].deadline, planning[i].points);
			if(h.equals(homework))
				return true;
		}
		return false;
	}
	
	Homework[] chooseHomeworks(Homework[] homeworks, int lastDay)
	{
		//adaugati in planning pe indicele i, tema care se va rezolva
		//in ziua i. Daca nu se va rezolva nicio tema, lasati null
		Homework[] planning = new Homework[lastDay+1];
		Homework[] homeworksCopy = new Homework[homeworks.length];
		int hi = 0;
		int ziua = lastDay;
		for (Homework h: homeworks)
			homeworksCopy[hi++] = new Homework(h.deadline, h.points);

		//TODO porniti planificarea de la ultima zi si adaugati tema care
		//maximizeaza numarul total de puncte obtinute.
		Arrays.sort(homeworksCopy);
		/*for(Homework homework: homeworksCopy){
			System.out.println(homework);
		}*/
		
		hi = 0;
		while(ziua >= 0){
			for(Homework homework: homeworksCopy){
				if(homework.deadline <= ziua){
					if(!contains(planning, homework, hi)){
						planning[hi++] = new Homework(homework.deadline, homework.points);
						ziua--;
						break;
					}
				}
			}
		}

		return planning;
	}

	/**
	 * Function to read all the tests
	 * @param filename
	 */
	private void readData ( String filename ) {
		Scanner scanner = null;

		/* you should use try-catch for proper error handling! */
		try {

			scanner = new Scanner(new File(filename));

			for (int i=0;i<NO_TESTS;i++){

				/* read the array in which to look for data */
				lastDay[i] = scanner.nextInt();		// ultima zi in care se pot rezolva teme
				int n = scanner.nextInt();			// numar de teme
				homeworks[i] = new Homework[n];
				for (int j=0;j<n;j++) {
					homeworks[i][j] = new Homework(scanner.nextInt(), scanner.nextInt());
				}

			}

		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			/* trebuie sa inchidem buffered reader-ul */
			try {
				if (scanner != null) scanner.close();
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}

	/**
	 * Functie ce afiseaza pe ecran un vector
	 */
	private void printv(Object[] v) {
		System.out.print("{ ");
		for (Object elem:v){
			if (elem==null) System.out.println("null");
			else System.out.print(elem+" ");
		}
		System.out.print("}");
	}

	private class Homework implements Comparable{
		int deadline;
		int points;

		public Homework(int deadline, int points) {
			super();
			this.deadline = deadline;
			this.points = points;
		}

		@Override
		public String toString() {
			return "(d:" + deadline + ", p:" + points + ") ";
		}

		public int compareTo(Object o) {
			Homework h = (Homework) o;
			if(h.deadline == this.deadline) return h.points - this.points;
			return (h.deadline -  this.deadline);
		}

	}
}
