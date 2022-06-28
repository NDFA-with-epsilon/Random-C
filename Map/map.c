#include "map.h"

pair* initialize_map()
{
    pair* map = malloc(MAP_SIZE * sizeof(pair));
    if(map)
    {
        for(int i = 0; i < MAP_SIZE; i++)
        {
            (map+i)->index = i+1;
            (map+i)->key = 0;
            (map+i)->val = 0;
            (map+i)->next = (i != MAP_SIZE - 1) ? (map+(i+1)) : NULL;
        }

        // for(pair* tmp = map; tmp != NULL; tmp = tmp->next)
        // {
        //     printf("\nIndex: %d\tKEY: %p\t VAL: %d\n", tmp->index, (void*)tmp->key, tmp->val);
        // }
    }

    return map;
}

int insert(pair** map, uintptr_t key, uint32_t val)
{   
    pair* tmp = *map;
    while( (tmp->key != 0) && (tmp->next != NULL) )
    {
        tmp = tmp->next;
    }

    if(!(tmp->next))
    {
        if(!tmp->key)
        {
            tmp->key = key;
            tmp->val = val;
            return 1;
        }

        printf("\nMAP FULL\n");
        return -1;
    }

    tmp->key = key;
    tmp->val = val;
    return 1;
}

uint32_t fetch(pair** map, uintptr_t key)
{
    if(!(*map) || !key)
    {
        printf("\nInvalid parameter\n");
        return -1;
    }

    pair* tmp = *map;

    while( (tmp->key != key) && (tmp->next != NULL) )
    {
        tmp = tmp->next;
    }

    if(!(tmp->next))
    {
        if(tmp->key == key)
        {
            return tmp->val;
        }

        printf("\nKey not found\n"); //if not found, insert the key ?
        return -1;
    }

    printf("\nKey found\n");
    return tmp->val;
}

int main(void)
{
    pair* map = initialize_map();
    uint32_t buf[MAP_SIZE +1];

    // for(int i = 0; i < MAP_SIZE + 1; i++)
    // {
    //     printf("\nbuf[%d]:\n", i);
    //     scanf("%d", &buf[i]);
    // }

    for(uint32_t i = 0; i < MAP_SIZE; i++)
    {
        buf[i] = i;
    }

    for(int i = 0; i < MAP_SIZE; i++)
    {
        int ins_map = insert(&map, (uintptr_t)(&buf[i]), buf[i]);
        assert(ins_map != -1);
    }
    
    for(pair* tmp = map; tmp != NULL; tmp = tmp->next)
    {
        printf("\nIndex: %d\tKEY: %p\t VAL: %d\n", tmp->index, (void*)tmp->key, tmp->val);
    }
    
    // uint32_t fetched_key = fetch(&map, (uintptr_t)&buf[rand() % 10]);
    // printf("\n%d\n", fetched_key);
}
