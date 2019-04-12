#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

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

bool test3(void)
{
    typedef struct Item
    {
        ListNode list1;
        ListNode list2;
        int      id;
    } Item;

    Item items[5];

    ARRAY_FOREACH(items, i) {
        list_reset(&items[i].list1);
        list_reset(&items[i].list2);
        items[i].id = i;
    }

    LIST_HEAD(list_head1);
    LIST_HEAD(list_head2);

    ARRAY_FOREACH(items, i) {
        list_insert_after(&list_head1, &items[i].list1);

        Item* item = LIST_ENTRY(list_head1.next, Item, list1);
        assert(item->id == i);

        list_insert_before(&list_head2, &items[i].list2);

        item = LIST_ENTRY(list_head2.prev, Item, list2);
        assert(item->id == i);
    }

    ListNode* iterator;
    int count = 4;

    LIST_FOREACH(&list_head1, iterator) {
        Item* entry = LIST_ENTRY(iterator, Item, list1);
        printf(" > %d", entry->id);
        assert(entry->id == count);
        --count;
    }
    printf("\n");

    count = 4;
    LIST_FOREACH_REVERSE(&list_head2, iterator) {
        Item* entry = LIST_ENTRY(iterator, Item, list2);
        printf(" < %d", entry->id);
        assert(entry->id == count);
        --count;
    }
    printf("\n");

    count = 4;
    Item* entry = NULL;
    LIST_FOREACH_ENTRY(&list_head1, list1, entry) {
        printf(" %d", entry->id);
        assert(entry->id == count);
        --count;
    }
    printf("\n");

    /*entry = NULL;
    Item* saver;
    LIST_FOREACH_ENTRY_SAFE(&list_head1, list1, entry, saver) {
        printf(" %d", entry->id);
        list_delete(&entry->list1);
        free(entry);
    }
    printf("\n");*/

    return true;
}

int main(void)
{
    assert(test1());
    assert(test2());
    assert(test3());

    return 0;
}
