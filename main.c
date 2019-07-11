#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INFINITY 99999
//struct for the edges of the graph
struct Edge
{
    int u;	//start vertex of the edge
    int v;	//end vertex of the edge
    int w;	//weight of the edge (u,v)
};
//Graph - it consists of edges
struct Graph
{
    int V;	//total number of vertices in the graph
    int E;	//total number of edges in the graph
    struct Edge *edge;	//array of edges
};
void bellmanford(struct Graph *g, int source);
void display(int arr[], int size);




int main()
{
    EntradaGraph();
}


void bellmanford(struct Graph *g, int source)
{
    //variables
    int i, j, u, v, w;
    //total vertex in the graph g
    int tV = g->V;

    //total edge in the graph g
    int tE = g->E;

    //distance array
    //size equal to the number of vertices of the graph g
    int d[tV];

    //predecessor array
    //size equal to the number of vertices of the graph g
    int p[tV];

    //step 1: fill the distance array and predecessor array
    for (i = 0; i < tV; i++)
    {
        d[i] = INFINITY;
        p[i] = 0;
    }

    //mark the source vertex
    d[source] = 0;

    //step 2: relax edges |V| - 1 times
    for(i = 1; i <= tV-1; i++)
    {
        for(j = 0; j < tE; j++)
        {
            //get the edge data
            u = g->edge[j].u;
            v = g->edge[j].v;
            w = g->edge[j].w;

            if(d[u] != INFINITY && d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                p[v] = u;
            }
        }
    }

    //step 3: detect negative cycle
    //if value changes then we have a negative cycle in the graph
    //and we cannot find the shortest distances
    for(i = 0; i < tE; i++)
    {
        u = g->edge[i].u;
        v = g->edge[i].v;
        w = g->edge[i].w;
        if(d[u] != INFINITY && d[v] > d[u] + w)
        {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }

    //No negative weight cycle found!
    //print the distance and predecessor array
    printf("Distance array: ");
    display(d, tV);
    printf("Predecessor array: ");
    display(p, tV);
}
void display(int arr[], int size)
{
    int i;
    for(i = 0; i < size; i ++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void EntradaGraph()
{

    //create graph
    struct Graph *g = (struct Graph*)malloc(sizeof(struct Graph));
    //array of edges for graph
    g->edge = (struct Edge*)malloc(g->E * sizeof(struct Edge));

    int Vertices,Edges;
    printf("Quantos vertices tera o grafo?\n");
    scanf("%d",&Vertices);
    printf("Quantas arestas tem seu grafo?\n");
    scanf("%d",&Edges);

    g->V = Vertices;	//total vertices
    g->E = Edges;	//total edges

    //------- adding the edges of the graph*/
    int i,Va,Vb,Peso,resp;
    bool stats = true;
    for(i = 0; i < Edges; i ++)
    {

        stats = true;
        fflush(stdin);
        system("cls");

        while(stats)
        {
            fflush(stdin);
            system("cls");
            printf("\t\tInicializando Ligacao dos vertices\n\n");

            printf("O vertice %d sera ligado com qual outro vertice? ",i+1);
            scanf("%d",&Vb);
            printf("E qual eh o peso dessa aresta criada? ");
            scanf("%d",&Peso);

            g->edge[i].u = i;
            g->edge[i].v = Vb-1;
            g->edge[i].w = Peso;

            printf("\n\t\tAresta Vertice %d -- Peso %d --> Vertice %d\n\n",i+1,Peso,Vb);
            printf("O vertice %d tem mais alguma ligacao?\n\tNao-> 0\n\tSim->1\n ");
            scanf("%d",&resp);
            if(resp == 0)
                stats = false;
        }




    }

    int source;
    system("cls");
    printf("\t\tExecutando o Bellman Ford's\n\n");
    printf("Qual sera o vertice de inicio? ");
    scanf("%d",&source);
    if(source > Vertices)
    {
        printf("Valor invalido!!\nInicializando pelo vertice 1\n\n");
        bellmanford(g, 0);
    }

    else
        bellmanford(g, source-1);		//0 is the source vertex


}
