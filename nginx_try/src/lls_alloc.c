
#include "../inc/lls_core.h"
#include "../inc/lls_config.h"
#include "../inc/lls_log.h"
#include "../inc/lls_errno.h"
#include "../inc/lls_alloc.h"
#include "../inc/lls_string.h"

uint_t pagesize;
uint_t pagesize_shift;
uint_t cacheline_size;

void *lls_alloc(size_t size, log_t *log){
    void *p;

    p = malloc(size);
    if(p == NULL){
        log_error(LOG_EMERG, log, errno, "malloc(%uz) failed", size);
    }
    log_debug2(LOG_DEBUG_ALLOC, log, 0, "malloc: %p:%uz", p, size);

    return p;
}

void *lls_calloc(size_t size, log_t *log){
    void *p;

    p = lls_alloc(size, log);

    if(p){
        lls_memzero(p, size);
    }

    return p;
}