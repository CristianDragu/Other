import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws FileNotFoundException{
		
		Scanner br = new Scanner(new FileInputStream("adunare.in"));
		long a = br.nextLong();
		long b = br.nextLong();
		long sum = a + b;
		
		br.close();
		
		PrintWriter pr = new PrintWriter("adunare.out");
		pr.write(sum + "\n");
		pr.close();
		
	}
	
}
