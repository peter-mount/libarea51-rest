/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/log.h>
#include <area51/webserver.h>

extern int verbose;

WEBSERVER_HANDLER *webserver_add_handler(const char *url, int (*handler)(struct MHD_Connection *connection, WEBSERVER_HANDLER *handler)) {
    if (!url || strlen(url) == 0 || url[0] != '/') {
        logconsole("Invalid url \"%s\" for a handler", url);
        return NULL;
    }

    WEBSERVER_HANDLER *h = (WEBSERVER_HANDLER *) list_findNode(&webserver.handlers, url);
    if (!h) {

        // Common bit of debugging so include this if -vv on command line
        if (verbose > 1)
            logconsole("Add handler: %s", url);

        h = (WEBSERVER_HANDLER *) malloc(sizeof (WEBSERVER_HANDLER));
        memset(h, 0, sizeof (WEBSERVER_HANDLER));
        h->node.name = strdup(url);
        h->handler = handler;
        list_addTail(&webserver.handlers, &h->node);
    }
    return h;
}
