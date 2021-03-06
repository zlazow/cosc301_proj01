#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

/* your list function definitions */

/*
struct node {
    int number;
    struct node *next; 
};
*/


void list_append(int num, struct node**head){
	struct node *new = malloc(sizeof(struct node));
	new->number = num;

	//if head is null, make the node the head
	if(*head == NULL) {
		new->next = *head;
		*head = new;
		return;
	}
	//if head's val > i, make the head the new value.
	if ( ((*head)->number) >num){
		new->next = *head;
		*head = new;
		return;
	}
	//otherwise iterate through the list, finding a value bigger 
	//than the node. Make the previous node point to the new node,
	//and the new node point to the node that was just found to be 		//bigger. 
	struct node *iterator = *head;
	struct node *prev = *head;
	iterator = iterator->next;
	
	while(iterator != NULL) {
		if((iterator->number) > num){
			break;
		}
		prev = iterator;
		iterator = iterator->next;
	}
	//break fixes the case in which the new node is the max.
	prev->next = new;
	new->next = iterator;
}

void list_print(struct node *list) {
	//cycle through each element and print it out...
    	while (list != NULL) {
        	printf("%d\n", list->number);
        	list = list->next;
    	}
}

void list_delete(struct node *list) {
	//cycle through each element and delete it.
    	while (list != NULL) {
        	struct node *tmp = list;
        	list = list->next;
        	free(tmp);
   	}
}


