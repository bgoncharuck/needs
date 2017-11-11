void bubbleSort(int arr[], long size) {
	int swapped = 1;
	for(int i = 0; i < size - 1 && swapped; i++) {
		swapped = 0;
		for(int j = 0; j < size - 1 - i; j++)
			if(arr[j + 1] < arr[j]) {
				swapInt(&arr[j+1], &arr[j]);
					swapped = 1;
			}
	}
}

void shakerSort(int arr[], long size) {
	long l = 0;
	long r = size - 1;
	int swapped = 1;
	do {
		swapped = 0;
		for (int i = l; i < r; i++) {
			if (arr[i + 1] < arr[i]) {
				swapInt(&arr[i], &arr[i + 1]);
				swapped = 1;
			}
		}
		r--;
		for (int i = r; i > l; i--) {
			if (arr[i] < arr[i - 1]) {
				swapInt(&arr[i], &arr[i - 1]);
				swapped = 1;
			}
		}
		l++;
	} while (l < r && swapped);
}

void combSort(int arr[], long size) {
	int swapped = 1;
	long gap = size;
	while (gap > 1 || swapped) {
		gap = gap * 10 / 13;
		if (gap < 1)
			gap = 1;
		swapped = 0;
		for (long i = 0, j = gap; j < size; i++, j++) {
			if (arr[i] > arr[j]) {
				swapInt(&arr[i], &arr[j]);
				swapped = 1;
			}
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
