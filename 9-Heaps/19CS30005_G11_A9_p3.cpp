/*
    author : Aryan Agarwal, 19CS30005
    created : 05-November-2020 14:00:25 IST
*/
#include <iostream>
using namespace std;

#define MAX_SIZE 100
#define mxn 100000

struct job
{
    int jobId;
    int startTime;
    int jobLength;
    int remLength;
};

struct jobpair
{
    int jobid_from;
    int jobid_to;
};

struct heap
{
    job list[MAX_SIZE];
    int numJobs;
};

void initHeap(heap *H)
{
    H->numJobs=0;
}

void insertJob(heap *H, job j)
{
    H->numJobs=H->numJobs+1;
    H->list[H->numJobs].jobId=j.jobId;
    H->list[H->numJobs].jobLength=j.jobLength;
    H->list[H->numJobs].startTime=j.startTime;
    H->list[H->numJobs].remLength=j.remLength;

    if(H->numJobs==1)return;
    // cout<<"(( "<<j.jobId<<" " << H->numJobs<<"))\n";


    int par=H->numJobs/2;
    int child=H->numJobs;
    
    while(H->list[par].remLength > H->list[child].remLength)
    {
        // swap(H->list[par],H->list[child]);

        job temp;
        temp.jobId=H->list[par].jobId;
        temp.jobLength=H->list[par].jobLength;
        temp.startTime=H->list[par].startTime;
        temp.remLength=H->list[par].remLength;

        H->list[par].jobId=H->list[child].jobId;
        H->list[par].jobLength=H->list[child].jobLength;
        H->list[par].startTime=H->list[child].startTime;
        H->list[par].remLength=H->list[child].remLength;

        H->list[child].jobId=temp.jobId;
        H->list[child].jobLength=temp.jobLength;
        H->list[child].startTime=temp.startTime;
        H->list[child].remLength=temp.remLength;


        par/=2;
        child/=2;
    }
}

void heapify(heap *H,int ind)
{
    int l = 2*ind;
    int r = 2*ind +1;
    int p=ind;

    int mx_ind = p;
    if(l<=H->numJobs)if(H->list[mx_ind].remLength > H->list[l].remLength){mx_ind=l;}
    if(r<=H->numJobs)if(H->list[mx_ind].remLength > H->list[r].remLength){mx_ind=r;}

    if(mx_ind==p)
    {
        return;
    }
    else
    {
        // swap(H->list[p],H->list[mx_ind]);

        job temp;
        temp.jobId=H->list[p].jobId;
        temp.jobLength=H->list[p].jobLength;
        temp.startTime=H->list[p].startTime;
        temp.remLength=H->list[p].remLength;

        H->list[p].jobId=H->list[mx_ind].jobId;
        H->list[p].jobLength=H->list[mx_ind].jobLength;
        H->list[p].startTime=H->list[mx_ind].startTime;
        H->list[p].remLength=H->list[mx_ind].remLength;

        H->list[mx_ind].jobId=temp.jobId;
        H->list[mx_ind].jobLength=temp.jobLength;
        H->list[mx_ind].startTime=temp.startTime;
        H->list[mx_ind].remLength=temp.remLength;

        heapify(H,mx_ind);
        return;
    }
        
}

int extractMinJob(heap *H, job *j)
{
    if(H->numJobs==0)return -1;

    j->jobId=H->list[1].jobId;
    j->jobLength=H->list[1].jobLength;
    j->startTime=H->list[1].startTime;
    j->remLength=H->list[1].remLength;

    // swap(H->list[1],H->list[H->numJobs]);
    
    job temp;
    temp.jobId=H->list[1].jobId;
    temp.jobLength=H->list[1].jobLength;
    temp.startTime=H->list[1].startTime;
    temp.remLength=H->list[1].remLength;

    H->list[1].jobId=H->list[H->numJobs].jobId;
    H->list[1].jobLength=H->list[H->numJobs].jobLength;
    H->list[1].startTime=H->list[H->numJobs].startTime;
    H->list[1].remLength=H->list[H->numJobs].remLength;

    H->list[H->numJobs].jobId=temp.jobId;
    H->list[H->numJobs].jobLength=temp.jobLength;
    H->list[H->numJobs].startTime=temp.startTime;
    H->list[H->numJobs].remLength=temp.remLength;

    H->numJobs--;
    heapify(H,1);
    return 1;

}

void decrease_key(heap *H,int jid)
{
    H->list[jid/2].remLength/=2;
}

void new_scheduler(job jobList[], int n,jobpair pairlist[],int m)
{
    int T=0;

    for(int i=0;i<n;i++)
    {
        T+=jobList[i].jobLength;
    }

    int _time[T+1]={};
    

    for(int i=0;i<n;i++)
    {
        _time[jobList[i].startTime]++;
    }
    
    for(int i=T;i>=1;i--)
    {
        _time[i]=_time[i-1];
    }
    _time[0]=0;
    for(int i=1;i<=T;i++)
    {
        _time[i]+= _time[i-1];
    }

    job* new_list = (job*)malloc(n*sizeof(job));

    for(int i=0;i<n;i++)
    {
        new_list[_time[jobList[i].startTime]]=jobList[i];
        _time[jobList[i].startTime]++;
    }

    // for(int i=0;i<n;i++)cout<<new_list[i].jobId<<" ";cout<<"\n";

    cout<<"Jobs scheduled at each timestep are: \n";

    heap H;
    initHeap(&H);

    for(int i=0;i<=T;i++)
    {
        _time[i]=0;
    }
    for(int i=0;i<n;i++)
    {
        _time[jobList[i].startTime]++;
    }

    int ind=0;
    for(int t=0;t<=T;t++)
    {
        job temp;

        if(_time[t]==0)
        {
            if(extractMinJob(&H,&temp)==-1)
            {
                cout<<"-1 ";
            }
            else
            {
                cout<<temp.jobId<<" ";
                temp.remLength--;
                if(temp.remLength>0)insertJob(&H,temp);
            }
            
        }
        else
        {
            if(extractMinJob(&H,&temp)==-1)
            {
                cout<<new_list[ind].jobId<<" ";
                new_list[ind].remLength--;
                if(new_list[ind].remLength>0)insertJob(&H,new_list[ind]);
                ind++;
                _time[t]--;
                
            }

            else
            {
                if(temp.remLength<new_list[ind].remLength)
                {
                    cout<<temp.jobId<<" ";
                    temp.remLength--;
                    if(temp.remLength>0)
                    {
                        // if(t==2)cout<<temp.jobId<<" && "<<temp.remLength;
                        insertJob(&H,temp);}
                        // if(t==2){cout<<"^^\n";for(int j=1;j<=4;j++)cout<<"("<<H.list[j].jobId<<" , "<<H.list[j].remLength<<") ";cout<<"\n";}
                }

                else if(temp.remLength==new_list[ind].remLength)
                {
                    if(temp.jobId<new_list[ind].jobId)
                    {
                        cout<<temp.jobId<<" ";
                        temp.remLength--;
                        if(temp.remLength>0)insertJob(&H,temp);
                    }
                    else
                    {
                        cout<<new_list[ind].jobId<<" ";
                        new_list[ind].remLength--;
                        if(new_list[ind].remLength>0)insertJob(&H,new_list[ind]);
                        insertJob(&H,temp);
                        ind++;
                        _time[t]--;
                    }
                }

                else
                {
                    cout<<new_list[ind].jobId<<" ";
                    new_list[ind].remLength--;
                    if(new_list[ind].remLength>0)insertJob(&H,new_list[ind]);
                    insertJob(&H,temp);
                    ind++;
                    _time[t]--;
                }
            }

            
            while (_time[t]--)
            {
                // cout<<new_list[ind].jobId<<"**\n";
                insertJob(&H,new_list[ind]);
                ind++;
            }
            
        }

        
        // if(t==2){cout<<"\n";for(int j=1;j<=4;j++)cout<<"("<<H.list[j].jobId<<" , "<<H.list[j].remLength<<") ";cout<<"\n";}
    }




}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    
    int n;
    cout<<"Enter no. of jobs (n): ";
    cin>>n;

    job* arr = (job*)malloc(n*sizeof(job));
    
    for(int i=0;i<n;i++)
    {
        cin>>arr[i].jobId>>arr[i].startTime>>arr[i].jobLength;
        arr[i].remLength=arr[i].jobLength;
    }

    cout<<"Enter the number of dependency pairs ";
    int m;
    cin>>m;

    cout<<"Enter the dependency pairs\n";

    jobpair* jpi = (*jobpair)malloc(m*sizeof(jobpair));

    for(int i=0;i<m;i++)
    {
        cin>>jpi[i].jobid_from>>jpi[i].jobid_to;
    }

    new_scheduler(arr,n,jpi,m);
    
    return 0;
}