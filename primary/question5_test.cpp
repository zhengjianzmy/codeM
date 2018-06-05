#include <stdio.h>
#include <math.h>
int map[100][100];
int road[120], m=1, n, x, y;///存储路径
int visited[100]={0};
void dfs(int p)
{
    visited[p]=1;
    int i, j;
    for(i=0; i<n; i++)
    {
        if(map[p][i]==1&&visited[i]==0)
        {
            if(i == y)///如果深搜到了终点，就输出刚才经过的路径
            {
                for(j=0; j<m; j++)
                {
                    printf("%d", road[j]);
                }
                printf("%d\r\n", y);
            }
            else///如果该点不是终点
            {
                map[p][i] = 0;
                road[m] = i;///将该点存起来
                m++;
                dfs(i);///接着深搜
                map[p][i] = 1;
            visited[i]=0;
                m--;
            }
        }
    }
}

int main()
{
    int i, j;
    scanf("%d", &n); 
    scanf("%d %d", &x, &y);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    road[0] = x;
    dfs(x);
    return 0;
}