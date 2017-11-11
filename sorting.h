void bubbleSort(int arr[], long size) {
	for(int i = 0; i < size - 1; i++) {
		int swapped = 0;
		for(int j = 0; j < size - 1 - i; j++)
			if(arr[j + 1] < arr[j]) {
				swapInt(&arr[j+1], &arr[j]);
					swapped = 1;
			}
	}
}

void insertionSort(int arr[], long size) {
	if(size < 100000)
		for(long i = 1; i < size; i++)
		 	for(long j = i; j > 0 && arr[j] < arr[j-1]; j--)
				swapInt(&arr[j], &arr[j-1]);
	else if(size >= 100000)
		for(long i = 1; i < size; i++) {
			long key = arr[i];
			long j = i - 1;
			while(j >= 0  && arr[j] > key) {
				arr[j + 1] = arr[j];
				j -= 1;
			}
			arr[j+1] = key;
		}
}

void selectionSort(int arr[], long size) {
	long tmp = (size > 100000) ? 1 : 0;
	for (long i = 0; i < size - tmp; i++) {
		long minIndex = i;
		for (long j = i + 1; j < size; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		if (i != minIndex) {
			swapInt(&arr[i], &arr[minIndex]);
		}
	}
}
