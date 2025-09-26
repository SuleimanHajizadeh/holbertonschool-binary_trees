#include "binary_trees.h"

/* ==== Forward declarations ==== */
avl_t *avl_insert_recursive(avl_t **tree, int value);
avl_t *avl_rebalance(avl_t *node);

/**
 * avl_insert - inserts a value in an AVL Tree
 * @tree: double pointer to the root node of the AVL tree
 * @value: value to store in the node
 *
 * Return: pointer to the created node, or NULL on failure
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	if (tree == NULL)
		return (NULL);

	if (*tree == NULL)
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}

	return (avl_insert_recursive(tree, value));
}

/**
 * avl_insert_recursive - helper to recursively insert and rebalance
 * @tree: double pointer to current node
 * @value: value to insert
 *
 * Return: pointer to inserted node or existing node on failure
 */
avl_t *avl_insert_recursive(avl_t **tree, int value)
{
	avl_t *node = *tree, *new_node = NULL;

	if (value < node->n)
	{
		if (node->left)
			new_node = avl_insert_recursive(&node->left, value);
		else
		{
			new_node = binary_tree_node(node, value);
			if (new_node == NULL)
				return (NULL);
			node->left = new_node;
		}
	}
	else if (value > node->n)
	{
		if (node->right)
			new_node = avl_insert_recursive(&node->right, value);
		else
		{
			new_node = binary_tree_node(node, value);
			if (new_node == NULL)
				return (NULL);
			node->right = new_node;
		}
	}
	else
		return (NULL); /* no duplicates */

	/* Rebalance tree */
	*tree = avl_rebalance(*tree);

	return (new_node);
}

/**
 * avl_rebalance - rebalances a node if it's unbalanced
 * @node: pointer to node to rebalance
 *
 * Return: new root after rotation
 */
avl_t *avl_rebalance(avl_t *node)
{
	int balance;

	if (!node)
		return (NULL);

	balance = binary_tree_balance(node);

	/* Left heavy */
	if (balance > 1)
	{
		if (binary_tree_balance(node->left) < 0) /* Left-Right case */
			node->left = binary_tree_rotate_left(node->left);
		return (binary_tree_rotate_right(node)); /* Left-Left */
	}

	/* Right heavy */
	if (balance < -1)
	{
		if (binary_tree_balance(node->right) > 0) /* Right-Left case */
			node->right = binary_tree_rotate_right(node->right);
		return (binary_tree_rotate_left(node)); /* Right-Right */
	}

	return (node); /* Already balanced */
}
