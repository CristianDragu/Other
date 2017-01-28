
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Proiectarea Algoritmilor, 2014 Lab 4: Backtracking si optimizari Task 2:
 * Task 2 : Sudoku - Backtracking + AC-3
 *
 * @author Stefan Ruseti
 * @email	stefan.ruseti@gmail.com
 */
public class P2 {

    private static class Arc {

        public Cell c1;
        public Cell c2;

        public Arc(Cell c1, Cell c2) {
            this.c1 = c1;
            this.c2 = c2;
        }
    }

    public static int bktCounter = 0;
    public static int solutionCounter = 0;

    /**
     * Metoda care intoarce o copie deep (un ArrayList nou ce contine copii ale
     * obiectelor) a ArrayList-ului trimis ca parametru
     */
    public static ArrayList<Cell> makeListCopy(ArrayList<Cell> cells) {

        ArrayList<Cell> result = new ArrayList<Cell>(cells.size());
        for (Cell c : cells) {
            result.add((Cell) c.clone());
        }
        return result;
    }

    /**
     * Intoarce true daca valorile de pe casutele c1 si c2 sunt valide
     *
     */
    public static boolean areValid(Cell c1, Cell c2) {
        return !areRelated(c1, c2) || c1.getValue() != c2.getValue();
    }

    /**
     * Intoarce true daca (c1, c2) apartine listei de arce
     *
     */
    public static boolean areRelated(Cell c1, Cell c2) {
        if (c1.getRow() == c2.getRow()) {
            return true;
        }
        if (c1.getColumn() == c2.getColumn()) {
            return true;
        }
        if (c1.getRow() / 3 == c2.getRow() / 3
                && c1.getColumn() / 3 == c2.getColumn() / 3) {
            return true;
        }

        return false;
    }

    /**
     * Implementarea functiei de Verifica(Xk, Xm) - actualizeaza domeniul lui c1
     * si pastreaza valorile care au un corespondent in c2 care sa satisfaca
     * restrictiile - intoarce true daca domeniul variabilei c1 a suferit
     * modificari
     */
    public static boolean check(Cell c1, Cell c2) {
        boolean delete = false;

		// TODO 1: Pentru fiecare valoare din domeniul variabilei c1
        // verifica daca exista o valoare valida in domeniul lui c2
        for(Integer i : c1.getPossibleValues()){
        	boolean sterge = true;
        	for(Integer j : c2.getPossibleValues()){
        		Cell c11 = (Cell)c1.clone();
        		Cell c22 = (Cell)c2.clone();
        		c11.setValue(i);
        		c22.setValue(j);
        		if(areValid(c11, c22)){
        			sterge = false;
        		}
        	}
        	if(sterge == true){
        		c1.removeFromDomain(i);
        		delete = true;
        	}
        }
        
        return delete; // intoarcem true daca s-au sters valori
    }

    /**
     * Metoda care aplica agloritmul AC3 pe variabilele primite in lista cells
     * Intoarce true daca un domeniu al vreunei variabile a devenit gol
     */
    public static boolean doAC3(ArrayList<Cell> cells) {

        Queue<Arc> q = new LinkedList<Arc>();
        boolean empty = false;
        // TODO 2: Initializare coada cu multimea arcelor
        for(int i = 0; i < 81; i++)
        	for(int j = 0; j < 81; j++)
        		if(i != j && areRelated(cells.get(i), cells.get(j))){
        			q.add(new Arc(cells.get(i), cells.get(j)));
        		}
        
		// TODO 3: Cat timp mai exista arce de verificat in coada,
        // extrage primul arc si verifica domeniile folosind functia check de mai sus
        while(!q.isEmpty()){
        	Arc arc = q.poll();
        	if(check(arc.c1, arc.c2)){
        		if(arc.c1.getDomainSize() == 0){
        			return true;
        		}
        		for(Cell c : cells){
        			if(areRelated(c, arc.c1) && !c.equals(arc.c1) && !c.equals(arc.c2)){
        				q.add(new Arc(c, arc.c1));
        			}
        		}
        	}
        }
        
        return false;

    }

    /**
     * Implementarea backtracking + AC-3 simplu
     *
     */
    public static void doBKT(ArrayList<Cell> cells, int row, int column) {

        bktCounter++; // incrementam numarul total de intrari in recursivitate
        //TODO 4: Testam daca am completat tot si afisam solutia]
        
        boolean sem = true;
        for(int i = 0; i < 9; i++)
        	for(int j = 0; j < 9; j++)
        		if(cells.get(i * 9 + j).getValue() == 0){
        			sem = false;
        			break;
        		}
        if(sem == true && row == 9){
        	printGrid(cells);
        	solutionCounter++;
        }
        
        // Aplicam algoritmul AC3 pe variabilele din lista queens
        if (doAC3(cells)) {
            return;
        }

		// TODO 5: Aplicam backtracking pe valorile ramase in domeniul variabilei curente.
        // Atentie! va trebui sa folosim o copie a listei cells la intrarea in recursivitate.
        // Daca folosim direct functia setValue pe lista originala queens, la intoarcerea din
        // recursivitate vom pierde celelalte valori din domeniul variabilei pe care iteram.
        // Hint: folositi functia makeListCopy
        
        ArrayList<Cell> cellsCopy = (ArrayList<Cell>)cells.clone();
       
	        if(cellsCopy.get(row * 9 + column).getValue()!=0){
				if(column == 8)
					doBKT(cellsCopy, row + 1, 0);
				else
					doBKT(cellsCopy, row, column + 1);
				return;
			}
	        
	        for(Integer i : cellsCopy.get(row * 9 + column).getPossibleValues()){
	        	cellsCopy.get(row * 9 + column).setValue(i);
				if(column == 8)
					doBKT(cellsCopy, row + 1, 0);
				else
					doBKT(cellsCopy, row, column + 1);
	        }
	        if(column < 9)
	        	cellsCopy.set(row * 9 + column, new Cell(row, column));
    }

    public static void printGrid(ArrayList<Cell> cells) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (cells.get(i * 9 + j).getValue() == 0) {
                    System.out.print(" ");
                } else {
                    System.out.print(cells.get(i * 9 + j).getValue());
                }
                System.out.print(" ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void main(String[] args) {
        try {
            Scanner s = new Scanner(new File("sudoku.in"));
            ArrayList<Cell> cells = new ArrayList<Cell>(81);
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    int value = s.nextInt();
                    if (value == 0) {
                        cells.add(new Cell(i, j));
                    } else {
                        cells.add(new Cell(i, j, value));
                    }

                }
            }

            bktCounter = 0;
            solutionCounter = 0;

            doBKT(cells, 0, 0);

            System.out.println("Numar de intrari in recursivitare :" + bktCounter);
            System.out.println("Numar de solutii gasite: " + solutionCounter);
            System.out.println();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(P1.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
