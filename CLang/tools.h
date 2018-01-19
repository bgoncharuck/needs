#define swapXOR(x,y) do {if(x!=y){*x = *x ^ *y; *y = *y ^ *x; *x = *x ^ *y;}} while(0)
/*
*/
#define swap(x,y) do { \
	typeof(*x) temp = *x; \
	*x = *y; \
	*y = temp; \
} while(0)

size_t better_fgets(char* to, size_t size, FILE* from, const char control) {
	if(to != NULL && from != NULL) {
		size_t currentSize = 0;
		char temp;
		while(currentSize < size && (temp = fgetc(from)) != control) {
			*to++ = temp;
			++currentSize;
		}
		return currentSize;
	}
	return 0;
}
