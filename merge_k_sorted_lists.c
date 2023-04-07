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

void merge(struct ListNode* list, int l, int mid, int r);
void mergesort(struct ListNode* list, int l, int r);

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
    int cnt = 0;
    int l_half = mid - l + 1;
	int r_half = r - mid;

    // we only care about values stored inside the node i.e. the "container". Not their interlinking
    int* l_buf = malloc(l_half * sizeof(int));
	int* r_buf = malloc(r_half * sizeof(int));


    struct ListNode* tmp = list;
    while(cnt < l)
    {
        cnt++;
        tmp = tmp->next;
    }
    cnt = 0;

    for(int i = 0; i < l_half; i++)
	{
		l_buf[i] = tmp->val;
        tmp = tmp->next;
	}

    tmp = list;
    while(cnt < mid + 1)
    {
        cnt++;
        tmp = tmp->next;
    }
    cnt = 0;

	for(int i = 0; i <r_half; i++)
	{
		r_buf[i] = tmp->val;
        tmp = tmp->next;
	}
    tmp = list;

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

			if(l_buf[lc]< r_buf[rc])
			{
				// list[i] = l_buf[lc];
            
                while(cnt < i)
                {
                    tmp = tmp->next;
                    cnt++;
                }    
                cnt = 0;

                tmp->val = l_buf[lc];  
                tmp = list;

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
                while(cnt < i)
                {
                    tmp = tmp->next;
                    cnt++;
                }    
                cnt = 0;
                
				tmp->val = r_buf[rc];
                tmp = list;

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
			while(cnt < i)
            {
                tmp = tmp->next;
                cnt++;
            }    
            cnt = 0;
            
            tmp->val = r_buf[rc];
            tmp = list;

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
			while(cnt < i)
            {
                tmp = tmp->next;
                cnt++;
            }    
            cnt = 0;
            
            tmp->val = l_buf[lc];  
            tmp = list;

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

static inline int listSize(struct ListNode* list) 
{
    //already checked if "list" is NULL or not in mergeKLists()

    int size = 0;
    struct ListNode* tmp = list;

    while(tmp != NULL)
    {
        size++;
        tmp = tmp->next;
    }

    return size;
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if(!lists || !listsSize || listsSize < 0) //what if there are holes in the array of lists ??
    {
        return NULL;
    }

    // merge all the lists first
    
    struct ListNode *tmp = NULL;
    struct ListNode* merged = NULL;
    
    for(int i = 1; i < listsSize; i++)
    {
        if(lists[i] == NULL)
        {
            continue;
        }
        tmp = lists[i]; 
        
        if(!merged)
        {
            merged = tmp;
        }

        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        
        tmp->next = lists[i];
        tmp = lists[i];
    }

    //calculate size of merged list

    int size = listSize(lists[0]);

    //sort the merged list

    mergesort(lists[0], 0, size-1);

    //return the sorted list
    
    return lists[0];
}