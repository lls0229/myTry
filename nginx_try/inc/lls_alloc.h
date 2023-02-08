#ifndef _LLS_ALLOC_H_
#define _LLS_ALLOC_H_

#include"lls_config.h"
#include"lls_core.h"

void *lls_alloc(size_t size, log_t *log);
void *lls_calloc(size_t size, log_t *log);

#endif