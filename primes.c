#include "util.h"
#include <omp.h>

int main(int argc, char *argv[]){
    unsigned long *e = 0, limit = 0, sz = 0, b_mem_req = 0;
    float mb_mem_req = 0;

    if(argc == 2){
        limit = strtoul(argv[1], NULL, 0);
    }else{
        fprintf(stderr, "Please provide integer limit as an argument.\nUSAGE: primes.c {LIMIT}\n");
        return EXIT_FAILURE;
    }

    sz = limit >> 1;
    b_mem_req = sizeof(unsigned long) * sz;
    mb_mem_req = (float)b_mem_req/(1 << 20);

    if((e = (unsigned long *)malloc(sizeof(unsigned long)*sz)) == NULL){
        fprintf(stderr, "Attempted to allocate %lu members with %lu bytes (%.2f MB)", sz, b_mem_req, mb_mem_req);
        return EXIT_FAILURE;
    }
    fprintf(stderr, "Allocated %lu bytes (%.2f MB)\n", b_mem_req, mb_mem_req);
    
    init_entries(e, sz);
    for(unsigned long i = 1; i <= (unsigned long)sqrt(sz); ++i){
#if defined OMP && OMP == 1
        #pragma omp parallel shared(e, i)
#endif
        {
            if(e[i] != 0){
#if defined OMP && OMP == 1
                #pragma omp for 
#endif
                for(unsigned long j = e[i] + i; j < sz; j += e[i]){
                    e[j] = 0;
                }
            }
        }
    }

    free(e);
    return EXIT_SUCCESS;
}
