#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ArbolesTrie.h"



/*****************************************************************************
 * NOMBRE: stNuevoNodo
 * 
 * DESCRIPCION: Esta funcion Crea un nodo  pidiendo memoria Dinamica, y poniendo 
 *              en cero todo
 * 
 * PARAMETROS: Ninguno
 * 
 * RETORNA: apuntador a la estructura de tipo Trie
 * **************************************************************************/


stTrie *stNuevoNodo(void)
{
    stTrie *stNodo;
    stNodo = ( stTrie *) malloc(sizeof (stTrie)) ;  // se pide memoria dinamica
    memset((char *)stNodo, 0, sizeof(stTrie)) ;     // se inicializa toda el aera de memoria en cero
    return( stNodo) ;
}


/*******************************************************************************
 * NOMBRE:      vInsertar_Palabra
 * 
 * DESCRIPCION: Inserta una palabra en el arbol trie, asigna 1 si es 
 *              una hoja, Ademas de asignale  a esa hoja, la posicion en el 
 *              archivo del significado
 * 
 * PARAMETROS: 
 *              stCabeza, apuntador al primer nodo del arbol
 *              szPablapra, apuntador a la cadena de caracteres que contien la palabra
 *              a insertar en el arbol trie
 *              ulSignificado, Possicion en el archivo qie contiene el significado
 * 
 * RETORNA:     nada
 * ****************************************************************************/
void vInsertar_Palabra(stTrie *stCabeza, char *pszPalabra, unsigned long ulSignificado)
{
    stTrie *stActualNodo ;
    stActualNodo = stCabeza ;
    short sIndice ;

    if( *pszPalabra == 0)
        return ;

    // ciclo para recorre el string palabra por palabra hasta que encuentre el final de cadena
    while( *pszPalabra ) 
    {
        if(isalpha(*pszPalabra))
            sIndice = tolower(*pszPalabra) - 97;
        else
            continue ;

        if( stActualNodo->stCaracteres[sIndice] == NULL) // si no hay continuacion, agrega la letra
            stActualNodo->stCaracteres[sIndice] = stNuevoNodo(); // se agrega el nodo de la nueva letra
        stActualNodo = stActualNodo->stCaracteres[*pszPalabra-'a'] ; // se continua al siguiendo nodo siguiendo la rama del arbol 
                                                                    // hasta llegar a la ultima letra de la palabra
        pszPalabra ++ ;     
    }
    stActualNodo->ulSignificado = ulSignificado ; // se le asigna a esa palabra el significado
}

/*******************************************************************************
 * NOMBRE:      stBuscar
 * 
 * DESCRIPCION: Busca el nodo que corresponde a la ultima letra que esta en el string
 *              pszBuscar 
 * 
 * PARAMETROS: 
 *              stCabeza, apuntador al primer nodo del arbol
 *              pszBuscar, apuntador a la cadena de caracteres que contien la palabra
 *              a Buscar en el arbol trie
 * 
 * RETORNA:     el nodo desde sonde se va buscar toods los posibles significados
 *              o NULL sino lo encontro
 * ****************************************************************************/
stTrie *stBuscar(stTrie *stCabeza, char *pszBuscar)
{
stTrie *stNodo = stCabeza ;
short sIndice ;

    if( stNodo == NULL)
        return(NULL) ;
    while(*pszBuscar)
    {
        // se usa el valor de la letra ascii que comieza en 
        // 'a' = 97 y termina en 'z' = 122. para poder saber en que posisicion del vector
        // le corresponde a cada letra, siempre se reta por la letra 'a' en su valos ascii que es la inicial 
        // ejemplo: la letra 'g' = 103. Restamos 'g' - 'a' en realidad la computadora hace 103 - 97 = 6 
        // le corresponde la posicion 6 al apuntador de la letra g  
        if(isalpha(*pszBuscar))
            sIndice = tolower(*pszBuscar) - 97;
        else
            continue ;
        stNodo = stNodo->stCaracteres[sIndice] ;
        if( stNodo == NULL ) // si no hay continuidad en arbol es porque no encontro
            return(NULL);
        pszBuscar++ ; // continua con la siguiente letra
    }
    return(stNodo) ; // Retorna el Nodo encontrado
}


/*******************************************************************************
 * NOMBRE:      vBusca_Imprime_Archivo
 * 
 * DESCRIPCION: Busca el nodo que corresponde a la ultima letra que esta en el string
 *              szPalabra 
 * 
 * PARAMETROS: 
 *              stCabeza, apuntador al primer nodo del arbol
 *              szPalabra, apuntador a la cadena de caracteres que contien la palabra
 *              a Buscar en el arbol trie
 * 
 * RETORNA:     nada
 * ****************************************************************************/


void vBusca_Imprime_Archivo( unsigned long ulPosicion, char *pszPalabra)
{
    FILE *fpArchivo ;
    char szSignificado[500] ;
    
    fpArchivo = fopen(szDiccionario, "r"); /* se abre el archivo diccionario*/
    if( fpArchivo  == NULL)
        return ;

    fseek(fpArchivo,ulPosicion,SEEK_SET) ;  // se posiciona en el archivo para leer el significado
    fgets(szSignificado,500,fpArchivo) ;    // Lee la linea del significado
    printf("\n[%s]:%s",pszPalabra,szSignificado);
    while(fgets(szSignificado,500,fpArchivo)) // lee todos los siguientes significados
    {
        if(szSignificado[0] == '+') // si comienza por + debe imprimirse sino debe salirce del ciclo
                                    // no es significado de esa palabra
            printf("\n[%s]:%s",pszPalabra,szSignificado) ;
        else
            break;
    }
    fclose(fpArchivo) ;
}


/*******************************************************************************
 * NOMBRE:      vImprime
 * 
 * DESCRIPCION: Busca el nodo que corresponde a la ultima letra que esta en el string
 *              pszPalabra
 *               
 * PARAMETROS: 
 *              stCabeza, apuntador al primer nodo del arbol
 *              szPalabra, apuntador a la cadena de caracteres que contien la palabra
 *              a Buscar en el arbol trie
 * 
 * RETORNA:     nada
 * ****************************************************************************/

void vImprime(stTrie *stCabeza, char *pszPalabra)
{
    stTrie *stNodo ;
    short sCont ;
    char szNuevaPalabra[100] ;
    memset(szNuevaPalabra,0,100) ;

    stNodo = stCabeza ;

    if(stNodo == NULL)
        return ;
    /* si tiene significado se imprime */
    if( stNodo->ulSignificado != 0)
    {
        vBusca_Imprime_Archivo(stNodo->ulSignificado,pszPalabra);
    }
    // se busca si hay mas significados y se imprimen
    for( sCont = 0; sCont < CANT_CARACTERES; sCont++)  
    {
        sprintf(szNuevaPalabra,"%s%c",pszPalabra,(sCont+'a')) ;
        vImprime(stNodo->stCaracteres[sCont], szNuevaPalabra);
    }
}


/*******************************************************************************
 * NOMBRE:       sLeer_Diccionario
 * 
 * DESCRIPCION:  DAdo el nombre de una archivo, lo abre y guarda las palabras alli 
 *               contenidas en un formato especifico em un arbol de tipo trie
 *  
 * PARAMETROS: 
 *               pszDiccionario nombre del archivo que se va a abrir 
 * 
 * RETORNA:     ERROR se no fue posible abrir el archivo
 *              EXITO si la cargar del archivo fue posible
 ******************************************************************************/


short sLeer_Diccionario (char *pszDiccionario)
{
    FILE *fpArchivo;
    char szPalabra[250];
    char szSignificado[250] ;
    unsigned long ulOffSet = 0 ;

    // se hace la a pertura del archivo
    fpArchivo = fopen(pszDiccionario,"r") ;
    if( fpArchivo == NULL)
        return(ERROR) ;

    // se lee la palabra
    while(fscanf(fpArchivo, "%s",szPalabra))
    {
        // si no lee nada se acabo el archivo y sale
        if(strlen(szPalabra) == 0)
            break;
            
    szPalabra[strlen(szPalabra)] = 0 ;
        // se suma la cantidad de caracrteres de la palbra para saber
        // DOnde esta el primer significado de esa palabra 
        ulOffSet += strlen(szPalabra);
        // se lee el significado
        fgets(szSignificado,250,fpArchivo) ;
        // si la primera letra es un '+' es el significado adicional de la palabra anterior
        // solo se suma la cantidad de carcateres y lo regresa a la patte superior del while
        if(szPalabra[0] == '+')
        {
            ulOffSet += strlen(szSignificado) ;
            memset(szPalabra,0,sizeof(szPalabra));
            continue ;
        }
        //Agrega la nueva palabra al arbol
        //printf("[%s][%lu]",szPalabra,ulOffSet) ;
        vInsertar_Palabra (&stNodoInicial,szPalabra, ulOffSet) ;
        ulOffSet += strlen(szSignificado)  ;
        memset(szPalabra,0,sizeof(szPalabra));
    }
    return(EXITO) ;
}


int main()
{
    //char szOpcion[20] ;
    char szPalabra[250];
    stTrie *stRTA ;

    do 
    {

        printf("\n> ") ; 
        gets(szPalabra) ;
        if(szPalabra[0] == 'h')
        {
            printf("\n>TODOS LOS DERECHOS RESERVADOS") ;
            printf("\n>Este programa guarda un diccionario en ingles") ;
            printf("\n>dado los comando seguido :") ;
            printf("\n> h         ==> para obtener esta ayuda") ;
            printf("\n> q         ==> para salir de este programa");
            printf("\n> I  Nombre ==> Carga el diccionario que hay en el archivo <nombre>.dic") ;
            printf("\n> s palabra ==> busca el sognificado de la pablabra <palabra>");
            printf("\n> p prefijo ==> muestra los significados de de todas la palabras que comienza con el prefijo <prefijo>") ;
            printf("\n> ");
        }
        if( szPalabra[0] == 'I')
        {
            sprintf(szDiccionario,"%s.dic",(szPalabra+2)) ;
            if( sLeer_Diccionario (szDiccionario) == 0 )
                printf("\n>ERROR: No pude cargar el diccionario %s.dic",(szPalabra+2)) ;

        }
        if( szPalabra[0] == 's')
        {
            stRTA = stBuscar(&stNodoInicial, (szPalabra+2)) ;
            if(stRTA == NULL )
            {
                printf("\n>ERROR: La palabra no existe") ;
            }
            else{
            
                if(stRTA->ulSignificado != 0)
                {
                    vBusca_Imprime_Archivo(stRTA->ulSignificado,szPalabra+2) ;
                }
                else
                    printf("\n>ERROR: No es una palabra") ;
            }
        }

        if( szPalabra[0] == 'p')
        {              
            stRTA = stBuscar(&stNodoInicial, (szPalabra+2)) ;
            if( stRTA == NULL)
                printf("\n>ERROR: El prefijo no existe") ;
            else
                vImprime(stRTA, (szPalabra+2)) ;
        }
    }
    while(szPalabra[0] != 'q');

return 0 ;    
}
