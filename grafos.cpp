#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <list>
#include <stack>
#include <limits.h>
#define NINF INT_MIN
using namespace std;
class AdjListNode{

        int v;

        int weight;

    public:

        AdjListNode(int _v, int _w)

        {

            v = _v;

            weight = _w;

        }

        int getV()

        {

            return v;

        }

        int getWeight()

        {

            return weight;

        }

};

 

// Clase para representar un gráfico usando representación de lista de adyacencia

class Graph

{

        int V; // No. of vertices’

 

        // Pointer to an array containing adjacency lists

        list<AdjListNode> *adj;

 

        // A function used by longestPath

        void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);

    public:

        Graph(int V); // Constructor

 

        // function to add an edge to graph

        void addEdge(int u, int v, int weight);

 

        // Finds longest distances from given source vertex

        void longestPath(int s);

};

 

Graph::Graph(int V) // Constructor

{

    this->V = V;

    adj = new list<AdjListNode> [V];

}

 

void Graph::addEdge(int u, int v, int weight)

{

    AdjListNode node(v, weight);

    adj[u].push_back(node); // Add v to u’s list

}


void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack)

{

    // Mark the current node as visited

    visited[v] = true;

 

    // Recur for all the vertices adjacent to this vertex

    list<AdjListNode>::iterator i;

    for (i = adj[v].begin(); i != adj[v].end(); ++i)

    {

        AdjListNode node = *i;

        if (!visited[node.getV()])

            topologicalSortUtil(node.getV(), visited, Stack);

    }

 

    // Push current vertex to stack which stores topological sort

    Stack.push(v);

}

 

// The function to find longest distances from a given vertex. It uses

// recursive topologicalSortUtil() to get topological sorting.

void Graph::longestPath(int s)

{

    stack<int> Stack;

    int dist[V];

 

    // Mark all the vertices as not visited

    bool *visited = new bool[V];

    for (int i = 0; i < V; i++)

        visited[i] = false;

 

    // Call the recursive helper function to store Topological Sort

    // starting from all vertices one by one

    for (int i = 0; i < V; i++)

        if (visited[i] == false)

            topologicalSortUtil(i, visited, Stack);

 

    // Inicializar distancias a todos los vértices como infinito y distancia

    //a la fuente como 0

    for (int i = 0; i < V; i++)

        dist[i] = NINF;

    dist[s] = 0;

 

    // Procesar vértices en orden topológico

    while (Stack.empty() == false)

    {

        // Get the next vertex from topological order

        int u = Stack.top();

        Stack.pop();

 

        // Update distances of all adjacent vertices

        list<AdjListNode>::iterator i;

        if (dist[u] != NINF)

        {

            for (i = adj[u].begin(); i != adj[u].end(); ++i)

                if (dist[i->getV()] < dist[u] + i->getWeight())

                    dist[i->getV()] = dist[u] + i->getWeight();

        }

    }

 

    // Calculamo eimprimimos la distancia larga

    for (int i = 0; i < V; i++)

        (dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";

}

 

// Driver program to test above functions


#define MAX 10005 //máximo numero de vértices
#define Nodo pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas

//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {//cmp es un comparador.
    bool operator() ( const Nodo &a , const Nodo &b ) {//se utiliza para realizar una comparación, puesto que se necesita recibir información y compararla
    }
};
vector< Nodo > ady[ MAX ]; //lista  adyacencia
int distancia[ MAX ];      //distancia  de vértice inicial a vértice
bool visitado[ MAX ];      //para vértices visitados
priority_queue< Nodo , vector<Nodo> , cmp > Q; /*priority queue propia del c++, en español cola de prioridades, la cual es similar a una cola solo que tiene
adicionalmente, una propiedad asignada; usamos el comparador definido para que el de menor valor este en el tope, el tope sería q*/
int V;                     //numero de vertices, número de nodos
int previo[ MAX ];         //para la impresion de caminos

//función de inicialización
void init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF;  //inicializamos todas las distancias con valor infinito
        visitado[ i ] = false; //inicializamos todos los vértices o nodos como no visitados
        previo[ i ] = -1;      //inicializamos el previo del vertice i con -1
    }
}

//Paso de minimización
void minimizacion( int actual , int adyacente , int peso ){
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  //minimizamos el vértice o nodo actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vértice o nodo previo
        Q.push( Nodo( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}

//Impresion del camino más corto desde el vértice inicial y final ingresados.
void print( int destino ){
    if( previo[ destino ] != -1 )    //si aun poseo un vértice o nodo previo
        print( previo[ destino ] );  //recursivamente sigo explorando
    printf("%d " , destino );        //terminada la recursion imprimo los vertices recorridos
}

void corto( int inicial ){//función creada para indicar el camino más corto de un nodo a otro
    init(); //inicializamos nuestros arreglos
    Q.push( Nodo( inicial , 0 ) ); //Insertamos el vértice o nodo inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;      // inicializamos la distancia del nodo o vértice inicial como 0
    int actual , adyacente , peso; //declaración de variables de tipo entero
    while( !Q.empty() ){                   //Mientras cola no este vacia haga la siguiente acción
        actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial.
        Q.pop();                           //Sacamos el elemento de la cola
        if( visitado[ actual ] ) continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[ actual ] = true;         //Marco como visitado el vértice actual

        for( int i = 0 ; i < ady[ actual ].size() ; ++i ){ //reviso las adyacentes al vértice actual
            adyacente = ady[ actual ][ i ].first;   //identificación del vértice adyacente
            peso = ady[ actual ][ i ].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !visitado[ adyacente ] ){        //si el vertice adyacente no fue visitado
                minimizacion( actual , adyacente , peso ); //realizamos el paso de minimización
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
 int opcion;
 			  	  // Numero de los vertices son

    // 0, 1, 2, 3, 4, 5 con las siguientes asignaciones:

    // 0=r, 1=s, 2=t, 3=x, 4=y, 5=z

    Graph g(6);

    g.addEdge(0, 1, 5);

    g.addEdge(0, 2, 3);

    g.addEdge(1, 3, 6);

    g.addEdge(1, 2, 2);

    g.addEdge(2, 4, 4);

    g.addEdge(2, 5, 2);

    g.addEdge(2, 3, 7);

    g.addEdge(3, 5, 1);

    g.addEdge(3, 4, -1);

    g.addEdge(4, 5, -2);

 

    int s ;
 bool repetir = true;

     do {
        system("cls");
        
        // Texto del menú que se verá cada vez
        cout << "\n\nMenu de Opciones" << endl;
         cout<<"1. Programa de Grafos para hallar la distancia mas corta de un nodo o vertice al otro. "<<endl;
        cout << "2.  Programa de Grafos para hallar la ruta critica de un nodo o vertice al otro." << endl;
        cout << "0. SALIR" << endl;
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
        	  case 1:
			    cout<<"\tIngrese la cantidad de nodos y arcos que contendra el grafo. "<<endl;//mensajes en pantalla para el usuario
                cout<<"\tingrese numero de nodos: ";
                scanf("%d", &V);//almacenamiento de datos
                cout<<"\tingrese numero de arcos: ";
                scanf("%d", &E);
				cout<<"\tIngresar El nodo o vertice de origen, su arista y la distancia o peso de un nodo a otro dejando un espacio entre cada numero "<<endl;
                for (int i=0; i<E; i++){//ciclo usado para almacenar la información que se le va a pedir al usuario
			       scanf("%d %d %d" , &origen , &destino , &peso );
                   ady[ origen ].push_back( Nodo( destino , peso ) ); //consideremos grafo dirigido
                }
			    cout<<"\tIngrese el vertice inicial: "<<endl;
			    scanf("%d" , &inicial );corto( inicial );
			    break;
			  case 2:
			  
				  cout << "Digite s: "<<endl;
				  cin>>s;
				  cout << "Las siguientes son las distancias más largas desde el vértice de origen " << s << " \n";
				  g.longestPath(s);
				  return 0;
			  	break;
			  case 0:
			    repetir = false;//retomamos a false para salir
			    break;
			  
}
}while (repetir);//retomamos falso para salir
	 return 0;
}
