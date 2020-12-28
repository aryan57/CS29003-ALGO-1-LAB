//Please read the comment on line 11 and line 110
#include <stdio.h> 
#include <stdlib.h>

typedef struct {
    int x, y;
}POINT;

//---STACK---------------------------------------------
/*
Here we use dummy node as the head of stack. The node is initialized
with some point outside of the grid (-1, -1). Initially stack looks like
this : (-1, -1) -> NULL
If we insert (1, 2) to the stack, the stack will look like
(-1, -1) -> (1, 2) -> NULL
In this way double pointers can be avoided.
*/
typedef struct STACK{
    POINT head;
    struct STACK *next;
}STACK;

void init_stack(STACK *s){ //initializes the head and next pointer
    (s->head).x = -1, (s->head).y = -1;
    s->next = NULL;
}

int isempty_stack(STACK s){//returns 1 if the stack is empty, 0 otherwise
    return ((s.next) == NULL); // Checks if only dummy node is present
}

void push(STACK *s, POINT p){
    STACK *temp = (STACK *)malloc(sizeof(STACK));
    temp->head = p;
    temp->next = s->next;
    s->next = temp;
}

POINT pop(STACK *s){
    if(isempty_stack(*s)){
        perror("Empty stack being popped");
        exit(-1);
    }

    POINT rock = s->next->head;
    s->next = s->next->next;

    return rock;
}
//Stack implementation ends---------------------------------------------------

//---QUEUE---------------------------------------------
typedef struct {
    POINT *Arr ;
    int queue_size, start_id, end_id;
}QUEUE;

void init(QUEUE *qP, int size){//allocates space for queue
    qP->Arr = (POINT *)malloc(size*sizeof(POINT));
    qP->start_id = 0;
    qP->end_id = -1;
    qP->queue_size = 0;
}

int isempty(QUEUE qP){//returns 1 if the queue is empty, else 0
    return (qP.queue_size == 0);
}

void enqueue(QUEUE *qP, POINT p){
    qP->end_id++;
    qP->Arr[qP->end_id].x = p.x;
    qP->Arr[qP->end_id].y = p.y;
    qP->queue_size++;
}

POINT dequeue(QUEUE *qP){
    if(qP->queue_size == 0){
        perror("Trying to dequeue empty queue");
        exit(-1);
    }
    qP->start_id++;
    qP->queue_size--;
    return qP->Arr[qP->start_id-1];
}

//Queue implementation ends---------------------------------------------------

void printgrid(int a, int b, int **stable){
    for(int i=0; i<a; i++){
        for(int j=0; j<b; j++){
            if(stable[i][j] == -1)
                printf("-");
            else
                printf("*");
        }
        printf("\n");
    }
}

//Helper function to know if a given coordinate is stable and lies inside grid of rocks
int issafe(int x, int y, int a, int b, int **stable){
    return ((x >= 0 && y >= 0 && x < a && y < b) && stable[x][y] == 0);
}

int issame(POINT a, POINT b){
    return ((a.x == b.x) && (a.y == b.y));
}

/*
Useful implemetation detail: You can have two arrays denoting the directions
in which we can move. Eg. we can go from (x, y) to (x - 1, y + 0); this is 
captured in the first value i.e. (x + dx[0], y + dy[0])
*/
int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};

int strategy1(int a, int b, int **stable, POINT frog, POINT fly, QUEUE *q){
    int x, y;
    POINT rock;

    int **visited = (int **)malloc(a*sizeof(int *));
    
    for(int i=0; i<a; i++)
        visited[i] = (int *)malloc(b*sizeof(int));

    for(int i=0; i < a; i++){
        for(int j=0; j < b; j++){
            visited[i][j] = 0;
        }
    }

    enqueue(q, frog);
    visited[frog.x][frog.y] = 1;

    while(!isempty(*q)){
        x = (q->Arr)[q->start_id].x;
        y = (q->Arr)[q->start_id].y; 

        for(int i=0; i<4; i++){// iterate over possible 4 rocks
            if(issafe(x + dx[i], y + dy[i], a, b, stable) && visited[x + dx[i]][y + dy[i]] == 0){
                rock.x = x + dx[i];
                rock.y = y + dy[i];
                if(issame(fly, rock)){
                    printf("Path Exists\n");
                    return 1; 
                }
                visited[rock.x][rock.y] = 1;
                
                enqueue(q, rock);
            }
        }
        dequeue(q);
    }

    printf("No Path Exists\n");
    return 0;
}

void strategy2(int a, int b, int **stable, POINT frog, POINT fly, STACK *s){
    int **visited = (int **)malloc(a*sizeof(int *));
    
    for(int i=0; i<a; i++)
        visited[i] = (int *)malloc(b*sizeof(int));

    for(int i=0; i < a; i++){
        for(int j=0; j < b; j++){
            visited[i][j] = 0;
        }
    }

    push(s,fly);   // As we want to print the path from Frog to Fly, we
                    // find the path from fly to frog and use the dfs stack
                    // to print path in required order

    int found = 0; // represents that we have reached the destination
    visited[fly.x][fly.y] = 1;

    while(!isempty_stack(*s)){
        POINT cur = (s->next)->head;

        if(issame(cur, frog)){
            found = 1;
            break;
        }
        visited[cur.x][cur.y] = 1;

        POINT next_rock;
        int explored = 1;// to know if we have explored all neighbours of cur
        for(int i=0; i<4; i++){
            int newx = cur.x + dx[i], newy = cur.y + dy[i]; 
            // We can jump on only those points which are inside grid and not yet visited
            if(issafe(newx, newy, a, b, stable) && visited[newx][newy] == 0){
                next_rock.x = newx, next_rock.y = newy;
                // fprintf(stderr, "Error on line %d : %d %d\n", newx, newy, __LINE__);
                // visited[newx][newy] = 1;
                push(s, next_rock);
                explored = 0;   // We are yet to explore all neighbours of cur
                break;
            }
        }

        if(explored)
            pop(s);
    }

    if(found){
        while(!isempty_stack(*s)){
            POINT temp = pop(s);
            printf("(%d, %d), ",temp.x,temp.y);
            // printf("(%d, %d)",temp.x,temp.y);
            // if(!isempty_stack(*s))
            //     printf(", ");
        }
    }
}


signed main(){

    //Please read the comment on line 11 and line 110
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n); 

    int x[n], y[n];
    int **stable;
    stable = (int **)malloc((a+1) * sizeof(int *));
    for(int i=0; i<a; i++)
        stable[i] = (int *)malloc((b) * sizeof(int));
    
    for(int i=0; i<n; i++)
        scanf("%d", &x[i]);

    for(int i=0; i<n; i++)
        scanf("%d", &y[i]);

    for(int i=0; i<n; i++)
        stable[x[i]][y[i]] = -1;

    POINT fly, frog;
    scanf("%d %d %d %d", &frog.x, &frog.y, &fly.x, &fly.y);

    printgrid(a, b, stable);
    QUEUE *qp=(QUEUE *)malloc(sizeof(QUEUE));
    init(qp,200*200);
    STACK *s=(STACK *)malloc(sizeof(STACK));
    init_stack(s);

    if(strategy1(a, b, stable, frog, fly, qp))
        strategy2(a, b, stable, frog, fly, s);
    return 0;
}

