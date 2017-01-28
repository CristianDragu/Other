import java.util.LinkedList;
import java.util.List;

public class Kahn {

	public static boolean areMuchii(List<Cell> cells, Cell u){
		for(Cell c : cells){
			if(c.getDependentCells().contains(u))
				return true;
		}
		return false;
	}
	
	public static void main(String[] args){
		Reader reader = new Reader("date.in");
		List<Cell> cells = reader.parse();
		
		LinkedList<Cell> list = new LinkedList<Cell>();
		LinkedList<Cell> izolate = new LinkedList<Cell>();
		for(int i = 0; i < cells.size(); i++){
			if(!areMuchii(cells, cells.get(i))){
				izolate.add(cells.get(i));
			}
		}
		
		while(!izolate.isEmpty()){
			Cell u = izolate.poll();
			list.add(u);
			
			for(int i = 0; i < u.getDependentCells().size(); i++){
				u.getDependentCells().remove(u.getDependentCells().get(i));
				if(!areMuchii(cells, u.getDependentCells().get(i))){
					izolate.add(u.getDependentCells().get(i));
				}
			}
		}
	}
	
}
