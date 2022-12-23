
# include "../../include/minishell.h"


void dictionary_show(t_dictionary dic) 
{
    _t_dictionary *temp = dic.head;

    while (temp != NULL) {
        printf("%s=\"%s\"\n", temp->key, temp->value);
        temp = temp->link;
    }
}

int dictionary_add(t_dictionary *head, char* key, void* value) 
{
    _t_dictionary* temp = head->head;

    while (1) {
        if (head->count == 0) 
        {
            temp = (_t_dictionary *)malloc(sizeof(_t_dictionary));
            temp->key = key;
            temp->value = value;
            temp->link = NULL;
            head->head = temp;
            break;
        }
        else if (ft_strcmp(temp->key, key) == 0)
            return false;
        else if (temp->link == NULL) 
        {
            temp->link = (_t_dictionary*)malloc(sizeof(_t_dictionary));
            temp->link->key = key;
            temp->link->value = value;
            temp->link->link = NULL;
            break;
        }
        else
            temp = temp->link;
    }
    head->count++;
    return true;
}

void *dictionary_search(t_dictionary head, char *key) {
    _t_dictionary* temp = head.head;
    while (1) {
        if (temp == NULL) 
            return NULL;
        if (ft_strcmp(temp->key, key) == 0) 
            return temp->value;
        temp = temp->link;
    }
}

int dictionary_delete(t_dictionary *head, char *key) 
{
    _t_dictionary* ptr = head->head;
    _t_dictionary* pre = NULL;
    
    while (true) 
    {
        if (ptr == NULL) 
            return false;
        else if (ft_strcmp(ptr->key, key) == 0) 
            break;
        pre = ptr;
        ptr = ptr->link;
    }

    if (pre == NULL) 
    {
        free(ptr);
        head->head = NULL;
    }
    else 
    {
        pre->link = ptr->link;
        free(ptr);
    }
    head->count--;
    return true;
}

void dictionary_init(t_dictionary   *head)
{
    head->count = 0;
    head->head = NULL;
}