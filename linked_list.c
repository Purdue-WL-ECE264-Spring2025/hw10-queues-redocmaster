#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
	struct list_node * nd = malloc(sizeof(struct list_node));
	nd->value = value;
	nd->next = NULL;
	return nd; }

void insert_at_head(struct linked_list *list, size_t value) {
	struct list_node * ptr = new_node(value);
	ptr->next = list->head;
	list->head = ptr;
}

void insert_at_tail(struct linked_list *list, size_t value) {
	if(list->head == NULL)
	{list->head = new_node(value);}
	else
	{
		struct list_node * p = list->head;
		while((p->next) != NULL)
		{p = p->next;}
		p->next = new_node(value);
	}

}

size_t remove_from_head(struct linked_list *list) {
  	if(list->head == NULL)
	{
		printf("empty list");
		return 0;
	}	
	struct list_node * q = list->head;
	size_t value = q->value;
	list->head = list->head->next;
	free(q);	
	return value; }

size_t remove_from_tail(struct linked_list *list) {
	
	struct list_node *p = list->head;
 	struct list_node *q = p->next;
	if(q->next != NULL)
	{
		p = p->next;
		q = q->next;
	}
	size_t value = q->value;
	free(q);	

	return value; }

void free_list(struct linked_list list) {
	while(list.head != NULL)
	{
		struct list_node * p = list.head->next;
		free(list.head);
		list.head = p;
	}

}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
