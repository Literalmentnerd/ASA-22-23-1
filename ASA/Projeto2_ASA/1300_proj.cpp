/**
 * @file 1300_proj.cpp
 * @author Bernardo Augusto ist1102820 Tiago Loureiro ist1104107
 * @brief 
 * @version 0.1
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct MST{              //parente[x] and rank[x] makes a vertice
    int* parente;        //array with lenght of n_vertices, has the parent of every vertice
    int* rank;           //array with lenght of n_Vertices, has the rank of every vertice
};

struct Arco{            //Arch struct
    int source;         //source: source vertice
    int destino;        //destino: destination vertice
    int peso;           //peso: weight of the path
};

vector<Arco> grafo;      //vector that holds all archs
int n_vertices;                 //number of vertices
int n_arcos;                    //number of archs
long int MSTWeight = 0;                  //Weight of MST with the biggest weight

void link(int x, int y, MST m){         //Changes the parent based on eachothers ranks
    if(m.rank[x] > m.rank[y]){          //makes x the y parent
        m.parente[y] = x+1;
    }
    else if(m.rank[x] < m.rank[y]){     //makes y the x parent
        m.parente[x] = y+1;
    }
    else{                               //if both have the same rank, add 1 to the rank of the first and
        m.parente[y] = x+1;               //make it the parent of the other one
        m.rank[x]++;
    }
}

bool weight(const Arco& x, const Arco& y){     //Auxiliar function to sort the
    return x.peso > y.peso;                    //archs by their weight
}

int find(int node, MST m){                                  //Finds the root of the tree that is, the parent of all other vertices in the tree
    if(m.parente[node-1] == node){                               //if true, then i is its own parent/root of its tree
        return node;
    }
    return m.parente[node-1] = find(m.parente[node-1],m);      //else continue searching for the root from the parents of their parents
}

void addToMST(int a,int b,MST m){                            //links the MST by changing the parents of 2 vertices
    int x = find(a,m);
    int y = find(b,m);

    link(x-1,y-1,m);
}

void kruskal(MST m){
    for(int i = 0; i < n_arcos; i++){                //For loop that goes through the archs
        int a = grafo[i].source;
        int b = grafo[i].destino;

        if(find(a,m) != find(b,m)){                 //If the parents are different
            addToMST(a,b,m);                        //join them adding to the tree
            MSTWeight += grafo[i].peso;             //adds the weight of the arch to the solution
        }
    }
    printf("%ld\n",MSTWeight);
}

int main(){
    
    if(scanf("%d",&n_vertices) == 0){              //Gets the number of vertices
        return 0;
    }
    if(scanf("%d",&n_arcos) == 0){                 //Gets the number of archs
        return 0;
    }
    for(int i = 0; i < n_arcos ; i++){             //For loop that gets the input, loops n_arcos times
        int a,b,c;                                 //a: source vertice , b: destination vertice, w: weight
        Arco t;
        if(scanf("%d%d%d",&a,&b,&c) == 0){
            return 0;
        }
        t.source = a;                            //creates the t vector, an arch
        t.destino = b;
        t.peso = c;
        grafo.push_back(t);                        //adds to the vector of vectors
    }

    sort(grafo.begin(),grafo.end(), weight);        //Sorts the vector os archs by their weight from biggest to smallest

    MST m;
    m.parente = new int[n_vertices+1];              // Malloc didnt work so lets stay with new
    m.rank = new int[n_vertices+1];
    for( int i = 0; i < n_vertices; i++){           //MST initialization, creates the vertices with parents and rank set to 0
        m.parente[i] = i+1;
        m.rank[i] = 0;
    }

    kruskal(m);

    return 0;
}