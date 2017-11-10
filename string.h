#define END_OF_SEN_ARR(str, ind) (str[ind] == '.'|| str[ind] == '?' || str[ind] == '!')
#define END_OF_SEN_POIN(pointer) (*(pointer) == '.'|| *(pointer) == '?' || *(pointer) == '!')
#define END_OF_LINE_POIN(pointer) (*(pointer) == ' ' || *(pointer) == '\n')
#define LENGTH_ARR(arr) ( sizeof(arr)/sizeof(arr[0]) )


enum {
	EQUAL,
	HOW_FAR,
	FROM_ONE_TEXT
};

struct Sentence {
	unsigned start;
	char string[SIZE_OF_SENTENCE];
};

struct SentenceArray {
	unsigned size;
	struct Sentence* arr;
};

int indexOfSentenceStart(const unsigned numOfSen, const char* text) {
	if(LENGTH_ARR(text) < 1)
	 	return -1;
	unsigned senNum = 1;
	int indexOfSenStart = 0;
	while(senNum != numOfSen && *text) {
		while(!END_OF_SEN_POIN(text)) {
			indexOfSenStart++;
			text++;
		}
		while(END_OF_SEN_POIN(text) || END_OF_LINE_POIN(text)) {
			indexOfSenStart++;
			text++;
		}
		senNum++;
	}
	if(senNum < numOfSen)
		return -1;
	return indexOfSenStart;
}

void anySenToBuf(const unsigned numberOfSen, const char* text, char* buf, int sizeOfBuf) {
	cleanBuf(buf, sizeOfBuf);
	int i = indexOfSentenceStart(numberOfSen, text);
	if(LENGTH_ARR(text) < 1 || i >= LENGTH_ARR(text))
	 	return;
	text += i;
	i = 0;
	while(!END_OF_SEN_POIN(text)) {
		buf[i] = *text;
		text++; i++;
	}
	while(END_OF_SEN_POIN(text)) {
		buf[i] = *text;
		text++; i++;
	}
	return;
}

unsigned strEqual(const char* str1, const char* str2) {
	if(sizeof(str1) != sizeof(str2))
		return 0;
	unsigned valid = 1;
	while(*str1 && *str2) {
		if(*str1 != *str2)
			valid = 0;
		str1++; str2++;
	}
	return valid;
}

int amountOfSen(const char* text) {
	int count = 0;
	while(*text) {
		while(!END_OF_SEN_POIN(text))
			text++;
		while(END_OF_SEN_POIN(text) || END_OF_LINE_POIN(text))
			text++;
		count++;
	}
	return count;
}

int compareSentences(struct Sentence first, struct Sentence second,
	const unsigned MODE) {
	if(MODE == EQUAL) {
		if(0 != strcmp(first.string, second.string))
	 		return 0;
		else if(strEqual(first.string, second.string))
			return 1;
		return 0;
	}
	else if(MODE == HOW_FAR)
		return abs(first.start - second.start);
	return 0;
}

int compareArrOfSen(struct SentenceArray* first, struct SentenceArray* second,
	const unsigned MODE) {
	if(MODE == EQUAL) {
		if(first->size != second->size)
			return 0;
		for(int i = 0; i < first->size; i++)
			if(!compareSentences(first->arr[i], second->arr[i], EQUAL))
				return 0;
		return 1;
	}
	else if(MODE == FROM_ONE_TEXT) {
		if(first->size > 0 && second->size > 0) {
			int valid = 0;
			int minSize = (first->size < second->size) ? first->size : second->size;
			int tempSize = (first->size < second->size) ? second->size : first->size;
			for(int i = 0; i < minSize; i++)
				for(int j = 0; j < tempSize; j++)
					if(compareSentences(first->arr[i], second->arr[j], EQUAL))
						valid = 1;
			return valid;
		}
	}
	return 0;
}

struct Sentence makeSen(const unsigned numOfSen, const char* text) {
	struct Sentence returnSen;
	returnSen.start = indexOfSentenceStart(numOfSen, text);
	anySenToBuf(numOfSen ,text, returnSen.string, SIZE_OF_SENTENCE);
	return returnSen;
}

struct SentenceArray* getAllSentencesArrayNew(const char* text) {
	struct SentenceArray* result = malloc(sizeof(struct SentenceArray));
	result->size = amountOfSen(text);
	result->arr = malloc(result->size*sizeof(struct Sentence));
	for(int i = 0; i < result->size; i++) {
		result->arr[i] = makeSen(i+1, text);
	}
	return result;
}

void sentenceArrFree(struct SentenceArray* array) {
	free(array->arr);
	free(array);
}
