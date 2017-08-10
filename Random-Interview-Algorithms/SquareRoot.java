/**
* Bakhshali approximation
*
* Method for finding an approximation to a square root of a non-negative real number.
*/
public class SquareRoot {
	public static void main(String[] args) {

		double num = 17;

		if(args.length == 1) {
			try {
				num = Double.parseDouble(args[0]);

				if (num < 0) {
					System.out.println("The input number can't be negative.");
					System.exit(0);
				}
				
			} catch(NumberFormatException e) {
				System.out.println("The input argument is not a number.");
				System.exit(0);
			} catch (Exception e) {
				System.out.println("Unexpected error occurred. Message: " + e);
			    System.exit(0);
		    }
		}

		System.out.println("Square root of " + num + " is " + sqrt(num));
	}

	private static double sqrt(double num) {
		int perfectSquare 		= 0;
		int perfectSquareRoot 	= 0;

		// nearest perfect square
		for (int i = (int) num; i > 0; i--) {
			for(int j = 1; j < i; j++) {
				if (j*j == i) {
					perfectSquare = i;
					perfectSquareRoot = j;
					break;
				}
			}

			if (perfectSquare > 0)
				break;
		}
		//System.out.println("Perfect square: " + perfectSquare);

		double d = num - (perfectSquareRoot * perfectSquareRoot);
		double P = d / (2 * perfectSquareRoot);
		double A = perfectSquareRoot + P;
		double sqrt = A - ((P * P)/(2 * A));

		return sqrt;
	} 
}