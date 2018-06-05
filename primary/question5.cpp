#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <iomanip>
#include <ostream>
#include <string.h>
#include <vector>
#include <stack>
#define INT_MAX 2147483647
using namespace std;


class Route{
public:
    int flag;
    int start_city;
    int end_city;
    int cost;
    int begin_time;
    int end_time;
    Route(){
        flag = 0;
        start_city = 0;
        end_city = 0;
        cost = INT_MAX;
        begin_time = 0;
        end_time = 48;
    }
};

class Edge{
public:
    int flag;
    vector<int> num;
    vector<int> cost;
    int early_time;
    int late_time;
    Edge(){
        flag = 0;
        //cost = INT_MAX;
        early_time = 48;
        late_time = 0;
    }
};
bool Early(int begin_time, Edge **edge, int start, int n);
void dfs_find_route(int start, int end, int m, int **graph, int *road, int mm, int *visited);
int main(){

    int n,m = 0;
    vector<int> start_route;
    vector<int> end_route;
    scanf("%d", &n);
    scanf("%d", &m);

    int cost = 0;

    int *x = new int[m];
    int *y = new int[m];
    int *c = new int[m];
    char ts[m][5];
    char td[m][5];
    int min_cost = INT_MAX;
    Route *route = new Route[m];
    
    Edge edge[n][n];

    //int graph[m][m];
    int **graph;      //动态申请二维数组 n行 m列  
    graph = new int*[m];  
    for(int i = 0;i < m; i++){ 
        graph[i] = new int[m];
    }
    int **tmp_graph;      //动态申请二维数组 n行 m列  
    tmp_graph = new int*[m];  
    for(int i = 0;i < m; i++){ 
        tmp_graph[i] = new int[m];
    }

    int score[n][m];  

    int start_node = 0;
    int end_node = 0;

    for(int i = 0; i < m; i++){
        scanf("%d", &x[i]);
        scanf("%d", &y[i]);
        scanf("%d", &c[i]);
        //scanf("%s", ts[i]);
        //scanf("%s", td[i]);
        cin >> ts[i];
        cin >> td[i];

        route[i].flag = 1;
        route[i].start_city = x[i];
        route[i].end_city = y[i];
        route[i].cost = c[i];
        route[i].begin_time = atoi(strtok(ts[i], ":")) + atoi(strtok(NULL, ""))/30;
        route[i].end_time = atoi(strtok(td[i], ":")) + atoi(strtok(NULL, ""))/30;

        edge[x[i]-1][y[i]-1].flag += 1;
        edge[x[i]-1][y[i]-1].num.push_back(route[i].begin_time);
        edge[x[i]-1][y[i]-1].cost.push_back(c[i]);
        edge[x[i]-1][y[i]-1].early_time = min(edge[x[i]-1][y[i]-1].early_time, route[i].begin_time);
        edge[x[i]-1][y[i]-1].late_time = max(edge[x[i]-1][y[i]-1].late_time, route[i].begin_time);
        //cout << edge[x[i]-1][y[i]-1].flag << " ";
        //cout << edge[x[i]-1][y[i]-1].cost << " ";
        //cout << edge[x[i]-1][y[i]-1].begin_time << " ";
        //cout << edge[x[i]-1][y[i]-1].end_time << " ";
        //cout << endl;
        if(x[i] == 1){
            start_node += 1;
            start_route.push_back(i);
        }
        if(y[i] == n){
            end_node += 1;
            end_route.push_back(i);
        }
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            //cout << route[i].end_city << route[j].start_city << endl;
            if(route[i].end_city == route[j].start_city && route[i].end_time < route[j].begin_time){
                graph[i][j] = 1;
            }
        }
    }

    /*int road[m*m];
    int mm = 1;
    int visited[m];
    road[0] = start_node;
    for(int ii = 0; ii < m; ii++){
        for(int jj = 0; jj < m; jj++){
            tmp_graph[ii][jj] = graph[ii][jj];
        }
    }
    cout << "test2!" << endl;
    dfs_find_route(1, 3, m, tmp_graph, road, mm, visited);

    cout << "test3!" << endl;*/

    for(int i = 0; i < start_node; i++){
        for(int j = 0; j < end_node; j++){
            int *road = new int[m*m];
            int mm = 0;
            int *visited = new int[m];
            road[0] = start_node;
            for(int ii = 0; ii < m; ii++){
                for(int jj = 0; jj < m; jj++){
                    tmp_graph[ii][jj] = graph[ii][jj];
                }
            }
            //cout << i << j << endl;
            //cout << start_route[i] << end_route[j] << endl;
            dfs_find_route(start_route[i], end_route[j], m, tmp_graph, road, mm, visited);
        }
    }

    /*int start = 0;
    int destination = n-1;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < edge[0][i].flag; j++){
            //bool flag_available = Early(edge[0][i].num[j], edge, 0, n);
            start = i;
            cost = edge[0][i].cost[j];
            while(start < destination){
                for(int s = 0; s < n; s++){
                    for(int r = 0; r < edge[start][i].flag; r++){
                        start = s;
                        cost += edge[start][s].cost[r];
                        //flag_available = 0;
                    }
                }
            }
        }
        for(int j = 0; j < n; j++){

        }
    }*/

    cout << cost << endl;
    return 0;
}

void dfs_find_route(int start, int end, int m, int **graph, int *road, int mm, int *visited){
    if(start == end) {
        cout << "The end!" << endl;
        return;
    }
    visited[start] = 1;
    int i, j;
    for(i = 0; i < m; i++){
        //cout << i << endl;
        if(graph[start][i] == 1 && visited[i] == 0){
            if(i == end)///如果深搜到了终点，就输出刚才经过的路径
            {
                cout << start << " ";
                for(j = 0; j < mm; j++)
                {
                    cout << road[j] << " ";
                }
                cout << end << endl;
            }
            else///如果该点不是终点
            {
                graph[start][i] = 0;
                road[mm] = i;///将该点存起来
                mm++;
                dfs_find_route(i, end, m, graph, road, mm, visited);///接着深搜
                graph[start][i] = 1;
                visited[i] = 0;
                mm--;
            }
        }
    }
}

bool Early(int begin_time, Edge **edge, int start, int n){
    bool early = false;
    for(int i = 0; i < n; i++){
        if(edge[start][i].flag == 1 && edge[start][i].late_time > begin_time){
            early = true;
        }
    }

    return early;
}
