#ifndef  _LLS_CORE_H_
#define  _LLS_CORE_H_

#include "lls_config.h"
typedef struct open_file_s   open_file_t;
typedef struct log_s         log_t;


typedef int fd_t;

typedef struct {
    size_t len;
    u_char *data;
}str_t;

struct open_file_s{
    fd_t      fd;
    str_t     name;

    void      (*flush)(open_file_t *file, log_t *log);
    void      *data;
};

//typedef struct log_s         log_t;
//typedef struct open_file_s   open_file_t;



#endif 