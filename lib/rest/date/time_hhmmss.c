#include <time.h>
#include <area51/charbuffer.h>
#include <area51/json.h>
#include <area51/rest.h>

void json_append_time_hhmmss(CharBuffer *b, time_t *t) {
    struct tm tm;
    if (t && *t) {
        gmtime_r(t, &tm);
        charbuffer_printf(b, "\"%02d:%02d:%02d\"", tm.tm_hour, tm.tm_min, tm.tm_sec);
    } else
        json_append_str(b, "null");
}
