//don't compare for equality also
//find node where a and b's path diverge

node *lca(node *p, int a, int b)
{
    if (a>b)//make a smaller
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    while (p!=nullptr)
    {
        int k = p->data;
        if (a>k)//b is too
            p = p->right;
        else if (b<k)//and a
            p = p->left;
        else
            break;
    }

    return p;
}
