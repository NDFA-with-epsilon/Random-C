/* 
You are given an array of k linked-lists "lists", each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

int merge_stub(struct ListNode* list, int listSize)
{
    if(!list) return -1;

    mergesort(list, 0, listSize-1);
    return 0; //success
}

void mergesort(struct ListNode* list, int l, int r)
{
    //can i select words with same name in a lexical scope and not global scope VSCode ?????

    if(l >= r) //l > r is for sanity check and l == r is for indivisibility 
    {
        return;
    } 

    int mid = floor(l + ((r - l) / 2)); 
	
	/* Call mergesort recursively on the two halves */
    mergesort(list, l, mid);
    mergesort(list, mid + 1, r);

    /* Merge the two sorted halves*/
    merge(list, l, mid, r);
}

void merge(struct ListNode* list, int l, int mid, int r)
{
    int l_half = mid - l + 1;
	int r_half = r - mid;

    struct ListNode** l_buf = malloc(l_half * sizeof(struct ListNode*));
	struct ListNode** r_buf = malloc(r_half * sizeof(struct ListNode*));


    struct ListNode* tmp = list + l;
    for(int i = 0; i < l_half; i++)
	{
		l_buf[i]->val = tmp->val;
        tmp = tmp->next;
	}

    tmp = list + (mid + 1);
	for(int i = 0; i <r_half; i++)
	{
		r_buf[i]->val = tmp->val;
        tmp = tmp->next;
	}

    int lc = 0; 
    int rc = 0;

	enum first_buf_to_fill
	{
		none,
		left,
		right
	}lrbuf; 
    lrbuf = none; //not initializing it with `none` causes issues


    for(int i = l; i < r + 1; i++)
	{	
		if(lrbuf == none) //both bufs are non-empty
		{
			if(l_buf[lc] < r_buf[rc])
			{
				buf[i] = l_buf[lc];

				if(lc + 1 < l_half)	//l_buf is still non-empty
				{
					lc += 1; continue;
				}

				else	//l_buf is empty now
				{
					lrbuf = left; continue;
				}
			}

			else
			{
				buf[i] = r_buf[rc];

				if(rc + 1 < r_half)	//r_buf is still non-empty
				{
					rc += 1; continue;
				}
				else	//r_buf is empty now
				{
					lrbuf = right; continue;
				}
			}
			//condition for equal entries in l_buf & r_buf	
		}

		else if(lrbuf == left)	//l_buf has been emptied, now read from r_buf sequentially
		{
			buf[i] = r_buf[rc];
			if(rc + 1 == r_half) //r_buf is also empty now, so terminate loop
			{
				break;
			}
			
			else
			{
				rc += 1; continue;
			}
		}

		else	//r_buf is empty, now read from l_buf
		{
			buf[i] = l_buf[lc];
			if(lc + 1 == l_half)	//l_buf is also empty now, so terminate loop
			{
				break;
			}

			else
			{
				lc += 1; continue;
			}
		}
	}
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if(!listsSize || listsSize < 0)
    {
        return NULL;
    }

    // merge all the lists first
    
    struct ListNode *tmp = lists[0];
    
    for(int i = 1; i < listsSize; i++)
    {
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        
        tmp->next = lists[i];
        tmp = lists[i];
    }

    //point the iterator to back to head node
    
    tmp = lists[0];

    //sort the merged list




    //return the sorted list
    
    return tmp;
}

int main(void)
{
    struct ListNode* x = malloc(sizeof(struct ListNode));
    x->val = 1;
    x->next = malloc(sizeof(struct ListNode));
    x->next->val = 4;
    x->next->next = malloc(sizeof(struct ListNode));
    x->next->next->val = 5;
    x->next->next->next = NULL;

    struct ListNode* y = malloc(sizeof(struct ListNode));
    y->val = 1;
    y->next = malloc(sizeof(struct ListNode));
    y->next->val = 3;
    y->next->next = malloc(sizeof(struct ListNode));
    y->next->next->val = 4;
    x->next->next->next = NULL;

    struct ListNode* z = malloc(sizeof(struct ListNode));
    z->val = 2;
    z->next = malloc(sizeof(struct ListNode));
    z->next->val = 6;
    z->next->next = NULL;

    struct ListNode* arr[] = {x, y, z};
    struct ListNode* merged = mergeKLists(arr, 3);
    
    while(merged != NULL)
    {
        printf("%d\t", x->val);
        x = x->next;
    }
    return 0;
}