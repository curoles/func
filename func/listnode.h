#pragma once

/** Node of a list
 *
 * Usage:
 * struct MyList {
 *     ListNode list;
 *     T data;
 * };
 */
typedef struct ListNode
{
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

///
/// @return true if empty
extern inline bool list_empty(ListNode* node)
{
    return node->next == node;
}

extern inline void list_reset(ListNode* node)
{
    node->prev = node;
    node->next = node;
}

/**
 * If the structure is statically created at compile time,
 * and you have a direct reference to it, you can simply do this:
 *
 * struct my_struct mine = {
 *     .list  = LIST_NODE_INIT(mine.list),
 *     .dog   = 0,
 *     .cat   = NULL
 * };
 */
#define LIST_NODE_INIT(name) { &(name), &(name) }

/// Create on-stack variable that is head of a list. 
#define LIST_HEAD(name) \
struct ListNode name = LIST_NODE_INIT(name)

/*
 * Insert a new entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
extern inline
void list_insert__(
    ListNode* new_node,
    ListNode* prev,
    ListNode* next
)
{
    next->prev = new_node; //          new_node <-  next
    new_node->next = next; //          new_node  -> next
    new_node->prev = prev; // prev <-  new_node
    prev->next = new_node; // prev  -> new_node
                           // prev <-> new_node <-> next
}

/**
 * List_insertAfter - add a new entry
 * @param new_node new entry to be added
 * @param node list head to add new_node after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
extern inline
void list_insert_after(ListNode* node, ListNode* new_node)
{
    // node <-> new_node <-> node.next
    list_insert__(new_node, node, node->next);
}

#if 0
/**
 * List_insertBefore - add a new entry
 * @param new_node new entry to be added
 * @param node list head to add new_node before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline
void List_insertBefore(ListNode* node, ListNode* new_node)
{
    // node.prev <-> new_node <-> node
    List_insert__(new_node, node->prev, node);
}

/**
 * List_add - add a new entry
 * @param new_node new entry to be added
 * @param node list head to add new_node after
 *
 * Alias for List_insertAfter.
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline
void List_add(ListNode* node, ListNode* new_node)
{
    List_insertAfter(node, new_node);
}


/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline
void List_connectNodes__(ListNode* prev, ListNode* next)
{
    next->prev = prev;
    prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
static inline
void List_delete(ListNode* node)
{
    List_connectNodes__(node->prev, node->next);
    node->next = (void *) 0;
    node->prev = (void *) 0;
}



/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define List_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define List_forEach(head, iterator) \
    for (iterator = (head)->next; iterator != (head); \
         iterator = iterator->next)

/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define List_forEachReverse(head, pos) \
    for (pos = (head)->prev; pos != (head); \
         pos = pos->prev)


/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define List_forEachEntry(head, member, pos)                 \
    for (pos = List_entry((head)->next, typeof(*pos), member); \
        &pos->member != (head);                                \
         pos = List_entry(pos->member.next, typeof(*pos), member))

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop counter.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define List_forEachEntrySafe(head, member, pos, n)			\
	for (pos = List_entry((head)->next, typeof(*pos), member),	\
		n = List_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = List_entry(n->member.next, typeof(*n), member))



#endif
