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
    tmp -> bf = 0;
    tmp -> left = nullptr;
    tmp -> right = nullptr;
    return tmp;
}

int height(Node *T) {
    if (T == nullptr) return 0;

    if (height(T -> left) > height(T -> right)) return height(T -> left) + 1;
    else return height(T -> right) + 1;
}

int noNodes(Node *T) {
    if (T) return noNodes(T -> left) + noNodes(T -> right) + 1;
    else return 1;
}

int BF(Node *n) { return height(n -> left) - height(n -> right); }

Node *maxNode(Node *T)
{
    Node *q = nullptr;
    Node *p = T;
    while (p) {
        q = p;
        p = p -> right;
    }
    return q;
}

Node *minNode(Node *T)
{
    Node *q = nullptr;
    Node *p = T;
    while (p) {
        q = p;
        p = p -> left;
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
    Node *q = *T;
    Node *tmp = nullptr;

    while(tmp != y) {
        q -> bf = BF(q);
        if(q -> bf < -1 || q -> bf > 1) {
            *x = q;
            *p = tmp;
        }
        tmp = q;
        if(y -> key < q -> key) q = q -> left;
        else q = q -> right;
    }
}

/**
 * rotateLL implements LL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLL(Tree *T, Node *x, Node *p) {
  /* write your code here */
  Node * tmp;
  tmp = x -> left;
  x -> left = tmp -> right;
  tmp -> right = x;
  Node *unbalance = nullptr;
  Node *p_unbalance = nullptr;

  if(p == nullptr) *T = tmp;
  else if(p -> left == x) p -> left = tmp;
  else p -> right = tmp;

  updateBF(T, x, &unbalance, &p_unbalance);
}

/**
 * rotateRR implements RR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRR(Tree *T, Node *x, Node *p) {
    /* write your code here */
    Node * tmp;
    tmp = x -> right;
    x -> right = tmp -> left;
    tmp -> left = x;
    Node *unbalance = nullptr;
    Node *p_unbalance = nullptr;

    if(p == nullptr) *T = tmp;
    else if(p -> left == x) p -> left = tmp;
    else p -> right = tmp;

    updateBF(T, x, &unbalance, &p_unbalance);
}

/**
 * rotateLR implements LR rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateLR(Tree *T, Node *x, Node *p) {
  /* write your code here */
    Node *unbalance = nullptr;
    Node *p_unbalance = nullptr;
    rotateRR(&x, x -> left, x);
    rotateLL(T, x, p);

    updateBF(T, x, &unbalance, &p_unbalance);
}

/**
 * rotateRL implements RL rotation in subtree rooted with x.
 * @param T: an AVL tree
 * @param x: root node of subtree
 * @param p: parent node of x
 */
void rotateRL(Tree *T, Node *x, Node *p) {
  /* write your code here */
    Node *unbalance = nullptr;
    Node *p_unbalance = nullptr;
    rotateLL(&x, x -> right, x);
    rotateRR(T, x, p);

    updateBF(T, x, &unbalance, &p_unbalance);
}

/**
 * insertBST inserts newKey into T
 * and returns the inserted node.
 * @param T: a binary search tree
 * @param newKey: a key to insert
 * @return the inserted node
 */
Node *insertBST(Tree *T, int newKey) {
    Node *q = nullptr;
    Node *p = *T;

    while (p != nullptr) {
        if (newKey == p->key) return nullptr;
        q = p;
        if (newKey < p -> key) p = p -> left;
        else p = p -> right;
    }
    Node *newNode = getNode();
    newNode -> key = newKey;

    if (*T == nullptr) *T = newNode;
    else if (newKey < q -> key) q -> left = newNode;
    else q -> right = newNode;

    return newNode;
}

/**
 * insertAVL inserts newKey into T.
 * @param T: an AVL tree
 * @param newKey: a key to insert
 */
void insertAVL(Tree *T, int newKey) {
  Node *insert, *unbalance, *p_unbalance;
  insert = insertBST(T, newKey);
  unbalance = nullptr;
  p_unbalance = nullptr;
  updateBF(T, insert, &unbalance, &p_unbalance);

  int diff, ubdiffLeft, ubdiffRight;

  if(unbalance == nullptr) diff = 0;
  else diff = unbalance->bf;

  if(diff > 1) {
    ubdiffLeft = unbalance -> left -> bf;

    if(ubdiffLeft > 0) {
      cout << "LL";
      rotateLL(T, unbalance, p_unbalance);
    }
    else {
      cout << "LR";
      rotateLR(T, unbalance, p_unbalance);
    }
  }

  else if(diff < -1) {
    ubdiffRight = unbalance -> right -> bf;

    if(ubdiffRight > 0) {
      cout << "RL";
      rotateRL(T, unbalance, p_unbalance);
    }
    else {
      cout << "RR";
      rotateRR(T, unbalance, p_unbalance);
    }
  }
  else cout << "NO";
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
    q = nullptr;
    while (p -> key != deleteKey) {
        if (p -> key < deleteKey) {
            q = p;
            p = p -> right;
        }
        else {
            q = p;
            p = p -> left;
        }
    }

    if (p == nullptr) return nullptr;
    if (p -> left == nullptr && p -> right == nullptr) {
        if (q == nullptr) {
            if (p == *T) *T = nullptr;
        }
        else {
            if (q -> left == p) q->left = nullptr;
            else q -> right = nullptr;
        }
    }

    else if (p -> left == nullptr || p -> right == nullptr) {
        if (q == nullptr) {
            if (p -> left != nullptr) *T = p -> left;
            else *T = p -> right;
        }
        else {
            if (p -> left != nullptr) {
              if (q -> left == p) q -> left = p -> left;
              else q -> right = p -> left;
            }
            else {
              if (q -> left == p) q -> left = p -> right;
              else q -> right = p -> right;
            }
        }
    }
    else {
        r = nullptr;
        bool flag = false;
        if (height(p -> left) < height(p -> right)) {
            r = minNode(p -> right);
            flag = true;
        }
        else if (height(p -> left) > height(p -> right)) {
            r = maxNode(p -> left);
            flag = false;
        }
        else {
            if (noNodes(p -> left) < noNodes(p -> right)) {
                r = minNode(p -> right);
                flag = true;
            }
            else {
                r = maxNode(p -> left);
                flag = false;
            }
        }
        p -> key = r -> key;
        if (!flag)
            deleteBST(&p->left, r->key);
        else
            deleteBST(&p->right, r->key);
    }
    return q;
}

/**
 * deleteAVL deletes deleteKey from T.
 * @param T: an AVL tree
 * @param deleteKey: a key to delete
 */
void deleteAVL(Tree *T, int deleteKey) {
  Node *deleteNode, *unbalance, *p_unbalance;
  deleteNode = deleteBST(T, deleteKey);
  unbalance = nullptr;
  p_unbalance = nullptr;
  updateBF(T, deleteNode, &unbalance, &p_unbalance);

  int diff, ubdiffLeft, ubdiffRight;

  if(unbalance == nullptr) diff = 0;
  else diff = unbalance -> bf;

  if(diff > 1) {
    ubdiffLeft = unbalance -> left -> bf;

    if(ubdiffLeft > 0) {
      cout << "LL";
      rotateLL(T, unbalance, p_unbalance);
    }
    else {
      cout << "LR";
      rotateLR(T, unbalance, p_unbalance);
    }
  }

  else if(diff < -1) {
    ubdiffRight = unbalance -> right -> bf;

    if(ubdiffRight > 0) {
      cout << "RL";
      rotateRL(T, unbalance, p_unbalance);
    }
    else {
      cout << "RR";
      rotateRR(T, unbalance, p_unbalance);
    }
  }
  else cout << "NO";
}


/**
 * inorderAVL implements inorder traversal in T.
 * @param T: an AVL tree
 */
void inorderAVL(Tree T) {
  /* write your code here */
  if (T != nullptr) {
        inorderAVL(T -> left);
        cout << T -> key << " ";
        inorderAVL(T -> right);
    }
  
}

int main() {
  /* Do not modify the code below */

  int testcase[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };

  Tree T = nullptr;

  // insertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // deletion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  T = nullptr;

  // reinsertion
  for (int i=0; i<20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

  // redeletion
  for (int i=19; 0<=i; i--) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
}
