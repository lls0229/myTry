#include"../inc/lls_log.h"

void log_error(uint_t level, log_t *log, err_t err,
    const char *fmt, ...)
{
    va_list args;

    if(log->log_level >= level){
        va_start(args, fmt);
        log_error_core(level, log, err, fmt, args);
        va_end(args);
    }
}