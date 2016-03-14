import java.util.LinkedList;

class WorkPool_Map {
	int nThreads;
	int nWaiting = 0;
	public boolean ready = false; 
	
	LinkedList<PartialSolution> tasks = new LinkedList<PartialSolution>();

	public WorkPool_Map(int nThreads) {
		this.nThreads = nThreads;
	}

	public synchronized PartialSolution getWork() {
		if (tasks.size() == 0) {
			nWaiting++;
			if (nWaiting == nThreads) {
				ready = true;
				notifyAll();
				return null;
			} 
			else {
				while (!ready && tasks.size() == 0) {
					try {
						this.wait();
					} catch(Exception e) {e.printStackTrace();}
				}
				if (ready)
				    return null;
				nWaiting--;	
			}
		}
		return tasks.remove();

	}

	synchronized void putWork(PartialSolution sp) {
		//System.out.println("WorkPool - adaugare task: " + sp);
		tasks.add(sp);
		this.notify();
	}

}


class WorkPool_Reduction {
	int nThreads;
	int nWaiting = 0;
	public boolean ready = false;
	
	LinkedList<PartialSolutionReduction> tasks = new LinkedList<PartialSolutionReduction>();

	public WorkPool_Reduction(int nThreads) {
		this.nThreads = nThreads;
	}

	public synchronized PartialSolutionReduction getWork() {
		if (tasks.size() == 0) {
			nWaiting++;
			if (nWaiting == nThreads) {
				ready = true;
				notifyAll();
				return null;
			}
			else {
				while (!ready && tasks.size() == 0) {
					try {
						this.wait();
					} catch(Exception e) {e.printStackTrace();}
				}
				if (ready)
				    return null;
				nWaiting--;
			}
		}
		return tasks.remove();
	}

	synchronized void putWork(PartialSolutionReduction sp) {
		//System.out.println("WorkPoolRed - adaugare task: " + sp);
		tasks.add(sp);
		this.notify();
	}
		
}