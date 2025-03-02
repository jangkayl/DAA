struct node
{
    int num;
    node *next;
    node *prev;

    node(int val)
    {
        num = val;
        next = nullptr;
        prev = nullptr;
    }
};