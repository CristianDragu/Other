import java.util.List;
import java.util.Stack;

public class p2 {
	
	public static int timp = 0;
	
	public static Stack<Cell> cellStack = new Stack<Cell>();
	
	public static void DFS(Cell cell) {
		cell.setInitTime(timp++);
		cell.setColor(Cell.Color.GRAY);
		List<Cell> neighbors = cell.getDependentCells();
		
		for(Cell c : neighbors){
			if(c.getColor().equals(Cell.Color.WHITE)){
				DFS(c);
			}
		}
		
		cell.setColor(Cell.Color.BLACK);
		cell.setFinishTime(timp++);
		cellStack.add(cell);
	}
	
	public static void main(String[] args) {
		Reader reader = new Reader("date.in");
		List<Cell> cells = reader.parse();
		
		//TODO: Afisati parcurgerea celulelor.
		for(Cell cell : cells){
			if(cell.getColor().equals(Cell.Color.WHITE)){
				DFS(cell);
			}
		}
		
		for(Cell cell : cellStack)
			System.out.println(cell + " " + cell.getInitTime() + " " + cell.getFinishTime());
	}
}
