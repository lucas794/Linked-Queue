#include "cola.h"
#include <stdlib.h>
#include <string.h>

/***************ESTRUCTURA NODO & COLA***********************/
typedef struct cola_nodo nodo_cola_t;                     
														  
struct cola_nodo {                                        
	void *dato;                                           
	nodo_cola_t *siguiente;                               
};                                                        
                                                          
struct cola {                                              
	nodo_cola_t *ptrPrimero, *ptrUltimo;                  
};                                                        
/************************************************************/

cola_t* cola_crear( void )
{
	cola_t* nueva_cola = malloc( sizeof(cola_t) );
	
	if( nueva_cola == NULL )
		return NULL;
	
	/* no hay ni primero ni último */
	nueva_cola->ptrPrimero = NULL;
	nueva_cola->ptrUltimo  = NULL;
	
	return nueva_cola;
}

bool cola_esta_vacia(const cola_t *cola)
{
	/* aclaración:
	 * Una pila está vacia cuando no tiene ningun puntero apuntando
	 * a primero y a la vez ningun puntero apuntando al último
	*/
	return ( !cola->ptrPrimero && !cola->ptrUltimo ); 
}

bool cola_encolar(cola_t *cola, void* valor)
{
	nodo_cola_t* vagon;
	
	vagon = malloc( sizeof(nodo_cola_t) );
	
	if( vagon == NULL )
		return false;
			
	vagon->dato = valor;
	
	/* es el ultimo vagon el agregado ,por ende el siguiente es NULL */
	vagon->siguiente = NULL;
		
	if( cola_esta_vacia(cola) ) 
	{
		/* La cola está vacia? este vagon procede a ser el primero 
		 * y a la vez tambien el último*/
		cola->ptrPrimero = vagon;
	}
	else
	{
		/* como todo vagón a agregar debe ir al final de la cola
		 * referenciamos el último vagon que teniamos 
		 * (cola->ptrUltimo) al vagon actual */
		cola->ptrUltimo->siguiente = vagon;	
	}
	
	/* ahora, nuestro ultimo vagon es el ingresado */
	cola->ptrUltimo = vagon;
	
	return true;
}

void* cola_ver_primero(const cola_t *cola)
{
	return cola_esta_vacia(cola) ? NULL : cola->ptrPrimero->dato;
}

void* cola_desencolar(cola_t *cola)
{
	if( cola_esta_vacia(cola) )
		return NULL;
	
	/* sacamos el dato de cola->ptrPrimero */
	void *aux_dato = cola_ver_primero(cola);
	
	/* ahora, el primero es el siguiente del primero 
	 * Sin embargo, hay que armar un vagón temporal que 'storee'
	 * el primer nodo , así liberar posteriormente
	 * la memoria pedida por el nodo en 'encolar' */
	nodo_cola_t *nodo_auxiliar = cola->ptrPrimero;

	if( cola->ptrPrimero == cola->ptrUltimo )
	{
		/* si ingresó aqui significa que solo habia 1 elemento */
		/* La cola ahora empieza vacia sin referencia ni al final
			ni al primero */
		cola->ptrPrimero = NULL;
		cola->ptrUltimo = NULL;
	}
	else
	{
		/* hay mas nodos, hay que ahora setear el primero de la 
		 * cola con el siguiente del elemento a borrar */
		cola->ptrPrimero = cola->ptrPrimero->siguiente;
	}
	free(nodo_auxiliar);
	
	return aux_dato;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*))
{		
	while( !cola_esta_vacia(cola) )
	{
		void *dato = cola_desencolar(cola);
		
		if( destruir_dato )
			destruir_dato(dato);
	}
			
	free(cola);
}
	
