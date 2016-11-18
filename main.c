#include <string.h>
#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %lu elementos\n", longitud(lista));
	
    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %lu elementos\n", longitud(lista));
    
    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %lu elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %lu elementos\n", longitud(lista));
	
    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);
	
    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}

/*Compara 2 'Elemento' que contienen como valor un 'int'*/
int cmp_int(const void* a, const void* b) {
	int *ac = (int*) a, *bc = (int*) b;
	return (*ac > *bc) - (*ac < *bc);
}

/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)) {
	if (*lista == NULL)	return;
	Elemento *tmp = *lista;
	size_t i, n = longitud(lista);
	int data[n];
	for (i = 0; i < n; i++) {					//guardamos valores en un arreglo para que lo ordene qsort
		data[i] = *(int*)tmp->valor;
		tmp = tmp->siguiente;
	}
	qsort(&data, n, sizeof(int), cmp);
	for (i = 0, tmp = *lista; i < n; i++) {		//regresamos los valores a la lista
		memcpy(tmp->valor, data+i, sizeof(int));
		tmp = tmp->siguiente;
	}
}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista ls) {
	Elemento *tmp = *ls;
	while(tmp != NULL) {
		Elemento *aux = tmp;
		tmp = tmp->siguiente;
		free(aux->valor);
		free(aux);
	}
	free(ls);	//liberamos la lista
	ls = NULL;
}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista lista, size_t posicion) {
	if (*lista == NULL || posicion < 0)	return NULL;
	Elemento *tmp = *lista, *ret;
	if (posicion == 0) {		//caso distinto a que si fuese en una posicion distinta
		*lista = tmp->siguiente;
		return tmp;
	}
	while (--posicion) {
		tmp = tmp->siguiente;
		if (tmp->siguiente == NULL)
			return NULL;
	}
	ret = tmp->siguiente;
	tmp->siguiente = tmp->siguiente->siguiente;
	return ret;
}

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_int(Lista lista) {
	Elemento *tmp = *lista;
	printf("[ ");
	while (tmp != NULL) {
		printf("%d ", *(int*)tmp->valor);
		tmp = tmp->siguiente;
	}
	printf("]\n");
}

/*Crea una lista vacía*/
Lista crea_lista() {
	Lista lista = (Lista) malloc(sizeof(Lista));
	*lista = NULL;		//lista esta vacia
	return lista;
}

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
int inserta_elemento(Lista lista, void *valor) {
	Elemento *new = (Elemento*) malloc(sizeof(Elemento));
	new->siguiente = NULL;
	new->valor = valor;
	if (*lista == NULL) {	//la lista esta vacia
		*lista = new;
		return 1;
	}
	int tam = 0;
	Elemento *tmp = *lista;		//si hay elomentos nos recorremos hasta el final.
	while (tmp->siguiente != NULL) {
		tmp = tmp->siguiente;
		tam++;
	}
	tmp->siguiente = new;
	return tam;
}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
	Elemento *tmp = *lista;
	size_t tam = 0;
	while (tmp != NULL) {
		tam++;
		tmp = tmp->siguiente;
	}
	return tam;
}
