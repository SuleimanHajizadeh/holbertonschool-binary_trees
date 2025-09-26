#include "binary_trees.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * heap_size - Counts the number of nodes in a heap
 * @root: Pointer to the root node
 * Return: Number of nodes
 */
size_t heap_size(heap_t *root)
{
	size_t left_size, right_size;

	if (!root)
		return (0);

	left_size = heap_size(root->left);
	right_size = heap_size(root->right);

	return (1 + left_size + right_size);
}

/**
 * heap_last_node - Find the last node in the heap
 * @root: Pointer to the root node
 * @index: Current node index in level-order traversal
 * @size: Total number of nodes in heap
 * Return: Pointer to the last node
 */
heap_t *heap_last_node(heap_t *root, size_t index, size_t size)
{
	if (!root)
		return (NULL);

	if (index == size)
		return (root);

	/* Level-order traversal: left child index = 2*index, right = 2*index+1 */
	{
		heap_t *left, *right;

		left = heap_last_node(root->left, 2 * index, size);
		if (left)
			return (left);

		right = heap_last_node(root->right, 2 * index + 1, size);
		return (right);
	}
}

/**
 * swap_nodes - Swap values of two heap nodes
 * @a: First node
 * @b: Second node
 */
void swap_nodes(heap_t *a, heap_t *b)
{
	int temp = a->n;
	a->n = b->n;
	b->n = temp;
}

/**
 * heapify_down - Restores Max Heap property
 * @node: Node to heapify down
 */
void heapify_down(heap_t *node)
{
	heap_t *largest = node;

	if (node->left && node->left->n > largest->n)
		largest = node->left;

	if (node->right && node->right->n > largest->n)
		largest = node->right;

	if (largest != node)
	{
		swap_nodes(node, largest);
		heapify_down(largest);
	}
}

/**
 * heap_extract - Extract the root node of a Max Binary Heap
 * @root: Pointer to pointer to root node
 * Return: Value stored in extracted root
 */
int heap_extract(heap_t **root)
{
	heap_t *last, *tmp;
	int value, size;

	if (!root || !*root)
		return (0);

	value = (*root)->n;
	size = (int)heap_size(*root);

	if (size == 1)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	last = heap_last_node(*root, 1, size);

	/* Move last node value to root */
	(*root)->n = last->n;

	/* Remove last node from tree */
	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;

	free(last);

	heapify_down(*root);

	return (value);
}
