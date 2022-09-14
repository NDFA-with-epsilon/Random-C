#ifndef _MERGE_SORT_
#define _MERGE_SORT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUF_SIZE 10 //tweak this for your needs
#define INVALID_PARAM -1
#define SUCCESS 1

/* None of these functions take ownership of the buffer passed to them */

int merge_stub(int* buf);	//doubtful utility, but still call this with a pointer to your buffer. 
void mergesort(int* buf, int l, int r);
void merge(int* buf, int l, int mid, int r);

int merge_stub(int* buf)	
{
    if(!buf)
    {   
        return INVALID_PARAM;
    }

    mergesort(buf, 0, BUF_SIZE - 1);
    return SUCCESS;
}

void mergesort(int* buf, int l, int r)
{
    if(l >= r) //l > r is for sanity check and l == r is for indivisibility 
    {
        return;
    } 

	/* Divide the array into two halves */
    int mid = floor(l + ((r - l) / 2)); 
	
	/* Call mergesort recursively on the two halves */
    mergesort(buf, l, mid);
    mergesort(buf, mid + 1, r);
    
    	/* Merge the two sorted halves*/
    merge(buf, l, mid, r);
}

void merge(int* buf , int l, int mid, int r)
{
	int l_half = mid - l + 1;
	int r_half = r - mid;

	int l_buf[l_half];
	int r_buf[r_half];

	for(int i = 0; i < l_half; i++)
	{
		l_buf[i] = buf[l+i];
	}

	for(int i = 0; i <r_half; i++)
	{
		r_buf[i] = buf[mid + 1 + i];
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

#endif
