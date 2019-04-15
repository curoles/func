#include <assert.h>

#define ANCHOR_EXTERN_INLINE

#define T int
#define Q QueueInt
#define new_Q new_QueueInt
#define cleanup_Q cleanup_QueueInt
#include "func/queue.h"

#if defined(T) || defined(Q) || defined(new_Q) || defined(cleanup_Q)
#error queue.h must undef all "template" macros
#endif

bool test1(void)
{
    QueueInt q CLEANUP(cleanup_QueueInt) = new_QueueInt(1);

    assert(q.size == 0);

    q.push_back(&q, 1);

    assert(q.size == 1 && q.item[0] == 1 && *(q.front(&q)) == 1);

    q.push_back(&q, 2);

    assert(q.size == 2 && *(q.front(&q)) == 1);

    assert(q.pop_front(&q) == 1);

    assert(q.size == 1 && *(q.front(&q)) == 2);

    q.pop_front(&q);

    q.push_back(&q, 1); q.push_back(&q, 2); q.push_back(&q, 3);

    assert(q.size == 3);

    q.foreach(&q, lambda(void, (unsigned i, int* e) {
         assert(*e == (i + 1));
    }));

    return true;
}

int main()
{
    assert(test1());

    return 0;
}
