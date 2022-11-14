#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *Key;
typedef int Value;
typedef long (*HashFunction)(Key, long);

typedef struct Element
{
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable
{
  Element **elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f)
{
  // Cerinta 1
  *h = malloc(sizeof(HashTable));
  (*h)->size = size;
  (*h)->hashFunction = f;
  (*h)->elements = calloc(size, sizeof(void *));
}

int exists(HashTable *hashTable, Key key)
{
  int i = hashTable->hashFunction(key, hashTable->size);
  Element *aux = hashTable->elements[i];
  while (aux != NULL)
  {
    if (strcmp(key, aux->key) == 0)
      return 1;
    aux = aux->next;
  }
  return 0;
}

Value get(HashTable *hashTable, Key key)
{
  // Cerinta 1
  int i = hashTable->hashFunction(key, hashTable->size);
  Element *aux = hashTable->elements[i];
  while (aux != NULL)
  {
    if (strcmp(key, aux->key) == 0)
      return aux->value;
    aux = aux->next;
  }
  return 0;
}

void put(HashTable *hashTable, Key key, Value value)
{
  // Cerinta 1
  if (hashTable == NULL)
    return;
  int i = hashTable->hashFunction(key, hashTable->size);
  Element *aux = hashTable->elements[i];
  while (aux != NULL)
  {
    if (strcmp(key, aux->key) == 0)
      aux->value = value;
    return;
    aux = aux->next;
  }
  Element *elem = malloc(sizeof(Element));
  elem->next = hashTable->elements[i];
  hashTable->elements[i] = hashTable->elements[i]->next;
  elem->value = value;
}

void deleteKey(HashTable *hashTable, Key key)
{
  // Cerinta 1
  int i = hashTable->hashFunction(key, hashTable->size);
  Element *aux = hashTable->elements[i];
  while (aux != NULL)
  {
    if (strcmp(key, aux->key) == 0)
    {
      aux = NULL;
      free(aux);
    }
    aux = aux->next;
  }
}

void print(HashTable *hashTable)
{
  // Cerinta 1
  for (int i = 0; i < hashTable->size; i++)
  {
    printf("%d : \n", i);
    if (hashTable->elements[i])
    {
      Element *index = hashTable->elements[i];
      while (index)
      {
        printf("%s %d\n", index->key, index->value);
        index = index->next;
      }
    }
    printf("\n");
  }
}

void freeHashTable(HashTable *hashTable)
{
  // Cerinta 1
  if (hashTable == NULL)
    return;
  for (int i = 0; i < hashTable->size; i++)
  {
    if (hashTable->elements[i])
    {
      deleteKey(hashTable, hashTable->elements[i]->key);
    }
  }
  free(hashTable);
}

long hash1(Key word, long size)
{
  long h = 0;
  for (int i = 0; i < strlen(word); i++)
  {
    h = h * 17 + word[i];
  }
  return h;
}

int minimum(int x, int y)
{
  if (x <= y)
    return x;
  return y;
}

int main(int argc, char *argv[])
{
  if (argc < 4)
    return 0;

  HashTable *hashTable;
  HashTable *hashTable2;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);
  initHashTable(&hashTable2, hashSize, &hash1);

  // Cerinta 3
  int ret = fscanf(f1, "%s", word);

  while (ret != EOF)
  {
    put(hashTable, word, get(hashTable, word) + 1);
    ret = fscanf(f1, "%s", word);
  }
  print(hashTable);

  ret = fscanf(f2, "%s", word);

  print(hashTable2);

  for (int i = 0; i < hashSize; i++)
  {
    if (hashTable->elements[i])
    {
      Element *current = hashTable->elements[i];

      while (current)
      {
        if (exists(hashTable2, current->key))
        {
          put(hashTable, current->key, minimum(current->value, get(hashTable2, current->key)));
        }
        else
        {
          put(hashTable, current->key, (Value)0);
        }
        current = current->next;
      }
    }
  }

  print(hashTable);

  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}