#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

#define MAX 10005 //m�ximo numero de v�rtices
#define Nodo pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas

//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {//cmp es un comparador.
    bool operator() ( const Nodo &a , const Nodo &b ) {//se utiliza para realizar una comparaci�n, puesto que se necesita recibir informaci�n y compararla
    }
};
vector< Nodo > ady[ MAX ]; //lista  adyacencia
int distancia[ MAX ];      //distancia  de v�rtice inicial a v�rtice
bool visitado[ MAX ];      //para v�rtices visitados
priority_queue< Nodo , vector<Nodo> , cmp > Q; /*priority queue propia del c++, en espa�ol cola de prioridades, la cual es similar a una cola solo que tiene
adicionalmente, una propiedad asignada; usamos el comparador definido para que el de menor valor este en el tope, el tope ser�a q*/
int V;                     //numero de vertices, n�mero de nodos
int previo[ MAX ];         //para la impresion de caminos

//funci�n de inicializaci�n
void init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF;  //inicializamos todas las distancias con valor infinito
        visitado[ i ] = false; //inicializamos todos los v�rtices o nodos como no visitados
        previo[ i ] = -1;      //inicializamos el previo del vertice i con -1
    }
}

//Paso de minimizaci�n
void minimizacion( int actual , int adyacente , int peso ){
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  //minimizamos el v�rtice o nodo actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el v�rtice o nodo previo
        Q.push( Nodo( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}

//Impresion del camino m�s corto desde el v�rtice inicial y final ingresados.
void print( int destino ){
    if( previo[ destino ] != -1 )    //si aun poseo un v�rtice o nodo previo
        print( previo[ destino ] );  //recursivamente sigo explorando
    printf("%d " , destino );        //terminada la recursion imprimo los vertices recorridos
}

void corto( int inicial ){//funci�n creada para indicar el camino m�s corto de un nodo a otro
    init(); //inicializamos nuestros arreglos
    Q.push( Nodo( inicial , 0 ) ); //Insertamos el v�rtice o nodo inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;      // inicializamos la distancia del nodo o v�rtice inicial como 0
    int actual , adyacente , peso; //declaraci�n de variables de tipo entero
    while( !Q.empty() ){                   //Mientras cola no este vacia haga la siguiente acci�n
        actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo ser� el inicial.
        Q.pop();                           //Sacamos el elemento de la cola
        if( visitado[ actual ] ) continue; //Si el v�rtice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[ actual ] = true;         //Marco como visitado el v�rtice actual

        for( int i = 0 ; i < ady[ actual ].size() ; ++i ){ //reviso las adyacentes al v�rtice actual
            adyacente = ady[ actual ][ i ].first;   //identificaci�n del v�rtice adyacente
            peso = ady[ actual ][ i ].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !visitado[ adyacente ] ){        //si el vertice adyacente no fue visitado
                minimizacion( actual , adyacente , peso ); //realizamos el paso de minimizaci�n
            }
        }
    }


    printf( "\tDistancias mas cortas iniciando en vertice %d\n" , inicial );//mensaje en pantalla.
    for( int i = 1 ; i <= V ; ++i ){
        printf("\tVertice %d , distancia mas corta = %d\n" , i , distancia[ i ] );
    }

    puts("\tPara hallar el camino mas corto del vertice de origen al vertice destino," );
    printf("\tIngrese el vertice destino: ");
    int destino;
    scanf("%d" , &destino );
    print( destino );
    printf("\n");
}


int main(){
 int a;
 int E , origen, destino , peso , inicial;
 cout<<"\tBienvenido al programa de Grafos para hallar la distancia mas corta de un nodo o vertice al otro. "<<endl;
 cout<<"\tIngrese la cantidad de nodos y arcos que contendra el grafo. "<<endl;//mensajes en pantalla para el usuario
 cout<<"\tingrese numero de nodos: ";
 scanf("%d", &V);//almacenamiento de datos
 cout<<"\tingrese numero de arcos: ";
 scanf("%d", &E);
 
 cout<<"\tIngresar El nodo o vertice de origen, su arista y la distancia o peso de un nodo a otro dejando un espacio entre cada numero "<<endl;
 for (int i=0; i<E; i++){//ciclo usado para almacenar la informaci�n que se le va a pedir al usuario
     scanf("%d %d %d" , &origen , &destino , &peso );
     ady[ origen ].push_back( Nodo( destino , peso ) ); //consideremos grafo dirigido
 }
     
    cout<<"\tIngrese el vertice inicial: "<<endl;
    scanf("%d" , &inicial );
    corto( inicial );
    return 0;
}
