
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Proiectarea Algoritmilor, 2014
 * Lab 4: Backtracking si optimizari
 * Task 1: Sudoku - Simple Backtracking
 *
 * @author 	Stefan Ruseti
 * @email	stefan.ruseti@gmail.com
 */

public class P1 {

	public static int bktCounter = 0;
	public static int solutionCounter = 0;
    
    
	
	/**
	 * Intoarce true daca cifra adaugata la pozitia (row, column)
	 * nu contrazice cifrele deja completate
     * 
	 */
	public static boolean isValid(int[][] grid, int row, int column) {
		for (int i = 0; i < 9; i++)
            if (i != column && grid[row][i] != 0 && grid[row][i] == grid[row][column])
                return false;
		for (int i = 0; i < 9; i++)
            if (i != row && grid[i][column] != 0 && grid[i][column] == grid[row][column])
                return false;
        for (int i = (row / 3) * 3; i < (row / 3 + 1) * 3; i++)
            for (int j = (column / 3) * 3; j < (column / 3 + 1) * 3; j++)
                if ((i != row || j != column) && 
                        grid[i][j] != 0 && grid[i][j] == grid[row][column])
                    return false;
        
		return true;
	}

	/**
	 * Implementarea backtracking-ului simplu
	 * 
	 */
	public static void doBKT(int[][] grid, int row, int column) {

		bktCounter++; // incrementam numarul total de intrari in recursivitate

		// TODO 2: Implementarea algoritmului de backtracking simplu
		// TODO 3: Afisarea tuturor solutiilor gasite
		// TODO 4: Incrementarea variabilei solutionCounter pentru fiecare solutie
        
		if(row == 9){
		    printGrid(grid);
			solutionCounter++;
		}
		else{
				if(grid[row][column]!=0){
					if(column == 8)
						doBKT(grid, row + 1, 0);
					else
						doBKT(grid, row, column + 1);
					return;
				}
				for(int i = 1; i <= 9; i++){
					grid[row][column] = i;
					if(isValid(grid, row, column))
						if(column == 8)
							doBKT(grid, row + 1, 0);
						else
							doBKT(grid, row, column + 1);
				}
				grid[row][column] = 0;
		}
	}
    
    public static void printGrid(int[][] grid) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] == 0) System.out.print(" ");
                else System.out.print(grid[i][j]);
                System.out.print(" ");
            }
            System.out.println();
        }
        System.out.println();
    }

	public static void main(String[] args) {
        try {
            Scanner s = new Scanner(new File("sudoku.in"));
            int[][] grid = new int[9][9];
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    grid[i][j] = s.nextInt();
            bktCounter = 0;
            solutionCounter = 0;
            
            doBKT(grid, 0, 0);
            
            System.out.println("Numar de intrari in recursivitare :" + bktCounter);
            System.out.println("Numar de solutii gasite: " + solutionCounter);
            System.out.println();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(P1.class.getName()).log(Level.SEVERE, null, ex);
        }
    }


}
