#include<stdio.h>

struct node{

	int data; // stores the value in the node.
	
	struct node *add; // stores the XOR value of the next and prev pointer.
};

void traverse_from_front_to_end(struct node *head){
    struct node *ptr = head, *prev = NULL, *next = NULL;
	while(ptr != NULL){
		// print the value.
		printf("%d, ", ptr->data);

		// compute the next pointer.
		next = (unsigned long long)ptr->add^(unsigned long long)prev;
        
		// move to the next pointer.
        prev = ptr;
        ptr = next;
	}
	printf("\b\b.");
}

void traverse_from_end_to_front(struct node *tail){
    struct node *ptr = tail, *prev = NULL, *next = NULL;
	while(ptr != NULL){
		// print the value.
		printf("%d, ", ptr->data);

		// compute the next pointer.
		next = (unsigned long long)ptr->add^(unsigned long long)prev;
        
		// move to the next pointer.
        prev = ptr;
        ptr = next;
	}
	printf("\b\b.");
}

void reverse(struct node **head, struct node **tail){
	// Just swapping the Values works!
	// This is where the Benifit of XORs comes in !!
	struct node *temp = *head;
	*head = *tail;
	*tail = temp;
}

// Smart way of doing it using the reverse!
void alternate(struct node **head, struct node **tail){
	struct node * ptr = *head;
	struct node * prev = NULL;
	struct node * next = NULL, *nextToNext = NULL;

	while(ptr!=NULL){
		// get the pointer to next element
		next = (unsigned long long)ptr->add ^ (unsigned long long)prev;
		
		// Last single element
		if(next==NULL){
			*tail = ptr;
			break;
		}
		
		// Break the list from the next element, by making prev of next as NULL.
		nextToNext = (unsigned long long)next->add ^ (unsigned long long)ptr;
		next->add = (unsigned long long) nextToNext ^ (unsigned long long)NULL;
		
		// Reverse the list from the next to the end.
		reverse(&next, tail);

		// fix next element's add value by joining with ptr
		nextToNext = (unsigned long long)next->add ^ (unsigned long long)NULL;
		next->add = (unsigned long long) nextToNext ^ (unsigned long long)ptr;

		// fix the current ptr element's add value
		ptr->add = (unsigned long long)prev^(unsigned long long)next;
        
        // Move to the next element.
        prev = ptr;
        ptr = next;
	}
}



int main(){

	int n;

	// Take the input size
	printf("Enter n:");
	scanf("%d", &n);
	
	// Make the Head node.
	struct node *head, *tail;
	head = (struct node *)malloc(sizeof(struct node));

	struct node *prev = NULL, *next = NULL, *ptr = head;

	// Create the first n-1 nodes.
	for(int i = 1; i < n; i++)
	{
		next = (struct node *)malloc(sizeof(struct node));
		// Fill with random value
		ptr->data = rand()%100;
		// Make the XOR value saved.
		ptr->add = (unsigned long long)prev^(unsigned long long)next;
        // Move to the next pointer.
        prev = ptr;
        ptr = next;     
	}

	// Fill the last value.
	ptr->data = rand()%100;
	ptr->add = (unsigned long long)prev^(unsigned long long)NULL;
	tail = ptr;

	// Print from front to end.
	printf("Doubly linked list traversed from front to end: ");
    traverse_from_front_to_end(head);
	
	// Print from end to front.
	printf("\nDoubly linked list traversed from end to front: ");
	traverse_from_end_to_front(tail);

	// reverse without extra space
    reverse(&head,&tail);

    // Print from front to end the reversed list.
	printf("\nReversed doubly linked list traversed from front to end: ");
    traverse_from_front_to_end(head);

    // Create the alternate list
	alternate(&head,&tail);

	// Print from front to end the alternated list.
	printf("\nAlternated doubly linked list traversed from front to end: ");
  	traverse_from_front_to_end(head);
    
    printf("\n");
	return 0;
}
