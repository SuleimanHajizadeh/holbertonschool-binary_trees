#include "binary_trees.h"
#include <stdlib.h>

/* Helper: find the minimum node in a subtree */
static avl_t *find_min(avl_t *node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

/* Forward declaration of rebalance function */
avl_t *avl_rebalance(avl_t *node);

/* Recursive removal function */
static avl_t *remove_node(avl_t *root, int value)
{
    if (!root)
        return NULL;

    if (value < root->n)
        root->left = remove_node(root->left, value);
    else if (value > root->n)
        root->right = remove_node(root->right, value);
    else
    {
        /* Node found */
        if (!root->left || !root->right)
        {
            avl_t *tmp = root->left ? root->left : root->right;
            if (!tmp)
            {
                /* No child */
                tmp = root;
                root = NULL;
            }
            else
            {
                /* One child */
                *root = *tmp; /* Copy contents */
            }
            free(tmp);
        }
        else
        {
            /* Two children: replace with in-order successor */
            avl_t *succ = find_min(root->right);
            root->n = succ->n;
            root->right = remove_node(root->right, succ->n);
        }
    }

    if (!root)
        return NULL;

    /* Rebalance this node */
    return avl_rebalance(root);
}

/* Main avl_remove function */
avl_t *avl_remove(avl_t *root, int value)
{
    return remove_node(root, value);
}
