import java.util.ArrayList;
import java.util.List;

/**
 * 
 * Reprezentarea unei celule dintr-un spreadsheet.
 * 
 * @author Claudia Cardei
 *
 */
public class Cell {
	
	/**
	 * Culorile ce le poate avea o celula in timpul unei parcurgeti DFS.
	 */
	public static enum Color {
		WHITE, GRAY, BLACK
	}
	
	/**
	 * Pozitia celulei in cadrul spreadsheet-ului.
	 */
	private final String position;
	
	/*
	 * Celulele care depind de celula curenta.
	 */
	private List<Cell> dependentCells;
	
	/**
	 * Atribute folositoare in cadrul DFS-ului.
	 */
	private Color color;
	private int initTime;
	private int finishTime;
	
	public Cell(String position) {
		this.position = position;
		dependentCells = new ArrayList<Cell>();
		
		color = Color.WHITE;
		initTime = finishTime = 0;
	}
	
	public List<Cell> getDependentCells() {
		return dependentCells;
	}
	
	public void setColor(Color color) {
		this.color = color;
	}
	
	public Color getColor() {
		return color;
	}
	
	public void setInitTime(int time) {
		this.initTime = time;
	}
	
	public int getInitTime() {
		return initTime;
	}
	
	public void setFinishTime(int time) {
		this.finishTime = time;
	}
	
	public int getFinishTime() {
		return finishTime;
	}

	@Override
	public String toString() {
		return position;
	}
}
