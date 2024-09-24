#include "list.h"
#include <stdlib.h>

typedef struct node {
    void *item;
    struct node *next;
} node_t;

struct list {
	node_t *head;
}

list_t *list_create(void) {
	list_t newList;

	// this is missing a bit that hold the item
	newList->next = NULL;
}

void list_addfirst(list_t *list, void *item){
	
}

//Walks through the list untill we find the node pointing to void and add our new item
void list_addlast(list_t *list, void *item){
	while(list->next != NULL){
		list = list->next;		
	}
	
	node_t *newNode = malloc(sizeof(list_t));
	
	newNode->next = NULL;
	newNode->item = item;

	list->next = newNode;	
}

//assuming item is unique
//Walking through the list untill we find the item that is to be removed, then changing the pointers in the list to point "past" that item
void list_remove(list_t *list, void *item){
	list_t *previous = NULL;
	list_t *current = *list;

	while(current != NULL){
		if(current->item == item){
			if(previous != NULL){		//If there are no items before the one we want to remove, change the start of the list
				list->head = current->next;
			} else {					//Else change the pointer of previous to the pointer of the object we wish to remove
				previous->next = current->next;
			}
			//free(current); Not sure if we need this because of the "only freeing the node." line						
		} else {
			previous = current;
			current = current->next;
		}
	}
}

// Walk thorugh the list, starting at one to count the first item. If the node has a next node, add one to the count and walk.
int list_size(list_t *list){
	int count = 0;
	while(list != NULL){
		count++;
		list = list->next;
	}
	return count;
}