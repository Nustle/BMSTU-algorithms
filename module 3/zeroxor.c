#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

typedef struct Unit Unit;
struct Unit
{
    Unit *parent, *l, *r;
    ll key, v;
};

typedef struct Tree Tree;
struct Tree
{
    Unit *base;
};

void clear(Unit *unit)
{
    if(unit->r) {
        clear(unit->r);
    }
    if(unit->l) {
        clear(unit->l);
    }
    free(unit);
}

Unit *Insert(Tree *tree, ll key, ll v)
{
    Unit *new_unit = (Unit *)malloc(sizeof(Unit));
    new_unit->parent = NULL;
    new_unit->l = NULL;
    new_unit->r = NULL;
    new_unit->key = key;
    new_unit->v = v;
    if(tree->base == NULL) {
        tree->base = new_unit;
        return tree->base;
    }
    Unit *unit = tree->base;
    while(1) {
        if(key >= unit->key) {
            if(unit->r == NULL) {
                unit->r = new_unit;
                new_unit->parent = unit;
                break;
            }
            unit = unit->r;
        } else {
            if(unit->l == NULL) {
                unit->l = new_unit;
                new_unit->parent = unit;
                break;
            }
            unit = unit->l;
        }
    }
    return new_unit;
}

Unit *Find(Tree *tree, ll key)
{
    Unit *unit;
    ll i=0;
    for (unit = tree->base; unit && unit->key != key; ++i) {
        if(unit->key <= key) {
            unit = unit->r;
        } else {
            unit = unit->l;
        }
    }
    return unit;
}

int main()
{
    ll n;
    Tree tree;
    tree.base = NULL;
    scanf("%lld", &n);
    ll res = 0;
    ll temp = 0;
    for(ll i = 0; i < n; i++) {
        ll x;
        scanf("%lld", &x);
        temp ^= x;
        Unit *unit = Find(&tree, temp);
        if(unit == NULL) {
            unit = Insert(&tree, temp, 0);
        }
        res += ++unit->v-(temp!=0);
    }
    printf("%lld", res);
    if(tree.base!=NULL) {
        clear(tree.base);
    }
    return 0;
}
