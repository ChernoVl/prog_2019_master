#include <stdio.h>
#include <stdlib.h>

struct BinaryTree
{
	int value;
	struct BinaryTree* left;
	struct BinaryTree* right;
};

void addNode(struct BinaryTree **root, int value);
void dell_el(struct BinaryTree **Tree_arr, int *size, int number_del);
void freeBinaryTree(struct BinaryTree *root);
int  binary_trees_comparison(struct BinaryTree *root1, struct BinaryTree *root2);

int main(void)
{
	int value;
	int n, k;
	struct BinaryTree **Tree_arr = NULL;
	scanf("%d", &n);
	scanf("%d", &k);
	if (n >= 1 && n <= 50 && k >= 1 && k <= 20)
	{
		Tree_arr = (struct BinaryTree**)calloc(n, sizeof(struct BinaryTree*));
		for (int i = 0; i < n; i++)
		{
			Tree_arr[i] = NULL;
			for (int j = 0; j < k; j++)
			{
				scanf("%d", &value);
				addNode(&Tree_arr[i], value);
			}
		}
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (binary_trees_comparison(Tree_arr[i], Tree_arr[j]) == 1)//1 -  
				{
					dell_el(Tree_arr, &n, j--);
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			freeBinaryTree(Tree_arr[i]);
		}
		free(Tree_arr);
		printf("%d\n", n);
	}
	return 0;
}

void addNode(struct BinaryTree **root, int value)
{
	if (*root == NULL)
	{
		*root = (struct BinaryTree *)calloc(1, sizeof(struct BinaryTree));
		(*root)->value = value;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return;
	}
	if (value > (*root)->value)
	{
		addNode(&(*root)->right, value);
	}
	else
	{
		addNode(&(*root)->left, value);
	}
}

void dell_el(struct BinaryTree **Tree_arr, int *size, int number_del)
{
	if (Tree_arr)
	{
		freeBinaryTree(Tree_arr[number_del]);///
		Tree_arr[number_del] = NULL;
		if (number_del >= 0 && number_del < *size)
		{
			(*size)--;
		}
		for (int i = number_del; i < *size; i++)
		{
			Tree_arr[i] = Tree_arr[i + 1];
		}
	}
}

void freeBinaryTree(struct BinaryTree *root)
{
	if (root == NULL)
	{
		return;
	}
	freeBinaryTree(root->left);
	root->left = NULL;
	freeBinaryTree(root->right);
	root->right = NULL;
	if (root->left == NULL && root->right == NULL)
	{
		free(root);
	}
}

int  binary_trees_comparison(struct BinaryTree *root1, struct BinaryTree *root2)
{
	if ((root1 == NULL && root2 == NULL))
	{
		return 1;
	}
	if ((root1 == NULL && root2 != NULL) || (root1 != NULL && root2 == NULL))
	{
		return -1;
	}
	if ((binary_trees_comparison(root1->left, root2->left) == -1)
		|| (binary_trees_comparison(root1->right, root2->right) == -1))
	{
		return -1;
	}
	return 1;
}
