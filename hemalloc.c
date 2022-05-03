#include "hemalloc.h"
#include <stdio.h>

typedef struct ops
{
    
    int value;
    
    struct ops *next;

}Ops;


int main()
{
    int *p = malloc(sizeof(int)*100);
    assert(p!=NULL);

    for (size_t i = 0; i < 20; i++)
    {
        *(p+i) = i;
    }
    
    for (size_t i = 0; i < 20; i++)
    {
        printf("%d\n",p[i]);
    }
    
    

    free(p);

    Ops *new = malloc(sizeof(Ops)*20);

    void nssew(){
        return 1;
    }
    
    for (size_t i = 0; i < 20; i++)
    {
        new[i].value = i;
        if (i == 0)
            new[i].next  = NULL;
        else
            new[i].next = &new[i-1];
        
    }
    
    

    Ops *current = &new[19];

    while(current){
        printf("%d\n",current->value);
        current  = current->next;
    }
    
    free(new);

    return 0;
}
