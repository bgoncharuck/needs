void insertionSort(int array[], long size) {
	long externalCount = 0;
	long internalCount = 0;
	long temp = 0;
	if(size < 100000)
		for(externalCount = size; externalCount > 0; externalCount--) {
			internalCount = externalCount;
			while(internalCount < size && array[internalCount] < array[internalCount - 1]) {
				swapInt(&array[internalCount], &array[internalCount - 1]);
				internalCount += 1;
			}
		}
	else if(size >= 100000)
		for(externalCount = 1; externalCount < size; externalCount++) {
			temp = array[externalCount];
			internalCount = externalCount - 1;
			while(internalCount >= 0  && array[internalCount] > temp) {
				array[internalCount + 1] = array[internalCount];
				internalCount -= 1;
			}
			array[internalCount+1] = temp;
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
