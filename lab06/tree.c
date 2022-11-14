/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Tree parent, Item value) {
	// TODO 0
	(*root) = malloc(sizeof(TreeNode));
	(*root)->value = value;
	(*root)->left = NULL;
	(*root)->right = NULL;
	(*root)->parent = parent;
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	// TODO 1
	if(root == NULL){
		root = createTree(root, value);
		return root;
	}else if(root->value == value) {
		return root;
	}else {
		if(root->value > value) { 
			if(root->left == NULL) {
				init(&root->left, root, value);
				return root;
			}else {
				root->left = insert(root->left, value);
				return root;
			}
		}else if(root->value < value) {
			if(root->right == NULL){
				init(&root->right, root, value);
				return root;
			}else {
				root->right = insert(root->right, value);
				return root;
			}
		}
	}
}


/*
*	Funcție care verifică dacă un arbore este vid sau nu
*		- întoarce 1 dacă arborele este vid
*		- întoarce 0 dacă arborele nu este vid
*/
int isEmpty(Tree root) {
	if(root == NULL) return 1;
	return 0;
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	if(tree == NULL) return 0;
	else if(tree -> value == value) return 1;
	else if(tree -> value > value) return contains(tree -> left, value);
	else return contains(tree -> right, value);
	return 0;
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree minimum(Tree tree) {
	// TODO 4.1
	if(tree != NULL) {
		while(tree -> left != NULL) {
			tree = tree -> left;
		}
		return tree;
	}
	return NULL;
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree maximum(Tree tree) {
	// TODO 4.2
	if(tree != NULL) {
		while(tree -> right != NULL) {
			tree = tree -> right;
		}
		return tree;
	}
	return NULL;
}

/*
*	Funcție care determină succesorul în inordine pentru nodul care conține
* valoarea value.
*/

Tree BSTSearch(Tree temp, Item value){
	if(temp == NULL){
		return NULL;
	}else if(temp->value == value){
		return temp;
	}else if(value < temp->value){
		return BSTSearch(temp->left, value);
	}else if(value > temp->value){
		return BSTSearch(temp->right, value);
	}
}

Tree successor(Tree root, Item value){
	Tree nod;
	if(root == NULL || maximum(root)->value == value){
		return NULL;
	}
    nod = BSTSearch(root, value);
	
	if(nod->right != NULL){
		return minimum(nod->right);
	}
	else {
		while(nod->parent->left != nod) {
			nod = nod->parent;
		}
		return nod->parent;
	}
	// TODO 5
	
}

/*
*	Funcție care determină predecesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree predecessor(Tree root, Item value) {
	// TODO 6
	Tree nod;
	if(root == NULL || minimum(root)->value == value){
		return NULL;
	}
    nod = BSTSearch(root, value);
	
	if(nod->left != NULL){
		return maximum(nod->left);
	}
	else {
		while(nod->parent->right != nod) {
			nod = nod->parent;
		}
		return nod->parent;
	}
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void destroyTree(Tree *root) {
	// TODO
	if(*(root) == NULL){
		return;
	}
	destroyTree(&((*root)->left));
	destroyTree(&((*root)->right));
	free(*(root));
	(*root) = NULL;
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
	// TODO 7
	Tree tmp;
	if(root == NULL){
		return root;
	}
	if(root->value > value){
		root->left = delete(root->left, value);
	}else if(root->value < value){
		root->right = delete(root->right, value);
	}else{
		if(root->left != NULL && root->right != NULL){
			tmp = minimum(root->right);
			root->value = tmp->value;
			root->right = delete(root->right, tmp->value);
		}else{
			tmp = root;
			if(root->left != NULL){
				root = root->right;
			}else{
				root= root->right;
			}
			free(tmp);
		}
	}
	return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/
Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
	// TODO 8
	return NULL;
}
