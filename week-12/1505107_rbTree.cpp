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
#define N 200010
#define inf 100000000
#define pp pair<int,int>

#define red 1
#define black 0

using namespace std;

struct node
{
	int data,color;
	node *left, *right, *parent;

	node(int mdata)
	{
		data =mdata;
		color = red;
		left = right = parent = NULL;
	}
};

class rbTree
{
	node *root, *temp;
	node *parent, *uncle, *grandParent;
	node *t1, *t2, *t3, *t4, *gt;
	node *a, *b, *c;

public:

	rbTree()
	{
		root = NULL;
	}

	//-----------------------------------------------------------------------inorder traversal
	void inOrderTraversal(node *t)
	{
		if (t == NULL)
			return;

		inOrderTraversal(t->left);
		printf("%d ", t->data);
		inOrderTraversal(t->right);
	}
	//-----------------------------------------------------------------------inorder traversal


	//-----------------------------------------------------------------------right rotation
	node* rightRotate(node *t)
	{
		c = t;
		b = t->parent;
		a = b->parent;

		swap(a->color, b->color);

		t1 = c->left; t2 = c->right;
		t3 = b->right; t4 = a->right;
		gt = a->parent;

		//a is the right child
		if (gt != NULL &&  a->data > gt->data)
			gt->right = b;

		else if(gt != NULL &&  a->data < gt->data)
			gt->left = b;

		b->parent = gt;
		b->left = c; b->right = a;
		c->parent = a->parent = b;
		c->left = t1; c->right = t2;
		a->left = t3; a->right = t4;

		if (t1 != NULL)
			t1->parent = c;

		if (t2 != NULL)
			t2->parent = c;

		if (t3 != NULL)
			t3->parent = a;

		if (t4 != NULL)
			t4->parent = a;

		return b;
	}
	//-----------------------------------------------------------------------right rotation


	//-----------------------------------------------------------------------left rotation
	node* leftRotate(node *t)
	{
		c = t;
		b = t->parent;
		a = b->parent;

		swap(a->color, b->color);

		t1 = a->left; t2 = b->left;
		t3 = c->left; t4 = c->right;
		gt = a->parent;

		//a is the right child
		if (gt!=NULL && a->data > gt->data)
			gt->right = b;

		else if (gt != NULL && a->data < gt->data)
			gt->left = b;

		b->parent = gt;
		b->left = a; b->right = c;
		c->parent = a->parent = b;
		a->left = t1; a->right = t2;
		c->left = t3; c->right = t4;

		if (t1 != NULL)
			t1->parent = a;

		if (t2 != NULL)
			t2->parent = a;

		if (t3 != NULL)
			t3->parent = c;

		if (t4 != NULL)
			t4->parent = c;

		return b;
	}
	//-----------------------------------------------------------------------left rotation


	//-----------------------------------------------------------------------right-left rotation
	node* rightLeftRotate(node *t)
	{
		c = t;
		b = c->parent;
		a = b->parent;

		swap(a->color, c->color);

		t1 = a->left; t2 = c->left;
		t3 = c->right; t4 = b->right;
		gt = a->parent;

		//a is the right child
		if (gt!=NULL && a->data > gt->data)
			gt->right = c;

		else if (gt != NULL && a->data < gt->data)
			gt->left = c;

		c->parent = gt;
		c->left = a; c->right = b;
		a->parent = b->parent = c;
		a->left = t1; a->right = t2;
		b->left = t3; b->right = t4;

		if (t1 != NULL)
			t1->parent = a;

		if (t2 != NULL)
			t2->parent = a;

		if (t3 != NULL)
			t3->parent = b;

		if (t4 != NULL)
			t4->parent = b;

		return c;
	}
	//-----------------------------------------------------------------------right-left rotation


	//-----------------------------------------------------------------------left-right rotation
	node* leftRightRotate(node *t)
	{
		c = t;
		b = c->parent;
		a = b->parent;

		swap(a->color, c->color);

		t1 = b->left; t2 = c->left;
		t3 = c->right; t4 = a->right;
		gt = a->parent;

		//a is the right child
		if (gt!=NULL && a->data > gt->data)
			gt->right = c;

		else if (gt != NULL && a->data < gt->data)
			gt->left = c;

		c->parent = gt;
		c->left = b; c->right = a;
		b->parent = a->parent = c;
		b->left = t1; b->right = t2;
		a->left = t3; a->right = t4;

		if (t1 != NULL)
			t1->parent = b;

		if (t2 != NULL)
			t2->parent = b;

		if (t3 != NULL)
			t3->parent = a;

		if (t4 != NULL)
			t4->parent = a;

		return c;
	}
	//-----------------------------------------------------------------------left-right rotation


	//-----------------------------------------------------------------------fix the properties of the tree
	void fix(node *t)
	{
		if (root == t)
		{
			t->color = black;
			return;
		}

		while (t->parent != NULL && t->parent->color==red)
		{
			parent = t->parent;
			grandParent = parent->parent;

			if (grandParent->left == parent)
			{
				uncle = grandParent->right;

				//parent and uncle both are red
				//needs re-coloring
				if (uncle != NULL && uncle->color==red)
				{
					parent->color = black;
					uncle->color = black;
					grandParent->color = red;

					t = grandParent;
				}

				//uncle is either empty or black
				//needs rotation and re-coloring
				else
				{
					if (parent->right == t)
					{
						/*   g
						*   /
						*  p
						*   \
						*    t           */
						t = leftRightRotate(t);
					}

					else
					{
						/*      g
						*      /
						*     p
						*   /
						*  t	                   */
						t=rightRotate(t);
					}
				}
			}

			else
			{
				uncle = grandParent->left;

				//parent and uncle both are red
				//needs re-coloring
				if (uncle != NULL && uncle->color == red)
				{
					parent->color = black;
					uncle->color = black;
					grandParent->color = red;
					t = grandParent;
				}

				//uncle is either empty or black
				//needs rotation and re-coloring
				else
				{
					if (parent->left == t)
					{
						/*    g
						*		 \
						*         p
						*       /
						*     t          */
						t = rightLeftRotate(t);
					}

					else
					{
						/*  g
						*		\
						*         p
						*           \
						*             t     */
						t=leftRotate(t);
					}
				}
			}

			if (t->parent == NULL)
			{
				root = t; break;
			}
		}

		root->color = black;
	}
	//-----------------------------------------------------------------------fix the properties of the tree


	//-----------------------------------------------------------------------insert in the tree
	void insert(int data)
	{
		if (lookUp(data))
		{
			printf("%d already exists in the tree !!!\n", data);
			return;
		}

		struct node *newNode = new node(data);
		if (root == NULL)
			root = newNode;

		else
		{
			temp = root;
			while (temp)
			{
				if (data > temp->data && temp->right == NULL)
				{
					newNode->parent = temp;
					temp->right = newNode;
					break;
				}

				else if (data < temp->data && temp->left == NULL)
				{
					newNode->parent = temp;
					temp->left = newNode;
					break;
				}

				else if (data > temp->data && temp->right)
					temp = temp->right;

				else if (data < temp->data && temp->left)
					temp = temp->left;

				else
					exit(EXIT_FAILURE);
			}
		}

		//fix
		fix(newNode);
	}
	//-----------------------------------------------------------------------insert in the tree


	//-----------------------------------------------------------------------search a key in the tree
	node* lookUp(int k)
	{
		struct node *temp;
		temp = root;

		while (temp != NULL)
		{
			if (temp->data == k)
				return temp;

			else if (temp->data > k)
				temp = temp->left;

			else
				temp = temp->right;
		}

		return temp;
	}
	//-----------------------------------------------------------------------search a key in the tree


	//-----------------------------------------------------------------------minimum of the tree
	node* getMin()
	{
		if (root == NULL)
			return NULL;

		struct node *temp;
		temp = root;

		while (temp->left!= NULL)
		{
			temp = temp->left;
		}

		return temp;
	}
	//-----------------------------------------------------------------------minimum of the tree


	//-----------------------------------------------------------------------maximum of the tree
	node* getMax()
	{
		if (root == NULL)
			return NULL;

		struct node *temp;
		temp = root;

		while (temp->right != NULL)
		{
			temp = temp->right;
		}

		return temp;
	}
	//-----------------------------------------------------------------------maximum of the tree


	//-----------------------------------------------------------------------traverse the tree and print in sorted order
	void print()
	{
		inOrderTraversal(root);
		printf("\n");
	}
	//-----------------------------------------------------------------------traverse the tree and print in sorted order
};

int main()
{
	//freopen("in2.txt", "r", stdin);

	int i, j, k;
	int n, m, t;

	rbTree x;

	while (1)
	{
		printf("1. insert  2. delete  3.look-up  4. minimum  5. maximum  6. print  7.exit\n");
		scanf("%d", &t);

		if (t == 1)
		{
			scanf("%d", &n);
			x.insert(n);
		}

		else if (t == 2)
		{
			scanf("%d", &n);
			//del
		}

		else if (t == 3)
		{
			scanf("%d", &n);

			if (x.lookUp(n)==NULL)
				printf("%d is not found in the tree :(\n", n);
			else
				printf("found !!!\n");
		}

		else if (t == 4)
		{
			if (x.getMin()==NULL)
				printf("the tree is empty !!!\n");
			else
				printf("%d is the minimum\n", x.getMin()->data);
		}

		else if (t == 5)
		{

			if (x.getMax()==NULL)
				printf("the tree is empty !!!\n");
			else
				printf("%d is the maximum\n", x.getMax()->data);
		}

		else if (t == 6)
			x.print();

		else
			break;
	}

	return 0;
}
