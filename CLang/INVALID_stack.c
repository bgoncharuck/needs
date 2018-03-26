#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <dynamicList.h>
#include <stack.h>

#define throw(MSG) do { \
	fprintf(stderr, MSG); \
	assert(0 && MSG); \
	abort(); \
} while(0)

struct __Stack {
	DynamicList* list;
};

Stack* Stack_new(void) {
	Stack* self = malloc(sizeof(Stack));
	if(!self)
		throw("Error: out of memory in Stack_new()");
	self->list = DynamicList_new();
	return self;
}

void Stack_free(Stack* self) {
	if(!self)
		throw("Error: NULL pointer Exception in Stack_free()");
	if(self->list) {
		DynamicList_free(self->list);
	}
	free(self);
}

void * Stack_top(Stack * self) {
	if(!self || !self->list)
		throw("Error: NULL pointer Exception in Stack_top()");
	return DynamicList_at(self->list, DynamicList_count(self->list) - 1);
}

void * Stack_botton(Stack * self) {
	if(!self || !self->list)
		throw("Error: NULL pointer Exception in Stack_botton()");
	return DynamicList_at(self->list, 0);
}

void Stack_push(Stack * self, void * data) {
	if(!self || !self->list || !data)
		throw("Error: NULL pointer Exception in Stack_push()");
	DynamicList_add(self->list, data);
}

void * Stack_pop(Stack * self) {
	if(!self || !self->list)
		throw("Error: NULL pointer Exception in Stack_pop()");
	void* saveElement = DynamicList_at(self->list, DynamicList_count(self->list) - 1);
	DynamicList_removeAt(self->list, DynamicList_count(self->list) - 1);
	return saveElement;
}

void Stack_cleanPop(Stack * self) {
	if(!self || !self->list)
		throw("Error: NULL pointer Exception in Stack_cleanPop()");
	DynamicList_removeAt(self->list, DynamicList_count(self->list) - 1);
}

int Stack_size(Stack * self) {
	return DynamicList_count(self->list);
}

bool Stack_isEmpty(Stack * self) {
	return DynamicList_isEmpty(self->list);
}
