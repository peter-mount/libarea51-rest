#include <area51/charbuffer.h>
#include <area51/string.h>
#include <area51/webserver.h>
#include <string.h>
#include <limits.h>

struct data {
    int prefixLength;
    void (*handler)(CharBuffer *);
};

static int handler(struct MHD_Connection * connection, WEBSERVER_HANDLER *handler, const char *url) {
    void (*api)(CharBuffer *) = handler->userdata;

    CharBuffer b;
    charbuffer_init(&b);

    api(&b);

    struct MHD_Response *response = MHD_create_response_from_buffer(b.pos, b.buffer, MHD_RESPMEM_MUST_FREE);
    return queueResponse(connection, &response);
}

void webserver_add_static(const char *prefix, void (*api)(CharBuffer *)) {
    WEBSERVER_HANDLER *h = webserver_add_handler(prefix, handler);
    if (h) {
        h->userdata = api;
    }
}
