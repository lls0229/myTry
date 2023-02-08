// #include"../inc/lls_config.h"
// #include"../inc/lls_core.h"
#include"../inc/lls_alloc.h"

int main(){
    void *p;
    log_t *log;
    p = lls_alloc(sizeof(int), log);
    if(p == NULL){
        printf("error");
    }
    return 0; 
}