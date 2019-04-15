#include <assert.h>
#include <stdlib.h>

#include "func/func.h"

#ifndef T
#error T is not defined
#endif

#ifndef Q
#error Q is not defined
#endif

#ifndef new_Q
#error new_V is not defined
#endif

#ifndef cleanup_Q
#error cleanup_Q is not defined
#endif

typedef struct Q
{
    unsigned space, size;
    unsigned first, last;
    T* item;

    void (*cleanup)(struct Q*);
    void (*resize)(struct Q*, unsigned amount);
    void (*push_back)(struct Q*, T);
    T    (*pop_front)(struct Q*);
    T*   (*front)(struct Q*);
    void (*foreach)(struct Q*, void (*)(unsigned,T*));
} Q;

EXTERN_INLINE
void cleanup_Q(Q* q)
{
    if (q != NULL && q->item != NULL) {
        free(q->item);
        q->item = NULL;
    }
}

EXTERN_INLINE
Q new_Q(unsigned init_sz)
{
    void resize(Q* q, unsigned amount) {
        unsigned int old_tail = q->space;
        q->space += amount;
        void* new_space = realloc(q->item, sizeof(T) * q->space);
        assert(new_space != NULL);
        q->item = new_space;
        for (unsigned int i = 0; i < q->first; ++i) // assume space is *doubled*!!!
            q->item[old_tail + i] = q->item[i]; // copy [0..first] to [old_tail..]
        q->last = q->first + q->size; // x2 space on resizing => fit old data w/o wrap-around
    }

    void push_back(Q* q, T item) {
        if (q->size == q->space)
            resize(q, q->space); // *double* size and recopy front
        q->item[q->last] = item;               // add item
        ++q->last;
        if (q->last == q->space) q->last = 0;  // wrap-around
        ++q->size;
    }

    T pop_front(Q* q) {
        T item = q->item[q->first];
        if (q->size > 0) {
            --q->size;
            ++q->first;
            if (q->first == q->space) q->first = 0; // wrap-around
        }
        return item;
    }

    T* front(Q* q) {
        if (q->size == 0) return NULL;
        return &q->item[q->first];
    }

    void foreach(struct Q* q, void (*visitor)(unsigned,T*)) {
        for (unsigned i = 0; i < q->size; ++i)
            visitor(i, &q->item[(q->first + i) % q->space]);
    }

    Q q = {.space = 0,
           .size  = 0,
           .first = 0,
           .last  = 0,
           .item  = NULL,
           .cleanup   = cleanup_Q,
           .resize    = resize,
           .push_back = push_back,
           .pop_front = pop_front,
           .front     = front,
           .foreach   = foreach
    };

    resize(&q, init_sz);

    return q;
}

#undef T
#undef Q
#undef new_Q
#undef cleanup_Q

