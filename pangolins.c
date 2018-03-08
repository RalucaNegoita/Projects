#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the type of node that the tree contains
typedef struct node {
  char *object;         // a string declaration to hold an object-name (which may be NULL)
  char *question;       // a string declaration to hold a question (which may be NULL)
  struct node *yes_ptr; // only NULL for objects
  struct node *no_ptr;  // only NULL for objects
}node;


// Prints a node
// If the pointer doesnt contain a node, it's null
// Else the pointer points to either an object or a question
// In either case it prints it out
void nodePrint(struct node *info)
{
  if(info == NULL)
    printf("It's null");
  else if (info->object == NULL)
    printf("Q: %s\n", info->question);
   else
    printf(" %s\n", info->object);
}//nodePrint


  FILE *file2;

// Pointer ptr points to the root in the beginning
// Then it goes down on the tree 
void treePrint(struct node *ptr)
{ 

  if (ptr != NULL)
  {
    //is a question
    if(ptr->object == NULL)
    {
    // now print its children, left-to-right:
    fprintf(file2, "Question: %s",ptr->question);
    //fprintf(file2,"Yes:\n");
    treePrint(ptr->yes_ptr);
    //fprintf(file2,"No:\n");
    treePrint(ptr->no_ptr);
    }
    else 
    fprintf(file2,"Object: %s",ptr->object);
  }
 
}//treePrint
 
FILE *file;

struct node* treeRead()
{ 
  // first line from stdin
  char *input = malloc(250 *sizeof(char));
  struct node *ptr;

  if(fgets(input, 250, file) == NULL)
    return NULL;
  else
  {
    ptr = malloc(sizeof(struct node));
    if( strstr(input, "Question: ") != NULL )
    { 
      ptr->object = NULL;
     //fill ptr with the question from the input line
      ptr->question = input + 10;

      ///now read the yes and no subtrees:
      ptr->yes_ptr = treeRead();
      ptr->no_ptr = treeRead();

      
    }
    else if(strstr(input, "Object: ") != NULL )
    {
      ptr->object = input + 8;
      ptr->question = ptr->yes_ptr = ptr->no_ptr= NULL;
     
    }
    
  }  
  return ptr;
}//treeRead

int main(int argc, char **argv)
{
  struct node *root  = malloc(sizeof(struct node));

  
  // root node
  root->object = "a pangolin";//"a pangolin";
  root->question = NULL;
  root->yes_ptr = NULL;
  root->no_ptr = NULL;

  
  int finished = 0;
  struct node *current_node = root;
  char YNanswer[6];
  char question[50];
  char objectAnswer[10];
  int pos;


  printf("Do you want to load the game?\n\n");
  fgets(YNanswer, 6, stdin);
  pos = strlen(YNanswer) -1;
  YNanswer[pos] = '\0';

  if(strcmp(YNanswer,"yes") == 0)
  {
    file = fopen("pangolins.txt", "r");
    root = treeRead(file);
  }
  current_node = root;

  printf("/n/nLets start the game\n\n");


  while(!finished)
  {
    // this node is an object
    if(current_node->question == NULL) // if question is null it means answer
    { 
      printf("Is it %s ? \n", current_node->object);
     
      fgets(YNanswer, 6, stdin);
      pos = strlen(YNanswer) -1;
      YNanswer[pos] = '\0';

      if(strcmp(YNanswer,"yes") == 0)
        printf("I win!!\n");

      else // here i may add a new node
      { 
        //ask for new object-name
        printf("Oh. Well you win then -- What were you thinking of?\n");
        fgets(objectAnswer, 30, stdin);

        ////ask for new question
        printf("Please give me a question about %s so I can tell the difference between %s and %s\n", objectAnswer, objectAnswer, current_node->object);
        fgets(question, 50, stdin);

        printf("What is the answer for %s?\n", objectAnswer);
        fgets(YNanswer, 6, stdin);
        pos = strlen(YNanswer) -1;
        YNanswer[pos] = '\0';

        current_node->question = strdup(question);
       
        current_node->no_ptr = malloc(sizeof(struct node));
        current_node->yes_ptr= malloc(sizeof(struct node));

        if(strcmp(YNanswer,"yes") == 0)
        { 
          current_node->yes_ptr->object = strdup(objectAnswer);
          current_node->no_ptr->object = current_node->object; 
        }      
        else
        {
          current_node->no_ptr->object = strdup(objectAnswer); 
          current_node->yes_ptr->object = current_node->object;
        }

        current_node->object = NULL;
      }  
      printf("Do you want to play again?\n");
      fgets(YNanswer, 6, stdin);
      pos = strlen(YNanswer) - 1;
      YNanswer[pos] = '\0';

      if (strcmp(YNanswer,"no") == 0)
      {
        finished = 1;
      }
      else
      { 
        
        current_node = root;
      }       
    } 

     else // it is an question
    { 
      printf("%s\n", current_node->question );
      fgets(YNanswer, 6, stdin);
      pos = strlen(YNanswer) -1;
      YNanswer[pos] = '\0';
     

      if(strcmp(YNanswer,"yes") == 0)
      {
        current_node = current_node->yes_ptr;
      }
      else
      {
        current_node = current_node->no_ptr;
      }
    }

  }//while

  file2 = fopen("pangolins.txt", "w");
  treePrint(root);
  fclose(file2);

  //free the memory in part 4 freeMem(root)

  
  
}
