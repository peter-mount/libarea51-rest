
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/list.h>
#include <area51/rest.h>

void json_append_list(struct charbuffer *b, struct List *l, void (*appender)(struct charbuffer *, struct Node *)) {
    charbuffer_reset(b);
    charbuffer_add(b, '[');

    if (l) {
        struct Node *n = list_getHead(l);
        while (n && list_isNode(n)) {
            if (b->pos > 1)
                charbuffer_add(b, ',');
            appender(b, n);
            n = n->n_succ;
        }
    }

    charbuffer_add(b, ']');
}
