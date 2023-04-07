#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

static inline int numberofListNodes(struct ListNode* head)
{
    if(!head)
    {
        return -1;
    }

    struct ListNode* tmp = head;

    int count = 0;
    while(tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }

    return count;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
        if(!head || !n || n < 0)
        {
            return NULL;
        }

        struct ListNode* tmp = head;
        
        int N = numberofListNodes(head);
        if(N == -1)
        {
            return NULL;
        }

        if(n == N)
        {
            head = head->next;
            return head;
        }

        for(int i = 1; i < N-n; i++)
        {
            tmp = tmp->next;
        }

        if(n == 1)
        {
            tmp->next = NULL;
            return head;    
        }   
        tmp->next = tmp->next->next;
        return head;
}   