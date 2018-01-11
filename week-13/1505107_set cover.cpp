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
#include<sstream>
#include<stack>
#include<string>
#include<time.h>
#include<utility>
#include<vector>

#define dbg printf("in\n");
#define nl printf("\n");
#define N 1010
#define inf 100000000000

using namespace std;

int main()
{
	//freopen("in2.txt", "r", stdin);

	int i, j, k;
	int n, m, x;
	string s;

	scanf("%d%d", &n, &m);

	vector<int> *v = new vector<int>[m];
	bool *taken = new bool[m];
	bool *notInFinal = new bool[n + 1];
	int *unCov = new int[m];

	for (i = 0; i <= m; i++)
	{
		getline(cin, s);
		stringstream str(s);

		while (str >> x)
		{
			v[i - 1].push_back(x);
		}
	}

	for (i = 0; i < m; i++)
		taken[i] = false;

	for (i = 0; i <= n; i++)
		notInFinal[i] = false;

	vector<int> ans;

	while (n)
	{
		x = 0; k = -1;
		for (i = 0; i < m; i++)
		{
			if (!taken[i])
			{
				unCov[i] = 0;
				for (j = 0; j < v[i].size(); j++)
				{
					if (!notInFinal[v[i][j]])
						unCov[i]++;
				}

				if (x < unCov[i])
					x = unCov[i], k = i;
			}
		}

		taken[k] = true; ans.push_back(k);
		n -= x;

		for (i = 0; i < v[k].size(); i++)
			notInFinal[v[k][i]] = true;
	}

	printf("%d\n", ans.size());
	for (i = 0; i < ans.size(); i++)
	{
		for (j = 0; j < v[ans[i]].size(); j++)
			printf("%d ", v[ans[i]][j]);

		printf("\n");
	}

	return 0;
}
