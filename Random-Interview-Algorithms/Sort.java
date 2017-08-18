import java.util.Random;
import java.util.Arrays;

/**
* 
*/
public class Sort {

	/** Default array size. */
	protected static final int ARRAY_SIZE_CONST = 50;

	/** Array size. */
	private int arraySize;

	/**
	* Constructor.
	*/
	public Sort() {
		this.arraySize = ARRAY_SIZE_CONST;
	}

	/** 
	* Constructor.
	*
	* @param arraySize - size of array of random number
	*/
	public Sort(int arraySize) {
		this.arraySize = arraySize;
	}


	public int[] generateNumbers() {
		int[] array = new int[this.arraySize];
		Random r = new Random();

	    for (int i = 0; i < this.arraySize; i++){
	    	array[i] = r.nextInt(100);
	    }

		return array;
	}

	public void sortNumbers() {
		System.out.println("The sorting of " + this.arraySize + " numbers started.");
	}

	public void printArray(int[] array) {
		System.out.println(Arrays.toString(array));
	}
}