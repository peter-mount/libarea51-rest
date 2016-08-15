
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <area51/charbuffer.h>
#include <area51/list.h>
#include <area51/rest.h>

void json_append_list(struct charbuffer *b, struct List *l, void (*appender)(struct charbuffer *, struct Node *)) {
    bool sep = false;
    charbuffer_add(b, '[');

    if (l) {
        struct Node *n = list_getHead(l);
        while (n && list_isNode(n)) {
            if (sep)
                charbuffer_add(b, ',');
            else
                sep = true;
            appender(b, n);
            n = n->n_succ;
        }
    }

    charbuffer_add(b, ']');
}
