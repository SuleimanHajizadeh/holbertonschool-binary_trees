#include "binary_trees.h"
#include <stddef.h>

/**
 * array_to_avl - builds an AVL tree from an array
 * @array: pointer to array of integers
 * @size: size of the array
 *
 * Return: pointer to root of AVL tree
 */
avl_t *array_to_avl(int *array, size_t size)
{
	avl_t *root;
	size_t i;

	if (!array || size == 0)
		return (NULL);

	root = NULL;

	for (i = 0; i < size; i++)
		avl_insert(&root, array[i]);

	return (root);
}
