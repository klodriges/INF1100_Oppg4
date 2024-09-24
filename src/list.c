#include "list.h"
#include <stdlib.h>

//A structure for the nodes in the list
typedef struct node {
    void *item;
    struct node *next;
} node_t;

struct list {
	node_t *head;
};

//A funciton to create a new node
node_t *create_node(void *item, node_t *next) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        //Memory allocation failure
        return NULL;
    }
    new_node->item = item;
    new_node->next = next;
    return new_node;
}

//Allocate space in the memory for the address of the head of a new list
list_t *list_create(void) {
	list_t *list = malloc(sizeof(list_t));
 	if (list == NULL) {
        //Allocation failure
        return NULL;
    }

	list->head = NULL;	
	return list;
}

//Progressivly free each element in the list, then the list itself at the end
void list_destroy(list_t *list){
	node_t *current = list->head;
	while(current != NULL){
		node_t *next = current->next;
		free(current);
		current = next;
	}
	free(list);
}

//Sets up a new node then puts it at the head of the list, moving the original head element to its next
void list_addfirst(list_t *list, void *item){    
    node_t *new_node = create_node(item, list->head);

    list->head = new_node;
}

//Walks through the list untill we find the node pointing to void and add our new item
void list_addlast(list_t *list, void *item) {
    node_t *new_node = create_node(item, NULL);

    if (list->head == NULL) {
        // If the list is empty, set the head to the new node
        list->head = new_node;
    } else {
        // Traverse to the last node
        node_t *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

//Walking through the list untill we find the item that is to be removed, then changing the pointers in the list to point "past" that item
void list_remove(list_t *list, void *item){
	node_t *previous = NULL;
	node_t *current = list->head;

	while(current != NULL){
		if(current->item == item){
			if(previous == NULL){
				//If there are no items before the one we want to remove, change the start of the list
				list->head = current->next;
			} else {		
				//Else change the pointer of previous to the pointer of the object we wish to remove
				previous->next = current->next;
			}
			free(current);
		} else {
			previous = current;
			current = current->next;
		}
	}
}

// Walk thorugh the list, starting at one to count the first item. If the node has a next node, add one to the count and walk.
int list_size(list_t *list){
	int count = 0;
	node_t *current = list->head;
	while(current != NULL){
		count++;
		current = current->next;
	}
	return count;
}
