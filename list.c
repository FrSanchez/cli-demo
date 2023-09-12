#include <stdlib.h>
#include <string.h>
#include "list.h"

ListNode *insertIntoList(ListNode *head, const char *data)
{

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->data = (char *)malloc(sizeof(char) * strlen(data) + 1);
    strcpy(newNode->data, data);
    newNode->next = NULL;
    if (!head)
    {
        return newNode;
    }
    else
    {
        ListNode *curr = head;
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    return head;
}

void freeList(ListNode *head)
{
    if (head->next)
    {
        freeList(head->next);
    }
    free(head->data);
    free(head);
}