/**************Second Best MST***************/
/**************       1505107       ***************/

#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -999999
#define INFINITY 999999

#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

#define dbg printf("in\n");
#define nl printf("\n");

//----------------------------------------------------------------------------------vertex
class HeapItem
{
    public:
        int data;
        float key;
};
//----------------------------------------------------------------------------------vertex


//----------------------------------------------------------------------------------edge
struct edge
{
    int v,w;
    edge(){}
    edge(int to,int weight)
    {
        v=to;
        w=weight;
    }
};
//----------------------------------------------------------------------------------edge


//----------------------------------------------------------------------------------edge
struct edge2
{
    int u,v,w;
    edge2(){}
    edge2(int from,int to,int weight)
    {
        u=from;
        v=to;
        w=weight;
    }
};
//----------------------------------------------------------------------------------edge


//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem *A;        //stores nodes
    int heapLength;
    int *map;

    //---------------------------------------------------------------------------------------------
    //constructor
    MinHeap()
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //destructor
    ~MinHeap()
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0;                        //set to NULL after deletion
        A = 0;                            //set to NULL after deletion
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //Fills the heap with an array of integers
    //key values do not maintain heap property
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //insert an item
    void insertItem(int data, float key)
    {
        heapLength++;
        A[heapLength].data=data;
        A[heapLength].key=key;

        map[A[heapLength].data]=heapLength;

        //restore the properties of the heap
        buHeapify(heapLength);
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        HeapItem temp=A[1];
        A[1]=A[heapLength];

        if(heapLength==0)
        {
            printf("Nothing to delete\n");
            temp.data=-1;temp.key=-1;
            return  temp;
        }

        heapLength--;
        heapify(1);

        return temp;
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //The function updates the key value of an existing data stored in the heap
    void updateKey(int data, float key)
    {
        //search
        int idx=0;
        idx=map[data];

        if(!idx)
        {
            printf("Data not found\n");
            return ;
        }

        //this node should be placed in lower parts of the tree
        if(A[idx].key>key)
        {
            A[idx].key=key;
            buHeapify(idx);
        }

        else
        {
             A[idx].key=key;
             heapify(idx);
        }

    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //This function returns the key value of a data stored in heap
    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //this function will restore heap property
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;          //left child index
            r=2*i+1;     //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom

            else if(r>heapLength)
                smallest = l;

            else if(l>heapLength)
                smallest = r;

            else if( A[l].key < A[r].key )
                smallest = l;

            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying

            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }
        }
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //restoring heap properties starting from index i to the root
    void buHeapify(int i)
    {
        HeapItem temp;
        int parent,child;

        child=i;
        while(child>1)
        {
            //i be the parent, then 2i is the left child, 2i+1 the right
            if(child%2==0)
                parent=child/2;
            else
                parent=(child-1)/2;

            if(A[parent].key>A[child].key)
            {
                temp=A[child];
                A[child]=A[parent];
                A[parent]=temp;

                map[A[parent].data]=parent;
                map[A[child].data]=child;

            }

            child=parent;
        }
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    //print the heap
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    bool Empty()
    {
        if(heapLength==0)
            return true;

        else
            return false;
    }
    //---------------------------------------------------------------------------------------------

};

//----------------------------------------------------------------------------------Dynamic ArrayList
class ArrayList
{
    edge *list;
    int length ;
    int listMaxSize,listInitSize ;
public:
    ArrayList()
    {
        listInitSize = 2 ;
        listMaxSize = listInitSize ;
        list = new edge[listMaxSize] ;
        length = 0 ;
    }

    void clearArrayList()
    {
        if(list)
            delete[] list;

        listInitSize = 2 ;
        listMaxSize = listInitSize ;
        list = new edge[listMaxSize] ;
        length = 0 ;
    }

    void insertItem(edge newitem)
    {
        edge *tempList ;
        if (length == listMaxSize)
        {
            //allocate new memory space for tempList
            listMaxSize = 2 * listMaxSize ;
            tempList = new edge[listMaxSize] ;
            for(int i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ; //copy all items from list to tempList
            }

            delete[] list ; //free the memory allocated before
            list = tempList ; //make list to point to new memory
        }

        list[length] = newitem ;
        length++ ;
    }

    int searchItem(edge item)
    {
        int i = 0;
        for (i = 0; i < length; i++)
        {
            if( list[i].v == item.v && list[i].w==item.w )
                return i;
        }
        return NULL_VALUE;
    }

    void removeItemAt(int position)
    {
        if ( position < 0 || position >= length ) return;
        list[position] = list[length-1] ;
        length-- ;
    }

    void removeItem(edge item)
    {
        int position;
        position = searchItem(item) ;
        if ( position == NULL_VALUE ) return ; //nothing to remove
        removeItemAt(position) ;
    }

    int getLength()
    {
        return length ;
    }

    edge getItem(int position)
    {
        if(position < 0 || position >= length) return edge(-1,-1) ;
        return list[position] ;
    }

    bool empty()
    {
        if(length==0)return true;
        else return false;
    }

    void printList()
    {
        int i;
        for(i=0; i<length; i++)
            printf("%d %d\n", list[i].v,list[i].w);

        printf("Current size: %d, current length: %d\n", listMaxSize, length);
    }

    ~ArrayList()
    {
        if(list) delete [] list;
        list = 0 ;
    }
};

//----------------------------------------------------------------------------------ArrayList class ends here


//----------------------------------------------------------------------------------Graph class starts here
class Graph
{
    bool *vis;
    int nVertices, nEdges ;
    int *parent,*dist;
    ArrayList  *adjList ;
    edge2 *minEdges;
    MinHeap pq;

public:
    //--------------------------------------------------Constructing
    Graph()
    {
        nVertices = 0 ; nEdges = 0;
        adjList = 0 ;vis=0;
        parent=0;dist=0;
        minEdges=0;
    }
    //--------------------------------------------------Constructing


    //--------------------------------------------------Memory allocation
    void setnVertices(int n)
    {
        //node number will start from 1
        nVertices=n+1;

        if(adjList!=0)
            delete[] adjList ; //delete previous list

        //deleting previous statistics
        if(parent!=0)
            delete[] parent;

        if(dist!=0)
            delete[] dist;

        adjList=new ArrayList[nVertices] ;

        dist=new int[nVertices];
        parent=new int[nVertices];
        vis=new bool[nVertices];
        minEdges=new edge2[n-1];

        nVertices--;
    }
    //--------------------------------------------------Memory allocation


    //--------------------------------------------------Add Edge
    void addEdge(int u, int v,int w)
    {
        //vertex out of range
        if(u<=0 || v<=0 || u>nVertices || v>nVertices)
        {
            printf("vertex out of range\n");
            return;
        }

        this->nEdges++ ;

        adjList[u].insertItem(edge(v,w)) ;
        adjList[v].insertItem(edge(u,w)) ;
    }
    //--------------------------------------------------Add Edge


    //--------------------------------------------------Remove Edge
    void removeEdge(int u, int v,int w)
    {
        if(u<=0 || v<=0 || u>nVertices || v>nVertices)
            return;

        adjList[u].removeItem(edge(v,w));
        adjList[v].removeItem(edge(u,w));
    }
    //--------------------------------------------------Remove Edge


    //--------------------------------------------------Prim's algorithm
    int prim(bool f)
    {
        int i,j,k;
        edge e;

        for(i=1;i<=nVertices;i++)
        {
            dist[i]=INFINITY;
            parent[i]=-1;
            vis[i]=0;
        }

        dist[1]=0;
        for(i=1;i<=nVertices;i++)
            pq.insertItem(i,dist[i]);

        while(!pq.Empty())
        {
            HeapItem u=pq.removeMin();

            if(vis[u.data])
                continue;

            for(i=0;i<adjList[u.data].getLength();i++)
            {
                e=adjList[u.data].getItem(i);

                if(!vis[e.v] && dist[e.v]>e.w)
                {
                    parent[e.v]=u.data;
                    dist[e.v]=e.w;
                    pq.updateKey(e.v,dist[e.v]);
                }
            }

            vis[u.data]=1;
        }

        //output of MST
        for(i=2;i<=nVertices;i++)
        {
            if(parent[i]==-1)
                return -1;
        }

        //second best MST function will call prims to get the MST
        //when f=1, it means we are  storing the best MST
        if(f)
        {
            for(i=2;i<=nVertices;i++)
            {
                minEdges[i-2]=edge2(i,parent[i],dist[i]);
            }

            return 0;
        }

        int sum=0;
        for(i=1;i<=nVertices;i++)
            sum+=dist[i];

        return sum;
    }
    //--------------------------------------------------Prim's algorithm


    //--------------------------------------------------second best MST
    void sbMST()
    {
        int i,j,k;
        int m=INFINITY;
        int *tempParent=new int[nVertices+1];

        j=prim(1);

        //no minimum spanning tree as the graph is not connected
        //as there is no MST, there won't be any sbMST
        if(j==-1)
        {
            printf("Graph Not Connected\n");
            return;
        }

        k=0;
        edge2 x;
        for(i=0;i<nVertices-1;i++)
        {
            x=minEdges[i];
            removeEdge(x.u,x.v,x.w);

            j=prim(0);
            if(j==-1)
            {
                addEdge(x.u,x.v,x.w);
                continue;
            }

            if(m>j)
            {
                for(i=1;i<=nVertices;i++)
                    tempParent[i]=parent[i];

                m=j;
            }

            k++;
            addEdge(x.u,x.v,x.w);
        }

        if(k==0)
            printf("There is no second best MST.\n");

        else
        {
            for(i=2;i<=nVertices;i++)
                printf("%d %d\n",i,tempParent[i]);

            printf("%d",m);
        }

        delete[] tempParent;
    }
    //--------------------------------------------------second best MST


    //--------------------------------------------------Destruction
    ~Graph()
    {
        if(parent)
        {
            delete[] parent;
            parent=0;
        }

        if(dist)
        {
            delete[] dist;
            dist=0;
        }

        if(adjList)
        {
            delete[] adjList;
            adjList=0;
        }

        if(minEdges)
        {
            delete[] minEdges;
            minEdges=0;
        }

        if(parent)
        {
            delete[] parent;
            parent=0;
        }

        if(dist)
        {
            delete[] dist;
            dist=0;
        }
    }
};
//--------------------------------------------------Destruction
//----------------------------------------------------------------------------------Graph class ends here


int main()
{

    //freopen("in.txt","r",stdin);

    int i,j,k;
    int n,m;
    int u,v,w;

    Graph g;

    scanf("%d%d",&n,&m);
    g.setnVertices(n);

    for(i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        g.addEdge(u,v,w);
    }

    g.sbMST();

    return 0;
}
