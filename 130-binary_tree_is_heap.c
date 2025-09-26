#include "binary_trees.h"
#include <limits.h>

/**
 * count_nodes - Counts the number of nodes in a binary tree
 * @tree: Pointer to the root node
 *
 * Return: Number of nodes
 */
static int count_nodes(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (1 + count_nodes(tree->left) + count_nodes(tree->right));
}

/**
 * is_complete - Checks if a binary tree is complete
 * @tree: Pointer to the root node
 * @index: Index of the current node
 * @node_count: Total nodes in the tree
 *
 * Return: 1 if complete, 0 otherwise
 */
static int is_complete(const binary_tree_t *tree, int index, int node_count)
{
	if (!tree)
		return (1);

	if (index >= node_count)
		return (0);

	return (is_complete(tree->left, 2 * index + 1, node_count) &&
	        is_complete(tree->right, 2 * index + 2, node_count));
}

/**
 * is_heap_util - Checks if the tree maintains max-heap property
 * @tree: Pointer to the root node
 *
 * Return: 1 if max-heap, 0 otherwise
 */
static int is_heap_util(const binary_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->left && tree->n < tree->left->n)
		return (0);

	if (tree->right && tree->n < tree->right->n)
		return (0);

	return (is_heap_util(tree->left) && is_heap_util(tree->right));
}

/**
 * binary_tree_is_heap - Checks if a binary tree is a valid Max Binary Heap
 * @tree: Pointer to the root node
 *
 * Return: 1 if valid Max Binary Heap, 0 otherwise
 */
int binary_tree_is_heap(const binary_tree_t *tree)
{
	int node_count;

	if (!tree)
		return (0);

	node_count = count_nodes(tree);

	if (!is_complete(tree, 0, node_count))
		return (0);

	return (is_heap_util(tree));
}
