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
	node *temp;
	node *parent, *uncle, *grandParent;
	node *t1, *t2, *t3, *t4, *gt;
	node *a, *b, *c;

public:
	node *root;
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
	node *rightRotate(node *t)
	{
		b = t;
		a = b->parent; gt = a->parent;
		c = b->left; t3 = b->right;

		swap(a->color, b->color);

		b->parent = gt;
		//a is the right child
		if (gt != NULL &&  a->data > gt->data)
			gt->right = b;

		//a is the left child
		else if (gt != NULL &&  a->data < gt->data)
			gt->left = b;

		a->left = t3;
		b->right = a; a->parent=b;

		if (t3 != NULL)
			t3->parent = a;

		if (b->parent == NULL)
			root = b;

		return b;
	}
	//-----------------------------------------------------------------------right rotation


	//-----------------------------------------------------------------------left rotation
	node *leftRotate(node *t)
	{
		b = t;
		a = b->parent; gt = a->parent;
		c = b->right; t2 = b->left;

		swap(a->color, b->color);

		b->parent = gt;
		//a is the right child
		if (gt != NULL &&  a->data > gt->data)
			gt->right = b;

		//a is the left child
		else if (gt != NULL &&  a->data < gt->data)
			gt->left = b;

		a->right = t2;
		b->left = a; a->parent = b;

		if (t2 != NULL)
			t2->parent = a;

		//see if root needs to be updated
		if (b->parent == NULL)
			root = b;

		return b;
	}
	//-----------------------------------------------------------------------left rotation


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

						t = leftRotate(t);
						t = rightRotate(t);
					}

					else
					{
						/*      g
						*      /
						*     p
						*   /
						*  t	                   */

						t = rightRotate(t->parent);
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

						t = rightRotate(t);
						t = leftRotate(t);
					}

					else
					{
						/*  g
						*		\
						*         p
						*           \
						*             t     */

						t = leftRotate(t->parent);
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
		/*if (lookUp(data))
		{
			printf("%d already exists in the tree !!!\n", data);
			return;
		}*/

		struct node *newNode = new node(data);
		if (root == NULL)
			root = newNode;

		else
		{
			temp = root;
			while (temp)
			{
				if (data >= temp->data && temp->right == NULL)
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

				else if (data >= temp->data && temp->right)
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


	//-----------------------------------------------------------------------get sibling
	node *sibling(node *x)
	{
		parent = x->parent;

		if (parent != NULL)
		{
			if (parent->left==x)
				return parent->right;
			else
				return parent->left;
		}
	}
	//-----------------------------------------------------------------------get sibling


	//-----------------------------------------------------------------------case: red
	void caseRed(node *x)
	{
		parent = x->parent;
		t1 = x->left; t2 = x->right;

		//x is right child
		if (x==x->parent->right)
		{
			if (x->left != NULL)
				parent->right = x->left, x->left->parent = parent;

			else if (x->right != NULL)
				parent->right = x->right, x->right->parent = parent;

			else
				parent->right = NULL;
		}

		//x is left child
		else
		{
			if (x->left != NULL)
				parent->left = x->left, x->left->parent = parent;

			else if (x->right != NULL)
				parent->left = x->right, x->right->parent = parent;

			else
				parent->left = NULL;
		}

		delete x;
	}
	//-----------------------------------------------------------------------case: red


	//-----------------------------------------------------------------------delete case: 1
	void deleteCase1(node *x)
	{
		if (x->parent == NULL)
			x->color = black;
		else
			deleteCase2(x);
	}
	//-----------------------------------------------------------------------delete case: 1


	//-----------------------------------------------------------------------delete case: 2
	void deleteCase2(node *x)
	{
		t1 = sibling(x);

		if (t1 != NULL && t1->color == red)
		{
			if (x == x->parent->left)
				leftRotate(t1);
			else
				rightRotate(t1);
		}

		deleteCase3(x);
	}
	//-----------------------------------------------------------------------delete case: 2


	//-----------------------------------------------------------------------delete case: 3
	void deleteCase3(node *x)
	{
		t3 = sibling(x);

		bool f1=0, f2=0;
		if (t3->left == NULL)
			f1 = 1;
		else if (t3->left != NULL && t3->left->color == black)
			f1 = 1;

		if (t3->right == NULL)
			f2 = 1;
		else if (t3->right != NULL && t3->right->color == black)
			f2 = 1;

		if (x->parent->color == black && t3->color == black && f1 && f2)
		{
			t3->color = red;
			deleteCase1(x->parent);
		}

		else
			deleteCase4(x);
	}
	//-----------------------------------------------------------------------delete case: 3


	//-----------------------------------------------------------------------delete case: 4
	void deleteCase4(node *x)
	{
		t3 = sibling(x);

		bool f1 = 0, f2 = 0;
		if (t3->left == NULL)
			f1 = 1;
		else if (t3->left != NULL && t3->left->color == black)
			f1 = 1;

		if (t3->right == NULL)
			f2 = 1;
		else if (t3->right != NULL && t3->right->color == black)
			f2 = 1;

		if (x->parent->color == red && t3->color == black && f1 && f2)
		{
			t3->color = red;
			x->parent->color = black;
		}

		else
			deleteCase5(x);
	}
	//-----------------------------------------------------------------------delete case: 4


	//-----------------------------------------------------------------------delete case: 5
	void deleteCase5(node *x)
	{
		t3 = sibling(x);

		if (x == x->parent->left && x->parent->color == black && t3->color == black && (t3->left!=NULL && t3->left->color == red))
		{
			bool f1 = 0;
			if (t3->right == NULL)
				f1 = 1;
			else if (t3->right != NULL && t3->right->color == black)
				f1 = 1;

			if (f1)
				rightRotate(t3->left);
		}

		else if (x == x->parent->right && x->parent->color == black && t3->color == black && (t3->right!=NULL && t3->right->color == red))
		{
			bool f1 = 0;
			if (t3->left == NULL)
				f1 = 1;
			else if (t3->left != NULL && t3->left->color == black)
				f1 = 1;

			if (f1)
				leftRotate(t3->right);
		}

		deleteCase6(x);
	}
	//-----------------------------------------------------------------------delete case: 5


	//-----------------------------------------------------------------------delete case: 6
	void deleteCase6(node *x)
	{
		t3 = sibling(x);

			if (x == x->parent->left && t3->color == black && t3->right->color == red)
				t3->right->color = black, leftRotate(t3), visualize(root, getHeight());

		else if(x==x->parent->right && t3->color==black && t3->left->color==red)
			t3->left->color = black, rightRotate(t3);

		x->color = black;
	}
	//-----------------------------------------------------------------------delete case: 6


	//-----------------------------------------------------------------------delete a node from the tree, recursively !!!
	void deleteNode(node *x)
	{
		node *p;

		if(x->left!=NULL && x->right!=NULL)
		{
			//delete the succesor
			temp=getMax(x->left);
			x->data = temp->data;

			deleteNode(temp);
		}

		else
		{
			if (x->color == red)
				caseRed(x);

			else if (x->right != NULL && x->right->color == red && x->color == black)
			{
				//change color of x.right into black and stick it with x.parent, delete x
				x->right->color = black;
				parent = x->parent;

				//root
				if (parent == NULL)
					root = x->right;

				else
				{
					if (x==x->parent->left)
						parent->left = x->right;

					else
						parent->right = x->right;
				}

				x->right->parent = parent;
				delete x;
			}

			else if (x->left != NULL && x->left->color == red && x->color == black)
			{
				//change color of x.left into black and stick it with x.parent, delete x
				x->left->color = black;
				parent = x->parent;

				//root
				if (parent == NULL)
					root = x->left;

				else
				{
					if (x->data < parent->data)
						parent->left = x->left;

					else
						parent->right = x->left;
				}

				x->left->parent = parent;
				delete x;
			}

			//tryout the six cases
			else
			{
				deleteCase1(x);

				//replace with child;
				if (x->right != NULL)
				{
					t3 = x->right;
					t3->color = x->color;
					t3->parent = x->parent;

					if (x->parent && x == x->parent->right)
						x->parent->right = t3;
					else if (x->parent && x == x->parent->left)
						x->parent->left = t3;
				}

				else if (x->left != NULL)
				{
					t3 = x->left; t3->color = x->color;
					t3->parent = x->parent;

					if (x->parent && x == x->parent->right)
						x->parent->right = t3;
					else if (x->parent && x == x->parent->left)
						x->parent->left = t3;
				}

				else
				{
					if (x->parent && x == x->parent->right)
						x->parent->right = NULL;
					else if (x->parent && x == x->parent->left)
						x->parent->left = NULL;
				}

				if (root == x)
					root = NULL;

				delete x;
			}
		}
	}
	//-----------------------------------------------------------------------delete a node from the tree, recursively !!!


	//-----------------------------------------------------------------------delete a key from the tree, call from the main
	void deleteItem(int x)
	{
		node *rm = lookUp(x);

		if (rm == NULL)
			printf("item not found in the tree !!!\n");

		else
			deleteNode(rm);
	}
	//-----------------------------------------------------------------------delete a key from the tree, call from the main


	//-----------------------------------------------------------------------minimum of the tree
	node* getMin(node *x)
	{
		if (root == NULL)
			return NULL;

		temp = x;

		while (temp->left!= NULL)
		{
			temp = temp->left;
		}

		return temp;
	}
	//-----------------------------------------------------------------------minimum of the tree


	//-----------------------------------------------------------------------maximum of the tree
	node* getMax(node *x)
	{
		if (root == NULL)
			return NULL;

		temp = x;

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


	//-----------------------------------------------------------------------using dfs to traverse the tree and checking its properties
	void dfs(node *t,int cnt)
	{
		if (t->color == red)
		{
			if (t->right && t->right->color == red)
				printf("red-red property violated !!!\n");

			if (t->left && t->left->color == red)
				printf("red-red property violated !!!\n");
		}

		if (t->left == NULL && t->right == NULL)
		{
			if (t->color == black)
				cnt++;

			printf("%d %d\n", t->data, cnt);
			return;
		}

		if (t->right)
		{
			if (t->color == black)
				dfs(t->right, cnt + 1);
			else
				dfs(t->right, cnt);
		}

		if (t->left)
		{
			if (t->color == black)
				dfs(t->left, cnt + 1);
			else
				dfs(t->left, cnt);
		}
	}
	//-----------------------------------------------------------------------using dfs to traverse the tree and checking its properties


	//-----------------------------------------------------------------------verify red-black tree properties
	void verify()
	{
		if(root)
			dfs(root, 0);
	}
	//-----------------------------------------------------------------------verify red-black tree properties


	//-----------------------------------------------------------------------height of the tree
	int height(node *x)
	{
		if (x == NULL)
			return 0;

		return max(height(x->left) +1, height(x->right)+1);
	}

	int getHeight()
	{
		return height(root);
	}
	//-----------------------------------------------------------------------height of the tree


	//-----------------------------------------------------------------------visualize the tree
	void visualize(struct node * x, int h)
	{
		if (x == NULL)
			return;

		//print left sub-tree
		visualize(x->left, h - 1);

		//print item
		for (int i = 0; i<h; i++)printf("   ");
		printf("%03d\n", x->data);

		//print right sub-tree
		visualize(x->right, h - 1);
	}
	//-----------------------------------------------------------------------visualize the tree

};

int main()
{
	//freopen("in2.txt", "r", stdin);

	int i, j, k;
	int n, m, t;

	rbTree x;

	while (1)
	{
		printf("---------------------------------------------------------------------------------------\n");
		printf("1. insert  2. delete  3.look-up  4. minimum  5. maximum  6. print  7. verification \n");
		printf("8. height of the tree  9. visualize tree  10. exit\n");
		printf("---------------------------------------------------------------------------------------\n");
		scanf("%d", &t);

		if (t == 1)
		{
			scanf("%d", &n);
			x.insert(n);
		}

		else if (t == 2)
		{
			scanf("%d", &n);
			x.deleteItem(n);
		}

		else if (t == 3)
		{
			scanf("%d", &n);

			if (x.lookUp(n) == NULL)
				printf("%d is not in the tree :(\n", n);
			else
				printf("found !!!\n");
		}

		else if (t == 4)
		{
			if (x.getMin(x.root) == NULL)
				printf("the tree is empty !!!\n");
			else
				printf("%d is the minimum\n", x.getMin(x.root)->data);
		}

		else if (t == 5)
		{

			if (x.getMax(x.root) == NULL)
				printf("the tree is empty !!!\n");
			else
				printf("%d is the maximum\n", x.getMax(x.root)->data);
		}

		else if (t == 6)
			x.print();

		else if (t == 7)
			x.verify();

		else if (t == 8)
			printf("height of the tree is %d\n", x.getHeight());

		else if(t==9)
			x.visualize(x.root,x.getHeight());

		else
			break;
	}

	return 0;
}
