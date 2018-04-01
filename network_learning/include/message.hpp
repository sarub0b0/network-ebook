#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <cstdio>

#ifndef DEBUG
#define dprintf(message...)                      \
    do {                                         \
        std::fprintf(stderr, "%s", __FILE__);    \
        std::fprintf(stderr, "(%d) ", __LINE__); \
        std::fprintf(stderr, "%s: ", __func__);  \
        std::fprintf(stderr, message);           \
        std::fprintf(stderr, "\n");              \
    } while (0)
#else
#define dprintf(...)
#endif

#endif
