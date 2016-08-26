#include <area51/charbuffer.h>
#include <area51/string.h>
#include <area51/webserver.h>
#include <string.h>
#include <limits.h>

struct data {
    int prefixLength;
    void (*handler)(CharBuffer *);
};

static int handler(WEBSERVER_REQUEST *request) {
    void (*api)(CharBuffer *) = webserver_getUserData(request);

    CharBuffer b;
    charbuffer_init(&b);

    api(&b);

    struct MHD_Response *response = MHD_create_response_from_buffer(b.pos, b.buffer, MHD_RESPMEM_MUST_FREE);
    return webserver_queueResponse(request, &response);
}

void webserver_add_static(WEBSERVER *webserver, const char *prefix, void (*api)(CharBuffer *)) {
    webserver_add_handler(webserver, prefix, handler, api);
}
