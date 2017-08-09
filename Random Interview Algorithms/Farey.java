import java.util.TreeSet;

/**
 * Farey sequence is a sequence which is generated for order n. 
 * The sequence has all rational numbers in range [0/0 to 1/1] 
 * sorted in increasing order such that the denominators are 
 * less than or equal to n and all numbers are in reduced forms.
 *
 * Program accepts one argument - order of sequence. If there is
 * no argument, default order value will be 5.
 * 
 * Output is Farey sequence in the form of set of fractals.
 */
public class Farey {

	public static void main(String[] args) {
		int order = 5;
		
		if(args.length == 1) {
			try {
				order = Integer.parseInt(args[0]);
				
			} catch(NumberFormatException e) {
				System.out.println("The input argument is not a number.");
				System.exit(0);
			} catch (Exception e) {
				System.out.println("Unexpected error occurred. Message: " + e);
			    System.exit(0);
		    }
		}
		
		System.out.println(generateFareySeq(order));
	}
	
	/**
	 * Method generates fractal candidates. <i>Set</i> internally removes 
	 * duplicates therefore there will be no un-reduced fractals. 
	 * 
	 * @param order - order of sequence
	 * @return set of fractals
	 */
	private static TreeSet<Frac> generateFareySeq(int order) {
		TreeSet<Frac> set = new TreeSet<Frac>();
		
		for(int q = 1; q <= order; q++){
			for(int p = 0; p <= q; p++){
				set.add(new Frac(p, q));
			}
		}
		
		return set;
	}
	
	/**
	 * Fractal class.
	 */
	private static class Frac implements Comparable<Frac>{
		private int p; // numerator
		private int q; // denominator
		
		public Frac(int p, int q) {
			this.p = p;
			this.q = q;
		}
		
		@Override
		public String toString(){
			return p + "/" + q;
		}
 
		@Override
		public int compareTo(Frac o){
			return Double.compare((double)p / q, (double)o.p / o.q);
		}
	}

}
