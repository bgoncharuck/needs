struct DoubleLinkedNode {
	int data;
	struct DoubleLinkedNode* prev;
	struct DoubleLinkedNode* next;
};
typedef struct DoubleLinkedNode DLNode;

struct DoubleLinkedList {
	DLNode* head;
	DLNode* tail;
	size_t size;
};
typedef struct DoubleLinkedList DL_list;

DLNode* newDLNode(void) {
		DLNode* res = malloc(sizeof(DLNode));
		res->data = 0;
		res->prev = NULL;
		res->next = NULL;
		return res;
}

DLNode* newDLNodeDat(int dat) {
		DLNode* res = malloc(sizeof(DLNode));
		res->data = dat;
		res->prev = NULL;
		res->next = NULL;
		return res;
}

bool freeDLNode(DLNode* node) {
	if(node != NULL) {
		free(node);
		return true;
	}
	return false;
}

DLNode* remDLNodeInPos(DL_list* list, size_t POS) {
	if(list->head == NULL || POS == 0 || list->size == 0)
		return NULL;
	else if(POS > list->size)
		POS = list->size;
	DLNode* toRem = list->head;
	while(toRem != NULL && POS > 1) {
		toRem = toRem->next;
		POS--;
	}
	if (toRem->prev != NULL)
		toRem->prev->next = toRem->next;
	else
		list->head = list->head->next;
	if (toRem->next != NULL)
		toRem->next->prev = toRem->prev;
	list->size--;
	return toRem;
}

// O(1)
bool addFirstDLNode(DL_list* list, DLNode* node) {
	if(node != NULL) {
		node->prev = NULL;
		node->next = list->head;
		if (list->head != NULL)
			list->head->prev = node;
		list->size++;
		list->head = node;
		if(list->size == 1)
			list->tail = node;
		return true;
	}
	return false;
}

bool addLastDLNode(DL_list* list, DLNode* node) {
	if(node != NULL) {
		node->next = NULL;
		node->prev = list->tail;
		if (list->tail != NULL)
			list->tail->next = node;
		list->size++;
		list->tail = node;
		if(list->size == 1)
			list->head = node;
		return true;
	}
	return false;
}

DLNode* remFirstDLNode(DL_list* list) {
	if(list->size > 0) {
		DLNode* removed = list->head;
		list->size--;
		list->head = list->head->next;
		return removed;
	}
	return NULL;
}

DLNode* remLastDLNode(DL_list* list) {
	if(list->size > 0) {
		DLNode* removed = list->tail;
		list->size--;
		list->tail = list->tail->prev;
		return removed;
	}
	return NULL;
}
