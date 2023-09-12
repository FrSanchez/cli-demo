typedef struct _listNode
{
    char *data;
    struct _listNode *next;
} ListNode;

ListNode *insertIntoList(ListNode *head, const char *data);
void freeList(ListNode *head);