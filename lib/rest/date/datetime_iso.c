#include <time.h>
#include <area51/charbuffer.h>
#include <area51/json.h>
#include <area51/rest.h>

void json_append_datetime_ISO(CharBuffer *b, time_t *t) {
    struct tm tm;
    if (t && *t) {
        gmtime_r(t, &tm);
        charbuffer_printf(b, "\"%04d-%02d-%02dT%02d:%02d:%02dZ\"",
                1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday,
                tm.tm_hour, tm.tm_min, tm.tm_sec);
    } else
        json_append_str(b, "null");
}
