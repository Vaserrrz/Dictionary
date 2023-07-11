#include "func.h"

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
            printf("\n>dado los comandos seguido :") ;
            printf("\n> h         ==> para obtener esta ayuda") ;
            printf("\n> q         ==> para salir de este programa");
            printf("\n> I  Nombre ==> carga el diccionario que hay en el archivo <nombre>.dic") ;
            printf("\n> s palabra ==> busca el significado de la pablabra <palabra>");
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
                    vBusca_Imprime_Archivo(stRTA->ulSignificado,szPalabra) ;
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