#ifndef LOG_DEF_H
#define LOG_DEF_H

#ifdef NIF_DEBUG
#define DEBUG(X, ...) fprintf(stderr, X "\r\n", ##__VA_ARGS__)
#else
#define DEBUG(...)
#endif

#endif

