/* make a macro to print elements of array #define PRINT(buf_size) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUF_SIZE 10

void mergesort(int* buf, int l, int r);
void merge(int* buf, int l, int mid, int r);
void merge_tmp(int* buf, int l, int mid, int r);

static inline __attribute__((always_inline)) 
void populate_buf(int* buf)
{
    for(int i = 0; i < BUF_SIZE; i++)
    {
        buf[i] = 100 - i;
    }
}

void merge(int* buf, int l, int mid, int r) 
{
    int l_half = mid - l + 1;
    int r_half = r - mid;

    int l_buf[l_half];
    int r_buf[r_half];

    for(int i = 0; i < l_half; i++)
    {
        l_buf[i] = buf[l+i];
    }

    for(int i = 0; i < r_half; i++)
    {
        r_buf[i] = buf[mid + 1 + i];
    }

    int lc = 0;
    int rc = 0;
   
    for(int j = l; j < r + 1; j++)
    {
        if(lc < l_half && rc < r_half) //this condition is wrong, if one temp buf gets filled, there may still be another temp buf available for filling 
        {
            if(l_buf[lc] < r_buf[rc])
            {
                buf[j] = l_buf[lc];
                lc += 1; continue;
            }

            else if(l_buf[lc] > r_buf[rc])
            {
                buf[j] = r_buf[rc];
                rc += 1; continue;
            }

            else 
            {
                buf[j] = l_buf[lc];
                lc += 1;

                buf[j+1] = r_buf[rc];
                rc += 1;
                j += 1;
            }
        }
    }
}

void merge_tmp(int* buf , int l, int mid, int r)
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
	}lrbuf; //by default "none" i.e 0 at instantiation
    lrbuf = none;

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

				if(rc + 1 < r_half) //r_buf is still non-empty
				{
					rc += 1; continue;
				}
				else		//r_buf is empty now
				{
					lrbuf = right; continue;
				}
			}
			//condition for equal entries in l_buf & r_buf	
		}

		else if(lrbuf == left)
		{
			//l_buf has been emptied, now read from r_buf sequentially
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

		else //r_buf is empty, now read from l_buf
		{
			buf[i] = l_buf[lc];
			if(lc + 1 == l_half) //l_buf is also empty now
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
void mergesort(int* buf, int l, int r)
{
    if(l >= r)
    {
        return;
    }

    int mid = floor(l + ((r - l) / 2)); //Divide the array into half

    /* Call mergesort recursively on the two halves */
    mergesort(buf, l, mid);
    mergesort(buf, mid + 1, r);
    
    /* merge the two halves*/
    merge_tmp(buf, l, mid, r);
}

int merge_stub(int* buf)
{
    if(!buf)
    {   
        return -1;
    }

    mergesort(buf, 0, BUF_SIZE - 1);
}

int main(void)
{
    int buf[BUF_SIZE] = { 0 };
    populate_buf(buf);
    
    for(int i = 0; i < BUF_SIZE; i++)
    {
        printf("\n%d", buf[i]);
    }

    printf("\n\n***\n");

    if (merge_stub(buf) == -1) 
    {
        printf("\nInvalid parameter(s) passed to merge_stub()");
    };


    for(int i = 0; i < BUF_SIZE; i++)
    {
        printf("\n%d", buf[i]);
    }
}