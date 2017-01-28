public class p2 {

	public static void main(String[] args){
		
		int cest = 3, mest = 3, cvest = 0, mvest = 0;
		
		// euristica inadmisibila
		while(cest > 0 || mest > 0){
			if(cest > mest || cvest > mvest){
				System.out.println("Ai dat gres!");
				break;
			}
			if(cest <= 1){
				System.out.println("S-a facut mutarea");
				break;
			}
			else{
				cest --;
				cvest ++;
				System.out.println("canibali: " + cest + " " + cvest);
			}
			if(mest <= 1){
				System.out.println("S-a facut mutarea");
				break;
			}
			else{
				mest --;
				mvest ++;
				System.out.println("misionari: " + mest + " " + mvest);
			}
		}
		
	}
	
}
