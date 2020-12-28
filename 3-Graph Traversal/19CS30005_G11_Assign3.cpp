/*
    author : Aryan Agarwal, 19CS30005
    created : 24-September-2020 13:51:43 IST
*/
#include <iostream>
using namespace std;

const int mXn=200;

struct point
{
    int x;
    int y;
};

struct queue
{
    point *arr;
    int queue_size, start_id, end_id;
};

struct stack
{
    point head;
    stack* next;
};







void printgrid(int grid[][mXn], int a, int b)
{
    cout << "Grid of Stones is:\n";

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (grid[i][j])
                cout << "*";
            else
                cout << "-";
        }
        cout << "\n";
    }
}

void init_queue(queue *qp, int size)
{
    qp->queue_size = 0;
    qp->start_id = -1;
    qp->end_id = -1;
    qp->arr = (point *)malloc(size * sizeof(point));
}

int isempty_queue(queue qp)
{
    return qp.queue_size == 0 ? 1 : 0;
}

void enqueue(queue *qp, point P)
{

    if (isempty_queue(*qp))
    {
        qp->start_id = 0;
        qp->end_id = 0;
    }
    else
    {
        qp->end_id++;
    }

    qp->arr[qp->end_id] = P;
    qp->queue_size++;
}

point dequeue(queue *qp)
{
    point P;

    if (isempty_queue(*qp))
    {
        cout << "Cannot dequeue from empty queue\n";

        P={-1,-1};
        return P;
    }

    P = {qp->arr[qp->start_id].x,qp->arr[qp->start_id].y};

    if (qp->queue_size == 1)
    {
        qp->start_id = -1;
        qp->end_id = -1;
    }
    else
    {
        qp->start_id++;
    }

    qp->queue_size--;

    

    return P;
}

int strategy1(point src,point dest,int grid[][mXn],int a,int b)
{
    queue qp;
    init_queue(&qp, mXn*mXn);

    if(src.x==dest.x && src.y==src.y)
    {
        return 1;
    }

    int visited[mXn][mXn] = {};
    enqueue(&qp, src);
    visited[src.x][src.y] = 1;

    while (!isempty_queue(qp))
    {
        point v = dequeue(&qp);
        
        if(v.x==dest.x && v.y==dest.y)
        {
            return 1;
        }

        if (v.x + 1 < a && !visited[v.x + 1][v.y] && grid[v.x + 1][v.y])
        {
            enqueue(&qp, {v.x + 1, v.y});
            visited[v.x + 1][v.y] = 1;
        }
        if (v.x - 1 >= 0 && !visited[v.x - 1][v.y] && grid[v.x - 1][v.y])
        {
            enqueue(&qp, {v.x - 1, v.y});
            visited[v.x - 1][v.y] = 1;
        }
        if (v.y + 1 < b && !visited[v.x][v.y + 1] && grid[v.x][v.y + 1])
        {
            enqueue(&qp, {v.x, v.y + 1});
            visited[v.x][v.y + 1] = 1;
        }
        if (v.y - 1 >= 0 && !visited[v.x][v.y - 1] && grid[v.x][v.y - 1])
        {
            enqueue(&qp, {v.x, v.y - 1});
            visited[v.x][v.y - 1] = 1;
        }
    }

    return 0;
}

void init_stack(stack* s)
{
    // s=NULL;
    // s->next=NULL;
    // s->head={-1,-1};
}
int isempty_stack(stack *top)
{
    if(top==NULL)return 1;
    else return 0;
}

void push(point P,stack* s,stack** top)
{
    stack* node=(stack*)malloc(sizeof(stack));

    node->head=P;
    node->next=*top;
    *top=node;

    // cout<<s;
}

point pop(stack* s,stack** top)
{
    if(isempty_stack(*top))
    {
        cout<<"popping cannot be done from empty list";

        return {-1,-1};
    }
    
    point P = s->head;

    *top = (*top)->next;
    

    return P;
}

void strategy2(point src,point dest,int grid[][mXn],int a,int b)
{
    stack s;
    init_stack(&s);
    stack* top=NULL;
    
    

    int visited[mXn][mXn]={};
    push(src,&s,&top);


    while(!isempty_stack(top))
    {
        point v = top->head;
        visited[v.x][v.y]=1;

        if(v.x==dest.x && v.y==dest.y)
        {
            break;
        }

        if (v.x + 1 < a && !visited[v.x + 1][v.y] && grid[v.x + 1][v.y])
        {
            push({v.x + 1, v.y} ,&s, &top);
        }
        if (v.x - 1 >= 0 && !visited[v.x - 1][v.y] && grid[v.x - 1][v.y])
        {
            push({v.x - 1, v.y} ,&s, &top);
        }
        if (v.y + 1 < b && !visited[v.x][v.y + 1] && grid[v.x][v.y + 1])
        {
            push({v.x, v.y + 1} ,&s, &top);
        }
        if (v.y - 1 >= 0 && !visited[v.x][v.y - 1] && grid[v.x][v.y - 1])
        {
            push({v.x, v.y - 1} ,&s, &top);
        }
        
    }

    while (top!=NULL)
    {
        cout<<"("<<top->head.x<<","<<top->head.y<<") ,";
        top=top->next;
        
    }


}

int main()
{
    freopen("input.txt", "r", stdin);

    int a, b, n;
    cin >> a >> b >> n;

    int grid[mXn][mXn] = {};
    point james, fly;

    int x[n], y[n];

    for (int i = 0; i < n; i++)
        cin >> x[i];
    for (int i = 0; i < n; i++)
        cin >> y[i];

    cin >> james.x >> james.y;
    cin >> fly.x >> fly.y;

    for (int i = 0; i < n; i++)
    {
        grid[x[i]][y[i]] ^= 1;
    }

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            grid[i][j] ^= 1; // grid[i][j] = 0 if the point (i,j) is unstable
        }
    }

    printgrid(grid, a, b);

    if(strategy1(james,fly,grid,a,b))
    {
        cout<<"Path Exists\n";

        strategy2(james,fly,grid,a,b);
    }

    

    return 0;
}