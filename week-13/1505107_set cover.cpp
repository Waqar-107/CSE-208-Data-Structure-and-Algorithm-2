#define _CRT_SECURE_NO_WARNINGS

/***from dust i have come, dust i will be***/

/*
* if in any node the lower bound is lb and 'c' is the best answer found so far then
* if c<=lb then no need to go further or prune the branch
* else there might a solution in this path, so search further
*
* update 'c' when you cover the whole U
*/

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
#include<sstream>
#include<string>
#include<time.h>
#include<utility>
#include<vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 100
#define inf 100000

using namespace std;

string sans;
int n, m, ans, sz;
vector<int> subSet[N];

void setCover(string s,int l)
{
	//calculate lower_bound
	int picked = 0, cnt=0;
	int mxCardinality = 0;
	set<int> coveredSoFar;

	for (int i = 0; i < m; i++)
	{
		if (s[i] == '1')
		{
			picked++;

			for (int j = 0; j < subSet[i].size(); j++)
				coveredSoFar.insert(subSet[i][j]);
		}

		else
		{
			sz = subSet[i].size();
			mxCardinality = max(mxCardinality, sz);
		}
	}

	int lb=inf;
	if(mxCardinality)
		 lb = picked + (n - coveredSoFar.size()) / mxCardinality;

	//all done in this path
	if (coveredSoFar.size() == n)
	{
		cnt = 0;
		for (int i = 0; i < m; i++)
		{
			if (s[i] == '1')
				cnt++;
		}
		//cout << cnt << " " << l << " " << s << " " << ans<<" bahir"; nl;
		if (ans > cnt)
		{
			//cout << cnt << " " << l << " " << s << " " << ans << " vitor"; nl;
			ans = cnt;
			sans = s;
			return;
		}
	}

	if (lb >= ans)
		return;

	//two branches
	//we either take subset l else not
	string a, b;

	a = s;
	b = s; b[l] = '1';

	if (l < m)
	{
		//cout << s << " " << a << " " << b<<" "<<l<<" "<<cnt;
		//nl
		setCover(a, l + 1);
		setCover(b, l + 1);
	}

}

int main()
{
	//freopen("in2.txt", "r", stdin);

	int i, j, k;
	int x, y;
	string s;

	scanf("%d%d", &n, &m);
	for (i = 0; i <= m; i++)
	{
		getline(cin, s);
		stringstream str(s);

		while (str >> x)
		{
			subSet[i - 1].push_back(x);
		}
	}

	ans = m;

	s = "";
	for (i = 0; i < m; i++)
		s += '0';

	sans = s;
	setCover(s, 0);

	k = 0;
	for (i = 0; i < m; i++)
	{
		if (sans[i] == '1')
			k++;
	}

	cout << k << endl;
	for (i = 0; i < m; i++)
	{
		if (sans[i] == '1')
		{
			for (j = 0; j < subSet[i].size(); j++)
				cout << subSet[i][j] << " ";

			cout << endl;
		}
	}

	return 0;
}
