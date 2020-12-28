/*
    author : Aryan Agarwal, 19CS30005
    created : 22-October-2020 13:52:06 IST
*/
#include <iostream>
using namespace std;
// #define watch(x) cout<<#x<<" is "<<x<<"\n"

struct node
{
    int rank;
    int x;
    int y;
    node *parent;
};

node* make_set(int v,int n)
{
    node* new_node=(node*)malloc(sizeof(node));

    new_node->rank=0;
    new_node->x=v/n;
    new_node->y=v%n;
    new_node->parent=new_node;

    return new_node;
}

node* find_set(node* x)
{
    node* root=x;

    while (root->parent!=root)
    {
        root=root->parent;
    }

    // doing path compression
    node* temp=x;
    node* z=NULL;

    while (temp->parent!=temp)
    {
        z=temp;
        temp=temp->parent;
        z->parent=root;
    }
    
    return root;

}

void merge_set(node* a,node* b) // it is assumed that 'a' and 'b' are distinct parent pointers
{
    
    if(a->rank<b->rank)
    {
        a->parent=b;
        b->rank+=a->rank;
    }
    else if (a->rank>b->rank)
    {
        b->parent=a;
        a->rank+=b->rank;
    }
    
    else
    {
        b->parent=a;
        a->rank+=1;
    }
       
    
}

void print_grid(bool H[],bool V[],int m,int n)
{
    cout<<"+   ";
    for(int j=0;j<n-1;++j)cout<<"+---";
    cout<<"+\n";
    
    for(int i=0;i<m;++i)
    {
        cout<<"|";
        for(int j=0;j<n-1;j++)
        {
            if(V[(n-1)*i+j])cout<<"   |";
            else cout<<"    ";
        }
        if(i<m-1)cout<<"   |";
        else cout<<"   ";

        cout<<"\n";

        if(i<m-1)
        {
            cout<<"+";
            for(int j=0;j<n;j++)
            {
                if(H[n*i+j])cout<<"---+";
                else cout<<"   +";
            }
            cout<<"\n";
        }
        else
        {
            cout<<"+";
            for(int j=0;j<n;j++)
            {
                
                cout<<"---+";
            }
            cout<<"\n";
        }
        
    }
}

void find_treasure(node** C,bool H[],bool V[],int m,int n)
{
    int cnt=0;
    int ind,i,j;
    node *x,*y,*root_x,*root_y;

    bool* H1=(bool*)malloc((m-1)*n*sizeof(bool));
    bool* V1=(bool*)malloc((n-1)*m*sizeof(bool));

    for(int i=0;i<(m-1)*n;i++)H1[i]=true;
    for(int i=0;i<(n-1)*m;i++)V1[i]=true;

    int temp=0;

    while(find_set(C[0])->rank!=m*n-1 && cnt<=m*n-1)
    {
        
        // selecting a random index from 0 to (m-1)*n-1 for Horizantal walls
        ind=rand()%((m-1)*n);

        while (!H1[ind] && ind<(m-1)*n-1)
        {
            ind++;
        }
        while (!H1[ind] && ind>0)
        {
            ind--;
        }
        
        if(H1[ind])
        {

            x=C[ind];
            y=C[ind+n];

            root_x=find_set(x);
            root_y=find_set(y);
            // cout<<root_x->x<<" "<<root_x->y<<"\n";
            // cout<<root_y->x<<" "<<root_y->y<<"\n";
            // cout<<"**\n";

            if(root_x!=root_y)
            {
                // cout<<root_x->x<<" "<<root_x->y<<"\n";
                // cout<<root_y->x<<" "<<root_y->y<<"\n";
                merge_set(root_x,root_y);
                // cout<<find_set(root_x)->x<<" "<<find_set(root_x)->y<<"\n";
                // cout<<find_set(root_y)->x<<" "<<find_set(root_y)->y<<"\n";
                // cout<<"**\n";
                H[ind]=false;
                cnt++;
            }
            H1[ind]=false;
        }

        // selecting a random index from 0 to (n-1)*m-1 for Vetical walls
        ind=rand()%((n-1)*m);
        i=ind/(n-1);
        j=ind%(n-1);

        ind=n*i+j;
        
        while (!V1[ind] && ind<(n-1)*m-1)
        {
            ind++;
        }
        while (!V1[ind] && ind>0)
        {
            ind--;
        }

        if(V1[ind])
        {

            x=C[ind];
            y=C[ind+1];

            root_x=find_set(x);
            root_y=find_set(y);

            if(root_x!=root_y)
            {
                merge_set(root_x,root_y);
                V[ind]=false;
                cnt++;
            }
            V1[ind]=false;
        }

        temp++;
        if(temp>2e5)break;
        
    }

    
    // for(int i=0;i<m*n;i++)
    // {
    //     node* zz=C[i];
    //     while(zz->parent!=zz)
    //     {
    //         cout<<zz->x<<" "<<zz->y<<"\n";
    //         zz=zz->parent;
    //     }
    //     cout<<"**\n";

    // }



    if(find_set(C[0])==find_set(C[m*n-1]))
    {
        cout<<"\nsource and destination are connected...\n";
    }
    else
    {
        cout<<"\nsource and destination are not connected...\n";
    }

}


int main(int argc, char** argv)
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    srand((unsigned int)time(NULL));

    int m,n;

    if(argc==3)
    {
        m=(int)(argv[1][0]-'0');
        n=(int)(argv[2][0]-'0');
    }
    else
    {
        m=n=10;
        // m=n=4;
    }

    // m = #rows
    // n = #columns

    bool* H=(bool*)malloc((m-1)*n*sizeof(bool));
    bool* V=(bool*)malloc((n-1)*m*sizeof(bool));

    for(int i=0;i<(m-1)*n;i++)H[i]=true; // meaning, they are eligible for removal
    for(int i=0;i<(n-1)*m;i++)V[i]=true; // meaning, they are eligible for removal


    node** C=(node**)malloc(m*n*sizeof(node*));

    for(int i=0;i<m*n;i++)
    {
        C[i]=(node*)malloc(1*sizeof(node));
    }

    for(int i=0;i<m*n;i++)
    {
        C[i]=make_set(i,n);
    }

    // (considering 0 based indexing)

    // C[i] is the address of cell at (i/n)th row and (i%n)th column 
    // H[i] is the horizontal wall just below of cell at (i/n)th row and (i%n)th column 
    // V[i] is the vertical wall just right of cell at (i/(n-1))th row and (i%(n-1))th column

    // there is no point in removing horizontal walls just below of cells at (m-1)th row
    // there is no point in removing vertical walls just right of cells at (n-1)th row

    cout<<"\nInitial grid\n";
    print_grid(H,V,m,n);
    find_treasure(C,H,V,m,n);
    cout<<"\n\nFinal grid\n";
    print_grid(H,V,m,n);

    return 0;
}