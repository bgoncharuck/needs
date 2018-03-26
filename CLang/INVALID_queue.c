#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <dynamicList.h>
#include <queue.h>

#define throw(MSG) do { \
	fprintf(stderr, MSG); \
	assert(0 && MSG); \
	abort(); \
} while(0)

struct __Queue {
	DynamicList* list;
};

Queue * Queue_new(void) {
	Queue* self = malloc(sizeof(Queue));
	if(!self)
		throw("Error: out of memory in Queue_new()");
	self->list = DynamicList_new();
	return self;
}

void Queue_free(Queue* self) {
	if(!self)
		throw("Error: NULL pointer Exception in Queue_free()");
	if(self->list) {
		DynamicList_free(self->list);
	}
	free(self);
}

void * Queue_rear(Queue * self) {
	if(!self || !self->list)
		throw("Error: NULL pointer Exception in Queue_rear()");
	return DynamicList_at(self->list, 0);
}

void * Queue_front(Queue * self) {
	if(!self || !self->list)
		throw("Error: NULL pointer Exception in Queue_front()");
	return DynamicList_at(self->list, DynamicList_count(self->list) - 1);
}

void Queue_enqueue(Queue * self, void * data) {
	if(!self || !self->list || !data)
		throw("Error: NULL pointer Exception in Queue_enqueue()");
	DynamicList_add(self->list, data);
}

void * Queue_dequeue(Queue * self) {
	if(!self || !self->list)
		throw("Error: NULL pointer Exception in Queue_dequeue()");
	void* saveElement = DynamicList_at(self->list, 0);
	DynamicList_removeAt(self->list, 0);
	return saveElement;
}

void Queue_cleandDequeue(Queue * self) {
	if(!self || !self->list)
		throw("Error: NULL pointer Exception in Queue_cleandDequeue()");
	DynamicList_removeAt(self->list, DynamicList_count(self->list) - 1);
}

int Queue_size(Queue * self) {
	return DynamicList_count(self->list);
}

bool Queue_isEmpty(Queue * self) {
	return DynamicList_isEmpty(self->list);
}
