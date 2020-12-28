/*
    author : Aryan Agarwal, 19CS30005
    created : 08-October-2020 16:03:20 IST
*/
#include <iostream>
using namespace std;

struct pdi // pair of double and integer
{
    double val=0.0;
    int rem;
};

int main()
{
    freopen("input3.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n,c;
    cin>>n>>c;

    double e[n+1][c+1];

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=c;j++)
        {
            cin>>e[i][j];
        }
    }

    
    pdi dp[n+1][c+1];

    // base case
    for(int i=1;i<=c;i++)
    {
        dp[1][i].val=e[1][i];
        dp[1][i].rem=c-i;
    }

    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=c;j++)
        {
            int rem =dp[i-1][j].rem;

            
            for(int k=1;k<=c;k++)
            {
                if(i==n && rem-k>=0)if(dp[i][k].val<dp[i-1][j].val*e[i][k])
                {
                    dp[i][k].val=dp[i-1][j].val*e[i][k];
                    dp[i][k].rem=rem-k;

                }

                if(i!=n && rem-k>0)if(dp[i][k].val<dp[i-1][j].val*e[i][k])
                {
                    dp[i][k].val=dp[i-1][j].val*e[i][k];
                    dp[i][k].rem=rem-k;

                }
            }

            
            
        }

        // for(int k=1;k<=c;k++)
        // {
        //     cout<<i<<" "<<k<<"\n";
        //     cout<<dp[i][k].val<<" "<<dp[i][k].rem<<"\n";
        // }

        
    }

    double mx=-1.0;

    for(int j=1;j<=c;j++)
    {
        if(dp[n][j].rem==0)
        {
            mx=max(mx,dp[n][j].val);
        }
    }

    cout<<mx<<"\n";

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=c;j++)
        {
            long long int a = 1e6;
            long long int b = 1e12;

            a*=e[i][j];
            b*=mx;

            // cout<<a<<" "<<b<<" \n";
            
            if(b%a==0)
            {
                cout<<"reaction "<<i<<" : "<<j<<"\n";
                break;
            }
        }
    }
    
    return 0;
}




// approach 2
/*
//     author : Aryan Agarwal, 19CS30005
//     created : 08-October-2020 15:48:12 IST
// */
// #include <iostream>
// using namespace std;

// int main()
// {
//     freopen("input.txt","r",stdin);
//     freopen("output.txt","w",stdout);

//     int n,c;
//     cin>>n>>c;

//     double e[n][c];

//     for(int i=0;i<n;i++)
//     {
//         for(int j=0;j<c;j++)
//         {
//             cin>>e[i][j];
//         }
//     }

//     int dp[n];
//     int rem=c;

//     int pww=1;

//     for(int i=0;i<n;i++)
//     {
//         dp[i]=0;
//         rem-=1;
//         pww*=2;
//     }
    
//     for(int j=1;j<c;j++)
//     {
        
        
//         for(int num=0;num<pww;num++)
//         {
//             double pro=1.0;
//             int tt=0;
//             for(int bit=0;bit<n;bit++)
//             {
//                 if((num>>bit)&1)
//                 {
//                     pww*=e[bit][j];
//                     pww/=e[bit][dp[bit]];
//                     tt+=j-dp[bit];
//                 }

//             }

//             int zz=rem-tt;

//             if(zz<0)
//             {
                
//             }




//         }

//     }

//     return 0;
// }


// approach 3
// /*
//     author : Aryan Agarwal, 19CS30005
//     created : 08-October-2020 14:10:43 IST
// */
// #include <iostream>
// using namespace std;

// struct pdi // pair of double and integer
// {
//     double val;
//     int ind;
// };


// int main()
// {
//     freopen("input2.txt","r",stdin);
//     freopen("output.txt","w",stdout);

//     int n,c;
//     cin>>n>>c;

//     double e[n+1][c+1];

//     for(int i=1;i<=n;i++)
//     {
//         for(int j=1;j<=c;j++)
//         {
//             cin>>e[i][j];
//         }
//     }

//     double dp[n+1][c+1];
    
    
//     pdi temp[n+1];
//     int reaction[n+1];

//     // '1' based indexation is used

//     /* dp[i][j] is the maximum probability of success
//        if i reactions happen and j catalysts are used
//     */

//     /* here i have used the fact that all the probabilities of a reaction are in non-decreasing order,
//        so dp[i][j] will simply be the product of largest (j%i) probabilities at  (j/i+1)th column
//        and remaining 'n-j%i' probabilities at  (j/i)th column
//     */

//     /* dp[i][j] is -1 if no. of catalysts are less than no. of no. of reactions*/
    
//     for(int i=0;i<=n;i++)
//     {
//         for(int j=0;j<=c;j++)
//         {
//             // base case
//             if(i==0 || j==0)
//             {
//                 dp[i][j]=0.0;
//                 continue;
//             }
            
//             if(i>j) // no. of catalysts are less than no. of no. of reactions
//             {
//                 dp[i][j]=-1.0;
//                 continue;
//             }  
                    
//             // initialise dp[i][j] with 1 
//             dp[i][j]=1.0;
            

//             // since i have started the index from '1' instead of '0'
//             // i have to initialise the dummy variable temp[0]
//             temp[0].ind=0;
//             temp[0].val=-1.0;

//             // firstly, multiply dp[i][j] with elements at (j/i)th column
//             for(int k=1;k<=n;k++)
//             {
//                 dp[i][j]*=e[k][j/i];
//                 reaction[k]=j/i;

//                 temp[k].ind=k;
//                 if(j/i+1<=c)temp[k].val=e[k][j/i+1]/e[k][j/i];
//                 else temp[k].val=-1.0;
//             }

                
//             // simple O(n^2) bubble sort
//             // in non-increasing order
//             for (int x = 0; x < n; x++)
//             {
//                 for (int y = 0; y < n-x; y++)
//                 {
//                     if (temp[j].val < temp[j+1].val) //swap them
//                     {
//                         pdi z = temp[j];
//                         temp[j]=temp[j+1];
//                         temp[j+1]=z;
//                     } 
//                 }
//             }

//             // secondly, multiply dp[i][j] with remaining largest elements at (j/i + 1)th column
//             for(int k=1;k<=j%i;k++)
//             {
//                 dp[i][j]*=temp[k].val;
//                 reaction[temp[k].ind]=j/i+1;
//             }
            
//         }
//     }


//     cout<<dp[n][c]<<"\n";
//     for(int i=1;i<=n;i++)
//     {
//         cout<<"reaction "<<i<<" : "<<reaction[i]<<"\n";
//     }
    
    
//     return 0;
// }