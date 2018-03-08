#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;
struct node 
{
  Key_Type key; // only data is the key itself
  tree_ptr left, right;
  int height;
  // add anything else that you need
};

struct table 
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
};


int calculate_height(tree_ptr head)
{
    if(head == NULL)
        return 0;

    return head->height;
} 


int maximum(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}


Table initialize_table(/*ignore parameter*/) 
{
    struct table* table_to_insert = malloc(sizeof(struct table));
    table_to_insert->head = NULL;
    return table_to_insert;
}


tree_ptr function_to_insert(Key_Type key, tree_ptr head){
	/* 1.  Perform the normal BST insertion */
    if (head == NULL)
    {   
        head = malloc(sizeof(struct node));       
    	head->key = strdup(key);
        head->left   = NULL;
        head->right  = NULL;
        head->height = 1;  
        return head;
    }
        
    if(strcmp(key, head->key) < 0)
        head->left = function_to_insert(key, head->left);

    else if (strcmp(key, head->key) > 0)
        head->right = function_to_insert(key,head->right);

    else 
        return head;
 
    /* 2. Update height of this ancestor node */
    head->height = 1 + maximum(calculate_height(head->left),
                           calculate_height(head->right));
    return head;
}//function_to_insert


tree_ptr rightRotate(tree_ptr head)
{
    tree_ptr new_head = head->left;
    tree_ptr auxiliar = new_head->right;
 
    // Perform rotation
    new_head->right = head;
    head->left = auxiliar;
 
    // Update heights
    head->height = maximum(calculate_height(head->left), calculate_height(head->right)) + 1;
    new_head->height = maximum(calculate_height(new_head->left), calculate_height(new_head->right)) + 1;
 
    // Return new head of the tree
    return new_head;
}

tree_ptr leftRotate(tree_ptr head)
{
    tree_ptr new_head = head->right;
    tree_ptr auxiliar = new_head->left;
 
    // Perform rotation
    new_head->left = head;
    head->right = auxiliar;
 
    // Update heights
    head->height = maximum(calculate_height(head->left), calculate_height(head->right))+1;
    new_head->height = maximum(calculate_height(new_head->left), calculate_height(new_head->right))+1;
 
    // Return new head of the tree
    return new_head;
}

int getBalance(tree_ptr head)
{
    if (head == NULL)
        return 0;
    return calculate_height(head->left) - calculate_height(head->right);
}

tree_ptr avl_function(Key_Type key, tree_ptr head)
{
	if (head == NULL)
    {   
        head = malloc(sizeof(struct node));  
    	head->key = strdup(key);
        head->left   = NULL;
        head->right  = NULL;
        head->height = 1;  
        return head;
    }
    
    printf("%s %d %d\n", key, head->height, getBalance(head));
    
    if(strcmp(key, head->key) < 0)
        head->left = avl_function(key, head->left);

    else if (strcmp(key, head->key) > 0)
        head->right = avl_function( key, head->right);
    
    else 
        return head;
 
    /* 2. Update height of this ancestor node */
    head->height = 1 + maximum(calculate_height(head->left),
                               calculate_height(head->right));


    int balance = getBalance(head);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(key, head->left->key) < 0)
        return rightRotate(head);
 
    // Right Right Case
    if (balance < -1 && strcmp(key, head->right->key) > 0)
        return leftRotate(head);
 
    // Left Right Case
    if (balance > 1 && strcmp(key, head->left->key) > 0)
    {
        head->left =  leftRotate(head->left);
        return rightRotate(head);
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(key, head->right->key) < 0)
    {
        head->right = rightRotate(head->right);
        return leftRotate(head);
    }
 
    /* return the (unchanged) HEAD pointer */
    return head;

}

Table insert(Key_Type key, Table table_to_insert) 
{   
    if(mode == 1)
         table_to_insert->head = avl_function(key, table_to_insert->head);
     else
	
	     table_to_insert->head = function_to_insert(key, table_to_insert->head);


    return table_to_insert;
}

Boolean find_function(Key_Type key, tree_ptr head)
{   
    if(head == NULL)
        return FALSE;
    if(strcmp(key, head->key) == 0)
        return TRUE;
    else if(strcmp(key, head->key) > 0)
            return find_function(key, head->right);
        else
            return find_function(key, head->left);
}


Boolean find(Key_Type key, Table table_to_insert) 
{
    return find_function(key, table_to_insert->head);
}

void print_pre_order(tree_ptr head)
{
    if(head != NULL)
    {
        printf("%s %d \n", head->key, head->height);//, getBalance(head));
        print_pre_order(head->left);
        print_pre_order(head->right);
    }
}

void print_table(Table table_to_insert) 
{   
    if(table_to_insert->head != NULL)
       print_pre_order(table_to_insert->head);
}

void print_stats (Table table_to_insert) 
{   
    printf("%s\n", table_to_insert->head->key);
    printf("balance : %d\n", getBalance(table_to_insert->head));
    print_table(table_to_insert);
    printf("depth of the tree: %d\n", calculate_height(table_to_insert->head));

}
