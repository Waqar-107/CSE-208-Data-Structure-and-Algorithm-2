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
	//freopen("in.txt","r",stdin);

	int i, j, k;
	int n, x,v;

	scanf("%d%d", &v, &n);

	int coins[n];
	int q[n];

	for(i=0;i<n;i++)
        scanf("%d",&coins[i]);

    for(i=0;i<n;i++)
        scanf("%d",&q[i]);

    int tab[v+1];
    int used[n][v+1];

    tab[0]=0;
    for(i=1;i<=v;i++)
        tab[i]=inf;

    memset(used,0,sizeof(used));

    for(i=1;i<=v;i++)
    {
        for(j=0;j<n;j++)
        {
            x=tab[i-coins[j]];
            if(i>=coins[j])
            {
                if(x+1<tab[i] && x!=inf && used[j][i-coins[j]]+1<=q[j])
                {
                    tab[i]=x+1;

                    for(k=0;k<n;k++)
                        used[k][i]=used[k][i-coins[j]];

                    used[j][i]=used[j][i-coins[j]]+1;
                }
            }
        }
    }

    if(tab[v]!=inf)
        printf("%d\n",tab[v]);

    else
        printf("Impossible\n");


	return 0;
}
