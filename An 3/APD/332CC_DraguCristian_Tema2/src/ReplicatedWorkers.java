import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.io.PrintWriter;
import java.io.RandomAccessFile;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Set;
import java.util.StringTokenizer;


class PartialSolutionReduction {
	public String docName;
	public HashMap<Integer, Integer> hashPartial;
	public ArrayList<String> cuvinteMaximalePartial;
	public static HashMap<Integer, Integer> hash = new HashMap<Integer, Integer>();
	public static ArrayList<String> cuvinteMaximale = new ArrayList<String>();
	
	public PartialSolutionReduction(String docName, HashMap<Integer, Integer> hashPartial, ArrayList<String> cuvinteMaximalePartial) {
		this.docName = docName;
		this.hashPartial = hashPartial;
		this.cuvinteMaximalePartial = cuvinteMaximalePartial;
	}
	
	public String toString() {
		return "" + this.docName;
	}
}

class PartialSolution {
	public String docName;
	public long offset;
	public int dimFragment;
	public HashMap<Integer, Integer> hashPartial;
	public ArrayList<String> cuvinteMaximalePartial;
	public static ArrayList<HashMap<Integer, Integer>> hash = new ArrayList<HashMap<Integer, Integer>>();
	public static ArrayList<ArrayList<String>> cuvinteMaximale = new ArrayList<ArrayList<String>>();
	
	public PartialSolution(String docName, long offset, int dimFragment) {
		this.docName = docName;
		this.offset = offset;
		this.dimFragment = dimFragment;
		this.hashPartial = new HashMap<Integer, Integer>();
		this.cuvinteMaximalePartial = new ArrayList<String>();
	}
	
	public String toString() {
		return "" + this.offset;
	}
}

class WorkerRed extends Thread {
	WorkPool_Reduction wp;

	public WorkerRed(WorkPool_Reduction workpool) {
		this.wp = workpool;
	}

	void processPartialSolution(PartialSolutionReduction ps) throws IOException {
		
		synchronized (PartialSolutionReduction.hash) {
			Set<Integer> set = ps.hashPartial.keySet();
			for(Integer i : set)
				if(PartialSolutionReduction.hash.containsKey(i))
					PartialSolutionReduction.hash.put(i, PartialSolutionReduction.hash.get(i) + ps.hashPartial.get(i));
				else
					PartialSolutionReduction.hash.put(i, ps.hashPartial.get(i));
		}
		
		synchronized (PartialSolutionReduction.cuvinteMaximale) {
			for(String s : ps.cuvinteMaximalePartial)
				if(!PartialSolutionReduction.cuvinteMaximale.isEmpty()){
					if(s.length() > PartialSolutionReduction.cuvinteMaximale.get(0).length()){
						PartialSolutionReduction.cuvinteMaximale.clear();
						PartialSolutionReduction.cuvinteMaximale.add(s);
					}
					else if(s.length() == PartialSolutionReduction.cuvinteMaximale.get(0).length()){
						if(!PartialSolutionReduction.cuvinteMaximale.contains(s)) 
							PartialSolutionReduction.cuvinteMaximale.add(s);
					}
				}
				else{
					PartialSolutionReduction.cuvinteMaximale.add(s);
				}
		}
		
	}
	
	public void run() {
		while (true) {
			PartialSolutionReduction ps = wp.getWork();
			if (ps == null)
				break;
			try {
				processPartialSolution(ps);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}

class Worker extends Thread {
	WorkPool_Map wp;
	byte c1, c2;
	String separators = ";:/?~\\.,><~`[]{}()!@#$%^&-_+'=*\"|\t\n\r ";

	public Worker(WorkPool_Map workpool) {
		this.wp = workpool;
	}

	void processPartialSolution(PartialSolution ps) throws IOException {
		ps.hashPartial.clear();
		ps.cuvinteMaximalePartial.clear();
		File file = new File(ps.docName);
		RandomAccessFile raf = new RandomAccessFile(file, "r");
		
		if(ps.offset != 0){
			raf.seek(ps.offset - 1);
			c1 = (byte) raf.read();
			raf.seek(ps.offset);
			c2 = (byte) raf.read();
			if(separators.indexOf((char) c1) == -1 && separators.indexOf((char) c2) == -1){
				while(ps.offset < ps.offset + ps.dimFragment && separators.indexOf((char) c2) == -1){
					ps.offset++;
					ps.dimFragment--;
					raf.seek(ps.offset);
					c2 = (byte) raf.read();
				}
			}
		}
		if(ps.offset + ps.dimFragment < file.length()){
			raf.seek(ps.offset + ps.dimFragment - 1);
			c1 = (byte) raf.read();
			raf.seek(ps.offset + ps.dimFragment);
			c2 = (byte) raf.read();
			if(separators.indexOf((char) c1) == -1 && separators.indexOf((char) c2) == -1){
				while(ps.offset < file.length() && separators.indexOf((char) c2) == -1){
					ps.dimFragment++;
					raf.seek(ps.offset + ps.dimFragment);
					c2 = (byte) raf.read();
				}
			}
		}
		
		byte[] bytes = new byte[ps.dimFragment];
		raf.seek(ps.offset);
		raf.readFully(bytes);
		
		String fragment = new String(bytes);
		String aux;
		StringTokenizer token = new StringTokenizer(fragment, separators);
		
		while(token.hasMoreTokens()){
			aux = token.nextToken();
			if(aux.length() > 0){
				if(ps.hashPartial.containsKey(aux.length()))
					ps.hashPartial.put(aux.length(), ps.hashPartial.get(aux.length()) + 1);
				else
					ps.hashPartial.put(aux.length(), 1);
				if(ps.cuvinteMaximalePartial.isEmpty())
					ps.cuvinteMaximalePartial.add(aux);
				else
					if(aux.length() > ps.cuvinteMaximalePartial.get(0).length()){
						ps.cuvinteMaximalePartial.clear();
						ps.cuvinteMaximalePartial.add(aux);
					}
					else if(aux.length() == ps.cuvinteMaximalePartial.get(0).length())
						ps.cuvinteMaximalePartial.add(aux);
			}
		}
		
		synchronized(PartialSolution.hash){
			PartialSolution.hash.add(ps.hashPartial);
			PartialSolution.cuvinteMaximale.add(ps.cuvinteMaximalePartial);
		}
		
		raf.close();
		
	}
	
	public void run() {
		while (true) {
			PartialSolution ps = wp.getWork();
			if (ps == null)
				break;
			try {
				processPartialSolution(ps);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}

class DataOut {
	public String docName;
	public double rang;
	public int dimMax;
	public int maxWords;
	public int position;
	
	public DataOut(String docName, double rang, int dimMax, int maxWords, int position){
		this.docName = docName;
		this.rang = rang;
		this.dimMax = dimMax;
		this.maxWords = maxWords;
		this.position = position;
	}
	
}

public class ReplicatedWorkers {
	
	public static long fib(int n) {
        if (n <= 1) 
        	return n;
        else 
        	return fib(n-1) + fib(n-2);
    }

	public static void main(String args[]) throws Exception {
		try (FileReader fileReader = new FileReader(args[1]);
			
			LineNumberReader lineNumberReader = new LineNumberReader(fileReader)) {
			String fileName;
			PartialSolution ps;
			PartialSolutionReduction psr;
			int dimFragment = Integer.parseInt(lineNumberReader.readLine());
			int numberDocs = Integer.parseInt(lineNumberReader.readLine());
			int processors = Integer.parseInt(args[0]);
			long dimFile, numberOfFragments;
			WorkPool_Map workpoolMap;
			WorkPool_Reduction workpoolRed;
			ArrayList<Worker> workers;
			ArrayList<WorkerRed> workersRed;
			ArrayList<DataOut> dataOut = new ArrayList<DataOut>();
			double rankSum;
			int wordsCounter;
			int position = 0;
			DecimalFormat numberFormat = new DecimalFormat("#.00");
			numberFormat.setRoundingMode(RoundingMode.DOWN);
			long time1 = System.currentTimeMillis();
			for(int j = 0; j < numberDocs; j++){
				workpoolMap = new WorkPool_Map(processors);
				workers = new ArrayList<Worker>();
				fileName = lineNumberReader.readLine();
				File file = new File(fileName);
				dimFile = file.length();
				numberOfFragments = dimFile / dimFragment;
				for(int i = 0; i < numberOfFragments; i++){
					ps = new PartialSolution(fileName, i * dimFragment, dimFragment);
					workpoolMap.putWork(ps);
				}
				ps = new PartialSolution(fileName, numberOfFragments * dimFragment, (int) (dimFile - numberOfFragments * dimFragment));
				workpoolMap.putWork(ps);
				
				for(int i = 0; i < processors; i++)
					workers.add(new Worker(workpoolMap));
				for(int i = 0; i < processors; i++)
					workers.get(i).start();
				for(int i = 0; i < processors; i++)
					workers.get(i).join();
				
				workpoolRed = new WorkPool_Reduction(processors);
				workersRed = new ArrayList<WorkerRed>();
				
				for(int i = 0; i < numberOfFragments + 1; i++){
					psr = new PartialSolutionReduction(fileName, PartialSolution.hash.get(i), PartialSolution.cuvinteMaximale.get(i));
					workpoolRed.putWork(psr);
				}
				
				for(int i = 0; i < processors; i++)
					workersRed.add(new WorkerRed(workpoolRed));
				for(int i = 0; i < processors; i++)
					workersRed.get(i).start();
				for(int i = 0; i < processors; i++)
					workersRed.get(i).join();
				
				Set<Integer> set = PartialSolutionReduction.hash.keySet();
				
				rankSum = 0.0f;
				wordsCounter = 0;
				for(Integer i : set){
					rankSum += (fib(i + 1) * PartialSolutionReduction.hash.get(i));
					wordsCounter += PartialSolutionReduction.hash.get(i);
				}
				rankSum /= (double)wordsCounter;
				if(!PartialSolutionReduction.cuvinteMaximale.isEmpty())
					dataOut.add(new DataOut(fileName, Double.parseDouble(numberFormat.format(rankSum)), 
							PartialSolutionReduction.cuvinteMaximale.get(0).length(), 
							PartialSolutionReduction.cuvinteMaximale.size(), position++));
				else
					dataOut.add(new DataOut(fileName, rankSum, 0, 0, position++));
				
				PartialSolution.cuvinteMaximale = new ArrayList<ArrayList<String>>();
				PartialSolution.hash = new ArrayList<HashMap<Integer, Integer>>();
				PartialSolutionReduction.cuvinteMaximale = new ArrayList<String>();
				PartialSolutionReduction.hash = new HashMap<Integer, Integer>();
			}
			
			Collections.sort(dataOut, new Comparator<DataOut>() {

				@Override
				public int compare(DataOut o1, DataOut o2) {
					if(o1.rang < o2.rang)
						return 1;
					else if(o1.rang == o2.rang)
						if(o1.dimMax < o2.dimMax)
							return 1;
						else if(o1.dimMax == o2.dimMax)
							if(o1.maxWords < o2.maxWords)
								return 1;
							else if(o1.position > o2.position)
								return 1;
					return -1;
				}
				
			});
			long time2 = System.currentTimeMillis();
			System.out.println(time2 - time1);
			PrintWriter writer = new PrintWriter(args[2]);
			for(DataOut d : dataOut){
				//System.out.println(d.docName + ";" + numberFormat.format(d.rang) + ";" + "[" + d.dimMax + "," + d.maxWords + "]");
				writer.println(d.docName + ";" + numberFormat.format(d.rang) + ";" + "[" + d.dimMax + "," + d.maxWords + "]");
			}
			writer.close();
			fileReader.close();
		}
		
	}
	
}