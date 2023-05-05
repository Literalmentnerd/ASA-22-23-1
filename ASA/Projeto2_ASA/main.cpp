#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct MST{              //pai[x] and rank[x] makes a vertice
    int* parente;        //array with lenght of n_vertices, has the parent of every vertice
    int* rank;           //array with lenght of n_Vertices, has the rank of every vertice
};

vector<vector<int>> grafo;      //vector that holds all archs
int n_vertices;                 //number of vertices
int n_arcos;                    //number of archs
int MSTWeight = 0;                  //Weight of MST with the biggest weight

void link(int x, int y, MST m){         //Changes the parent based on eachothers ranks
    if(m.rank[x] > m.rank[y]){          //makes x the y parent
        m.parente[y] = x;
    }
    else if(m.rank[x] < m.rank[y]){     //makes y the x parent
        m.parente[x] = y;
    }
    else{                               //if both have the same rank, add 1 to the rank of the first and
        m.parente[y] = x;               //make it the parent of the other one
        m.rank[x]++;
    }
}

bool weight(const vector<int>& x, const vector<int>& y){     //Auxiliar function to sort the
    return x[2] > y[2];                                      //archs by their weight
}

int find(int index, MST m){                                  //Finds the root of the tree that is, the parent of all other vertices in the tree
    if(m.parente[index] == index){                               //if true, then i is its own parent/root of its tree
        return index;
    }
    return m.parente[index] = find(m.parente[index],m);      //else continue searching for the root from the parents of their parents
}

void addToMST(int a,int b,MST m){                            //links the MST by changing the parents of 2 vertices
    int x = find(a,m);
    int y = find(b,m);

    link(x,y,m);
}

void kruskval(MST m){
    for(int i = 0; i <n_arcos; i++){                //For loop that goes through the archs
        int a = grafo[i][0];
        int b = grafo[i][1];
        if(find(a,m) != find(b,m)){                 //If the parents are different
            addToMST(a,b,m);
            MSTWeight += grafo[i][2];
        }
    }
    printf("%d\n",MSTWeight);
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
        vector<int> t;
        if(scanf("%d%d%d",&a,&b,&c) == 0){
            return 0;
        }
        t.push_back(a);                            //creates the t vector, an arch
        t.push_back(b);
        t.push_back(c);
        grafo.push_back(t);                        //adds to the vector of vectors
    }

    sort(grafo.begin(),grafo.end(), weight);        //Sorts the vector os archs by their weight from biggest to smallest

    MST m;
    m.parente = new int[n_vertices+1];              // Malloc didnt work so lets stay with new
    m.rank = new int[n_vertices+1];
    for( int i = 0; i < n_vertices; i++){           //MST initialization, creates the vertices with parents and rank set to 0
        m.parente[i] = i;
        m.rank[i] = 0;
    }

    kruskval(m);

    return 0;
}