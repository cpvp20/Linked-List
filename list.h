#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

typedef struct strNode * Node, * Iterator;
typedef struct strList * List;
typedef void * Type;

//Funciones propias del contenedor List:

List list_create(void (*destructor)(Type));
void list_destroy(List);
int  list_size(List);
void list_add(List, Type);
Type list_get(List, int p);
void list_set(List, Type, int p);
Type list_remove(List, int p);

//Funciones- implementar iteradores para contenedor List

Iterator list_begin(List);
Iterator list_end(List);
bool list_hasNext(Iterator);
bool list_hasPrior(Iterator);
Iterator list_next(Iterator);
Iterator list_prior(Iterator);
Type list_data(Iterator);

#endif /* LIST_H_ */
