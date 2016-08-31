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

    CharBuffer *b = charbuffer_new();

    api(b);

    int len=0;
    void *buf = charbuffer_getBuffer(b,&len);
    
    charbuffer_free(b);
    
    struct MHD_Response *response = MHD_create_response_from_buffer(len, buf, MHD_RESPMEM_MUST_FREE);
    MHD_add_response_header(response, "Access-Control-Allow-Origin", "*");
    return webserver_queueResponse(request, &response);
}

void webserver_add_static(WEBSERVER *webserver, const char *prefix, void (*api)(CharBuffer *)) {
    webserver_add_handler(webserver, prefix, handler, api);
}
