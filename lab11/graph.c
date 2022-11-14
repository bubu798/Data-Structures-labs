#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
} TGraphL;

void alloc_list(TGraphL *G, int n)
{
	int i;
	G->nn = n;
	G->adl = (ATNode *)malloc((n + 1) * sizeof(ATNode));
	for (i = 0; i < n; i++)
		G->adl[i] = NULL;
}

void free_list(TGraphL *G)
{
	int i;
	ATNode it;
	for (i = 1; i < G->nn; i++)
	{
		it = G->adl[i];
		while (it != NULL)
		{
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
	TNode *t;
	t = (ATNode)malloc(sizeof(TNode));
	t->v = v2;
	t->c = c;
	t->next = G->adl[v1];
	G->adl[v1] = t;
	t = (ATNode)malloc(sizeof(TNode));
	t->v = v1;
	t->c = c;
	t->next = G->adl[v2];
	G->adl[v2] = t;
}

void dijkstra(TGraphL G, int s)
{
	int d[G.nn];
	MinHeapNode *u;
	ATNode aux;
	MinHeap *h = newQueue(G.nn);
	for (int i = 0; i < G.nn; ++i)
	{
		h->elem[i] = newNode(i, INT_MAX);
		h->pos[i] = i;
		d[i] = INT_MAX;
	}
	h->size = G.nn;
	SiftUp(h, s, 0);
	d[s] = 0;
	while (h->size > 0)
	{
		u = removeMin(h);
		aux = G.adl[u->v];
		while (aux != NULL)
		{
			if (isInMinHeap(h, aux->v) && d[aux->v] > d[u->v] + aux->c)
			{
				d[aux->v] = d[u->v] + aux->c;
				SiftUp(h, aux->v, d[aux->v]);
			}
			aux = aux->next;
		}
	}
	for (int i = 0; i < G.nn; ++i)
	{
		printf("%d   %d\n", i, d[i]);
	}
}

void Prim(TGraphL G)
{
	int d[G.nn];
	int p[G.nn];
	MinHeapNode *u;
	ATNode aux;
	MinHeap *h = newQueue(G.nn);
	for (int i = 0; i < G.nn; ++i)
	{
		h->elem[i] = newNode(i, INT_MAX);
		h->pos[i] = i;
		d[i] = INT_MAX;
		p[i] = -1;
	}
	h->size = G.nn;
	SiftUp(h, 0, 0);
	d[0] = 0;
	while (h->size > 0)
	{
		u = removeMin(h);
		aux = G.adl[u->v];
		while (aux != NULL)
		{
			if (isInMinHeap(h, aux->v) && d[aux->v] > aux->c)
			{
				d[aux->v] = aux->c;
				p[aux->v] = u->v;
				SiftUp(h, aux->v, d[aux->v]);
			}
			aux = aux->next;
		}
	}
	for (int i = 0; i < G.nn; ++i)
	{
		printf("%d   %d\n", i, p[i]);
	}
}

int main()
{
	int i, v1, v2, c;
	int V, E;
	TGraphL G;
	ATNode t;
	freopen("graph.in", "r", stdin);
	scanf("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i = 1; i <= E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
		insert_edge_list(&G, v1, v2, c);
	}

	for (i = 0; i < G.nn; i++)
	{
		printf("%d : ", i);
		for (t = G.adl[i]; t != NULL; t = t->next)
			printf("%d ", t->v);
		printf("\n");
	}
	dijkstra(G, 0);
	printf("\n");
	Prim(G);

	return 0;
}
