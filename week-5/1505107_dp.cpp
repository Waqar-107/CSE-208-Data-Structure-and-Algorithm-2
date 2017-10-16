/***1505107***/

#include<iostream>
#include<cstdio>
#include<cstring>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define inf 10000000

using namespace std;

int main()
{
	//freopen("in.txt", "r", stdin);

	int i, j, k;
	int n, x, v;

	scanf("%d%d", &v, &n);

	int *coins=new int[n];
	int *q=new int[n];

	for (i = 0; i<n; i++)
		scanf("%d", &coins[i]);

	for (i = 0; i<n; i++)
		scanf("%d", &q[i]);

	int *tab=new int[v + 1];

	int **used = new int*[n];
	for (i = 0; i < n; i++)
	{
		used[i] = new int[v + 1];
	}

	tab[0] = 0;
	for (i = 1; i <= v; i++)
		tab[i] = inf;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j <= v; j++)
			used[i][j] = 0;
	}

	//----------------------------------------------------------------
	for (i = 1; i <= v; i++)
	{
		for (j = 0; j<n; j++)
		{
			if (i - coins[j] < 0)
				continue;

			x = tab[i - coins[j]];
			if (i >= coins[j])
			{
				if (x + 1<tab[i] && x != inf && used[j][i - coins[j]] + 1 <= q[j])
				{
					tab[i] = x + 1;

					for (k = 0; k<n; k++)
						used[k][i] = used[k][i - coins[j]];

					used[j][i] = used[j][i - coins[j]] + 1;
				}
			}
		}
	}
	//----------------------------------------------------------------

	if (tab[v] != inf)
	{
		printf("%d\n", tab[v]);

		printf("notes used:\n");
		for (i = 0; i<n; i++)
		{
			if (used[i][v] != 0)
				printf("%d * %d\n", coins[i], used[i][v]);
		}
	}

	else
		printf("Impossible\n");

	for (i = 0; i < n; i++)
		delete[] used[i];

	delete[] used;
	delete[] q;
	delete[] coins;
	delete[] tab;


	return 0;
}
