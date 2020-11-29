/**
 * File processing, 2020
 * AVL.cpp
 * implementation of AVL tree
 */

#include <iostream>

using namespace std;

/**
 * Node represents a single node in AVL tree.
 */
typedef struct Node {
  int         key, bf;
  struct Node *left, *right;
} Node;

typedef Node *Tree;

/**
 * getNode returns a new node.
 * @return a new node
 */
Node *getNode() {
  /* write your code here */
    Node *tmp = new Node();
    tmp->key = 0;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
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
 * updateBF updates balancing factors of nodes in T
 * and finds the unbalanced node nearest to y.
 * @param T: an AVL tree
 * @param y: the inserted/deleted node
 * @param x: the unbalanced node nearest to y
 * @param p: parent node of x
 */
void updateBF(Tree *T, Node *y, Node **x, Node **p) {
  /* write your code here */
}

/**
 * rotateLL implements LL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLL(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

/**
 * rotateRR implements RR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRR(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

/**
 * rotateLR implements LR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLR(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

/**
 * rotateRL implements RL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRL(Tree *T, Node *x, Node *p) {
  /* write your code here */
}

/**
 * insertBST inserts newKey into T
 * and returns the inserted node.
 * @param T: a binary search tree
 * @param newKey: a key to insert
 * @return the inserted node
 */
Node *insertBST(Tree *T, int newKey) {
    Node *q = NULL;
    Node *p = *T;
    while (p != NULL)
    {
        if (newKey == p->key)
            return nullptr;
        q = p;
        if (newKey < p->key)
            p = p->left;
        else
            p = p->right;
    }
    Node *newNode = getNode();
    newNode->key = newKey;

    if (T == NULL)
        *T = newNode;
    else if (newKey < q->key)
        q->left = newNode;
    else
        q->right = newNode;

    return nullptr;
}

/**
 * insertAVL inserts newKey into T.
 * @param T: an AVL tree
 * @param newKey: a key to insert
 */
void insertAVL(Tree *T, int newKey) {
  /**
   * print "NO" if not rotates
   * print "LL" if rotates LL
   * print "RR" if rotates RR
   * print "LR" if rotates LR
   * print "RL" if rotates RL
   */
  /* write your code here */
  insertBST(T, newKey);
}

/**
 * deleteBST deletes deleteKey from T
 * and returns the parent node of the deleted node.
 * @param T: a binary search tree
 * @param deleteKey: a key to delete
 * @return the parent node of the deleted node
 */

Node *deleteBST(Tree *T, int deleteKey) {
    Node *p, *q, *r;
    p = *T;
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
        return nullptr;
    if ((p->left == NULL) && (p->right == NULL))
    {
        if (q == NULL)
        {
            if (p == *T)
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
    return nullptr;
}

/**
 * deleteAVL deletes deleteKey from T.
 * @param T: an AVL tree
 * @param deleteKey: a key to delete
 */
void deleteAVL(Tree *T, int deleteKey) {
  /**
   * print "NO" if not rotates
   * print "LL" if rotates LL
   * print "RR" if rotates RR
   * print "LR" if rotates LR
   * print "RL" if rotates RL
   */
  /* write your code here */
  deleteBST(T, deleteKey);
}


/**
 * inorderAVL implements inorder traversal in T.
 * @param T: an AVL tree
 */
void inorderAVL(Tree T) {
  /* write your code here */
}

int main() {
  /* Do not modify the code below */

  int testcase[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };

  Tree T = NULL;

  // insertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // deletion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  T = NULL;

  // reinsertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // redeletion
  for (int i=19; 0<=i; i--) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
}
