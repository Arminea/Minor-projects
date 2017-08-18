import java.util.Random;

/**
* QuickSort is a Divide and Conquer algorithm. It is based on partitioning 
* of array of data into smaller arrays. One of them holds values smaller 
* than the specified value, pivot, and another array holds values greater 
* than the pivot value. Quick sort partitions an array and then calls 
* itself recursively twice to sort the two resulting subarrays.
*
* It takes time O(n^2), worst case, and O(n logn), average case.
* It's a unstable algorithm.
*/
public class QuickSort extends Sort {

	/** Constructor */
	public QuickSort() {
		super();
	}

	/** 
	* Constructor.
	*
	* @param arraySize - size of array of random number
	*/
	public QuickSort(int arraySize) {
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

		sort(array, 0, array.length - 1);

		printArray(array);
	}

	/**
	* Quicksort.
	*
	* @param array - array of numbers
	* @param low - index of the first element from the left
	* @param high - index of the first element from the right
	*/
	private void sort(int[] array, int low, int high) {
		if (low < high) {
		int pi = partition(array, low, high);

		// Recursively sort elements
		sort(array, low, pi - 1);
		sort(array, pi + 1, high);
		}
	}

	/**
	* Partitioning of array.
	*
	* @param array - array of numbers
	* @param low - index of the first element from the left
	* @param high - index of the first element from the right
	*/
	private int partition(int[] array, int low, int high) {
		int pivot = array[high];
		int i = low - 1;

		for (int j = low; j < high; j++) {
			if (array[j] <= pivot) {
				i++;
				swap(array, i, j);
			}
		}

		swap(array, i + 1, high);

		return i + 1;
	}
	/**
	* Swaps two elements of array.
	*
	* @param array - array of numbers
	* @param i - index of the first element 
	* @param j - index of the second element
	*/
	private void swap(int[] array, int i, int j) {
		int tmp = array[j];
		array[j] = array[i];
		array[i] = tmp;
	}
}
