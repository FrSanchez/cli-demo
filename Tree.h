typedef struct _node
{
    char *name;
    int numChildren;
    struct _node **children;
} Node;

Node *createEmptyNode(char *name);
Node *createNode(char *name, int numChildren);
void addChild(Node *parent, Node *child);