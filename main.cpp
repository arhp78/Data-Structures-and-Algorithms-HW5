// refrence: https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

bool bfs(int *rGraph, int num,int s, int t, int parent[])
{
     int rgraph[num][num];
     int i,j;
     //intialization
     for(i=0;i<num;i++){
         for(j=0;j<num;j++){
            rgraph[i][j]=*(rGraph+i*num+j);
    }}
    // Create a visited array and mark all vertices as not
    // visited

    bool visited[num];
    memset(visited, 0, sizeof(visited));


    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < num; v++) {
            if (visited[v] == false && rgraph[u][v] > 0) {

                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}


int fordFulkerson(int *new_edge, int num,int s, int t)
{    int graph[num][num];
     int i,j;
     //intialization
     for(i=0;i<num;i++){
         for(j=0;j<num;j++){
            graph[i][j]=*(new_edge+i*num+j);
    }}
    /*
    //show graph
    for(i=0;i<num;i++){
         for(j=0;j<num;j++){

       cout<<graph[i][j]<<"\t";
    }
    cout<<"\n";}*/

    int u, v;


    int rGraph[num][num];
    for (u = 0; u < num; u++)
        for (v = 0; v < num; v++)
            rGraph[u][v] = graph[u][v];

    int parent[num];

    int max_flow = 0;


    while (bfs((int*)rGraph,num ,s, t, parent)) {

        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }


        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }


        max_flow += path_flow;
    }


    return max_flow;

}


int main()
{

    int i,j,V,E ;
    cin>>V>>E;
    int edge[V][V];
    //intialization
    for(i=0;i<V;i++){
         for(j=0;j<V;j++){

       edge[i][j]=0;
    }}
     //create matrix
     int n,m,val;
     for(i=0;i<E;i++){
        cin>>n>>m>>val;
        edge[n-1][m-1]=val;
        edge[m-1][n-1]=val;

     }
     /*
    for(i=0;i<V;i++){
         for(j=0;j<V;j++){

       cout<<edge[i][j]<<"\t";
    }
    cout<<"\n";}
    */
    int result=0,res=0;
    for(i=0;i<V;i++){
         for(j=i;j<V;j++){
                if(edge[i][j]==0){
                    continue;
                }
                int new_edge[V][V];
                int m,n;
                //intialization
                for(m=0;m<V;m++){
                    for(n=0;n<V;n++){
                    new_edge[m][n]=0;
                }}

                for(m=0;m<V;m++){
                    for(n=0;n<V;n++){
                            if(edge[i][j]>edge[m][n] && edge[m][n]!=0){
                            new_edge[m][n]=1;}
                }}

                /*
                for(m=0;m<V;m++){
                    for(n=0;n<V;n++){

                        cout<<new_edge[m][n]<<"\t";
                }
                cout<<"\n";
                }
            cout<<"\n";
            cout<<"\n";*/

            res=fordFulkerson((int*)new_edge, V,i, j);
            result=res+result;
            }
    }
    cout << result;

    return 0;
}
