#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	setbuf(stdout, 0);
	printf("Hello There\n");
	List myList = list_create(NULL);

	int aux[12]; //arreglos estaticso de variables auxiliares

	printf("Escribe 12 numeros que quieres agregar a la lista\n");
	for (int i = 0; i < 12; i++)
	{
		scanf("%d", &aux[i]);
		list_add(myList, &aux[i]);
	}

	int * a = list_get(myList, 2);	//imprime el elemento de posicion 2
	printf("Elemento 2 es %d\n", *a);

	a = list_get(myList, 3);	//imprime el elemtno de pos 3
	printf("Elemento 3 es %d\n", *a);

	printf("ahora reemplazaremos el elemento 5 por 88\n");
	int b = 88;
	int* bP = &b;
	list_set(myList, bP, 5);	//remplaza el elemento 5 por n
	a = list_get(myList, 5);	//imprime el elemento 5 para checar que si cambio
	printf("%d\n", *a);
	printf("ahora borraremos el elemento 11\n");
	list_remove(myList, 11);	//elimina y devuelve el elemento 11


	// Los iteradores nos permiten recorrer la lista del incio al final
	Iterator ite = list_begin(myList);
	while(list_hasNext(ite))
	{
		ite = list_next(ite);
		int *n = list_data(ite);
		printf("%d ", *n);
	}
	printf("\n");

	// Los iteradores también nos permiten recorrer la lista del final hacia el inicio
	ite = list_end(myList);
	while(list_hasPrior(ite))
	{
		ite = list_prior(ite);
		int *n = list_data(ite);
		printf("%d ", *n);
	}

	//list_destroy(myList);
	return 0;
}
