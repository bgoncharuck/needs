#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <hashcode.h>
#include <hashtable.h>

struct __HashItem {
   char * name;
   size_t hashKey;
   struct __HashItem * next;
   void * data;
};

struct __HashTable {
    int capacity;
	HashItem ** items;
};

#define ErrorMessage(MSG) do { \
	fprintf(stderr, "%s\n", MSG); \
	assert(0 && MSG); \
	abort(); \
} while(0)

static const size_t INITIAL_CAPASITY = 4200;
static void __checkSize(HashTable* self, int min);

HashItem * HashItem_new(char * name) {
	if(name) {
		HashItem * res = malloc(sizeof(HashItem));
		if(!res)
			ErrorMessage("Error: out of memory in HashItem_new()");
		res->name = name;
		res->hashKey = hash((unsigned char *) name);
		res->data = NULL;
		res->next = NULL;
		return res;
	}
	ErrorMessage("Error: NULL pointer Exception in HashItem_new()");
}

void HashItem_free(HashItem * self) {
	if(self) {
		free(self);
		return;
	}
	ErrorMessage("Error: NULL pointer Exception in HashItem_new()");
}

char * HashItem_name(HashItem * self) {
	if(self)
		return self->name;
	ErrorMessage("Error: NULL pointer Exception in HashItem_name()");
}

size_t HashItem_hashKey(HashItem * self) {
	if(self)
		return self->hashKey;
	ErrorMessage("Error: NULL pointer Exception in HashItem_hashKey()");
}

HashItem * HashItem_next(HashItem * self) {
	if(self)
		return self->next;
	ErrorMessage("Error: NULL pointer Exception in HashItem_next()");
}

void * HashItem_data(HashItem * self) {
	if(self)
		return self->data;
	ErrorMessage("Error: NULL pointer Exception in HashItem_next()");
}

void * HashItem_chgDat(HashItem * self, void * data) {
	if(self)
		self->data = data;
	ErrorMessage("Error: NULL pointer Exception in HashItem_next()");
}

HashItem * HashItem_findInColision(HashItem * head, HashItem * self) {
	HashItem * temp = head;
	while(temp != NULL) {
		if(temp->hashKey == self->hashKey)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

bool HashItem_colisionItemExist(HashItem * head, HashItem * item) {
	if(head && item) {
		HashItem * temp = head;
		while(temp != NULL) {
			if(temp->hashKey == item->hashKey)
				return true;
			temp = temp->next;
		}
		return false;
	}
	ErrorMessage("Error: NULL pointer Exception in HashTable_colisionItemExist()");
}

void HashItem_colisionFree(HashItem * self) {
	if(self) {
		if(self->next != NULL) {
			HashItem * head = self;
			HashItem * temp = self;
			int count = 0;
			while(temp->next != NULL) {
				count++;
				temp = temp->next;
			}
			if(count == 1) {
				HashItem_free(head->next);
				HashItem_free(head);
				return;
			}
			for(int i = 0; i < count; i++) {
				temp = head;
				while(temp->next != NULL) temp = temp->next;
				HashItem_free(temp);
			}
			if(head == NULL)
				return;
		} else {
			HashItem_free(self);
			return;
		}
	}
}

HashTable * HashTable_new(void) {
	HashTable * self = malloc(sizeof(HashTable));
	if(!self)
		ErrorMessage("Error: out of memory in HashTable_new()");
	self->capacity = INITIAL_CAPASITY;
	self->items = malloc(INITIAL_CAPASITY * sizeof(HashItem *));
	for(int i = 0; i < INITIAL_CAPASITY; i++) {
		self->items[i] = NULL;
	}
	return self;
}


void HashTable_free(HashTable * self) {
	if(!self)
		ErrorMessage("Error: NULL pointer Exception in HashTable_free()");
	if(self->items) {
		for(int i = 0; i < self->capacity; i++) {
			if(self->items[i])
				HashItem_colisionFree(self->items[i]);
		}
		free(self->items);
	}
    free(self);
}

bool HashTable_colisionCheck(HashItem * first, HashItem * second) {
	if(first && second) {
		int index1 = first->hashKey % strlen(first->name);
		int index2 = second->hashKey % strlen(second->name);
		if(index1 == index2)
			return first->hashKey != second->hashKey;
		return false;
	}
	ErrorMessage("Error: NULL pointer Exception in HashTable_colisionCheck()");
}

void HashTable_colisionSolution(HashItem * head, HashItem * packed) {
	if(head && packed) {
		HashItem * temp = head;
		while(temp->next != NULL) temp = temp->next;
		temp->next = packed;
	}
	ErrorMessage("Error: NULL pointer Exception in HashTable_colisionSolution()");
}

void HashTable_set(HashTable * self, size_t index, HashItem * name) {
    if(!name || !self)
		ErrorMessage("Error: NULL pointer Exception in HashTable_set()");
    if(index < 0 || index >= self->capacity)
		ErrorMessage("Error: index out of bounds in HashTable_set()");
	if(self->items[index] == NULL) {
		self->items[index] = name;
		return;
	}
	else if(HashTable_colisionCheck(self->items[index], name))
		HashTable_colisionSolution(self->items[index], name);
}

void HashTable_insert(HashTable * self, char * name) {
    if(!name || !self)
		ErrorMessage("Error: NULL pointer Exception in HashTable_insert()");
	HashItem * packed = HashItem_new(name);
	int index = packed->hashKey % strlen(name);
	if(index >= self->capacity)
		__checkSize(self, index + 1);
    HashTable_set(self, index, packed);
}

bool HashTable_contains(HashTable * self, char * name) {
    if(!name || !self)
		ErrorMessage("Error: NULL pointer Exception in HashTable_contains()");
	HashItem * packed = HashItem_new(name);
	int index = packed->hashKey % strlen(name);
	bool res = false;
    if(index < 0 || index >= self->capacity)
		res = false;
    else if(self->items[index]->hashKey == packed->hashKey)
		res = true;
	else if(HashTable_colisionCheck(self->items[index], packed))
		res = HashItem_colisionItemExist(self->items[index], packed);
	HashItem_free(packed);
	return res;
}

void * HashTable_dataByName(HashTable * self, char * name) {
	if(self && name) {
		HashItem * packed = HashItem_new(name);
		int index = packed->hashKey % strlen(name);
		if(self->items[index]->hashKey == packed->hashKey) {
			HashItem_free(packed);
			return self->items[index]->data;
		} else {
			HashItem * res = HashItem_findInColision(self->items[index], packed);
			HashItem_free(packed);
			return res->data;
		}
	}
	ErrorMessage("Error: NULL pointer Exception in HashTable_dataByName()");
}

void HashTable_chgDatByName(HashTable * self, char * name, void * data) {
	if(self && name) {
		HashItem * packed = HashItem_new(name);
		int index = packed->hashKey % strlen(name);
		if(self->items[index]->hashKey == packed->hashKey) {
			HashItem_free(packed);
			self->items[index]->data = data;
			return;
		} else {
			HashItem * res = HashItem_findInColision(self->items[index], packed);
			HashItem_free(packed);
			res->data = data;
			return;
		}
	}
	ErrorMessage("Error: NULL pointer Exception in HashTable_chgDatByName()");
}

static void __checkSize(HashTable* self, int min) {
	if(self) {
		int save = self->capacity;
		self->capacity *= 2;
		if(self->capacity <= min) self->capacity = min;
		HashItem ** new = realloc(self->items, self->capacity);
		if(!new)
			ErrorMessage("Out of memeory");
		self->items = new;
		for(int i = save; i < self->capacity; i++) {
			self->items[i] = NULL;
		}
	}
}
