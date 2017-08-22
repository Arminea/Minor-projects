/**
* MergeSort is a Divide and Conquer algorithm. Algorithm has two steps.
* 1. Divide the unsorted list into n sublists, each containing 1 element 
*	(a list of 1 element is considered sorted).
* 2. Repeatedly merge sublists to produce new sorted sublists until there 
*	is only 1 sublist remaining. This will be the sorted list.
*
* It takes time O(n logn) - avarage and worst.
* It's a stable algorithm.
*/
public class MergeSort extends Sort {

	/** Constructor */
	public MergeSort() {
		super();
	}

	/** 
	* Constructor.
	*
	* @param arraySize - size of array of random number
	*/
	public MergeSort(int arraySize) {
		super(arraySize);
	}

	/**
	* Overridden method for sorting numbers.
	*/
	@Override
	public void sortNumbers() {
		super.sortNumbers();
		System.out.println("-- " + this.getClass().getSimpleName() + " --");

		int[] array = generateNumbers();
		printArray(array, "Random array");

		sort(array, 0, array.length - 1);

		printArray(array, "Sorted array");
	}

	/**
	* Mergesort.
	*
	* @param array - array of numbers
	* @param low - index of the first element from the left
	* @param high - index of the first element from the right
	*/
	private void sort(int[] array, int low, int high) {
		if (low < high) {
			int middle = (low + high) / 2;

			sort(array, low, middle);			// sort the 1st part of array
			sort(array, middle + 1, high);		// sort the 2nd part of array
			merge(array, low, middle, high);	// merge both parts
		}
	}

	/**
	* Merges two subarrays.
	*
	* @param array - array of numbers
	* @param low - index of the first element from the left
	* @param middle - index of the element in the middle
	* @param high - index of the first element from the right
	*/
	private void merge(int[] array, int low, int middle, int high) {
		// starting position of both parts
		int p = low;
		int q = middle + 1;

		int[] tmpArray = new int[high - low + 1];
		int k = 0;

		for(int i = low; i <= high; i++) {
			if (p > middle)
				tmpArray[k++] = array[q++];
			else if (q > high)
				tmpArray[k++] = array[p++];
			else if (array[p] < array[q])
				tmpArray[k++] = array[p++];
			else
				tmpArray[k++] = array[q++];
		}

		// copy array
		for (int j = 0; j < k; j++) {
			array[low++] = tmpArray[j];
		}
	}
}