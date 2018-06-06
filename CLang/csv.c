#include <string_buffer.h>
#include <csv.h>
#include <stdio.h>
#include <assert.h>

#define foreach(VARTYPE, VARNAME, LIST)   \
   for (int VARNAME##_i = 0, VARNAME##_length = DynamicList_count(LIST); !VARNAME##_i; ++VARNAME##_i) \
       for (VARTYPE VARNAME = (VARTYPE)DynamicList_at(LIST, VARNAME##_i); \
           VARNAME##_i < VARNAME##_length; \
           VARNAME = (VARTYPE)DynamicList_at(LIST, ++VARNAME##_i))

#define ErrorMessage(error) do { \
	fprintf(stderr, "%s\n", error); \
	assert(0 && error); \
	abort(); \
} while(0)

static void DynamicList_CopyTo(DynamicList *self, DynamicList *dest);

struct __CsvTable {
    DynamicList * rows;
} ;

struct __CsvRow {
    DynamicList * value;
} ;

CsvRow * CsvRow_new(void){
    CsvRow * self = malloc(sizeof(CsvRow));
	if(!self)
		ErrorMessage("Error: out of memory in CsvRow_new()");
    self->value = DynamicList_new();
    return self;
}

void CsvRow_free(CsvRow * self){
	if(self) {
		DynamicList_free(self->value);
		free(self);
		return;
	}
	ErrorMessage("Error: NULL pointer in CsvRow_free()");
}

void CsvRow_add(CsvRow * self, const char * value){
	if(self && value) {
		DynamicList_add(self->value, (void *)value);
		return;
	}
	ErrorMessage("Error: NULL pointer in CsvRow_add()");
}

void CsvRow_values(CsvRow * self, DynamicList * values){
	if(self || self->value) {
		DynamicList_CopyTo(self->value, values);
		return;
	}
	ErrorMessage("Error: NULL pointer in CsvRow_values()");
}

CsvTable * CsvTable_new(void) {
    CsvTable * self = malloc(sizeof(CsvTable));
	if(!self)
		ErrorMessage("Error: out of memory in CsvTable_new()");
    self->rows = DynamicList_new();
    return self;
}

void CsvTable_free(CsvTable * self){
	if(self) {
		DynamicList_free(self->rows);
		free(self);
		return;
	}
	ErrorMessage("Error: NULL pointer in CsvTable_free()");
}

void CsvTable_add (CsvTable * self, CsvRow * row) {
	if(self && row) {
		DynamicList_add(self->rows, (void *)row);
		return;
	}
	ErrorMessage("Error: NULL pointer in CsvTable_add()");
}


void CsvTable_rows(CsvTable * self, DynamicList * rows) {
	if(self || self->rows) {
		DynamicList_CopyTo(self->rows, rows);
		return;
	}
	ErrorMessage("Error: NULL pointer in CsvTable_rows()");
}

CsvTable * CsvTable_newFromString(const char * csvString){

    if(!csvString)
        ErrorMessage("Error: NULL pointer in CsvTable_newFromString()");

    CsvTable * t = CsvTable_new();
    CsvRow * row = CsvRow_new();

		StringBuffer * value = StringBuffer_new();
    while(1){
        char ch = * csvString;
        if(ch == '\0'){
            char * newValue = StringBuffer_toNewString(value);
            CsvRow_add(row, newValue);
            StringBuffer_clear(value);
						//
            CsvTable_add(t, row);
						break;
        } else if(ch == '\n') {
            char * newValue = StringBuffer_toNewString(value);
            CsvRow_add(row, newValue);
            StringBuffer_clear(value);
            //
            CsvTable_add(t, row);
            row = CsvRow_new();
        } else if(ch == ',') {
            char * newValue = StringBuffer_toNewString(value);
            CsvRow_add(row, newValue);
            StringBuffer_clear(value);
        } else {
            StringBuffer_appendChar(value, ch);
        }
        csvString++;
    }
    StringBuffer_free(value);
		// CsvRow_free(row);
    return t;
}

char * CsvTable_toNewString  (CsvTable * self){
	if(!self)
		ErrorMessage("Error: NULL pointer in CsvTable_toNewString()");

	StringBuffer * sb = StringBuffer_new();
  // foreach(CsvRow *, row, self->rows){
  //     foreach(char * , value, row->value) {
  //         StringBuffer_append(sb, value);
  //     }
  // }


	DynamicList * rows = DynamicList_new();
	CsvTable_rows(self, rows);
	int rowsCnt = DynamicList_count(rows);

	for (int rowIndex = 0; rowIndex < rowsCnt; rowIndex++) {

		CsvRow * row = (CsvRow*) DynamicList_at(rows, rowIndex);

		DynamicList * values = DynamicList_new();
		CsvRow_values(row, values);
		int valuesCnt = DynamicList_count(values);

		for (int valueIndex = 0; valueIndex < valuesCnt; valueIndex++) {
			char * value = (char*) DynamicList_at(values,valueIndex);
      StringBuffer_append(sb, value);
			if (valueIndex < valuesCnt - 1)
      	StringBuffer_append(sb, ",");
			else if (rowIndex != rowsCnt - 1)
      	StringBuffer_append(sb, "\n");
		}
		DynamicList_free(values);

		if (rowIndex == rowsCnt - 1)
			StringBuffer_append(sb, "\0");

	}
	DynamicList_free(rows);

  char * copy = StringBuffer_toNewString(sb);
  StringBuffer_free(sb);

  return copy;
}

static void DynamicList_CopyTo(DynamicList *self, DynamicList *dest){
	int count = DynamicList_count(self);
	for(int i = 0; i < count; i++){
		void *value = DynamicList_at(self, i);
		DynamicList_add(dest, value);
	}
}
