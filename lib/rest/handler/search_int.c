#include <area51/webserver.h>
#include <area51/string.h>
#include <string.h>
#include <limits.h>

struct data {
    int prefixLength;
    void (*handler)(CharBuffer *, int value);
};

static int handler(WEBSERVER_REQUEST *request) {
    struct data *data = webserver_getUserData(request);

    const char *url = webserver_getRequestUrl(request);
    int val = INT_MIN;
    if (strlen(url)>(data->prefixLength) && url[data->prefixLength])
        val = atoi(&url[data->prefixLength]);

    CharBuffer b;
    charbuffer_init(&b);

    if (val > INT_MIN)
        data->handler(&b, val);

    struct MHD_Response *response = MHD_create_response_from_buffer(b.pos, b.buffer, MHD_RESPMEM_MUST_FREE);
    return queueResponse(request, &response);
}

void webserver_add_search_int(WEBSERVER *webserver, const char *prefix, void (*search)(CharBuffer *, int value)) {
    char *pattern = genurl(prefix, "/*");

    struct data *data = (struct data *) malloc(sizeof (struct data));
    if (data) {
        data->prefixLength = strlen(prefix) + 1;
        data->handler = search;
        WEBSERVER_HANDLER *h = webserver_add_handler(webserver, pattern, handler, data);
    }
}
