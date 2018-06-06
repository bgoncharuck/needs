#include <string.h>
#include <assert.h>
#include <stdio.h>

#include <string_buffer.h>

const int INITIAL_CAPACITY = 128;

static char * strDup(const char *s) {
    char *d = malloc(strlen(s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy(d, s);                        // Copy the characters
    return d;                            // Return the new string
}

#define ErrorMessage(error) do { \
	fprintf(stderr, "%s\n", error); \
	assert(0 && error); \
	abort(); \
} while(0)

typedef struct __StringBuffer {
    char * buffer;
    size_t capacity;
    size_t length;

} StringBuffer;

StringBuffer * StringBuffer_new(void){
    StringBuffer * self = malloc(sizeof(StringBuffer));
	if(!self)
		ErrorMessage("Error: out of memory in StringBuffer_new()");
    self->capacity = INITIAL_CAPACITY;
    self->buffer = malloc(sizeof(char) * self->capacity);
    self->buffer[0] = '\0';
    self->length = 1;
    return self;
}
void StringBuffer_free(StringBuffer * self){
	if(self) {
    	free(self->buffer);
    	free(self);
		return;
	}
	ErrorMessage("Error: NULL pointer in StringBuffer_free()");
}

static void ensureCapacity(StringBuffer * self, int appendLength){
if(self->length + appendLength > self->capacity){
        size_t newCapacity = self->capacity * 2;
        char * newBuffer = realloc(self->buffer, newCapacity * sizeof(char));
        if(!newBuffer)
			ErrorMessage("Error: out of memory in ensureCapacity()");
        else {
            self->buffer = newBuffer;
            self->capacity = newCapacity;
        }
    }
}

void StringBuffer_append(StringBuffer * self, const char * str) {
	if(self) {
		size_t len = strlen(str);
		ensureCapacity(self, len);
		strcat(self->buffer + (self->length - 1), str);
		self->length += len;
		return;
	}
	ErrorMessage("Error: NULL pointer in StringBuffer_append()");
}

void StringBuffer_appendChar(StringBuffer * self, char ch) {
	if(self) {
		ensureCapacity(self, self->length);
		self->buffer[self->length] = '\0';
		self->buffer[self->length - 1] = ch;
		self->length++;
		return;
	}
	ErrorMessage("Error: NULL pointer in StringBuffer_appendChar()");
}

void StringBuffer_clear(StringBuffer * self){
	if(self) {
		self->buffer[0] = '\0';
		self->length = 1;
		return;
	}
	ErrorMessage("Error: NULL pointer in StringBuffer_clear()");
}

char * StringBuffer_toNewString(StringBuffer * self) {
	if(!self)
		ErrorMessage("Error: NULL pointer in StringBuffer_toNewString()");
  return strDup(self->buffer);
}
