#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <curl/curl.h>

typedef struct {
    char *memory;
    size_t size;
} MemoryStruct;

char *http_get(const char *url);
char *http_post(const char *url, const char *data);

#endif // HTTP_CLIENT_H
