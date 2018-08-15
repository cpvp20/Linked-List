#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct strNode {
	Type data;
	struct strNode *prior, *next;
};

struct strList {
	struct strNode *first, *last, *prefirst, *postlast;
	int size;
	void (*destructor)(void *);
};

List list_create(void (*destructor)(Type)){
	List L = (List) malloc(sizeof(struct strList));
	L->first = NULL;
	L->last = NULL;

	L->prefirst = (Node) malloc(sizeof(struct strNode));
	L->prefirst->data = NULL;
	L->prefirst->prior = NULL;
	L->prefirst->next = NULL;

	L->postlast = (Node) malloc(sizeof(struct strNode));
	L->postlast->data = NULL;
	L->postlast->prior = NULL;
	L->postlast->next = NULL;

	L->size = 0;
	L->destructor = destructor;
	return L;
}

void list_destroy(List L){
	if(L == NULL) return;

	Node aux1, aux2;
	aux1 = L->prefirst;
	while(aux1 != NULL)
	{
		aux2 = aux1;
		aux1 = aux1->next;
		if(L->destructor != NULL)	//si no es nulo, lo usamos para liberar la memoria del dato adentro del nodo
			L->destructor(aux1->data);
		free(aux2);	//ahora liberamos el nodo, el ultimo ser el postlast
	}
	free(L);	//al final liberamo la instancia de Lista
}

int list_size(List L){
	return L->size;
}

void list_add(List L, Type t){
	Node n = (Node) malloc(sizeof(struct strNode));
	n->data = t;
	n->next = NULL;
	if (L->first == NULL)	//if the list empty ... this is the first node
	{
		L->first = n;	//set first and prefirst
		L->prefirst->next = L->first;
	}

	else	//if list not empty
	{
		L->last->next = n;	//set last and postlast
		n->prior = L->last;
	}
	L->last = n;	//either way, always update last to new node
	L->postlast->prior = L->last;
	++(L->size);	//update size

}

Type list_get(List L, int p){
	if (p >= L->size) {printf("Error"); exit(1);}	//check that user is not asking for a position not in list

	Node current = L->first;
	for (int i = 0; i < p; i++)
		current = current->next;	//encuentra el p-ano nodo en la lista
	return current->data;
}

void list_set(List L, Type t, int p){
	if (p >= L->size) {printf("Error"); exit(1);}	//check that user is not using a position not in list

	Node current = L->first;
	for (int i = 0; i < p; i++)
		current = current->next;	//encuentra el p-ano nodo en la lista

	current->data = t;
}

Type list_remove(List L, int p){
	if (p >= L->size) {printf("Error"); exit(1);}	//check that user is not deleting a position not in list

	Node current = L->first;
	for (int i = 0; i < p; i++)
		current = current->next;	//encuentra el p-ano nodo en la lista

	if (p == 0)	//en estos dos casos se debe borra de manera diferente, porque con la normal accedes a cosas q no existen, como el prior del primer nodo
	{
		L->prefirst->next = L->first = current->next;	//el nodo siguiente será ahora el primero.
		current->next->prior = L->prefirst;
	}
	else if (p == L->size-1)
	{
		L->postlast->prior = L->last = current->prior;	//el nodo anterior será ahora el ultimo.
		current->prior->next = L->postlast;
	}
	else
	{
		Node previous = current->prior;
		previous->next = current->next; //borrar logicamente
		current->next->prior = previous;
	}
	Type data = current->data;
	free (current);
	--(L->size);	//update size
	return data;
}

Iterator list_begin(List L){
	return L->prefirst;
}

Iterator list_end(List L){
	return L->postlast;
}

bool list_hasNext(Iterator I){
	 return I->next != NULL;	//if (I->next != NULL) return true; else return false;
}

bool list_hasPrior(Iterator I){
	if (I->prior != NULL)
		return true;
	return false;
}

Iterator list_next(Iterator I){
	return I->next;
}

Iterator list_prior(Iterator I){
	return I->prior;
}

Type list_data(Iterator I){
	return I->data;
}

