
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
