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
	size_t left = 0; \
	size_t right = size; \
	do { \
		swapped = 0; \
		for(size_t i = left; i < right; i++) \
			if(arr[i] > arr[i+1]) { \
				swap(&arr[i], &arr[i+1]); \
				swapped = 1; \
			} \
		right--; \
		for(size_t i = right; i > left; i--) \
			if(arr[i] < arr[i-1]) { \
				swap(&arr[i], &arr[i-1]); \
				swapped = 1; \
			} \
		left++; \
	} while(right > left && swapped); \
} while(0)

#define sortComb(arr, size) do { \
	int swapped = 1; \
	size_t gap = size; \
	while(gap != 1 && swapped) { \
		swapped = 0; \
		gap /= 1.247; \
		if(gap < 1) gap = 1; \
		for(size_t i = 0; i < size-gap; i++) \
			if(arr[i] > arr[i+gap]) { \
				swap(&arr[i], &arr[i+gap]); \
				swapped = 1; \
			} \
	} \
} while(0)

#define sortSelection(arr, size) do { \
	for(size_t i = 0; i < size - 1; i++) { \
		size_t min = i; \
		for(size_t j = i+1; j < size; j++) \
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
	size_t step = 1; \
	while(step <= size/3) \
		step = step*3 + 1; \
	while(step > 0) { \
		for(size_t i = step; i < size; i++) \
			for(size_t j = i; j > step - 1 && arr[j] <= arr[j-step]; j -= step) \
				swap(&arr[j], &arr[j-step]); \
		step /= 3; \
	} \
} while(0)
