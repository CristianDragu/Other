import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;


/**
 * Parsarea unui fisier de intrare si construirea grafului.
 * Fisierul de intrare contine linii de forma:
 * H3 = ( E3 + F3 ) / 4
 * 
 * @author Claudia Cardei
 *
 */
public class Reader {
	
	public final String fileName;
	
	public Reader(String fileName) {
		this.fileName = fileName;
	}
	
	public List<Cell> parse() {
		Map<String, Cell> cells = new HashMap<String, Cell>();
		try {
			Scanner scanner = new Scanner(new File(fileName));
			while (scanner.hasNextLine()) {
				String formula = scanner.nextLine();
				String[] tokens = formula.split(" ");
				// Primul token este celula.
				Cell cell = null;
				if (!cells.containsKey(tokens[0])) {
					cell = new Cell(tokens[0]);
					cells.put(tokens[0], cell);
				} else  {
					cell = cells.get(tokens[0]);
				}
				
				for (int i = 1; i < tokens.length; i++) {
					if (tokens[i].length() == 2) {
						if (!cells.containsKey(tokens[i])) {
							cells.put(tokens[i], new Cell(tokens[i]));
						}
						
						cells.get(tokens[i]).getDependentCells().add(cell);
					}
				}
			}
			
		} catch (FileNotFoundException e) {
			System.err.println("Fisier inexistent!");
		}
		
		return new ArrayList<Cell>(cells.values());
	}
}
