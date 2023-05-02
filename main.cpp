#include <iostream>
#include <vector>
#include <array>

using namespace std;

vector<int> temp;
vector<vector<int>> squares;
int squaresize = 0;
int count = 1;

int overlap(vector<int> indexes, int i, int size) {
    vector<int> comp = squares[i];
    for(int k=0; k<size; k++){
        vector<int> cur = squares[indexes[k]];
        if ((cur[0] > comp[0] - comp[2] && cur[0] - cur[2] < comp[0]) && (cur[1] + cur[2] > comp[1] && cur[1] < comp[1] + comp[2])){
            return 1;
        }
    }
    return 0;
}

void DFS(vector<int> indexes, int size, int curindex) {
    temp = indexes;
    for(int i = curindex; i < squaresize; i++) {
        if(!overlap(indexes, i, size)) {
            temp.push_back(i);
            count++;
            DFS(temp, size+1, i+1);
            temp.pop_back();
        }
    }
}

int main(){

    int n, m, i;
    cin >> n;                         //gets the number of lines
    cin >> m;                         //gets the number of columns
    int table[n];

    for(int k=0; k<n;k++){
        cin>> i;
        table[k] = i;
    }

    if(n == 0 || m == 0 || i == 0){
        cout<<0<<endl;
        return 0;
    }

    int y = n-1;
    int l = n-2;

    while(y>0){
        int x = table[l];
        while(x>1){
            int height = n-y+1;
            int size = min(x,height);
            while(size >= 2){
                vector<int> temp;
                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(size);
                squares.push_back(temp);
                temp.clear();
                size--;
                squaresize++;
            }
            x--;
        }
        l--;
        y--;
    }

    if(squaresize == 0){
        cout<<1<<endl;
        return 0;
    }

    vector<int> vazio = {};

    DFS(vazio,0,0);

    cout << count << endl;

    return 0;
}