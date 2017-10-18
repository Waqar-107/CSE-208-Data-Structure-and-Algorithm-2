/***Floyd-Warshalls Algorithm***/
/***        1505107         ***/

#include<iostream>
#include<cstdio>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000

using namespace std;

int main()
{
	freopen("in2.txt", "r", stdin);

	int i, j, k;
	int n, m;
	int u, v, w;

	scanf("%d%d", &n, &m);

	int **dist = new int*[n + 1];
	for (i = 0; i <= n; i++)
		dist[i] = new int[n + 1];

	int **parent = new int*[n + 1];
	for (i = 0; i <= n; i++)
		parent[i] = new int[n + 1];

	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= n; j++)
			dist[i][j] = inf,parent[i][j]=inf;
	}

	for (i = 0; i <= n; i++)
		dist[i][i] = 0;

	for (i = 0; i < m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);

		dist[u][v] = w;
		parent[u][v] = u;
	}

	for (k = 1; k <= n; k++)
	{
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				if (dist[i][j] > dist[i][k] + dist[k][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					parent[i][j] = parent[k][j];
				}
			}
		}
	}

	printf("--------------------------------------------------------------------\n");
	printf("Distance\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (dist[i][j] >= inf)
				printf("inf  ");

			else
				printf("%d  ", dist[i][j]);
		}

		printf("\n");
	}
	printf("--------------------------------------------------------------------\n");

	printf("--------------------------------------------------------------------\n");
	printf("Parent\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (parent[i][j] >= inf)
				printf("inf  ");

			else
				printf("%d  ", parent[i][j]);
		}

		printf("\n");
	}
	printf("--------------------------------------------------------------------\n");

	return 0;
}
