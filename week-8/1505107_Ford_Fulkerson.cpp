#define _CRT_SECURE_NO_WARNINGS

/***from dust i have come, dust i will be***/

#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<functional>
#include<iomanip>
#include<iostream>
#include<map>
#include<numeric>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 100005
#define inf 100000000
#define pp pair<int,int>

using namespace std;

class graph
{
	int n;
	int **res, *parent, **capacity;
	bool *vis;

public:
	graph(int n)
	{
		this->n = n;

		//residual capacity
		res = new int*[n + 1];
		for (int i = 0; i <= n; i++)
			res[i] = new int[n + 1];


		//capacity
		capacity = new int*[n + 1];
		for (int i = 0; i <= n; i++)
			capacity[i] = new int[n + 1];

		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= n; j++)
				capacity[i][j] = 0;
		}


		//parent
		parent = new int[n + 1];


		//visited or not
		vis = new bool[n + 1];
	}


	//add the capacities
	void addEdge(int u, int v, int w)
	{
		capacity[u][v] = w;
	}


	//find path from source to sink
	bool bfs(int s, int t)
	{
		for (int i = 0; i <= n; i++)
			vis[i] = 0;

		queue<int> q;

		vis[s] = 1;
		q.push(s);
		parent[s] = -1;

		while (!q.empty())
		{
			int u = q.front();
			q.pop();

			for (int v = 1; v <= n; v++)
			{
				if (!vis[v] && res[u][v] > 0)
				{
					parent[v] = u;
					vis[v] = 1;
					q.push(v);
				}
			}
		}

		return vis[t];
	}


	//ford-fulkerson method
	int fordFulkerson(int s, int t)
	{
		//initially residual capacity is equal to the actual capacity
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= n; j++)
				res[i][j] = capacity[i][j];
		}

		int flow = 0;
		int minFlow;
		int u, v;

		//augmenting the path to s to t while it is possible
		while (bfs(s, t))
		{
			minFlow = inf;

			//determine the minimum residual capacity in the path
			v = t;
			while (parent[v] != -1)
			{
				u = parent[v];
				minFlow = min(minFlow, res[u][v]);
				v = u;
			}

			//update residual capacity
			v = t;
			while (parent[v] != -1)
			{
				u = parent[v];
				res[u][v] -= minFlow;
				res[v][u] += minFlow;
				v = u;
			}

			//update flow
			flow += minFlow;
		}

		return flow;
	}
};

int main()
{
	//freopen("in2.txt", "r", stdin);

	int i, j, k;
	int n, m, x;
	int u, v, w;
	int s, t;

	scanf("%d%d", &n, &m);

	graph g(n);
	for (i = 0; i < m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		g.addEdge(u, v, w);
	}

	scanf("%d%d", &s, &t);

	cout << g.fordFulkerson(s, t) << endl;


	return 0;
}
