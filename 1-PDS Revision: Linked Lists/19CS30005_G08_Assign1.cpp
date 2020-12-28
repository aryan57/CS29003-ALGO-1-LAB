/*
    author : Aryan Agarwal, 19CS30005
    created : 03-September-2020 14:15:52 IST
*/
#include <iostream>
using namespace std;

struct node
{
    int data;  // stores the value in the node.
    node *add; // stores the XOR value of the next and prev pointer.
};

void traverse_from_front_to_end(node *head)
{
    node *prev = NULL, *tmp;
    while (head != NULL)
    {
        cout << head->data << " ";
        tmp = head;
        head = (node *)((unsigned long long)prev ^ (unsigned long long)(head->add));
        prev = tmp;
    }
}
void traverse_from_end_to_front(node *tail)
{
    node *next = NULL, *tmp;
    while (tail != NULL)
    {
        cout << tail->data << " ";
        tmp = tail;
        tail = (node *)((unsigned long long)next ^ (unsigned long long)(tail->add));
        next = tmp;
    }
}

void reverse(node **head, node **tail)
{
    node *tmp;

    tmp = *head;
    *head = *tail;
    *tail = tmp;

    traverse_from_front_to_end(*head);
}

void alternate(node **head, node **tail)
{
    node *tmp1, *tmp2, *tmp3;

    node *head_tmp = *head, *tail_tmp = *tail, *head_pre = NULL, *tail_next = NULL;
    
    if (*head != *tail) // if *head and *tail are equal , it means length of list is 1, no need to do anything.
    {
        //i have used the list from front and back at the same time, and break the loop at middle.
        // suppose list is 1->2->3->4->5
        // i have used 1->2->3->4->5 and 5->4->3->2->1 at the same time
        
        while (true)
        {
            tmp1 = head_pre;
            tmp2 = head_tmp;
            tmp3 = head_tmp->add;

            head_tmp->add = (node *)((unsigned long long)tail_tmp ^ (unsigned long long)(tail_next));
            head_tmp = (node *)((unsigned long long)tmp1 ^ (unsigned long long)tmp3);
            head_pre = tmp2;

            tmp1 = tail_next;
            tmp2 = tail_tmp;
            tmp3 = tail_tmp->add;

            if (head_tmp == tail_tmp) // even length linked list
            {
                head_tmp->add = (node *)((unsigned long long)NULL ^ (unsigned long long)(head_pre));
                *tail = head_tmp;
                break;
            }

            tail_tmp->add = (node *)((unsigned long long)head_tmp ^ (unsigned long long)(head_pre));
            tail_tmp = (node *)((unsigned long long)tmp1 ^ (unsigned long long)(tmp3));
            tail_next = tmp2;

            if (head_tmp == tail_tmp) // odd length linked list
            {
                head_tmp->add = (node *)((unsigned long long)NULL ^ (unsigned long long)(tail_next));
                *tail = head_tmp;
                break;
            }
        }
    }

    traverse_from_front_to_end(*head);
}

int main()
{
    int n, x;
    cout << "Enter length of doubly linked list : ";
    cin >> n;
    cout << "n = " << n << "\n";

    node *list = (node *)malloc(n * sizeof(node));
    node *head = &list[0], *tail = &list[n - 1];

    cout << "\nEnter the " << n << " integers between -100 to 100 :";
    for (int i = 0; i < n; i++)
    {
        cin >> x;

        while (x < -100 || x > 100)
        {
            cout << "Please enter a number between -100 to 100 : ";
            cin >> x;
        }

        list[i].data = x;

        if (n == 1)
        {
            list[i].add = NULL;
            break;
        }

        if (i == 0)
        {
            list[i].add = (node *)((unsigned long long)&list[i + 1] ^ (unsigned long long)NULL);
        }
        else if (i == n - 1)
        {
            list[i].add = (node *)((unsigned long long)&list[i - 1] ^ (unsigned long long)NULL);
        }
        else
        {
            list[i].add = (node *)((unsigned long long)&list[i - 1] ^ (unsigned long long)&list[i + 1]);
        }
    }

    cout << "\nDoubly linked list traversed from front to end : ";
    traverse_from_front_to_end(head);
    cout << "\n";
    cout << "\nDoubly linked list traversed from end to front : ";
    traverse_from_end_to_front(tail);
    cout << "\n";
    cout << "\nReversed doubly linked list traversed from front to end : ";
    reverse(&head, &tail);
    cout << "\n";
    cout << "\nAlternated doubly linked list traversed from front to end : ";
    alternate(&head, &tail);
    cout << "\n";

    return 0;
}