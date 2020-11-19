/**
 * File processing, 2020
 * AVL.cpp
 * implementation of AVL tree
 */

#include <iostream>

// Node represents a single node in AVL tree.
typedef struct Node
{
    int key, bf;
    struct Node *left, *right;
} Node;

/**
 * getNode returns a new node.
 * @return a new node
 */
Node *getNode()
{
    Node *tmp = new Node();
    tmp->key = 0;
    tmp->bf = 0;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

typedef Node *Tree;

// rotationType represents the rotation types of AVL tree.
typedef enum
{
    LL,
    RR,
    LR,
    RL,
    NO
} rotationType;

void insertBST(Tree *, int);
void deleteBST(Tree *, int);
Node *updateBF(Tree *, Node *);
int height(Node *);
int noNodes(Node *);
Node *maxNode(Node *);
Node *minNode(Node *);
void rotateLL(Node *);
void rotateLR(Node *);
void rotateRR(Node *);
void rotateRL(Node *);
void inorderAVL(Tree);

/**
 * insertBST inserts newKey into T.
 * @param T: a binary search tree
 * @param newKey: a key to insert
 */
void insertBST(Tree *T, int newKey)
{
    Node *q = NULL;
    Node *p = *T;
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

    if (*T == NULL)
        *T = newNode;
    else if (newKey < q->key)
        q->left = newNode;
    else
        q->right = newNode;

    return;
}

/**
 * deleteBST deletes deleteKey from T.
 * @param T: a binary search tree
 * @param deleteKey: a key to delete
 */
void deleteBST(Tree *T, int deleteKey)
{
    Node *p, *q, *r;
    p = *T;
    q = NULL;
    while (1)
    {
        if (p == NULL)
            break;
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
            if (p == *T)
                *T = NULL;
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
                *T = p->left;
            else
                *T = p->right;
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
            deleteBST((Tree *)p->left, r->key);
        else
            deleteBST((Tree *)p->right, r->key);
    }
    return;
}

/**
 * updateBF updates the balancing factors on the path from y to the root node and
 * returns the nearest unbalanced node.
 * @param T: an AVL tree
 * @param y: a node
 * @return the unbalanced node nearest to y
 */
Node *updateBF(Tree *T, Node *y)
{
    Node *p = y;
    if (p == NULL)
        return p;

    if (p->right == NULL && p->left == NULL)
        p->bf = 0;

    else if (p->left == NULL || p->right == NULL)
    {
        if (p->left == NULL)
            p->bf = -height(p->right);
        else if (p->right == NULL)
            p->bf = height(p->left);
    }
    else
        p->bf = height(p->left) - height(p->right);

    if (p->bf == 2 || p->bf == -2)
        return p;
    else
    {
        updateBF(T, p->left);
        updateBF(T, p->right);
    }

    return *T;
}

int height(Node *T)
{
    if (T == NULL)
        return 0;

    if (height(T->left) > height(T->right))
        return height(T->left) + 1;
    else
        return height(T->right) + 1;
}

int noNodes(Node *T)
{
    if (T)
        return noNodes(T->left) + noNodes(T->right) + 1;
    else
        return 1;
}

Node *maxNode(Node *T)
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

Node *minNode(Node *T)
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

/**
 * rotateLL implements LL rotation in subtree rooted with x.
 * @param x: root node of subtree
 */
void rotateLL(Node *x)
{
    Node *tmp = x->left;
    x->left = tmp->right;
    tmp->right = x;
}

/**
 * rotateRR implements RR rotation in subtree rooted with x.
 * @param x: root node of subtree
 */
void rotateRR(Node *x)
{
    Node *tmp = x->right;
    x->right = tmp->left;
    tmp->left = x;
}

/**
 * rotateLR implements LR rotation in subtree rooted with x.
 * @param x: root node of subtree
 */
void rotateLR(Node *x)
{
    Node *tmp = x->left;
    rotateRR(tmp);
    return rotateLL(x);
}

/**
 * rotateRL implements RL rotation in subtree rooted with x.
 * @param x: root node of subtree
 */
void rotateRL(Node *x)
{
    Node *tmp = x->right;
    rotateLL(tmp);
    return rotateRR(x);
}

/**
 * insertAVL inserts newKey into T.
 * @param T: an AVL tree
 * @param newKey: a key to insert
 * @return rotation type
 */
rotationType insertAVL(Tree *T, int newKey)
{
    insertBST(T, newKey);
    Node *p = updateBF(T, *T);
    if (p == NULL)
        return NO;

    if (p->bf == 2)
    {
        if (height(p->left) - height(p->right) == 2)
            return LL;
        else
            return RR;
    }
    else if (p->bf == -2)
    {
        if (height(p->left) - height(p->right) == -2)
            return RR;
        else
            return LL;
    }
    else
        return NO;
}

/**
 * deleteAVL deletes deleteKey from T.
 * @param T: an AVL tree
 * @param deleteKey: a key to delete
 * @return rotation type
 */
rotationType deleteAVL(Tree *T, int deleteKey)
{
    deleteBST(T, deleteKey);
    Node *p = updateBF(T, *T);

    if (p == NULL)
        return NO;

    if (p->bf == 2)
    {
        if (height(p->left) - height(p->right) == 2)
            return LL;
        else
            return RR;
    }
    else if (p->bf == -2)
    {
        if (height(p->left) - height(p->right) == -2)
            return RR;
        else
            return LL;
    }
    else
        return NO;
}

/**
 * inorderAVL implements inorder traversal in T.
 * @param T: an AVL tree
 */
void inorderAVL(Tree T)
{
    if (T != NULL)
    {
        inorderAVL(T->left);
        printf("%d ", T->key);
        inorderAVL(T->right);
    }
}

int main()
{
    /* do not modify the code below */

    int testcase[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49};

    const char *rotationTypes[] = {"LL", "RR", "LR", "RL", "NO"};

    Tree T = NULL;

    // insertion
    for (int i = 0; i < 20; i++)
    {
        printf("%d %s : ", testcase[i], rotationTypes[insertAVL(&T, testcase[i])]);
        inorderAVL(T);
        printf("\n");
    }

    // deletion
    for (int i = 0; i < 20; i++)
    {
        printf("%d %s : ", testcase[i], rotationTypes[deleteAVL(&T, testcase[i])]);
        inorderAVL(T);
        printf("\n");
    }

    T = NULL;

    // reinsertion
    for (int i = 0; i < 20; i++)
    {
        printf("%d %s : ", testcase[i], rotationTypes[insertAVL(&T, testcase[i])]);
        inorderAVL(T);
        printf("\n");
    }

    // redeletion
    for (int i = 19; 0 <= i; i--)
    {
        printf("%d %s : ", testcase[i], rotationTypes[deleteAVL(&T, testcase[i])]);
        inorderAVL(T);
        printf("\n");
    }
}