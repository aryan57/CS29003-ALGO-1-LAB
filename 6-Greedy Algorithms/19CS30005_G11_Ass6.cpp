/*
    THIS WAS MY SECOND ATTEMPT, IT IS CORRECT
    EVALUATE THIS
    author : Aryan Agarwal, 19CS30005
    created : 15-October-2020 15:02:22 IST
*/

#include <iostream>
#include <fstream> 
using namespace std;

struct pii
{
    int a;
    int b;
    int ind; // means index
};

/* n is very small 2<=n<=8
 calculating all the n! permutations and checking each will not do any harm
 time length [0,1440*60] is large , but i have used binary search there, so it should not be any problem
*/

/* if we sort the all the starting time then solve, it will be wrong sometimes
   so i am checking all n! permutations
*/

/* since we are not allowed to use STL,i cannot use 

    do{
        ....
    }while(next_permuation(v.begin(),v.end()));

    Therefore, I calculated all permutations of the 'temp' array using Heap's Algorithm
    It basically moves the element at pivot position to all the positions
    And the pivot to all the positions also.

*/

void schedule_visits(int temp[], int x, int y,pii arr[],int n,int ans_arr[],int *ans_num)  
{
    int z;
    
    if (x != y)for (int pos = x; pos <= y; pos++)  
    {
        // swap
        z=temp[x];
        temp[x]=temp[pos];
        temp[pos]=z; 

        schedule_visits(temp, x+1, y,arr,n,ans_arr,ans_num);  // now the pivot position is changed to 'x+1'

        // swap back
        z=temp[pos];
        temp[pos]=temp[x];
        temp[x]=z;   
    }



    int l=0,r=1440*60;
    int mid,min_diff,cur;
    bool ok;

    /* binary searching the answer
       and
       greedily checking each instance if it is possible or not
    */

    while(l<=r)
    {
        // mid is the smallest possible gap possible in the current instance
        // my 'mid' vaiable is sir's 'L' variable according to Hint-2
        mid=(l+r)/2;

        min_diff=1e9; // acts as infinity

        ok = true;

        // the first person in the current permutation will visit first
        cur=arr[temp[0]].a;

        //loop starting from second person
        for(int i=1;i<n;i++)
        {
            if(cur+mid<arr[temp[i]].a)
            {
                min_diff=min(min_diff,arr[temp[i]].a-cur);
                cur=arr[temp[i]].a;
            }
            else if (cur+mid<=arr[temp[i]].b)
            {
                min_diff=min(min_diff,cur+mid-cur);
                cur=cur+mid;
            }
            else
            {
                ok = false;
                break;
            }
        }

        if(!ok)
        {
            r=mid-1;
        }
        else
        {
            l=mid+1;
            if(*ans_num<min_diff)
            {
                *ans_num=min_diff;
                for(int i=0;i<n;i++)
                {
                    ans_arr[i]=temp[i];
                }
            }
        }

    }

}

int main()
{

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    FILE *f1;
    FILE *f2=NULL;

    f1=fopen("in.txt","r");
    f2=fopen("out.txt","w");

    if(f2==NULL)cout<<"-1"<<endl;


    int n;
    fscanf(f1,"%d",&n);

    pii arr[n];
    int temp[n]; //it basically stores indexes 0,1,...,n-1

    for(int i=0;i<n;i++)
    {
        // cin>>arr[i].a>>arr[i].b;
        fscanf(f1,"%d %d",&arr[i].a,&arr[i].b);
        arr[i].a*=60; // convert in sec
        arr[i].b*=60; // convert in sec
        arr[i].ind=temp[i]=i;
    }

    int ans_arr[n];
    int ans_num=0;
    
    schedule_visits(temp,0,n-1,arr,n,ans_arr,&ans_num);

    // cout<<ans_num/60<<":";
    // ans_num%60<10?cout<<"0"<<ans_num%60:cout<<ans_num%60; // i want to print 4:00 and not 4:0
    // cout<<"\n";

    fprintf(f2,"%d:",ans_num/60);
    
    ans_num%60<10?fprintf(f2,"0%d",ans_num%60):fprintf(f2,"%d",ans_num%60); // i want to print 4:00 and not 4:0
    fprintf(f2,"\n");

    for(int i=0;i<n;i++)
    {
        // cout<<ans_arr[i]<<" ";
        fprintf(f2,"%d ",ans_arr[i]);
    }

    fclose(f1);
    fclose(f2);
    
    return 0;
}







// /*
//     THIS WAS MY FIRST ATTEMPT, USING SORTING , WHICH TURNED OUT TO BE WRONG
//     PLEASE DO NOT EVALUATE THIS
//     author : Aryan Agarwal, 19CS30005
//     created : 15-October-2020 13:38:28 IST
// */
// #include <iostream>
// using namespace std;

// const int mXn = 1440;

// struct pii
// {
//     int a;
//     int b;
//     int ind;
// };

// void merge_main(pii arr[], int start, int mid, int end,int len)
// {
// 	pii temp[len];

// 	int i = start, j = mid+1, k = 0;

// 	// copying of elements to temp
//     while(i <= mid && j <= end)
//     {
// 		// sort the time slots in incresing order of arrival time
//         // if the arrival time is equal, sort them in increasing order of leaving time 
//         if(arr[i].a < arr[j].a || (arr[i].a == arr[j].a && arr[i].b<=arr[j].b))
//         {
// 			temp[k] = arr[i];
// 			++k;++i;
// 		}
// 		else
//         {
// 			temp[k] = arr[j];
// 			++k;++j;
// 		}
// 	}

//     // copying of elements to temp
//     for(;i<=mid;++i,++k)temp[k] = arr[i];

//     // copying of elements to temp
// 	for(;j<=end;++j,++k)temp[k] = arr[j];

//     // final copying of elements to 'arr'
// 	for(i=start; i <= end; ++i)arr[i]=temp[i-start];


// }


// void merge_sort(pii arr[], int x, int y)
// {
//     if(x >= y)
//     {
// 		return;
// 	}
//     else
//     {
//         merge_sort(arr, x, (x + y)/2);
// 		merge_sort(arr, (x + y)/2+1, y);
// 		merge_main(arr, x, (x + y)/2, y,y-x+1);
//     }
    
// }

// void schedule_visits(pii arr[],int n)
// {
//     merge_sort(arr,0,n-1);
//     int ans = 0;

//     int l=0,r=mXn*60;
//     int mid,min_diff,cur;
//     bool ok;

//     // binary searching the answer and greedily checking each instance if it is possible or not
//     while(l<=r)
//     {
//         // mid is the smallest possible gap possible in the current instance
//         mid=(l+r)/2; // my 'mid' vaiable is sir's 'L' variable according to Hint-2

//         min_diff=1e9; // acts as infinity

        
//         ok = true;

//         // the first person in the sorted list will visit at arr[0].a seconds
//         cur=arr[0].a;

//         // starting from second person
//         for(int i=1;i<n;i++)
//         {
//             if(cur+mid<arr[i].a)
//             {
//                 min_diff=min(min_diff,arr[i].a-cur);
//                 cur=arr[i].a;
//             }
//             else if (cur+mid<=arr[i].b)
//             {
//                 min_diff=min(min_diff,cur+mid-cur);
//                 cur=cur+mid;
//             }
//             else
//             {
//                 ok = false;
//                 break;
//             }
//         }

//         if(!ok)
//         {
//             r=mid-1;
//         }
//         else
//         {
//             l=mid+1;
//             ans=max(ans,min_diff);
//         }

//     }


//     cout<<ans/60<<":";
//     ans%60<10?cout<<"0"<<ans%60:cout<<ans%60;
//     cout<<"\n";

//     for(int i=0;i<n;i++)
//     {
//         cout<<arr[i].ind<<" ";
//     }
//     cout<<"\n";

// }


// int main()
// {
//     freopen("inp.txt","r",stdin);
//     freopen("out.txt","w",stdout);

//     int n;
//     cin>>n;

//     pii arr[n];

//     for(int i=0;i<n;i++)
//     {
//         cin>>arr[i].a>>arr[i].b;
//         arr[i].a*=60; // convert in sec
//         arr[i].b*=60; // convert in sec
//         arr[i].ind=i;
//     }

//     schedule_visits(arr,n);

//     return 0;
// }