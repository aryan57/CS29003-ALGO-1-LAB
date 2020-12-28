/*
    author : Aryan Agarwal, 19CS30005
    created : 01-October-2020 13:51:18 IST
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//  i have assumed maximum length of a word is mXn
const int mXn = 200;

struct node
{
    int frequency;
    char symbol[mXn];
    node* left;
    node* right;
    node* next;
};

int sid=1;

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

char ans[36][mXn*mXn];

// void preorder(node* cur,char *s)
// {
//     if(cur==NULL)return;
//     cout<<cur->symbol<<"("<<cur->frequency<<"), ";
//     if(cur->symbol[0]!='N')
//     {
//         if(cur->symbol[0]>='0' && cur->symbol[0]<='9')strcpy(ans[cur->symbol+26],*s);
//     }
//     preorder(cur->left,strcat(s,"0"));
//     preorder(cur->right,strcat(s,"1"));
// }

void preorder1(node* cur)
{
    if(cur==NULL)return;
    cout<<cur->symbol<<"("<<cur->frequency<<"), ";
    preorder1(cur->left);
    preorder1(cur->right);
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    cin>>n;

    char s[mXn+1];
    int freq[36]={}; // 0-25 for a..z and 26-35 for 0..9

    for(int i=0;i<n;i++)
    {
        cin>>s;
        int l = strlen(s);

        for(int j=0;j<l;j++)
        {
            if(s[j]>='a' && s[j]<='z')freq[s[j]-'a']++;
            if(s[j]>='0' && s[j]<='0')freq[s[j]-'0'+26]++;
        }
    }

    for(int i=0;i<26;i++)
    {
        char c='a'+i;
        cout<<c<<"="<<freq[i]<<", ";
    }
    cout<<"\n";
    for(int i=26;i<36;i++)
    {
        cout<<i-26<<"="<<freq[i]<<", ";
    }


    node* x = (node*)malloc(sizeof(node));
    x->frequency=freq[0];
    strcpy(x->symbol,"a");
    x->left=x->right=x->next=NULL;

    node* first=x;

    for(int i=1;i<36;i++)
    {
        

        char sym;
        if(i<26)sym = i+'a';
        else sym = i-26+'0';

        if(freq[i]< first->frequency)
        {

            node* new_node = (node*)malloc(sizeof(node));
            new_node->next=first;
            new_node->frequency=freq[i];
            new_node->symbol[0]=sym;
            new_node->symbol[1]='\0';
            new_node->left=new_node->right=NULL;
            first=new_node;

            continue;
        }

        node* temp = first;
        while(true)
        {
            if(temp->next==NULL)break;
            if(freq[i]>=temp->next->frequency){temp=temp->next;continue;}
            break;
            
        }
        node* new_node = (node*)malloc(sizeof(node));
        new_node->next=temp->next;
        new_node->frequency=freq[i];
        new_node->symbol[0]=sym;
        new_node->symbol[1]='\0';
        new_node->left=new_node->right=NULL;
        temp->next=new_node;

    }
    while(true)
    {
        // t++;
        
        node* new_node = (node*)malloc(sizeof(node));
        new_node->frequency=first->frequency+first->next->frequency;
        strcpy(new_node->symbol,"N");

        char tt[200];
        tostring(tt,sid);

        strcat(new_node->symbol,tt);

       
        sid++;
        new_node->symbol[2]='\0';
        new_node->left=first;
        new_node->right=first->next;

        first=(first->next)->next;

        if(first==NULL)
        {
            // cout<<"\ncase1";
            new_node->next=NULL;
            first=new_node;
            break;
        }

        if(new_node->frequency < first->frequency)
        {
            // cout<<"\ncase2";
            new_node->next=first;
            first=new_node;
            continue;
        }

        if((new_node->frequency==first->frequency) && first->symbol[0]!='N')
        {
            // cout<<"\ncase3";
            new_node->next=first;
            first=new_node;
            continue;
        }

        node* temp = first;
        // cout<<"\ncase4";

        while (true)
        {
            if(temp->next==NULL)break;
            if(temp->next->frequency<new_node->frequency){temp=temp->next;continue;}

            if(temp->next->frequency>new_node->frequency){break;}

            if(temp->next->frequency==new_node->frequency)
            {
                while (true)
                {
                    if(temp->next==NULL)break;
                    if(temp->next->symbol[0]!='N')break;
                    temp=temp->next;
                }

                break;
                
            }

        }

        // cout<<"\n** "<<temp->symbol[0]<<temp->symbol[1]<<"\n";

        new_node->next=temp->next;
        temp->next=new_node;

        
        

    }
    
    preorder1(first);cout<<"\n";


    // char c[mXn*mXn];
    // c[0]='\0';


    // preorder(first,&c);

    // for(int i=0;i<26;i++)
    // {
    //     char c='a'+i;
    //     cout<<c<<" = ";ans[i];cout<<"\n";
    // }
    // cout<<"\n";
    // for(int i=26;i<36;i++)
    // {
    //     cout<<i-26<<" = ";ans[i];cout<<"\n";
    // }
    


    
    return 0;
}