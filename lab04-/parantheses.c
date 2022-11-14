#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;
#include "Stack.h"

int isBalanced(const char *str, int length){

  /* TODO: Cerinta 3
   * Implementation must use a stack.
   * Do NOT forget to deallocate the memory you use.
   */
  Stack *stiva = malloc(sizeof(Stack));
  stiva->head = NULL;
  stiva->size = 0;
  for(int i = 0; i < length; ++i) {
    if(strncmp(str,"(") == 0 || strncmp(str,"[") == 0 || strncmp(str,"{") == 0) push(stiva,*str);
    else if(strncmp(str,")") == 0 || strncmp(str,"]") == 0 || strncmp(str,"}") == 0) {
      if(stiva->head == str) pop(stiva->head);
      else if(isStackEmpty(stiva)) return 0;
      else if(strcmp(str, stiva->head) != 0) return 0; 
    }
  } 
  if(isStackEmpty(stiva)) return 1;
  else return 0;
}

int main(){
    int len;
    char buffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-parantheses.txt","r");
    if(inputFile == NULL) return 1;


    while(fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL){
      buffer[strcspn(buffer, "\r\n")] = 0;
      len = strlen(buffer);
      if(len == 0) break;

      if(isBalanced(buffer, len))
        printf("%s ---> is balanced.\n", buffer);
      else
        printf("%s ---> not balanced.\n", buffer);
    }

    fclose(inputFile);

    return 0;
}
