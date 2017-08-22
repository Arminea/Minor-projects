import java.util.Random;
import java.util.Arrays;

/**
* Superclass.
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

    /**
    * Generates random numbers.
    */
	public int[] generateNumbers() {
		int[] array = new int[this.arraySize];
		Random r = new Random();

	    for (int i = 0; i < this.arraySize; i++){
	    	array[i] = r.nextInt(100);
	    }

		return array;
	}

    /**
    * Method will be overriden in inherited classes.
    */
	public void sortNumbers() {
		System.out.println("The sorting of " + this.arraySize + " numbers started.");
	}

    /**
    * Prints array.
    */
	public void printArray(int[] array, String title) {
		System.out.println(title);
		System.out.println(Arrays.toString(array));
	}
}
