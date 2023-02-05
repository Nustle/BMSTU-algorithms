#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define INSERTLEN 100
#define ll long long

typedef struct Tree Tree;
struct Tree {
    ll k, count;
    char *v;
    struct Tree *parent;
    struct Tree *left;
    struct Tree *right;
};

Tree *InitBinaryTree() {
    return NULL;
}

ll EmptyTree(Tree *T) {
    ll isEmpty =  (T == NULL) ? 1 : 0;
    return isEmpty;
}

Tree *Minimum(Tree *T)
{
    if (EmptyTree(T)) {
        return NULL;
    }
    Tree *X;
    for (X=T; X->left; X = X->left);
    return X;
}

Tree *Succ(Tree *X)
{
    if (X->right) {
        return Minimum(X->right);
    }
    Tree *Y;
    for (Y=X->parent; !(Y==NULL || (X != Y->right)); Y = Y->parent) {
        X = Y;
    }
    return Y;
}

Tree *Descend(Tree *T, ll k)
{
    Tree *X;
    ll i=0;
    for (X=T; !(X==NULL || (X->k == k)); ++i) {
        if (k >= X->k) {
            X = X->right;
        }
        else {
            X = X->left;
        }
    }
    return X;
}

char *Lookup(Tree *T, ll k) {
    Tree *X = Descend(T, k);
    return X->v;
}

Tree *Insert(Tree *T, ll k, char *v) {
    Tree *Y;
    Y = malloc(sizeof(Tree));
    Y->count = 0;
    Y->k = k;
    Y->v = malloc(INSERTLEN*sizeof(char));
    strcpy(Y->v, v);
    Y->parent = Y->right = Y->left = NULL;
    if (T) {
        Tree *X = T;
        ++X->count;
        for (;;) {
            if (k >= X->k) {
                if (!X->right) {
                    X->right = Y;
                    Y->parent = X;
                    break;
                }
                X = X->right;
                ++X->count;
            } else {
                if (!X->left) {
                    X->left = Y;
                    Y->parent = X;
                    break;
                }
                X = X->left;
                ++X->count;
            }
        }
    } else {
        T = Y;
    }
    return T;
}

Tree *ReplaceNode (Tree *T, Tree *X, Tree *Y) {
    if (X != T) {
        Tree *P = X->parent;
        if (Y) {
            Y->parent = P;
        }
        if (P->left != X) {
            P->right = Y;
        } else {
            P->left = Y;
        }
    } else {
        T = Y;
        if (Y) {
            Y->parent = NULL;
        }
    }
    return T;
}

Tree *Delete(Tree *T, ll k) {
    Tree *X = Descend(T, k);
    if (!(X->right || X->left)) {
        Tree *Z;
        for (Z=X; Z != T; Z = Z->parent, --Z->count);
        T = ReplaceNode(T, X, NULL);
    } else if (!X->right) {
        Tree *Z;
        for (Z=X; Z != T; Z = Z->parent, --Z->count);
        T = ReplaceNode(T, X, X->left);
    } else if (!X->left) {
        Tree *Z;
        for (Z=X; Z != T; Z = Z->parent, --Z->count);
        T = ReplaceNode(T, X, X->right);
    } else {
        Tree *Y = Succ(X);
        Y->count = X->count-1;
        Tree *Z;
        for (Z=Y; Z != T; Z = Z->parent, --Z->count);
        T = ReplaceNode(T, Y, Y->right);
        X->left->parent = Y;
        Y->left = X->left;
        if (X->right) {
            X->right->parent = Y;
        }
        Y->right = X->right;
        T = ReplaceNode(T, X, Y);
    }
    free(X->v);
    free(X);
    return T;
}

void Drop(Tree *T) {
    if (!EmptyTree(T)) {
        Drop(T->left);
        Drop(T->right);
        free(T->v);
        free(T);
    }
}

char *SearchRank(Tree *T, ll n) {
    ll temp = (T->left == NULL) ? 0 : (T->left->count + 1);
    if (n != temp) {
        return (n <= temp ? SearchRank(T->left, n) : SearchRank(T->right, n - temp - 1));
    } else {
        return T->v;
    }
}

int main() 
{
    Tree *T = InitBinaryTree();
    char b[6];
    char value[10];
    ll k;
    scanf("%s", b);
    while (strcmp(b, "END") != 0) {
        if (strcmp(b, "INSERT") == 0) {
            scanf(" %lld %s", &k, value);
            T = Insert(T, k, value);
        } else if (strcmp(b, "LOOKUP") == 0) {
            scanf(" %lld", &k);
            char *res = Lookup(T, k);
            printf("%s\n", res);
        } else if (strcmp(b, "DELETE") == 0) {
            scanf(" %lld", &k);
            T = Delete(T, k);
        } else if (strcmp(b, "SEARCH") == 0) {
            scanf(" %lld", &k);
            char *res = SearchRank(T, k);
            printf("%s\n", res);
        }
        scanf("%s", b);
    }
    Drop(T);
    return 0;
}
