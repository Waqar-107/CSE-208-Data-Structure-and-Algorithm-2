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
#include<time.h>
#include<utility>
#include<vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 200010
#define inf 1000000000
#define pp pair<string,int>

using namespace std;

ull djb2(string s)
{
	ull h = 5381;
	int l = s.length();

	for (int i = 0; i < l; i++)
		h += ((h * 33) + s[i]);

	return h;
}

ull adler32(string s)
{
	ull a = 1, b = 0;
	int l, mod = 65521;

	l = s.length();
	for (int i = 0; i < l; i++)
	{
		a = (a + s[i]) % mod;
		b = (b + a) % mod;
	}

	return b*65536 + a;
}

ull sdbm(string s)
{
	ull h = 0, l = s.length();
	for (ll i = 0; i < l; i++)
	{
		h = s[i] + (h << 6) + (h << 16) - h;
	}

	return h;
}

ull fnv(string s)
{
	ull fnv_prime = 16777619;
	ull fnv_offset = 2166136261;

	int l = s.length();
	ull h = 0;

	for (ll i = 0; i < l; i++)
	{
		h *= fnv_prime;
		h ^= s[i];
	}

	return h;
}

ull jenkins(string s)
{
	ull h = 0, l=s.length();
	for (ll i = 0; i < l; i++)
	{
		h += s[i];
		h += (h << 10);
		h ^= (h >> 6);
	}

	h += (h << 3);
	h ^= (h >> 11);
	h += (h << 15);

	return h;
}

void generate(string *dict,int n,int l)
{
	//n words of l size
	//characters from 65-90

	int randNum;

	for(int i=0;i<n;i++)
	{
		string str = "";
		for (int j = 0; j < l; j++)
		{
			randNum = rand() % (90 - 65 + 1) + 65;
			str.push_back((char)randNum);
		}

		dict[i] = str;
	}
}

struct node
{
	string key;
	int value;
	node *next, *prev;

	node() {
		next = 0;
		prev = 0;
	}

	node(string key, int value)
	{
		this->key = key;
		this->value = value;

		next = 0;
		prev = 0;
	}
};

class chaining
{
	int m, type, c, v;
	node **hashTable;
	node *head;
public:
	chaining(int m,int type)
	{
		this->m = m;
		this->type = type;
		head = 0;
		hashTable = new node*[m];

		for (int i = 0; i < m; i++)
			hashTable[i] = 0;

		c = 0; v = 1;
	}

	void insert(string s)
	{
		int i;
		type == 1 ? i = djb2(s) % m : type == 2 ? i = adler32(s) % m : i = fnv(s) % m;

		if (hashTable[i] == 0)
		{
			struct node *newNode = new node(s, v); v++;
			hashTable[i] = newNode;
		}

		else
		{
			c++;
			struct node *newNode = new node(s, v); v++;
			head = hashTable[i];
			hashTable[i] = newNode;
			newNode->next = head;
			head->prev = newNode;
		}

	}

	void remove(string s)
	{
		int i;
		type == 1 ? i = djb2(s) % m : type == 2 ? i = adler32(s) % m : i = fnv(s) % m;

		struct node *temp = search(s);

		if (temp)
		{
			//if in head
			//hashTable[i]
		}
	}

	node* search(string s)
	{
		int i;
		type == 1 ? i = djb2(s) % m : type == 2 ? i = adler32(s) % m : i = fnv(s) % m;

		if (hashTable[i] == 0)
			return NULL;

		head = hashTable[i];
		while (head)
		{
			if (head->key == s)
				return head;

			head = head->next;
		}

		return NULL;
	}

	void memFree()
	{
		delete[] hashTable;
	}
};

class linearProbing
{
	int m, c, type, v;
	pp *hashTable;
public:
	linearProbing(int m,int type)
	{
		c = 0, v = 1;
		this->m = m;
		this->type = type;
		hashTable = new pp[m];

		for (int i = 0; i < m; i++)
			hashTable[i] = { "null",NULL };
	}

	void insert(string s)
	{
		ull h;
		int i = 0;
		type == 1 ? h = djb2(s)  : type == 2 ? h = jenkins(s)  : h = fnv(s) ;

		//avoid duplicate
		if (search(s) != -1)
		{
			//duplicate
			//cout << "duplicate" << endl;
			return;
		}

		//update collision
		ull jdx = (i + h) % m;
		int idx = jdx;

		if (hashTable[idx].second != NULL)
			c++;

		while (i < m)
		{
			jdx = (i + h) % m;
			idx = jdx;

			if (hashTable[idx].second == NULL)
			{
				hashTable[idx] = { s,v }; v++;
				return;
			}

			i++;
		}
	}

	void remove(string s)
	{
		int i = search(s);
		if (i != -1)
			hashTable[i] = { "deleted",NULL };

		else
			printf("key not found");
	}

	int search(string s)
	{
		ull jdx, h;
		int i=0, idx;
		type == 1 ? h = djb2(s)  : type == 2 ? h = jenkins(s) : h = fnv(s);

		while (i < m)
		{
			jdx = (h + i) % m;
			idx = jdx;

			if (hashTable[idx].second == NULL)
				return -1;

			else if (hashTable[idx].first == s)
				return idx;

			else
				i++;
		}

		return -1;
	}

	int getCollision()
	{
		return c;
	}

	void memFree()
	{
		delete[] hashTable;
	}
};


int main()
{
	//freopen("in2.txt", "r", stdin);

	int i, j, k;
	int n, m;
	int t1, t2;
	int sc, usc;
	double time_spent;

	while (1)
	{
		printf("choose method: 1.seperate chaining. 2.linear probing. 3.quit\n");
		scanf("%d", &t1);

		if (t1 == 3)return 0;

		printf("\nchoose hash function: 1.djb2. 2.jenkins. 3.fnv\n");
		scanf("%d", &t2);

		printf("\ngive the number of words and size of the words to generate:\n");
		scanf("%d%d", &n, &m);

		//allocate memory for storing words
		string *dict = new string[n];

		//generate words that will be inserted
		generate(dict, n, m);

		if (t1 == 1)
		{
			/*chaining x(n, t2);

			clock_t begin = clock();

			for (i = 0; i < n; i++)
				x.insert(dict[i]);

			clock_t end = clock();

			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

			printf("inserted %d words in %f seconds\n", n, time_spent);

			//generate random words to search them in the hash-table
			generate(dict, n, m);

			clock_t begin = clock();

			for (i = 0; i < n; i++)
				x.search(dict[i]);

			clock_t end = clock();

			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf("%d collisions occured, searched in %f seconds\n");
			x.memFree();*/
		}

		else if (t1 == 2)
		{
			linearProbing x(n, t2);

			//--------------------------------------------------------------------------insert
			clock_t begin = clock();

			for (i = 0; i < n; i++)
				x.insert(dict[i]);

			clock_t end = clock();

			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

			printf("inserted %d words in %f seconds, %d collisions occured, \n", n, time_spent,x.getCollision());
			//--------------------------------------------------------------------------insert

			//generate random words to search them in the hash-table
			generate(dict, n, m);

			//--------------------------------------------------------------------------search
			sc = 0, usc = 0;
			begin = clock();

			for (i = 0; i < n; i++)
			{
				j=x.search(dict[i]);
				if (j == -1)
					usc++;
				else
					sc++;
			}

			end = clock();
			time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

			printf("searched in %f seconds\n",time_spent);
			printf("%d words found, %d not found\n", sc, usc);
			//--------------------------------------------------------------------------search

			x.memFree();
		}

		delete[] dict;
	}

	return 0;
}
