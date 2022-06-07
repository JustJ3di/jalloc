#include "jalloc.h"

#include <stdio.h>

typedef struct nodo{

    struct nodo *next_node;
    int value;

}Nodo;



void push(Nodo **head, int value){

    Nodo *new_nodo = malloc(sizeof(Nodo));
    assert(new_nodo != NULL);
    new_nodo->value = value;
    new_nodo->next_node = *head;
    *head = new_nodo;
    
}

void print(Nodo **head){

    Nodo * curr = *head;

    while (curr)
    {
        printf("%d\n", curr->value);
        curr = curr->next_node;
    }
    


}

void delete_list(Nodo **head){

    Nodo *curr = *head;
    Nodo *tmp = curr;

    while (curr)
    {
        curr = tmp->next_node;
        free(tmp);
        tmp = curr;
    }
    
}

int find(Nodo **head, int value){

    Nodo * curr = *head;

    while (curr)
    {
        if (curr->value == value)
            return value;
        curr = curr->next_node;
    }
    
    return -1;

}



int main(int argc, char const *argv[])
{


    Nodo *head = NULL;
    printf("%ld\n",sizeof(Nodo));

    
    for (size_t i = 0; i < 300; i++)
    {
        push(&head , i*10);
    }
    

    print(&head);

    int trovato = find(&head, 30);

    printf("%d\n", trovato);

    delete_list(&head);


    
    return 0;
}
