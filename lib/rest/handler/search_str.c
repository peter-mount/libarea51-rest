#include <area51/webserver.h>
#include <area51/string.h>
#include <string.h>
#include <limits.h>

struct data {
    int prefixLength;
    void (*handler)(CharBuffer *, const char *value);
};

static int handler(struct MHD_Connection * connection, WEBSERVER_HANDLER *handler, const char *url) {
    struct data *data = (struct data *) handler->userdata;

    CharBuffer b;
    charbuffer_init(&b);

    if (strlen(url)>(data->prefixLength) && url[data->prefixLength])
        data->handler(&b, &url[data->prefixLength]);

    struct MHD_Response *response = MHD_create_response_from_buffer(b.pos, b.buffer, MHD_RESPMEM_MUST_FREE);
    return queueResponse(connection, &response);
}

void webserver_add_search_str(const char *prefix, void (*search)(CharBuffer *, const char *value)) {
    char *pattern = genurl(prefix, "/*");

    WEBSERVER_HANDLER *h = webserver_add_handler(pattern, handler);
    if (h) {
        struct data *data = (struct data *) malloc(sizeof (struct data));
        data->prefixLength = strlen(prefix) + 1;
        data->handler = search;
        h->userdata = data;
    }
}
