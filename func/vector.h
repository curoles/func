#include <assert.h>
#include <stdlib.h>

#include "func/func.h"

#ifndef T
#error T is not defined
#endif

#ifndef V
#error V is not defined
#endif

#ifndef new_V
#error new_V is not defined
#endif

#ifndef cleanup_V
#error cleanup_V is not defined
#endif

typedef struct V
{
    unsigned space, size;
    T* item;

    void (*cleanup)(struct V*);
    void (*resize)(struct V*, unsigned amount);
    void (*push_back)(struct V*, T);
    void (*foreach)(struct V*, void (*)(unsigned,T*));
} V;

EXTERN_INLINE
void cleanup_V(V* v)
{
    if (v != NULL && v->item != NULL) {
        free(v->item);
        v->item = NULL;
    }
}

EXTERN_INLINE
V new_V(unsigned init_sz)
{
    void resize(V* v, unsigned amount) {
        v->space += amount;
        void* new_space = realloc(v->item, sizeof(T) * v->space);
        assert(new_space != NULL);
        v->item = new_space;
    }

    void push_back(V* v, T e) {
        if (v->size == v->space)
            resize(v, (v->space + 100)/10);
        v->item[v->size++] = e;
    }

    void foreach(struct V* v, void (*visitor)(unsigned,T*)) {
        for (unsigned i = 0; i < v->size; ++i)
            visitor(i, &v->item[i]);
    }

    V v = {.space = 0, .size = 0, .item = NULL,
           .cleanup=cleanup_V,
           .resize=resize, .push_back=push_back,
           .foreach=foreach};

    resize(&v, init_sz);

    return v;
}

#undef T
#undef V
#undef new_V
#undef cleanup_V

