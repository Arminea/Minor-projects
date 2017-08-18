/**
* BubbleSort is a sorting algorithm that repeatedly steps 
* through the list to be sorted, compares each pair of 
* adjacent items and swaps them if they are in the wrong order.
*
* It takes time O(n^2) - avarage and worst.
* It's a stable algorithm.
*/
public class BubbleSort extends Sort {

	/** Constructor */
	public BubbleSort() {
		super();
	}

	/** 
	* Constructor.
	*
	* @param arraySize - size of array of random number
	*/
	public BubbleSort(int arraySize) {
		super(arraySize);
	}

	/**
	* Overridden method for sorting numbers.
	*/
	@Override
	public void sortNumbers() {
		super.sortNumbers();

		int[] array = generateNumbers();
		printArray(array);

		boolean swapped;

		do {
			swapped = false;

			for(int i = 0; i < array.length-1; i++) {
				if(array[i] > array[i+1])  {
					int tmp = array[i+1];
					array[i+1] = array[i];
					array[i] = tmp;
					swapped = true;
				}
			}
		} while (swapped);

		printArray(array);
	}

}
