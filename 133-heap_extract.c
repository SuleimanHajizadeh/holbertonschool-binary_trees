#include "binary_trees.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root of the heap
 * Return: Value stored in the root node
 */
int heap_extract(heap_t **root)
{
	heap_t *node, *last;
	int value;

	if (!root || !*root)
		return (0);

	node = *root;
	value = node->n;

	if (!node->left && !node->right)
	{
		free(node);
		*root = NULL;
		return (value);
	}

	/* Find the last node to replace root */
	last = node;
	while (last->left || last->right)
	{
		if (last->right)
			last = last->right;
		else if (last->left)
			last = last->left;
	}

	/* Swap values */
	node->n = last->n;

	/* Remove last node */
	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;

	free(last);

	/* Rebalance heap */
	while (node)
	{
		heap_t *largest = node;
		heap_t *left = node->left;
		heap_t *right = node->right;

		if (left && left->n > largest->n)
			largest = left;
		if (right && right->n > largest->n)
			largest = right;
		if (largest == node)
			break;
		value = node->n;
		node->n = largest->n;
		largest->n = value;
		node = largest;
	}

	return (*root ? (*root)->n : 0);
}
