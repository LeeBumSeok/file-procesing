#include <iostream>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
};

class binarysearchtree
{
public:
    Node *root = NULL;
    Node *getNode();
    Node *maxNode(Node *);
    Node *minNode(Node *);
    void insertBST(Node *&, int);
    void inorderBST(Node *);
    void deleteBST(Node *&, int);
    int height(Node *);
    int noNodes(Node *);
};

Node *binarysearchtree::getNode()
{
    Node *tmp = new Node();
    tmp->key = 0;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

void binarysearchtree::insertBST(Node *&T, int newKey)
{
    Node *q = NULL;
    Node *p = T;
    while (p != NULL)
    {
        if (newKey == p->key)
            return;
        q = p;
        if (newKey < p->key)
            p = p->left;
        else
            p = p->right;
    }
    Node *newNode = getNode();
    newNode->key = newKey;

    if (T == NULL)
        T = newNode;
    else if (newKey < q->key)
        q->left = newNode;
    else
        q->right = newNode;

    return;
}

void binarysearchtree::inorderBST(Node *T)
{
    if (T != NULL)
    {
        inorderBST(T->left);
        cout << T->key << " ";
        inorderBST(T->right);
    }
}

void binarysearchtree::deleteBST(Node *&T, int deleteKey)
{
    Node *p, *q, *r;
    p = T;
    q = NULL;
    while (1)
    {
        if (p->key == deleteKey)
            break;
        if (p->key < deleteKey)
        {
            q = p;
            p = p->right;
        }
        else
        {
            q = p;
            p = p->left;
        }
    }

    if (p == NULL)
        return;
    if ((p->left == NULL) && (p->right == NULL))
    {
        if (q == NULL)
        {
            if (p == T)
                T = NULL;
        }
        else
        {
            if (q->left == p)
                q->left = NULL;
            else
                q->right = NULL;
        }
    }

    else if ((p->left == NULL) || (p->right == NULL))
    {
        if (q == NULL)
        {
            if (p->left != NULL)
                T = p->left;
            else
                T = p->right;
        }
        else
        {
            if (p->left != NULL)
            {
                if (q->left == p)
                    q->left = p->left;
                else
                    q->right = p->left;
            }
            else
            {
                if (q->left == p)
                    q->left = p->right;
                else
                    q->right = p->right;
            }
        }
    }
    else
    {
        r = NULL;
        bool flag = false;
        if (height(p->left) < height(p->right))
        {
            r = minNode(p->right);
            flag = true;
        }
        else if (height(p->left) > height(p->right))
        {
            r = maxNode(p->left);
            flag = false;
        }
        else
        {
            if (noNodes(p->left) < noNodes(p->right))
            {
                r = minNode(p->right);
                flag = true;
            }
            else
            {
                r = maxNode(p->left);
                flag = false;
            }
        }
        p->key = r->key;
        if (!flag)
            deleteBST(p->left, r->key);
        else
            deleteBST(p->right, r->key);
    }
    return;
}

int binarysearchtree::height(Node *T)
{
    if (T == NULL)
        return 0;

    if (height(T->left) > height(T->right))
        return height(T->left) + 1;
    else
        return height(T->right) + 1;
}

int binarysearchtree::noNodes(Node *T)
{
    if (T)
        return noNodes(T->left) + noNodes(T->right) + 1;
    else
        return 1;
}

Node *binarysearchtree::maxNode(Node *T)
{
    Node *q = NULL;
    Node *p = T;
    while (p)
    {
        q = p;
        p = p->right;
    }
    return q;
}

Node *binarysearchtree::minNode(Node *T)
{
    Node *q = NULL;
    Node *p = T;
    while (p)
    {
        q = p;
        p = p->left;
    }
    return q;
}

int main()
{
    binarysearchtree T;
    int treeList[20] = {25, 500, 33, 49, 17, 403, 29, 105, 39, 66, 305, 44, 19, 441, 390, 12, 81, 50, 100, 999};

    T.root = NULL;
    for (int i = 0; i < 20; i++)
    {
        T.insertBST(T.root, treeList[i]);
        T.inorderBST(T.root);
        cout << endl;
    }

    for (int i = 0; i < 20; i++)
    {
        T.deleteBST(T.root, treeList[i]);
        T.inorderBST(T.root);
        cout << endl;
    }

    T.root = NULL;
    for (int i = 0; i < 20; i++)
    {
        T.insertBST(T.root, treeList[i]);
        T.inorderBST(T.root);
        cout << endl;
    }

    for (int i = 19; i >= 0; i--)
    {
        T.deleteBST(T.root, treeList[i]);
        T.inorderBST(T.root);
        cout << endl;
    }
}