import java.io.BufferedReader;
import java.io.FileReader;

public class Excursie {

	public static void main(String[] args){
		
		try{
			
			BufferedReader br = new BufferedReader(new FileReader("excursie.in"));
			String linie = br.readLine();
			String[] slinie = linie.split(" ");
			
			int n, g1, g2;
			
			n=Integer.parseInt(slinie[0]);
			g1=Integer.parseInt(slinie[1]);
			g2=Integer.parseInt(slinie[2]);
			
		} catch(Exception e){
			
		}
		
	}
	
}
