struct DoubleLinkedNode {
	int data;
	//double data;
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

bool DLList_constructor(DL_list* list) {
	if(list != NULL) {
		list->head = NULL;
		list->tail = NULL;
		list->size = 0;
		return true;
	}
	return false;
}

DLNode* newDLNode(void) {
		DLNode* res = malloc(sizeof(DLNode));
		res->data = 0.0;
		res->prev = NULL;
		res->next = NULL;
		return res;
}

DLNode* newDLNodeDat(/*double*/ int dat) {
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
		if (list->tail != NULL)
			list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
		list->size++;
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

bool remFreeLastDLNode(DL_list* list) {
	if(list->size > 0) {
		list->size--;
		DLNode* toFree = list->tail;
		list->tail = list->tail->prev;
		freeDLNode(toFree);
		return true;
	}
	return false;
}

bool remFreeFirstDLNode(DL_list* list) {
	if(list->size > 0) {
		list->size--;
		DLNode* toFree = list->head;
		list->head = list->head->next;
		freeDLNode(toFree);
		return true;
	}
	return false;
}

bool swapDLNodes(DLNode* first, DLNode* second) {
	if(first != NULL && second != NULL) {
		DLNode* tempPrev = first->prev;
		DLNode* tempNext = first->next;
		first->prev = second->prev;
		first->next = second->next;
		second->prev = tempPrev;
		second->next = tempNext;
		return true;
	}
	return false;
}

bool freeDLList(DL_list* list) {
	if(list != NULL) {
		while(remFreeLastDLNode(list));
		return true;
	}
	return false;
}
