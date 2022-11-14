#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TreeMap.h"

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))

/* Creeaza un arbore cu o serie de metode asociate
 *
 * return: arborele creat
 */
TTree *createTree(void *(*createElement)(void *),
				  void (*destroyElement)(void *),
				  void *(*createInfo)(void *),
				  void (*destroyInfo)(void *),
				  int compare(void *, void *))
{
	TTree *tree = (TTree *)malloc(sizeof(TTree));
	tree->compare = compare;
	tree->createElement = createElement;
	tree->destroyElement = destroyElement;
	tree->createInfo = createInfo;
	tree->destroyInfo = destroyInfo;
	tree->size = 0;
	tree->root = NULL;
	return tree;
}

/* Verifica daca un arbore este gol (vid)
 * 		1 - daca arborele este gol
 * 		0 - in caz contrar
 */
int isEmpty(TTree *tree)
{
	if (tree->root == NULL)
		return 1;
	return 0;
}

/* Cauta un anumit element in interiorul unui arbore
 *
 * tree: structura cu metodele asociate arborelui
 *   !folosit pentru a putea compara elementul curent cu cel cautat
 *
 * x: radacina arborelui curent (in care se face cautarea)
 * elem: elementul ce trebuie cautat
 */
TreeNode *search(TTree *tree, TreeNode *x, void *elem)
{
	if (x == NULL || tree->compare(x->elem, elem) == 0)
		return x;
	else if (tree->compare(x->elem, elem) == -1)
		return search(tree, x->right, elem);
	else
		return search(tree, x->left, elem);
}

/* Gaseste nodul cu elementul minim dintr-un arbore
 * avand radacina in x
 */
TreeNode *minimum(TreeNode *x)
{
	if (x != NULL)
	{
		while (x->left != NULL)
		{
			x = x->left;
		}
		return x;
	}
	return NULL;
}

/* Gaseste nodul cu elementul maxim dintr-un arbore
 * avand radacina in x
 */
TreeNode *maximum(TreeNode *x)
{
	if (x != NULL)
	{
		while (x->right != NULL)
		{
			x = x->right;
		}
		return x;
	}
	return NULL;
}

/* Functie pentru gasirea succesorului unui nod
 * (succesorul in inordine)
 */
TreeNode *successor(TreeNode *x)
{
	TreeNode *root = x;
	while (root->parent != NULL)
	{
		root = root->parent;
	}
	if (x == NULL || maximum(root)->elem == x->elem)
		return NULL;
	if (x->right != NULL)
	{
		return minimum(x->right);
	}
	else
	{
		while (x->parent->left != x)
		{
			x = x->parent;
		}
		return x->parent;
	}
}

/* Functie pentru gasirea predecesorului unui nod
 * (predecesorul in inordine)
 */
TreeNode *predecessor(TreeNode *x)
{
	TreeNode *root = x;
	while (root->parent != NULL)
	{
		root = root->parent;
	}
	if (x == NULL || minimum(root)->elem == x->elem)
		return NULL;
	if (x->left != NULL)
	{
		return maximum(x->left);
	}
	else
	{
		while (x->parent->right != x)
		{
			x = x->parent;
		}
		return x->parent;
	}
}

/* Actualizeaza inaltimea unui nod din arbore
 */
void updateHeight(TreeNode *x)
{

	int leftHeight = 0;
	int rightHeight = 0;

	if (x != NULL)
	{
		if (x->left != NULL)
			leftHeight = x->left->height;
		if (x->right != NULL)
			rightHeight = x->right->height;
		x->height = MAX(leftHeight, rightHeight) + 1;
	}
}

/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la stanga
 * a subarborelui care are varful in x
 *
 *   (x)	 Rotatie    (y)
 *	 / \     stanga     / \
 *  a  (y)    ---->   (x)  c
 *	   / \			  / \
 *    b   c          a   b
 */
void avlRotateLeft(TTree *tree, TreeNode *x)
{
	if (tree == NULL || x == NULL)
		return;
	TreeNode *y = x->right;
	x->right = y->left;
	if (y->left != NULL)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL)
	{
		tree->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
	updateHeight(y);
	updateHeight(x);
}

/* Functie ce primeste adresa unui arbore si
 * a unui nod x si realizeaza o rotatie la dreapta
 * a subarborelui care are varful in y
 *
 *     (y)	 Rotatie    (x)
 *	   / \   dreapta    / \
 *   (x)  c   ---->    a  (y)
 *	 / \			      / \
 *  a   b                b   c
 */
void avlRotateRight(TTree *tree, TreeNode *y)
{
	if (tree == NULL || y == NULL)
		return;
	TreeNode *x = y->left;
	y->left = x->right;
	if (x->right != NULL)
	{
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent == NULL)
	{
		tree->root = x;
	}
	else if (y == y->parent->right)
	{
		y->parent->right = x;
	}
	else
	{
		y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
	updateHeight(y);
	updateHeight(x);
}

/* Calculeaza factorul de echilibrare pentru un nod x
 * (AVL balance factor)
 */
int avlGetBalance(TreeNode *x)
{
	if (x == NULL || x->left == NULL || x->right == NULL)
		return 0;
	return x->left->height - x->right->height;
}

/* Functie pentru reechilibrarea unui arbore AVL
 * in urma unei inserari prin rotatii simple sau duble
 * si recalcularea inaltimii fiecarui nod intalnit parcurgand
 * arborele de jos in sus, spre radacina
 *
 */
// void avlFixUp(TTree *tree, TreeNode *y)
// {
// 	while (y != tree->root)
// 	{
// 		updateHeight(y);
// 		int balance = avlGetBalance(y);
// 		if (balance > 1 && tree->compare(y->elem, y->left->elem) == -1)
// 		{
// 			avlRotateRight(tree, y);
// 		}
// 		if (balance < -1 && tree->compare(y->elem, y->right->elem) == 1)
// 		{
// 			avlRotateLeft(tree, y);
// 		}
// 		if (balance > 1 && tree->compare(y->elem, y->left->elem) == 1)
// 		{
// 			avlRotateLeft(tree, y->left);
// 			avlRotateRight(tree, y);
// 		}
// 		if (balance < -1 && tree->compare(y->elem, y->right->elem) == -1)
// 		{
// 			avlRotateRight(tree, y->right);
// 			avlRotateLeft(tree, y);
// 		}
// 		y = y->parent;
// 	}
// }

void avlFixUp(TTree *tree, TreeNode *y)
{
	while (y != tree->root)
	{
		updateHeight(tree->root);
		int bf = avlGetBalance(tree->root);
		// left-left
		if (bf > 1 && y->elem < tree->root->left->elem)
		{
			avlRotateRight(tree, tree->root);
		}
		// right-right
		if (bf < -1 && y->elem > tree->root->right->elem)
		{
			avlRotateLeft(tree, tree->root);
		}
		// left-right
		if (bf > 1 && y->elem > tree->root->left->elem)
		{
			avlRotateLeft(tree, tree->root->left);
			avlRotateRight(tree, tree->root);
		}
		// right-left
		if (bf < -1 && y->elem < tree->root->right->elem)
		{
			avlRotateRight(tree, tree->root->right);
			avlRotateLeft(tree, tree->root);
		}
		y = y->parent;
	}
}
/* Functie pentru crearea unui nod
 *
 * value: valoarea/cheia din cadrul arborelui
 * info: informatia/valoarea din dictionar
 */
TreeNode *createTreeNode(TTree *tree, void *value, void *info)
{

	if (tree == NULL)
		return NULL;

	// Alocarea memoriei
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

	// Setarea elementului si a informatiei
	node->elem = tree->createElement(value);
	node->info = tree->createInfo(info);

	// Initializarea legaturilor din cadrul arborelui
	node->parent = node->right = node->left = NULL;

	// Initializarea legaturilor din cadrul listei dublu inlantuite
	node->next = node->prev = node->end = NULL;

	// Inaltimea unui nod nou este 1
	// Inaltimea lui NULL este 0
	node->height = 1;

	return node;
}

/* Inserarea unul nou nod in cadrul multi-dictionarului
 * ! In urma adaugarii arborele trebuie sa fie echilibrat
 *
 */
void insert(TTree *tree, void *elem, void *info)
{
	// printf("TEST!\n");
	// if (tree->root == NULL)
	// {
	// 	TreeNode *node = createTreeNode(tree, elem, info);
	// 	tree->root = node;
	// 	return;
	// }
	// TreeNode *y = tree->root;
	// TreeNode *x = tree->root;
	// TreeNode *z = createTreeNode(tree, elem, info);
	// while (x != NULL)
	// {
	// 	y = x;
	// 	if (tree->compare(x->elem, elem) == 1)
	// 	{
	// 		x = x->left;
	// 	}
	// 	else if (tree->compare(x->elem, elem) == -1)
	// 	{
	// 		x = x->right;
	// 	}
	// 	return;
	// }
	// z->parent = y;
	// if ((y == tree->root) || (tree->compare(y->elem, z->elem) == 1))
	// {
	// 	y->left = z;
	// }
	// else
	// {
	// 	y->right = z;
	// }
	// tree->size++;
	// avlFixUp(tree, y);
}

/* Eliminarea unui nod dintr-un arbore
 *
 * ! tree trebuie folosit pentru eliberarea
 *   campurilor `elem` si `info`
 * */
void destroyTreeNode(TTree *tree, TreeNode *node)
{

	// Verificarea argumentelor functiei
	if (tree == NULL || node == NULL)
		return;

	// Folosirea metodelor arborelui
	// pentru de-alocarea campurilor nodului
	tree->destroyElement(node->elem);
	tree->destroyInfo(node->info);

	// Eliberarea memoriei nodului
	free(node);
}

/* Eliminarea unui nod din arbore
 *
 * elem: cheia nodului ce trebuie sters
 * 	! In cazul in care exista chei duplicate
 *	  se va sterge ultimul nod din lista de duplicate
 */
void delete (TTree *tree, void *elem)
{
}

/* Eliberarea memoriei unui arbore
 */
void destroyTree(TTree *tree)
{

	/* Se poate folosi lista dublu intalntuita
	 * pentru eliberarea memoriei
	 */
	if (tree == NULL || tree->root == NULL)
		return;
}