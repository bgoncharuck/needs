#define swapXOR(x,y) do {if(x!=y){*x = *x ^ *y; *y = *y ^ *x; *x = *x ^ *y;}} while(0)
/*
*/


#define ErrorMessage(MSG) do { \
	fprintf(stderr, "%s\n", MSG); \
	assert(0 && MSG); \
	abort(); \
} while(0)


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

time_t createDate(int day, int month, int year) {
	struct tm bday = {0};
	bday.tm_mday = day;
	bday.tm_mon = month - 1;
	bday.tm_year = year - 1900;
	return mktime(&bday);
}

int getAgeBetween(time_t t1, time_t t2) {
	struct tm tm1 = *localtime(&t1);
	struct tm tm2 = *localtime(&t2);
	int years = tm2.tm_year - tm1.tm_year;
    if (tm2.tm_mon < tm1.tm_mon || (tm2.tm_mon == tm1.tm_mon && tm2.tm_mday < tm1.tm_mday))
        years -= 1;
    return years;
}

int getYear(time_t t) {
	time_t now = time(NULL);
	struct tm tm1 = *localtime(&t);
	struct tm tm2 = *localtime(&now);
	int years = tm2.tm_year - tm1.tm_year;
    if (tm2.tm_mon < tm1.tm_mon || (tm2.tm_mon == tm1.tm_mon && tm2.tm_mday < tm1.tm_mday))
        years -= 1;
    return years;
}

time_t createDateFromString (char * date) { //day.month.year
  date[2] = '\0';
  int day = atoi (date);
  date[5] = '\0';
  int month = atoi ((date+3));
  int year = atoi ((date+6));
  return createDate (day, month, year);
}

int correctDate (char * date) {
    if (date == NULL) return false;
    return  (!((strlen(date) != 10)\
            || date[2] != '.' \
            || date[5] != '.' \
            || !(isdigit(date[0])&& date[0] <= '3')\
            || !(isdigit(date[1])&& (date[0] <= '2' || date[1] <= '1'))\
            || !(isdigit(date[3])&& date[3] <= '1')\
            || !(isdigit(date[4])&& ((date[3] == '0' && date[4] <= '9') || (date[3] == '1' && date[4] <= '2')))\
            || !(isdigit(date[6])&&date[6] >= '1')\
            || !isdigit(date[7])\
            || !isdigit(date[8])\
            || !isdigit(date[9]))) ? 1 : 0;
}
