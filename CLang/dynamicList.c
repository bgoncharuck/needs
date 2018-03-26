#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

// #include <dynamicList.h>


typedef struct Array {
    size_t itemSize;
    char * items;
    size_t length;
} Array;

void Array_copy(
    Array sourceArray,
    int sourceIndex,
    Array destinationArray,
    int destinationIndex,
    int length
);

#define empty(MEM, SIZE) memset(MEM, 0, SIZE)
#define throw(MSG) do { \
	fprintf(stderr, "%s\n", MSG); \
	assert(0 && MSG); \
	abort(); \
} while(0)

static const int INITIAL_CAPASITY = 8;
static void __checkSize(DynamicList* self, int min);

struct __DynamicList {
    int size;
    int capacity;
	void ** items;
};

DynamicList * DynamicList_new(void) {
	DynamicList * self = malloc(sizeof(DynamicList));
	if(!self)
		throw("Error: out of memory in DynamicList_new()");
	self->capacity = INITIAL_CAPASITY;
	self->size = 0;
	self->items = malloc(0);
	__checkSize(self, 0);
	return self;
}

void DynamicList_free(DynamicList * self) {
	if(!self)
		throw("Error: NULL pointer Exception in DynamicList_free()");
	if(self->items)
		free(self->items);
    free(self);
}

void DynamicList_set(DynamicList * self, size_t index, void* data) {
    if(!data || !self)
		throw("Error: NULL pointer Exception in DynamicList_set()");
    if(index < 0 || index >= self->size)
		throw("Error: index out of bounds in DynamicList_set()");
    self->items[index] = data;
}

void DynamicList_add(DynamicList * self, void * data) {
    if(!data || !self)
		throw("Error: NULL pointer Exception in DynamicList_add()");
    if(self->size <= self->capacity)
        __checkSize(self, self->size + 1);
    DynamicList_set(self, self->size++, data);
}

void DynamicList_insert(DynamicList * self, size_t index, void* data) {
    if(!data || !self)
		throw("Error: NULL pointer Exception in DynamicList_insert()");
    if(index > self->size)
		throw("Error: argument out of range in DynamicList_insert()");
    if(self->size >= self->capacity - 1)
        __checkSize(self, self->size + 1);
    if(index < self->size) {
        Array items = {
            .itemSize = sizeof(void *),
            .items = (char *)self->items,
            .length = self->size
        };
        Array_copy(items, index, items, index + 1, self->size - index);
    }
    DynamicList_set(self, index, data);
    self->size++;
}

void DynamicList_removeAt(DynamicList * self, size_t index) {
	if(!self)
		throw("Error: NULL pointer Exception in DynamicList_removeAt()");
    if (index < 0 || index >= self->size)
		throw("Error: index out of bounds in DynamicList_removeAt");
    self->size--;
    if(index < self->size) {
        Array items = {
            .itemSize = sizeof(void *),
            .items = (char *)self->items,
            .length = self->size
        };
        Array_copy(items, index + 1, items, index, self->size - index);
    }
}

int DynamicList_indexOf(DynamicList * self, void * data) {
    if(!data || !self)
		throw("Error: NULL pointer Exception in DynamicList_indexOf()");
    for (int i = 0; i < self->size; i++) {
        if (self->items[i] == data) {
            return i;
        }
    }
    return -1;
}

bool DynamicList_contains(DynamicList * self, void * data) {
    if(!data || !self)
		throw("Error: NULL pointer Exception in DynamicList_contains()");
    return DynamicList_indexOf(self, data) >= 0;
}

bool DynamicList_remove(DynamicList * self, void * data) {
    if(!data || !self)
		throw("Error: NULL pointer Exception in DynamicList_remove()");
    int index = DynamicList_indexOf(self, data);
    if (index >= 0) {
        DynamicList_removeAt(self, index);
        return true;
    }
    return false;
}

bool DynamicList_isEmpty(DynamicList * self) {
	if(!self)
		throw("Error: NULL pointer Exception in DynamicList_isEmpty()");
    return self->size == 0;
}

int DynamicList_count(DynamicList * self) {
	if(!self)
		throw("Error: NULL pointer Exception in DynamicList_count()");
    return self->size;
}

void* DynamicList_at(DynamicList * self, size_t index) {
	if(!self)
		throw("Error: NULL pointer Exception in DynamicList_at()");
    if (index < 0 || index >= self->size)
		throw("Error: index out of bounds in DynamicList_at()");
    return self->items[index];
}

void * DynamicList_takeLast(DynamicList * self) {
	if(!self || !self->items)
		throw("Error: NULL pointer Exception in DynamicList_takeLast()");
	void* saveElement = DynamicList_at(self, DynamicList_count(self) - 1);
	DynamicList_removeAt(self, DynamicList_count(self) - 1);
	return saveElement;
}

void * DynamicList_takeFirst(DynamicList * self) {
	if(!self || !self->items)
		throw("Error: NULL pointer Exception in DynamicList_takeFirst()");
	void* saveElement =  DynamicList_at(self, 0);
	DynamicList_removeAt(self, 0);
	return saveElement;
}

void DynamicList_freeAllData(DynamicList * self, void (*destructor) (void * data)) {
	if(self && self->items) {
		while(!DynamicList_isEmpty(self)) {
			destructor(DynamicList_takeFirst(self));
		}
	}
	throw("Error: NULL pointer Exception in DynamicList_freeAllData()");
}

void Array_copy(
    Array sourceArray,
    int sourceIndex,
    Array destinationArray,
    int destinationIndex,
    int length
) {
    // @todo add checks
    size_t itemSize = sourceArray.itemSize;
    size_t copySize = itemSize * length;
    char buffer[copySize];
    memcpy(buffer, sourceArray.items + (sourceIndex) * itemSize, copySize);
    memcpy(destinationArray.items + (destinationIndex) * itemSize, buffer, copySize);
}

static void __checkSize(DynamicList * self, int min) {
    if (self->size <= min) {
        int newCapacity = self->size == 0 ? INITIAL_CAPASITY : self->size * 2;
        if (newCapacity < min) newCapacity = min;
        self->capacity = newCapacity;
        size_t newSize = sizeof(void *) * self->capacity;
        void** newItems = realloc(self->items, newSize);
		// if(!newItems)
		if(newItems == NULL)
			throw("Error: out of memory in __checkSize() in dynamicList");
        self->items = newItems;
    }
}
