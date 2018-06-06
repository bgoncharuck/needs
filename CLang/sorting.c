#define sortCounting(arr, size, range) do { \
	size_t count[range+1], i, j, k; \
	for(i = 0; i <= range; i++) count[i] = 0; \
	for(i = 0; i < size; i++) count[arr[i]]++; \
	for(j = 0, i = 0; j <= range; j++) \
		for(k = 0; k < count[j]; k++, i++) \
			arr[i] = j; \
} while(0)

#define sortCountingStable(arr, size, range) do { \
	long tmp[size]; \
	size_t count[range+1], i; \
	for(i = 0; i <= range; i++) count[i] = 0; \
	for(i = 0; i < size; i++) count[arr[i]]++; \
	for(i = 1; i <= range; i++) count[i] += count[i - 1]; \
	for(i = 0; i < size; i++) { \
		count[arr[i]]--; \
		tmp[count[arr[i]]] = arr[i]; \
	} \
	for(i = 0; i < size; i++) arr[i] = tmp[i]; \
} while(0)

/* Needs list realization */
void sortDLListDouble(DL_list* list) {
	if(list->head == NULL)
		return;
	const size_t listSize = list->size;
	typeof(list->head->data) unsorted[listSize];
	DLNode* tempNode = NULL;
	for(size_t i = 0; i < listSize; i++) {
		tempNode = remFirstDLNode(list);
		unsorted[i] = tempNode->data;
		freeDLNode(tempNode);
	}
	sortComb(unsorted, listSize);
	for(size_t i = 0; i < listSize; i++) {
		tempNode = newDLNodeDat(unsorted[i]);
		addLastDLNode(list, tempNode);
	}
	tempNode = NULL;
}


/* Needs list realization */
#define sortBucketDouble(arr, arraySize) do { \
	DL_list buckets[arraySize]; \
	DLNode* tempNode = NULL; \
	for (size_t i = 0; i < arraySize; i++) \
		DLList_constructor(&buckets[i]); \
	for (size_t i = 0; i < arraySize; i++) { \
		size_t j = (size_t) arraySize * arr[i]; \
		DLNode* newNode = newDLNodeDat(arr[i]); \
		addFirstDLNode(&buckets[j], newNode); \
	} \
	for (size_t i = 0; i < arraySize; i++) \
		sortDLList(&buckets[i]); \
	for (size_t i = 0, j = 0; i < arraySize; i++) { \
		while (buckets[i].size > 0) { \
			tempNode = remFirstDLNode(&buckets[i]); \
			arr[j++] = tempNode->data; \
			freeDLNode(tempNode); \
		} \
	} \
} while(0)

#define sortRadixLSD(arr, size, num, base) do { \
	/* Sort the numbers beginning with least-significant digit */ \
	/* pos = 1, 10, 100, 1000, ... */ \
	for(size_t pos = 1; pos <= (size_t) pow(base, num); pos *= base) { \
		typeof(arr[0]) res[size]; \
		size_t count[base]; \
		for(int i = 0 ; i < base; i++) count[i] = 0; \
		/* counting sort */ \
		for (size_t i = 0; i < size; i++) { \
			res[i] = 0; \
			size_t digit = (arr[i] / pos) % base; \
			count[digit]++; \
		} \
		for (size_t i = 1; i < base; i++) \
			count[i] += count[i - 1]; \
		for (long i = size-1; i >= 0; i--) { \
			size_t digit = (arr[i] / pos) % base; \
			count[digit]--; \
			res[count[digit]] = arr[i]; \
		} \
		for (size_t i = 0; i < size; i++) \
			arr[i] = res[i]; \
	} \
} while(0)

void sortStringRadixLSD(char* str[], long size, long num) {
	int english26 = 26;
	char * tmp[size];
	for (long pos = num - 1; pos >= 0; pos--) {
		int count[english26];
		for (int i = 0; i < size; i++) {
			int key = tolower(str[i][pos]) - 'a'; // 97
			count[key]++;
		}
		for (int i = 1; i < english26; i++)
			count[i] += count[i - 1];
		for (int i = size - 1; i >= 0; i--) {
			int key = tolower(str[i][pos]) - 'a';
			count[key]--;
			tmp[count[key]] = str[i];
		}
		for (int i = 0; i < size; i++) {
			str[i] = tmp[i];
		}
	}
}

#define ___Merge(arr, left, mid, right) do { \
	int * tmp = malloc(sizeof(arr[0]) * right-left+1); \
	size_t pos = 0; \
	size_t leftPos = left; \
	size_t rightPos = mid + 1; \
	while(leftPos <= mid && rightPos <= right)  \
		if(arr[leftPos] < arr[rightPos]) \
				tmp[pos++] = arr[leftPos++]; \
		else \
				tmp[pos++] = arr[rightPos++]; \
	while(leftPos <= mid) \
		tmp[pos++] = arr[leftPos++]; \
	while(rightPos <= right) \
		tmp[pos++] = arr[rightPos++]; \
	for(int i = 0; i < pos; i++) \
		arr[left + i] = tmp[i]; \
	free(tmp); \
} while(0)

void sortMerge(void * arr, const char dataType, size_t left, size_t right) {
	if(left < right) {
		size_t mid = (left + right) / 2;
		sortMerge(arr, dataType, left, mid);
		sortMerge(arr, dataType, mid+1, right);

		/*TODO*/
		// another method to sort any basic datatype
		if(dataType == 'c') {
			char * ptr = (char *) arr;
			___Merge(ptr, left, mid, right);
		}
		else if(dataType == 'i') {
			int * ptr = (int *) arr;
			___Merge(ptr, left, mid, right);
		}
		else if(dataType == 'd') {
			double * ptr = (double *) arr;
			___Merge(ptr, left, mid, right);
		}
		else if(dataType == 'l') {
			long * ptr = (long *) arr;
			___Merge(ptr, left, mid, right);
		}
		else if(dataType == 'f') {
			float * ptr = (float *) arr;
			___Merge(ptr, left, mid, right);
		}
		else if(dataType == 'u') {
			unsigned * ptr = (unsigned *) arr;
			___Merge(ptr, left, mid, right);
		}
		else fprintf(stderr, "invalid argument in sortMerge()");
	}
}

#define sortShell(arr, size) do { \
	size_t step = 1, i, j; \
	while(step <= size/3) \
		step = step*3 + 1; \
	while(step > 0) { \
		for(i = step; i < size; i++) \
			for(j = i; j > step - 1 && arr[j] <= arr[j-step]; j -= step) \
				swap(&arr[j], &arr[j-step]); \
		step /= 3; \
	} \
} while(0)

#define sortBubble(arr, size) do { \
	int swapped = 1; \
	for(size_t i = 0; i < size - 1; i++) { \
		swapped = 0; \
		 for(size_t j = 0; j < size - i - 1; j++) \
		 	if(arr[j] > arr[j+1]) { \
				swap(&arr[j], &arr[j+1]); \
				swapped = 1; \
			} \
	} \
} while(0)

#define sortShaker(arr, size) do { \
	int swapped = 1; \
	size_t left = 0, right = size, i;\
	do { \
		swapped = 0; \
		for(i = left; i < right; i++) \
			if(arr[i] > arr[i+1]) { \
				swap(&arr[i], &arr[i+1]); \
				swapped = 1; \
			} \
		right--; \
		for(i = right; i > left; i--) \
			if(arr[i] < arr[i-1]) { \
				swap(&arr[i], &arr[i-1]); \
				swapped = 1; \
			} \
		left++; \
	} while(right > left && swapped); \
} while(0)

#define sortComb(arr, size) do { \
	int swapped = 1; \
	size_t gap = size, i; \
	while(gap != 1 && swapped) { \
		swapped = 0; \
		gap /= 1.247; \
		if(gap < 1) gap = 1; \
		for(i = 0; i < size-gap; i++) \
			if(arr[i] > arr[i+gap]) { \
				swap(&arr[i], &arr[i+gap]); \
				swapped = 1; \
			} \
	} \
} while(0)

#define sortSelection(arr, size) do { \
	size_t i, j, min; \
	for(i = 0; i < size - 1; i++) { \
		min = i; \
		for(j = i+1; j < size; j++) \
			if(arr[j] < arr[min]) \
				min = j; \
		if(min != i) \
			swap(&arr[min], &arr[i]); \
	} \
} while(0)

#define sortInsertion(arr, size) do { \
	for(size_t i = 1; i < size; i++) \
		for(size_t j = i; j > 0 && arr[j] < arr[j-1]; j--) \
			swap(&arr[j], &arr[j-1]); \
} while(0)


/*
*/
