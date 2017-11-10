void insertionSort(int array[], int size) {
	int externalCount = 0;
	int internalCount = 0;
	for(externalCount = 0; externalCount < size; externalCount++) {
		internalCount = externalCount;
		while((internalCount != 0) && (array[internalCount] < array[internalCount - 1])) {
			swapInt(&array[internalCount], &array[internalCount-1]);
			internalCount -= 1;
		}
	}
	return;
}

void selectionSort(int array[], int size) {
	int compareIndex = 0;
	int externalCount = 0;
	int internalCount = 0;
	for(externalCount = 0; externalCount < size; externalCount++) {
		compareIndex = externalCount;
		for(internalCount = externalCount + 1; internalCount < size; internalCount++)
		if(array[internalCount] < array[compareIndex])
		compareIndex = internalCount;
		swapInt(&array[externalCount], &array[compareIndex]);
	}
	return;
}
