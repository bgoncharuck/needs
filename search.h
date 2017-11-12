long sequentialSearch(int arr[], long size, int key) {
	long i;
	for(i  = 0; i < size && arr[i] != key; i++);
	return (i < size) ? i : -1;
}

long firInSeq(int arr[], long size, int key) {
	for(long i = 0; i < size; i++)
		if(key == arr[i]) return i;
	return -1;
}

long lasInSeq(int arr[], long size, int key) {
	for(long i = size - 1; i >= 0; i--)
		if(key == arr[i]) return i;
	return -1;
}

long binarySearch(int arr[], long size, int key) {
	for(long l = 0, r = size - 1, i = (l+r)/2; l <= r; i = (l+r)/2) {
		if(key == arr[i])
			return i;
		else if (key < arr[i])
			r = i - 1;
		else l = i + 1;
	}
	return -1;
}

long firInBin(int arr[], long size, int key) {
	for(long l = 0, r = size - 1, i = (l+r)/2; l <= r; i = (l+r)/2) {
		if(key == arr[0] || key > arr[i - 1] && arr[i] == key)
			return i;
		else if (key > arr[i])
			l = i + 1;
		else r = i - 1;
	}
	return -1;
}

long lasInBin(int arr[], long size, int key) {
	for(long l = 0, r = size - 1, i = (l+r)/2; l <= r; i = (l+r)/2) {
		if(key == arr[size-1] || key < arr[i + 1] && arr[i] == key)
			return i;
		else if (key < arr[i])
			r = i - 1;
		else l = i + 1;
	}
	return -1;
}

long interpolationSearch(int arr[], long size, int key) {
	for(long l = 0, r = size - 1, i = (l+r)/2; l <= r;
	i = l + (key - arr[l]) * (r - l) / (arr[r] - arr[l]) ) {
		if(key == arr[i])
			return i;
		else if (key < arr[i])
			r = i - 1;
		else l = i + 1;
	}
	return -1;
}
