#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define MAX_INF 0x3f3f3f3f
//n < 500, timeNumber < 50
#define maxNumber 100000
//24小时
#define timeNumber 49
//定义结构体，点代表城市编号和到0点的路费
struct Node
{
public:
	int point;
	int distance;

	Node(int point_ = 0, int distance_ = 0) 
	{
		point = point_;
		distance = distance_;
	}

	bool operator < (const Node &r)const
	{
		return distance > r.distance;
	}
};
//定义结构体，边代表到一城的费用
struct Edge
{
	int index;
	int cost;

	Edge(int index_ = 0, int cost_ = 0) 
	{
		index = index_;
		cost = cost_;
	}
};

//传参太多，定义为全局变量
int n, m;
//最短距离
int dist[maxNumber];
int counter[maxNumber];
//记录是否访问过
bool visited[maxNumber];
vector<Edge> edge[maxNumber];

//最短路径搜索
void Search(int n, int start)
{
	memset(visited, false, sizeof(visited));
	memset(dist, 0x3f, sizeof(dist));//定义为大数0x3f3f3f3f
	priority_queue<Node> nodePtr;
	dist[start] = 0;
	nodePtr.push(Node(start, 0));
	Node node;
	while (!nodePtr.empty())
	{
		node = nodePtr.top();
		nodePtr.pop();
		int point = node.point;
		//如果出事没有其他车
		if (!counter[point + 1])
		{
			continue;
		}

		if (visited[point])
		{
			continue;
		}
		visited[point] = true;
		for (int i = 0; i < edge[point].size(); i++)
		{
			int index = edge[node.point][i].index;
			int cost = edge[point][i].cost;
			//Djikstra算法更新最短距离
			if (!visited[index] && dist[index] > dist[point] + cost)
			{
				dist[index] = dist[point] + cost;
				nodePtr.push(Node(index, dist[index]));
			}
		}
	}
}

//深度优先搜索
bool dfs_find_route(int start)
{
	//到了终点
	if (start == n * timeNumber + 2)
	{
		return counter[start] = 1;
	}
	int flag = 0;
	//每一城的车次
	for (int i = 0; i < edge[start].size(); i++)
	{
		int index = edge[start][i].index;
		if (!visited[index])
		{
			visited[index] = 1;
			if (dfs_find_route(index))
			{
				flag = 1;
			}
		}
		else
		{
			if (counter[index])
			{
				flag = 1;
			}
		}
	}
	return counter[start] = flag;
}

int main()
{
	scanf("%d%d", &n, &m);

	int* x = new int[m];
	int* y = new int[m];
	int* c = new int[m];

	int* tsHour = new int[m];
	int* tsMin = new int[m];
	int* tdHour = new int[m];
	int* tdMin = new int[m];

	int* tBegin = new int[m];
	int* tEnd = new int[m];

	//数据输入
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &x[i]);
		scanf("%d", &y[i]);
		scanf("%d", &c[i]);

		scanf("%d:%d", &tsHour[i], &tsMin[i]);
		scanf("%d:%d", &tdHour[i], &tdMin[i]);
	}

	for (int i = 0; i < m; i++)
	{
		//半小时记一次，共timeNumber
		tBegin[i] = tsHour[i] * 2 + (tsMin[i] / 30) + 1;
		tEnd[i] = tdHour[i] * 2 + (tdMin[i] / 30) + 1;
		//如果火车不到终点一律延时半小时
		if (y[i] != n)
		{
			tEnd[i] += 1;
		}
		//记录每一城的各时刻车次
		for (int j = tEnd[i]; j <= timeNumber; j++)
		{
			edge[(x[i] - 1) * timeNumber + tBegin[i]].push_back(Edge((y[i] - 1) * timeNumber + j, c[i]));
		}
	}
	//n * timeNumber + 1 各时刻到达C点不消耗， 各时刻到达n * timeNumber + 2 不耗费
	for (int i = 1; i <= timeNumber; i++)
	{
		edge[n * timeNumber + 1].push_back(Edge(i, 0));
		edge[(n - 1) * timeNumber + i].push_back(Edge(n * timeNumber + 2, 0));
	}
	//从起始点开始深度优先搜索
	visited[n * timeNumber + 1] = 1;
	dfs_find_route(n * timeNumber + 1);
	for (int i = 1; i <= n; i++)
	{
		for (int j = timeNumber; j >= 1; j--)
		{
			counter[(i - 1) * timeNumber + j] += counter[(i - 1) * timeNumber + j + 1];
		}
	}
	//重新置零
	memset(visited, 0, sizeof(visited));
	//搜索最短路径
	Search(n * timeNumber + 2, n * timeNumber + 1);

	if (dist[n * timeNumber + 2] == MAX_INF)
	{
		cout << "-1" << endl;//无路线
	}
	else
	{
		cout << dist[n * timeNumber + 2] << endl;
	}
	return 0;
}
