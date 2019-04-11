#include <assert.h>
#include <stdbool.h>

#include "func/listnode.h"
#include "func/foreach.h"

bool test1(void)
{
    typedef struct Item
    {
        ListNode list;
        int      id;
        char*    name;
    } Item;

    Item item = {
        .list = LIST_NODE_INIT(item.list),
        .id = 1,
        .name = "#1"
    };

    assert(list_empty(&item.list));

    list_reset(&item.list);

    assert(list_empty(&item.list));

    return true;
}

bool test2(void)
{
    typedef struct Item
    {
        ListNode list;
        int      id;
    } Item;

    Item items[5];

    ARRAY_FOREACH(items, i) {
        list_reset(&items[i].list);
        items[i].id = i;
    }

    LIST_HEAD(list_head);

    ARRAY_FOREACH(items, i) {
        list_insert_after(&list_head, &items[i].list);

        Item* item = LIST_ENTRY(list_head.next, Item, list);
        assert(item->id == i);
    }

    return true;
}

int main(void)
{
    assert(test1());
    assert(test2());

    return 0;
}
