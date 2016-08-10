
#include <stdio.h>
#include <stdlib.h>
#include <area51/json.h>
#include <string.h>
#include <area51/charbuffer.h>
#include <area51/rest.h>

void json_append_int(struct charbuffer *b, int v) {
    if (v == INT_MIN)
        charbuffer_append(b, "null");
    else
        charbuffer_append_int(b, v, 0);
}
