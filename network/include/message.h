#ifndef __MESSAGE_H
#define __MESSAGE_H

#ifndef NODEBUG
#define dprintf(message...)                 \
    do {                                    \
        fprintf(stderr, "%s", __FILE__);    \
        fprintf(stderr, "(%d) ", __LINE__); \
        fprintf(stderr, "%s: ", __func__);  \
        fprintf(stderr, message);           \
    } while (0)
#else
#define dprintf(...)
#endif
/////////////////////////////////////////////
// Control the types of displayed messages
/////////////////////////////////////////////

//#define MESSAGE_WARNING
//#define MESSAGE_DEBUG
//#define MESSAGE_INFO

/////////////////////////////////////////////
// Special functions for messages
/////////////////////////////////////////////

// display a warning/error message
#ifdef MESSAGE_WARNING
#define WARNING(message...)                                            \
    do {                                                               \
        fprintf(stdout, "WARNING: %s, line %d: ", __FILE__, __LINE__); \
        fprintf(stdout, message);                                      \
        fprintf(stdout, "\n");                                         \
    } while (0)
#else
#define WARNING(message...) /* message */
#endif

// display a debugging message
#ifdef MESSAGE_DEBUG
#define DEBUG(message...)                                                    \
    do {                                                                     \
        fprintf(stdout, "DEBUG: %s(%d) %s: ", __FILE__, __LINE__, __func__); \
        fprintf(stdout, message);                                            \
        fprintf(stdout, "\n");                                               \
    } while (0)
#else
#define DEBUG(message...) /* message */
#endif

// display an informational message
#ifdef MESSAGE_INFO
#define INFO(message...)          \
    do {                          \
        fprintf(stdout, message); \
        fprintf(stdout, "\n");    \
    } while (0)
#else
#define INFO(message...) /* message */
#endif

#endif
