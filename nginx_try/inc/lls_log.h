#ifndef _LLS_LOG_H_
#define _LLS_LOG_H_

#include "./lls_config.h"
#include "./lls_core.h"

#define LOG_EMERG   1
#define LOG_ERR     4
#define LOG_DEBUG   8

#define LOG_DEBUG_ALLOC    0x020


#if (HAVE_C99_VARIADIC_MACROS)
#define HAVE_VARIADIC_MACROS 1
#define log_error(level, log, ...) \
        if((log)->log_level >= level) log_error_core(level, log, __VA_ARGS))

void log_error_core(uint_t level, log_t *log, err_t err, \
        const char *fmt, ...);

#define log_debug(level, log, ...) \
        if((log)->log_level & level) \
        log_error_core(LOG_DEBUG, log, __VA_ARGS__)

/*****************************************************/

#elif (HAVE_GCC_VARIADIC_MACROS)
#defile HAVE_VARIADIC_MACROS 1

#define log_err(level, log, args, ...) \
        if((log)->log_level >= level) log_error_core(level, log, args)
void log_error_core(uint_t level, log_t *log, err_t err, 
        const char *fmt, ...);
#define log_debug(level, log, args, ...) \
        if((log)->log_level & level) \
            log_error_core(LOG_DEBUG, log, args)


/*****************************************************/
#else  /* no variadic macros */ 
void log_error(uint_t level, log_t *log, err_t err, const char *fmt, ...);
void log_error_core(uint_t level, log_t *log, err_t err, const char *fmt, va_list args);
void log_debug_core(log_t *log, err_t err, const char *fmt, ...);
#endif  /* variadic macros */
/*****************************************************/
#if (DEBUG)
#if (HAVE_VARIADIC_MACROS)

#define log_debug2(level, log, err, fmt, arg1, arg2) \
        log_debug(level, log, err, fmt, arg1, arg2)

#else /* no variadic macros */

#define log_debug2(level, log, err, fmt, arg1, arg2) \
        if((log)->log_level & level) \
            log_debug_core(log, err, fmt, arg1, arg2)

#endif

#else /* !DEBUG */
#define log_debug2(level, log, err, fmt, arg1, arg2)
#endif




typedef u_char *(*log_handler_pt)(log_t *log, u_char *buf, size_t len);
typedef void (*log_writer_pt)(log_t *log, uint_t level);


struct log_s{
    int               log_level;
    open_file_t       *file;

    atomic_uint_t     connecttion;

    time_t            disk_full_time;

    log_handler_pt    handler;
    void              *data;

    log_writer_pt     writer;
    void              *wdata;

    char              *action;

    log_t             *next;
};


#endif