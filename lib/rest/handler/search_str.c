#include <area51/webserver.h>
#include <area51/string.h>
#include <string.h>
#include <limits.h>

struct data {
    int prefixLength;
    void (*handler)(CharBuffer *, const char *value);
};

static int handler(WEBSERVER_REQUEST *request) {
    struct data *data = webserver_getUserData(request);

    const char *url = webserver_getRequestUrl(request);
    CharBuffer b;
    charbuffer_init(&b);

    if (strlen(url)>(data->prefixLength) && url[data->prefixLength])
        data->handler(&b, &url[data->prefixLength]);

    struct MHD_Response *response = MHD_create_response_from_buffer(b.pos, b.buffer, MHD_RESPMEM_MUST_FREE);
    return webserver_queueResponse(request, &response);
}

void webserver_add_search_str(WEBSERVER *webserver, const char *prefix, void (*search)(CharBuffer *, const char *value)) {
    char *pattern = genurl(prefix, "/*");

    struct data *data = (struct data *) malloc(sizeof (struct data));
    if (data) {
        data->prefixLength = strlen(prefix) + 1;
        data->handler = search;
        WEBSERVER_HANDLER *h = webserver_add_handler(webserver, pattern, handler, data);
    }
}
