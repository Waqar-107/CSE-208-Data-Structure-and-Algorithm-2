/**************Bellman-Ford Algorithm***************/
/**************              1505107              ***************/

#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -999999
#define INFINITY 999999

#define dbg printf("in\n");
#define nl printf("\n");

//----------------------------------------------------------------------------------edge
struct edge
{
    int u,v,w;
    edge(){}
    edge(int from,int to,int weight)
    {
        u=from; v=to;
        w=weight;
    }
};
//----------------------------------------------------------------------------------edge


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

            delete[] list ;            //free the memory allocated before
            list = tempList ;       //make list to point to new memory
        }

        list[length] = newitem ;
        length++ ;
    }

    int searchItem(edge item)
    {
        int i = 0;
        for (i = 0; i < length; i++)
        {
            if(list[i].u==item.u && list[i].v == item.v && list[i].w==item.w )
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
        if(position < 0 || position >= length) return edge(-1,-1,-1);
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
            printf("%d %d %d\n",list[i].u,list[i].v,list[i].w);

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
    bool sol;
    int nVertices, nEdges ;
    int *parent,*dist;
    ArrayList  adjList ;

public:
    //--------------------------------------------------Constructing
    Graph()
    {
        nVertices = 0 ; nEdges = 0 ;
        parent=0;dist=0;
    }
    //--------------------------------------------------Constructing


    //--------------------------------------------------Memory allocation
    void setnVertices(int n)
    {
        //node number will start from 1
        nVertices=n+1;

        //deleting previous statistics
        if(parent!=0)
            delete[] parent;

        if(dist!=0)
            delete[] dist;

        dist=new int[nVertices];
        parent=new int[nVertices];

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

        adjList.insertItem(edge(u,v,w)) ;
    }
    //--------------------------------------------------Add Edge


    //--------------------------------------------------Remove Edge
    void removeEdge(int u, int v,int w)
    {
        if(u<=0 || v<=0 || u>nVertices || v>nVertices)
            return;

        adjList.removeItem(edge(u,v,w));
    }
    //--------------------------------------------------Remove Edge


    //--------------------------------------------------Bellman-Ford
    void BellmanFord(int s)
    {
        int i,j,k;
        int u,v,w;

        for(i=1;i<=nVertices;i++)
            dist[i]=INFINITY,parent[i]=-1;

        dist[s]=0;

        for(i=1;i<nVertices;i++)
        {
            for(j=0;j<adjList.getLength();j++)
            {
                u=adjList.getItem(j).u;v=adjList.getItem(j).v;w=adjList.getItem(j).w;
                if(dist[v]>dist[u]+w)
                {
                    dist[v]=dist[u]+w;
                    parent[v]=u;
                }
            }
        }

        //negative edge cycle
        for(i=0;i<adjList.getLength();i++)
        {
            u=adjList.getItem(i).u;v=adjList.getItem(i).v;w=adjList.getItem(i).w;
            if(dist[v]>dist[u]+w)
            {
                sol=0;return;
            }
        }
    }
    //--------------------------------------------------Bellman-Ford


    //--------------------------------------------------print
    void print()
    {
        for(int i=1;i<=nVertices;i++)
            printf("%d %d %d\n",i,dist[i],parent[i]);

        if(sol)
            printf("No negative edge cycle\n");
        else
            printf("Negative edge cycle found\n");
    }
    //--------------------------------------------------print


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

        if(parent)
        {
            delete[] parent;
            parent=0;
        }
    }
};
//--------------------------------------------------Destruction
//----------------------------------------------------------------------------------Graph class ends here


int main()
{

    freopen("in.txt","r",stdin);

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

    int source;
    scanf("%d",&source);

    g.BellmanFord(source);
    g.print();

    return 0;
}
