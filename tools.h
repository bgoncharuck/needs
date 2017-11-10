#define END_OF_SEN_ARR(str, ind) (str[ind] == '.'|| str[ind] == '?' || str[ind] == '!')
#define END_OF_SEN_POIN(pointer) (*(pointer) == '.'|| *(pointer) == '?' || *(pointer) == '!')
#define END_OF_LINE_POIN(pointer) (*(pointer) == ' ' || *(pointer) == '\n')
#define LENGTH_ARR(arr) ( sizeof(arr)/sizeof(arr[0]) )

void swapInt(int *left_value, int *right_value) {
	int tmp = *left_value;
	*left_value = *right_value;
	*right_value = tmp;
	return;
}

void swapChar(char *left_value, char *right_value) {
	char tmp = *left_value;
	*left_value = *right_value;
	*right_value = tmp;
	return;
}

void swapLong(long *left_value, long *right_value) {
	long tmp = *left_value;
	*left_value = *right_value;
	*right_value = tmp;
	return;
}

void swapDouble(double *left_value, double *right_value) {
	double tmp = *left_value;
	*left_value = *right_value;
	*right_value = tmp;
	return;
}
