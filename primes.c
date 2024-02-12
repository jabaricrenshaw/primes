#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#if defined THREADS
#include <pthread.h>
#endif

typedef struct t_args{
    unsigned long t_id;
} t_args;

char *e = 0;
unsigned long sz = 0;

#if defined THREADS
void hello(t_args *t){
    for(unsigned long i = t->t_id; i <= (unsigned long)sqrt(sz); i += THREADS){
        if(e[i]){
            for(unsigned long j = ((i << 1) + 1) + i; j < sz; j += ((i << 1) + 1)){
                e[j] ^= e[j];
            }
        }
    }
}
#endif

void display_primes(char *e, unsigned long sz){
    unsigned long cnt = 1;

    printf("%d\n", 2);
    for(unsigned long i = 1; i < sz; ++i){
        if(e[i] != 0){
        //    printf("%lu\n", (i << 1) + 1);
            cnt++;
        }
    }

    printf("TOTAL PRIMES: %lu\n", cnt);
}


void init_entries(char *e, unsigned long sz){
    e[0] = 1;
    for(unsigned long i = 4; i <= (sz << 1); i += 2){
        e[(i >> 1) - 1] = 1;
    }
}

int main(int argc, char *argv[]){
    unsigned long b_mem_req = 0;
    float mb_mem_req = 0;

    if(argc == 2){
        /*
         * Size of entries array -> (char *e) reduced by factor
         * of 2 since only odd numbers are evaluated in this program.
         */
        sz = strtoul(argv[1], NULL, 0) >> 1;
    }else{
        fprintf(stderr, "Please provide integer limit as an argument.\nUSAGE: primes.c {LIMIT}\n");
        return EXIT_FAILURE;
    }
    
    b_mem_req = sizeof(char) * sz;
    mb_mem_req = (float)b_mem_req/(1 << 20);

    if((e = (char *)malloc(sizeof(char) * sz)) == NULL){
        fprintf(stderr, "Attempted to allocate %lu members with %lu bytes (%.2f MB)", sz, b_mem_req, mb_mem_req);
        return EXIT_FAILURE;
    }
    printf("Allocated %lu members with %lu bytes (%.2f MB)\n", sz, b_mem_req, mb_mem_req);
    init_entries(e, sz);
    
#if defined THREADS && THREADS > 1
    pthread_t thr[THREADS];
    t_args ta[THREADS];
    
    for(size_t i = 0; i < THREADS; ++i){
        ta[i].t_id = i + 1;
        pthread_create(&thr[i], NULL, hello, &ta[i]);
    }

    for(size_t i = 0; i < THREADS; ++i){
        pthread_join(thr[i], NULL);
    }
#else
    for(unsigned long i = 1; i <= (unsigned long)sqrt(sz); ++i){
        if(e[i]){
            for(unsigned long j = ((i << 1) + 1) + i; j < sz; j += ((i << 1) + 1)){
                e[j] ^= e[j];
            }
        }
    }
#endif
    
    display_primes(e, sz);
    free(e);
    return EXIT_SUCCESS;
}
