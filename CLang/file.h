int fileExists(const char* path) {
	char command[PATH_MAX + 1];
	sprintf(command, "[ -f %s ]", path);
	return !system(command);
}

int textFileExists(const char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (!f) return 0;
    fclose(f);
    return 1;
}

void writeLine(FILE *file, long line_number, const char *line) {
	long count = 1;
	char* newLine = "\n";
	if(file != NULL) {
		while(count < line_number) {
			fwrite(newLine, strlen(newLine), 1, file);
			count++;
			if(count == line_number)
				fwrite(line, 1, strlen(line), file);
		}
	}
	return;
}

void appendLine(FILE *file, long count, long line_number, const char *line) {
	char* newLine = "\n";
	if(file != NULL) {
		while(count < line_number) {
			fwrite(newLine, strlen(newLine), 1, file);
			count++;
			if(count == line_number)
				fwrite(line, 1, strlen(line), file);
		}
	}
	return;
}

void printLine(FILE *file, long line_number) {
	long count = 1;
	if(file != NULL) {
		char line[256];
		while(fgets(line, sizeof line, file) != NULL)
		if(count == line_number) {
			printf("%s", line);
			return;
		}
		else
			count++;
	}
	else
		printf("Error. No such line\n");
	return;
}

long getFileSize(const char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fclose(f);
    return fsize;
}

int readFileToBuffer(const char *fileName, char *buffer, int bufferLength) {
	FILE *f = fopen(fileName, "rb");
    if (!f) return 0;
    long readBytes = fread(buffer, 1, bufferLength, f);
    fclose(f);
    return readBytes;
}
