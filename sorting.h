void bubbleSort(int arr[], long size) {
	int swapped = 1;
	for(int i = 0; i < size - 1 && swapped; i++) {
		swapped = 0;
		for(int j = 0; j < size - i - 1; j++)
			if(arr[j] > arr[j+1]) {
				swap(&arr[j], &arr[j+1]);
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
			if (arr[i] > arr[i + 1]) {
				swap(&arr[i], &arr[i + 1]);
				swapped = 1;
			}
		}
		r--;
		for (int i = r; i > l; i--) {
			if (arr[i] < arr[i - 1]) {
				swap(&arr[i], &arr[i - 1]);
				swapped = 1;
			}
		}
		l++;
	} while (l < r && swapped);
}

void combSort(int arr[], long size) {
	long gap = size;
	int swapped = 1;
	while (gap != 1 && swapped) {
		swapped = 0;
		gap = gap / 1.247;
		if (gap < 1)
			gap = 1;
		for (long i = 0; i < size - gap; i++)
			if (arr[i] > arr[i + gap])
				swap(&arr[i], &arr[i + gap]);
		swapped = 1;
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
			swap(&arr[i], &arr[minIndex]);
		}
	}
}


void insertionSort(int arr[], long size) {
	if(size < 100000)
		for(long i = 1; i < size; i++)
		 	for(long j = i; j > 0 && arr[j] < arr[j-1]; j--)
				swap(&arr[j], &arr[j-1]);
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

void shellSort(int arr[], long size) {
	long h = 1;
	while (h <= size / 3)
		h = h * 3 + 1;
	while (h > 0) {
		for (int i = h; i < size; i++)
			for(int j = i; j > h - 1 && arr[j] <= arr[j-h]; j -= h)
				swap(&arr[j-h], &arr[j]);
		h /= 3;
	}
}
