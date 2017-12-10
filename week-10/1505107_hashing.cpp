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
	ull h = 0, l = s.length();
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

void generate(string *dict, int n, int l)
{
	//n words of l size
	string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int randNum;

	for (int i = 0; i < n; i++)
	{
		string str;
		for (int j = 0; j < l; j++)
		{
			randNum = rand() % 52;
			str += letters[randNum];
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
	chaining(int m, int type)
	{
		this->m = m;
		this->type = type;
		head = 0;
		hashTable = new node*[m];

		for (int i = 0; i < m; i++)
			hashTable[i] = NULL;

		c = 0; v = 1;
	}

	void insert(string s)
	{
		if (search(s) != NULL)
			return;

		ull h;
		type == 1 ? h = djb2(s) % m : type == 2 ? h = jenkins(s) % m : h = fnv(s) % m;

		struct node *newNode = new node(s, v); v++;
		head = hashTable[h];

		//1st element
		if (head == NULL)
			hashTable[h] = newNode;

		else
		{
			head->prev = newNode;
			newNode->next = head;
			hashTable[h] = newNode;
		}
	}

	void remove(string s)
	{
		if (search(s) == NULL)
		{
			cout << "key not found" << endl;
			return;
		}

		ull h;
		type == 1 ? h = djb2(s) % m : type == 2 ? h = jenkins(s) % m : h = fnv(s) % m;

		struct node *temp = search(s);
		struct node *pre, *nxt;

		//the item is in head
		if (hashTable[h] == temp)
		{
			nxt = temp->next;
			hashTable[h] = nxt;

			if (nxt)
				nxt->prev = 0;

			delete temp;
		}

		else
		{
			pre = temp->prev;
			nxt = temp->next;

			pre->next = nxt;

			if(nxt)
				nxt->prev = pre;

			delete temp;
		}
	}

	node* search(string s)
	{
		ull h;
		type == 1 ? h = djb2(s) % m : type == 2 ? h = jenkins(s) % m : h = fnv(s) % m;

		int idx = h;
		if (hashTable[idx] == 0)
			return NULL;

		head = hashTable[idx];
		while (head)
		{
			if (head->key == s)
				return head;

			head = head->next;
		}

		return NULL;
	}

	int getCollision()
	{
		ll cnt = 0;
		for (ll i = 0; i < m; i++)
		{
			if (hashTable[i] != NULL)
				cnt++;
		}

		return (m - cnt);
	}

	void memFree()
	{
		for (ll i = 0; i < m; i++)
		{
			node *temp = hashTable[i];
			while (temp != NULL)
			{
				node *pre = temp;
				temp = temp->next;
				delete pre;
			}
		}

		delete[] hashTable;
	}
};

struct node2
{
	string key;
	int value;

	node2() { key = "null"; value = 0; }
	node2(string key, int value)
	{
		this->key = key;
		this->value = value;
	}
};

class linearProbing
{
	int m, c;
	int type, v;
	node2 *hashTable;
public:
	linearProbing(int m, int type)
	{
		c = 0, v = 1;
		this->m = m;
		this->type = type;
		hashTable = new node2[m];
	}

	void insert(string s)
	{
		//avoid duplicate
		if (search(s))
			return;

		ull h;
		int i = 0;
		type == 1 ? h = djb2(s) : type == 2 ? h = jenkins(s) : h = fnv(s);

		//update collision
		ull idx = (i + h) % m;

		if (hashTable[idx].value>0)
			c++;

		while (i < m)
		{
			idx = (i + h) % m;

			if (hashTable[idx].value==0 || hashTable[idx].value==-1)
			{
				hashTable[idx] = node2(s, v); v++;
				return;
			}

			i++;
		}
	}

	void remove(string s)
	{
		int i = search(s);
		if (i)
		{
			hashTable[i].key = "deleted"; hashTable[i].value = -1;
		}

		else
			printf("key not found\n");
	}

	int search(string s)
	{
		ull  h;
		int i = 0;
		type == 1 ? h = djb2(s) : type == 2 ? h = jenkins(s) : h = fnv(s);

		while (i < m)
		{
			ull idx = (h + i) % m;

			//empty cell
			if (hashTable[idx].key=="null")
				return 0;

			//key found
			else if (hashTable[idx].key == s)
				return idx;

			else
				i++;
		}

		return 0;
	}

	int getCollision()
	{
		return c;
	}

	int getSize()
	{
		return v - 1;
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
	int n, m, t;
	int sc, usc;
	clock_t begin, end;
	double time_spent;

	while (1)
	{
		printf("choose hash function: 1.djb2. 2.jenkins. 3.fnv\n");
		scanf("%d", &t);

		if (t > 3)
			return 0;

		printf("give the number of words and size of the words to generate:\n");
		scanf("%d%d", &n, &m);

		//---------------------------------------------------------------------------generate
		//allocate memory for storing words
		string *dict = new string[n];

		//generate words that will be inserted
		generate(dict, n, m);

		//allocate memory for words to be searched
		string *searchable = new string[n];

		//generate words that will be searched
		generate(searchable, n, m);
		//---------------------------------------------------------------------------generate

		//-----------------------------------------------------------------------------------------------chaining
		chaining x(n, t);
		printf("---------------------------------------------------------chaining\n");

		//--------------------------------------------------------------------------insert
		begin = clock();

		for (i = 0; i < n; i++)
			x.insert(dict[i]);

		end = clock();

		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("inserted %d words in %f seconds, %d collisions occured, \n", n, time_spent, x.getCollision());
		//--------------------------------------------------------------------------insert

		//--------------------------------------------------------------------------search
		sc = 0, usc = 0;
		begin = clock();

		for (i = 0; i < n; i++)
		{
			node *temp = x.search(searchable[i]);
			if (temp == 0)
				usc++;
			else
				sc++;
		}

		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("searched in %f seconds\n", time_spent);
		printf("%d words found, %d not found\n", sc, usc);
		//--------------------------------------------------------------------------search

		x.memFree();
		printf("---------------------------------------------------------chaining\n\n");
		//-----------------------------------------------------------------------------------------------chaining

		//-----------------------------------------------------------------------------------------------linear probing
		linearProbing y(n, t);
		printf("---------------------------------------------------------linear probing\n");

		//--------------------------------------------------------------------------insert
		begin = clock();

		for (i = 0; i < n; i++)
			y.insert(dict[i]);

		end = clock();

		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("inserted %d words in %f seconds, %d collisions occured, \n", n, time_spent, y.getCollision());
		//--------------------------------------------------------------------------insert

		//--------------------------------------------------------------------------search
		sc = 0, usc = 0;
		begin = clock();

		for (i = 0; i < n; i++)
		{
			j = y.search(searchable[i]);
			if (!j)
				usc++;
			else
				sc++;
		}

		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

		printf("searched in %f seconds\n", time_spent);
		printf("%d words found, %d not found\n", sc, usc);
		//--------------------------------------------------------------------------search

		y.memFree();
		printf("---------------------------------------------------------linear probing\n\n");
		//-----------------------------------------------------------------------------------------------linear probing

		delete[] searchable;
		delete[] dict;
	}

	return 0;
}
