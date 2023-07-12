#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define ERROR                0
#define EXITO                1
#define CANT_CARACTERES     26 // Cantidad de carcateres usados en el alfabeto EEUU

struct ArbolTrie 
{
    unsigned long ulSignificado  ;  // Posicion en el archivo donde se encuentra el significado de la
                                    // palbra que se junto, Tambien significa que es una hoja
    struct ArbolTrie *stCaracteres[CANT_CARACTERES]; // Apuntador a cada una de la letras del arbol 
} ;
typedef struct ArbolTrie stTrie ; // se renombra la estructura para mayor comodidad
stTrie stNodoInicial ;          // Nodo Cabecera del Arbol Trie
char szDiccionario[100] ;       // Nombre del Archivo Diccionario

// Funciones
stTrie *stBuscar(stTrie *stCabeza, char *pszPalabra);
void vBusca_Imprime_Archivo( unsigned long ulPosicion, char *pszPalabra);
void vImprime(stTrie *stCabeza, char *pszPalabra);
short sLeer_Diccionario (char *pszDiccionario);


