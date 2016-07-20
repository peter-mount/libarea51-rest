
#include <stdio.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include <area51/rest.h>

void json_append_str(struct charbuffer *b, char *s) {
    if (s) {
        charbuffer_add(b, '"');
        charbuffer_append(b, s);
        charbuffer_add(b, '"');
    } else
        charbuffer_append(b, "null");
}
