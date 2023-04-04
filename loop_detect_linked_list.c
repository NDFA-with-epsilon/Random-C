//detect and remove loop in a linked list

typedef struct node
{
	int val;
	struct node* next;
}node;

/*
brute force method:
	Traverse the list, maintain a list of visited nodes. Starting from the head node, call insert() on the next node. If the said node already has been traversed ===> loop exists
	Else there will be a tmp->next == NULL situation and thus implying no loop exists
	To remove loop, the last non-NULL entry in the 'visited' array is the last node whose 'next' pointer needs to be NULLed 		
*/

#define MAX_SIZE 4096

typedef struct node
{
	int val;
	struct node* next;
}node;

static inline int insert(node** buf, int idx, node* entry)
{   
    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(buf[i] == entry)
        {
            //entry exists already ===> loop exists

            printf("\nLOOP DETECTED AT NODE %d\n", i+1);
            buf[--idx]->next = NULL; //loop removed
            return -1; 
        }

        if(buf[i] == NULL)
        {
            // this NULL is due to NULL initialisation of visited array and thus entry is unique
            buf[i] = entry;
            return 0; //entry inserted
        }   
    }
}   

//provide sanitized input only please: make sure head != NULL
int loop_detect(node* head)
{
	if(!head)
	{
		return 0;
	}

	node* tmp = head;
    
    //if ok with this kind of hackery, then go ahead else use vectors from C++

    int idx = 0;
    node* visited[MAX_SIZE] = {0};
	
    visited[idx] = tmp; 
    idx++;

    while(tmp != NULL)
    {
        /*
        check if tmp->next is NULL before hand only. 2 reasons:
        1) it will insert() NULL into visited array. Since array was NULL initialised, insert() will say duplicate NULL exists and loop exists, which is false positive 
        2) also prevent looping cuz expensive
        */

        if(tmp->next == NULL)
        {
            return 0; //loop does not exist
        }

        //traverse each node and check on insert()'s value: -ve value means duplicate ===> loop
        
        if(insert(visited, idx, tmp->next) < 0)
        {
            return -1; //loop found
        }

        tmp = tmp->next;
        idx++;
    }

    return 0; //loop does not exist
}