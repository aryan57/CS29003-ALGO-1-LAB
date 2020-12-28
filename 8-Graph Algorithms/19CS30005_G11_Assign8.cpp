

// /*
//     author : Aryan Agarwal, 19CS30005
//     created : 29-October-2020 14:10:14 IST
// */
// #include <iostream>
// using namespace std;

// const int mxn = 1e3;
// const int INF = 1e9;
// int ans = INF;
// int grid[mxn][mxn];
// // int visited[mxn][mxn];
// int visited2[mxn][mxn];
// int visited3[mxn][mxn];
// int cntr = 0;
// bool ok;

// int N;

// struct pii
// {
//     int x, y;
// };

// bool isInside(pii z)
// {
//     return (z.x >= 0 && z.x < N && z.y >= 0 && z.y < N);
// }

// bool unEqual(pii z, pii p)
// {
//     return (z.x != p.x || z.y != p.y);
// }

// int help_X[] = {1, 0, -1, 0};
// int help_Y[] = {0, 1, 0, -1};

// // void dfs(pii pre,pii cur,pii f,int val)
// // {

// //     visited[cur.x][cur.y]=1;

// //     // cout<<"visited cell : [ "<<cur.x<<" , "<<cur.y<<" ]\n";
// //     // cout<<"val is "<<val<<"\n";

// //     val=max(val,grid[cur.x][cur.y]);

// //     if(!unEqual(cur,f))
// //     {
// //         ans=min(ans,val);
// //         return;
// //     }

// //     pii z;

// //     for(int i=0;i<4;i++)
// //     {
// //         z.x=cur.x+help_X[i];
// //         z.y=cur.y+help_Y[i];

// //         if(isInside(z))
// //         {
// //             if(grid[z.x][z.y]<ans && !visited[z.x][z.y] && unEqual(z,pre))
// //             {
// //                 dfs(cur,z,f,val);
// //             }
// //         }
// //     }

// // }

// void dfs2(pii pre, pii cur, int ans, pii f)
// {
//     cout << "(" << cur.x << ", " << cur.y << "), ";
//     visited2[cur.x][cur.y] = 1;
//     cntr++;

//     if (!unEqual(cur, f))
//         return;

//     pii z;

//     for (int i = 0; i < 4; i++)
//     {
//         z.x = cur.x + help_X[i];
//         z.y = cur.y + help_Y[i];

//         if (isInside(z))
//         {
//             if (grid[z.x][z.y] <= ans && !visited2[z.x][z.y] && unEqual(z, pre))
//             {
//                 dfs2(cur, z, ans, f);
//             }
//         }
//     }
// }

// struct que
// {
//     pii val;
//     que *next;
// };

// void createq(que **front, que **rear)
// {
//     *front = NULL;
//     *rear = NULL;
// }

// void enqueue(que **front, que **rear, pii x)
// {
//     que *ptr;
//     ptr = (que *)malloc(sizeof(que));
//     ptr->val = x;
//     ptr->next = NULL;
//     if (*rear == NULL)
//     /* Queue is empty */
//     {
//         *front = ptr;
//         *rear = ptr;
//     }
//     else
//     /* Queue is not empty */
//     {
//         (*rear)->next = ptr;
//         *rear = ptr;
//     }
// }

// pii dequeue(que **front, que **rear)
// {
//     que *old;
//     pii k;
//     if (*front == NULL)
//         /* Queue is empty */
//         printf("\n Queue is empty");
//     else if (*front == *rear)
//     /* Single element */
//     {
//         k = (*front)->val;
//         free(*front);
//         front = rear = NULL;
//         return (k);
//     }
//     else
//     {
//         k = (*front)->val;
//         old = *front;
//         *front = (*front)->next;
//         free(old);
//         return (k);
//     }
// }

// int isempty(que *front)
// {
//     if (front == NULL)
//         return (1);
//     else
//         return (0);
// }

// void dfs_check(pii cur, int limit, pii f)
// {
//     visited3[cur.x][cur.y] = 1;
//     if (!unEqual(cur, f))
//     {
//         ok = true;
//         return;
//     }

//     pii z;

//     for (int i = 0; i < 4; i++)
//     {
//         z.x = cur.x + help_X[i];
//         z.y = cur.y + help_Y[i];

//         if (isInside(z))
//         {
//             if (grid[z.x][z.y] <= limit && !visited3[z.x][z.y])
//             {
//                 dfs_check(z, limit, f);
//             }
//         }
//     }
// }

// int main()
// {

//     freopen("in2.txt", "r", stdin);
//     freopen("out.txt", "w", stdout);

//     cin >> N;

//     int maxx = 0;
//     int minn = INF;

//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             cin >> grid[i][j];
//             maxx = max(maxx, grid[i][j]);
//             minn = min(minn, grid[i][j]);
//             // visited[i][j]=0;
//             visited2[i][j] = 0;
//         }
//     }

//     pii s, f;

//     cin >> s.x >> s.y >> f.x >> f.y;
//     // ans is minimum of maximum elements in all paths from 's' to 'f'

//     // pii pre={-1,-1};
//     // dfs(pre,s,f,0);

//     // i tried a lot of times finding 'ans' using dfs but could not succeed
//     // so using simple binary search

//     int l = minn, r = maxx, m;

//     while (l <= r)
//     {

//         for (int i = 0; i < N; i++)
//         {
//             for (int j = 0; j < N; j++)
//             {
//                 visited3[i][j] = 0;
//             }
//         }

//         m = (l + r) / 2;

//         ok = false;

//         dfs_check(s, m, f);

//         if (ok)
//         {
//             r = m - 1;
//             ans = min(ans, m);
//         }
//         else
//         {
//             l = m + 1;
//         }
//     }

//     cout << "Minimum time taken is: " << ans << "\n";
//     cout << "The Path to reach from (" << s.x << "," << s.y << ") to (" << f.x << "," << f.y << ") is\n";
//     // dfs2(pre, s, ans, f);

//     que *front=NULL,*rear=NULL;
//     // createq(&front,&rear);
//     enqueue(&front,&rear,s);

//     visited2[s.x][s.y]=1;
//     pii pre = {-1, -1};

//     while (!isempty(front))
//     {
//         pii cur= dequeue(&front,&rear);
//         cout<<"("<<cur.x<<" "<<cur.y<<") ";
//         cntr++;
//         pii z;
//         for (int i = 0; i < 4; i++)
//         {
//             z.x = cur.x + help_X[i];
//             z.y = cur.y + help_Y[i];

//             if (isInside(z))
//             {
//                 if (grid[z.x][z.y] <= ans && !visited2[z.x][z.y])
//                 {
//                     enqueue(&front,&rear,z);
//                     visited2[z.x][z.y]=1;
//                 }
//             }
//         }
//     }
    

//     // we have to minimize the 'ans' not 'cntr'
//     cout << "\nThe Number of Blocks traversed are: " << cntr;

//     return 0;
// }


/*
    author : Aryan Agarwal, 19CS30005
    created : 29-October-2020 14:10:14 IST
*/
#include <iostream>
using namespace std;

const int mxn = 1e3;
const int INF = 1e9;
int ans = INF;
int grid[mxn][mxn];
// int visited[mxn][mxn];
int visited2[mxn][mxn];
int visited3[mxn][mxn];
int cntr = 0;
bool ok;

int N;

struct pii
{
    int x, y;
};

bool isInside(pii z)
{
    return (z.x >= 0 && z.x < N && z.y >= 0 && z.y < N);
}

bool unEqual(pii z, pii p)
{
    return (z.x != p.x || z.y != p.y);
}

int help_X[] = {1, 0, -1, 0};
int help_Y[] = {0, 1, 0, -1};

// void dfs(pii pre,pii cur,pii f,int val)
// {

//     visited[cur.x][cur.y]=1;

//     // cout<<"visited cell : [ "<<cur.x<<" , "<<cur.y<<" ]\n";
//     // cout<<"val is "<<val<<"\n";

//     val=max(val,grid[cur.x][cur.y]);

//     if(!unEqual(cur,f))
//     {
//         ans=min(ans,val);
//         return;
//     }

//     pii z;

//     for(int i=0;i<4;i++)
//     {
//         z.x=cur.x+help_X[i];
//         z.y=cur.y+help_Y[i];

//         if(isInside(z))
//         {
//             if(grid[z.x][z.y]<ans && !visited[z.x][z.y] && unEqual(z,pre))
//             {
//                 dfs(cur,z,f,val);
//             }
//         }
//     }

// }

void dfs2(pii pre, pii cur, int ans, pii f)
{
    cout << "(" << cur.x << ", " << cur.y << "), ";
    visited2[cur.x][cur.y] = 1;
    cntr++;

    if (!unEqual(cur, f))
        return;

    pii z;

    // bool bb=false;
    for (int i = 0; i < 4; i++)
    {
        z.x = cur.x + help_X[i];
        z.y = cur.y + help_Y[i];

        if (isInside(z))
        {
            if (grid[z.x][z.y] <= ans && !visited2[z.x][z.y] && unEqual(z, pre))
            {
                dfs2(cur, z, ans, f);
                // bb = true;
            }
        }
    }

    // if(!bb)
    // {
    //     dfs2(cur,pre,ans,f);
    // }
}
// int que[mxn];
// int ind,j,_f,_r=-1;
// void bfs(pii cur,pii f,pii pre)
// {
//     for (int ind = 1; ind <= N; ind++)
//     {
//         pii z;
//         for (int j = 0; j < 4; j++)
//         {
//             z.x = cur.x + help_X[j];
//             z.y = cur.y + help_Y[j];

//             if (isInside(z))
//             {
//                 if (grid[z.x][z.y] <= ans && !visited2[z.x][z.y] && unEqual(z, pre))
//                 {
//                     que[++_r] = ind;
//                 }
//             }
//         }
//     }
            
//     if (f <= r)
//     {
//         visited[q[f]] = 1;
//         bfs(q[f++]);
//     }
// }

void dfs_check(pii cur, int limit, pii f)
{
    visited3[cur.x][cur.y] = 1;
    if (!unEqual(cur, f))
    {
        ok = true;
        return;
    }

    pii z;

    for (int i = 0; i < 4; i++)
    {
        z.x = cur.x + help_X[i];
        z.y = cur.y + help_Y[i];

        if (isInside(z))
        {
            if (grid[z.x][z.y] <= limit && !visited3[z.x][z.y])
            {
                dfs_check(z, limit, f);
            }
        }
    }
}

int main()
{

    freopen("in2.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cin >> N;

    int maxx = 0;
    int minn = INF;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
            maxx = max(maxx, grid[i][j]);
            minn = min(minn, grid[i][j]);
            // visited[i][j]=0;
            visited2[i][j] = 0;
        }
    }

    pii s, f;

    cin >> s.x >> s.y >> f.x >> f.y;
    // ans is minimum of maximum elements in all paths from 's' to 'f'

    // pii pre={-1,-1};
    // dfs(pre,s,f,0);

    // i tried a lot of times finding 'ans' using dfs but could not succeed
    // so using simple binary search

    int l = minn, r = maxx, m;

    while (l <= r)
    {

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                visited3[i][j] = 0;
            }
        }

        m = (l + r) / 2;

        ok = false;

        dfs_check(s, m, f);

        if (ok)
        {
            r = m - 1;
            ans = min(ans, m);
        }
        else
        {
            l = m + 1;
        }
    }

    cout << "Minimum time taken is: " << ans << "\n";
    cout << "The Path to reach from (" << s.x << "," << s.y << ") to (" << f.x << "," << f.y << ") is\n";
    pii pre = {-1, -1};
    dfs2(pre, s, ans, f);

    // we have to minimize the 'ans' not 'cntr'
    cout << "\nThe Number of Blocks traversed are: " << cntr;

    return 0;
}