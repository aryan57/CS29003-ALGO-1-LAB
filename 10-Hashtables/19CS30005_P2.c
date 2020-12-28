/*
    author : Aryan Agarwal, 19CS30005
    created : 12-November-2020 14:13:39 IST
*/
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
// #include <math.h>



typedef struct _node{
    int val;
    struct _node *next;
} node;

typedef struct _hashing {
int key;
node* val;
struct _hashing *next;
} hash;

int main()
{

    FILE *f1=NULL;
    FILE *f2=NULL;

    f1=fopen("input.txt","r");
    f2=fopen("output.txt","w");
    // fscanf(f1,"%d %d",&a,&b);
    // fprintf(f2,"%d:",a);

    if(f1==NULL)printf("-1\n");
    if(f2==NULL)printf("-1\n");

    int N,Q;
	fscanf(f1,"%d",&N);
	fscanf(f1,"%d",&Q);

    // fprintf(f2,"\n%d %d",N,Q);

    hash *c2p =(hash*)malloc(N*sizeof(hash));
    hash *p2c =(hash*)malloc(N*sizeof(hash));

    hash **c2p2 =(hash**)malloc(N*N*sizeof(hash*));
    hash **p2c2 =(hash**)malloc(N*N*sizeof(hash*));

    for(int i=0;i<N;i++)
    {
        c2p[i].next=NULL;
        c2p[i].key;
        c2p[i].val=NULL;

        p2c[i].next=NULL;
        p2c[i].key;
        p2c[i].val=NULL;

        c2p2[i] =(hash*)malloc(N*sizeof(hash));
        p2c2[i] =(hash*)malloc(N*sizeof(hash));

        for(int j=0;j<N;j++)
        {
            c2p[i].next=NULL;
            c2p[i].key;
            c2p[i].val=NULL;

            p2c[i].next=NULL;
            p2c[i].key;
            p2c[i].val=NULL;
        }

    }
    
	char x;
    int c,p;
    
    int key,key2;
    hash *temp,*temp3,*preh;
    node *temp2,*temp4,*pre;
    int oknew,oknew2;
    while(Q--)
	{
		fscanf(f1," %c",&x);

        if(x=='+')
        {
            fscanf(f1," %d %d",&c,&p);

            // c2p...
            key=c%N;
            temp=c2p[key].next;

            oknew=1;

            while(temp!=NULL)
            {
                if(temp->key==c)
                {
                    oknew=0;
                    break;
                }
                temp=temp->next;
            }

            if(oknew)
            {
                hash *new_hash =(hash*)malloc(sizeof(hash));
                c2p[key].next=new_hash;
                new_hash->key=c;
                new_hash->next=NULL;

                key2=p%N;
                temp3=c2p2[key][key2].next;
                preh=temp3;

                

                while(temp3!=NULL)
                {
                    preh=temp3;
                    temp3=temp3->next;
                }

                hash *new_hash2 =(hash*)malloc(sizeof(hash));
                c2p2[key][key2].next=new_hash2;
                new_hash2->key=p;
                new_hash2->next=NULL;


            }
            else
            {
                
                key2=p%N;
                temp3=c2p2[key][key2].next;
                preh=temp3;

                

                while(temp3!=NULL)
                {
                    preh=temp3;
                    temp3=temp3->next;
                }

                hash *new_hash2 =(hash*)malloc(sizeof(hash));
                c2p2[key][key2].next=new_hash2;
                new_hash2->key=p;
                new_hash2->next=NULL;
            }

            // p2c...
            key=p%N;
            temp=p2c[key].next;

            oknew=1;

            while(temp!=NULL)
            {
                if(temp->key==p)
                {
                    oknew=0;
                    break;
                }
                temp=temp->next;
            }

            if(oknew)
            {
                hash *new_hash =(hash*)malloc(sizeof(hash));
                p2c[key].next=new_hash;
                new_hash->key=p;
                new_hash->next=NULL;

                key2=c%N;
                temp3=p2c2[key][key2].next;
                preh=temp3;

                

                while(temp3!=NULL)
                {
                    preh=temp3;
                    temp3=temp3->next;
                }

                hash *new_hash2 =(hash*)malloc(sizeof(hash));
                p2c2[key][key2].next=new_hash2;
                new_hash2->key=c;
                new_hash2->next=NULL;


            }
            else
            {
                
                key2=c%N;
                temp3=p2c2[key][key2].next;
                preh=temp3;

                

                while(temp3!=NULL)
                {
                    preh=temp3;
                    temp3=temp3->next;
                }

                hash *new_hash2 =(hash*)malloc(sizeof(hash));
                p2c2[key][key2].next=new_hash2;
                new_hash2->key=c;
                new_hash2->next=NULL;
            }
            
            
        }
        else
        {
            fscanf(f1," %d",&c);

            key=c%N;
            temp=c2p[key].next;
            preh=temp;

            oknew=1;

            while(temp!=NULL)
            {
                
                if(temp->key==c && preh!=temp)
                {
                    temp2=temp->val;
                    preh->next=temp->next;//deleting company...
                    oknew=0;
                    break;
                }
                else if(temp->key==c && preh==temp)
                {
                    temp2=temp->val;
                    c2p[key].next=temp->next;//deleting company...
                    oknew=0;
                    break;
                }
                preh=temp;
                temp=temp->next;
            }

            if(oknew==1)
            {
                fprintf(f2,"\nunavailable company cannot be delted...");
                continue;
            }

            while(temp2!=NULL)
            {
                
                key=(temp2->val)%N;
                temp3=p2c[key].next;
                preh=temp3;

                oknew=1;

                while(temp3!=NULL)
                {
                    if(temp3->key==temp2->val)
                    {
                        oknew=0;
                        break;
                    }
                    preh=temp3;
                    temp3=temp3->next;
                }

                if(oknew==1)
                {
                    fprintf(f2,"\nunavailable portfolio cannot be delted...");
                }
                else
                {
                    temp4=temp3->val;
                    pre=temp4;

                    while(temp4!=NULL)
                    {
                        if(temp4->val==c && temp3->val!=temp4)
                        {
                            pre->next=temp4->next;//deleting company...
                        
                            // break; //not breaking because the same company have multiple same portfoios
                        }
                        else if(temp4->val==c && temp3->val==temp4)
                        {
                            temp3->val=temp4->next;//deleting company...
                            
                            // break; //not breaking because the same company have multiple same portfoios
                        }
                        else pre=temp4;

                        temp4=temp4->next;
                    }

                }

                
                temp2=temp2->next;
            }
            
            

        }
        
	}


    for(int i=0;i<N;i++)
    {
        
        temp=p2c[i].next;

        if(temp==NULL)
        {
            fprintf(f2,"\np %d -1 -1",i);
            continue;
        }

        while(temp!=NULL)
        {
            temp2=temp->val;

            if(temp2==NULL)
            {
                fprintf(f2,"\np %d -1 -1",i);
                break;
            }

            while(temp2!=NULL)
            {
                fprintf(f2,"\np %d %d %d",i,temp->key,temp2->val);
                temp2=temp2->next;
            }
            temp=temp->next;
        }

    }

    for(int i=0;i<N;i++)
    {
        
        temp=c2p[i].next;

        if(temp==NULL)
        {
            fprintf(f2,"\nc %d -1 -1",i);
            continue;
        }

        while(temp!=NULL)
        {
            temp2=temp->val;

            if(temp2==NULL)
            {
                fprintf(f2,"\nc %d -1 -1",i);
                break;
            }

            while(temp2!=NULL)
            {
                fprintf(f2,"\nc %d %d %d",i,temp->key,temp2->val);
                temp2=temp2->next;
            }
            temp=temp->next;
        }

    }


    fclose(f1);
    fclose(f2);
    
    return 0;
}