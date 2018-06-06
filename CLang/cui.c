#include <progbase/console.h>

void menuPoint(int switcher, int numberOfSwitcherState,
	const char * string, int X, int Y, const int FG_COLOR) {
		Console_setCursorPosition(X, Y);
		if (switcher == numberOfSwitcherState)
	   Console_setCursorAttribute(FG_COLOR);
	  printf("%s", string);
	  Console_setCursorAttribute(FG_DEFAULT);
}

void cleanLine(int X, int Y, const int BORDER) {
	for(int i = Y; i < BORDER; i++) {
		Console_setCursorPosition(X,i);
		putchar(' ');
	}
}

char * scanString(int x, int y) {
	Console_lockInput();

	char symbol = '\0';
	int BORDER = Console_size().columns;

	int firstChar = 0;
	int sizeOfString = BORDER;
	char * result = malloc(sizeof(char) * sizeOfString + 1);
	memset(result, '\0', sizeOfString+1);

	for(int i = y; (symbol = Console_getChar()) != '\n'; i++) {
		if (i == BORDER - 1) {
			memset(result, ' ', sizeOfString - 1);
			cleanLine(x,y, BORDER);
			i = y;
			firstChar = 0;
		}
		else {
			if(symbol == 127) {
					i--;
					if(i < y) i = y;
					Console_setCursorPosition(x,i);
					putchar(' ');
					result[i-y] = ' ';
					if (i > y)
						i--;
					firstChar = 0;
			}
			else {
				if (i == y+1 && result[i-y] == ' ' && !firstChar) {
					i--;
					firstChar = 1;
				}
				Console_setCursorPosition(x,i);
				putchar(symbol);
				result[i-y] = symbol;
			}
		}
	}

	for (int i = 0; i < sizeOfString-1; i++)
		if(isspace(result[i]) && isspace(result[i+1]))
			result[i] = '\0';
	Console_unlockInput();

	if (strlen(result) <= 1 && (result[0] == '\0' || result[0] == ' ')) {
		free (result);
		return NULL;
	}

	return result;
}

int isDigitString (const char * str) {
	int s = (int) strlen(str);
	for (int i = 0; i < s; i++)
		if (!isdigit(str[i]))
			return 0;
	return 1;
}

int scanInt (int x, int y) {
  char * scannedString = NULL;
  int parsed = 0;
	bool loopController = true;
  while (loopController) {
		scannedString = scanString (x, y);
		loopController = !isDigitString(scannedString);
    cleanLine(x, y, Console_size().columns);
		if (!loopController)
			parsed = atoi (scannedString);
		free (scannedString);
	}
	return parsed;
}

int scanIntInRange (int x, int y, int from, int to) {
  int scannedInRange = 0;
	bool loopController = true;
  while (loopController) {
		scannedInRange = scanInt(x,y);
		loopController = scannedInRange >= to || scannedInRange < from;
	}
  return scannedInRange;
	// return scanInt(x,y);
}

