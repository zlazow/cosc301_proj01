#ifndef __LIST_H__
#define __LIST_H__

/* your function declarations associated with the list */
struct node {
	int number;
	struct node *next;
} node;

/* your function declarations associated with the list */
void list_append(int num, struct node **head);
void list_print(struct node *list);
void list_delete(struct node *list);
#endif // __LIST_H__
