#include "binary_trees.h"
#include <limits.h>

/**
 * count_nodes - Counts the total nodes in a binary tree
 * @tree: Pointer to the root node
 * Return: Number of nodes
 */
static size_t count_nodes(const binary_tree_t *tree)
{
	if (!tree)
		return (0);
	return (1 + count_nodes(tree->left) + count_nodes(tree->right));
}

/**
 * is_complete - Checks if a binary tree is complete
 * @tree: Pointer to the root node
 * @index: Index of current node
 * @node_count: Total number of nodes
 * Return: 1 if complete, 0 otherwise
 */
static int is_complete(const binary_tree_t *tree, size_t index, size_t node_count)
{
	if (!tree)
		return (1);
	if (index >= node_count)
		return (0);
	return (is_complete(tree->left, 2 * index + 1, node_count) &&
		is_complete(tree->right, 2 * index + 2, node_count));
}

/**
 * is_max_heap - Checks Max Heap property recursively
 * @tree: Pointer to root node
 * Return: 1 if valid Max Heap, 0 otherwise
 */
static int is_max_heap(const binary_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->left && tree->n < tree->left->n)
		return (0);
	if (tree->right && tree->n < tree->right->n)
		return (0);

	return (is_max_heap(tree->left) && is_max_heap(tree->right));
}

/**
 * binary_tree_is_heap - Checks if a binary tree is a valid Max Binary Heap
 * @tree: Pointer to the root node
 * Return: 1 if valid Max Binary Heap, 0 otherwise
 */
int binary_tree_is_heap(const binary_tree_t *tree)
{
	size_t nodes;

	if (!tree)
		return (0);

	nodes = count_nodes(tree);

	if (!is_complete(tree, 0, nodes))
		return (0);

	if (!is_max_heap(tree))
		return (0);

	return (1);
}
