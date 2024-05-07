#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined THREADS
#include <pthread.h>
#endif

unsigned long sz;
char *e = 0;

struct thread_carrier {
    pthread_t thread;
    unsigned int id;  
};

#if defined THREADS
void* work(void *args){
    struct thread_carrier *thc = args;
    
    for(unsigned long i = thc->id; i <= (unsigned long)sqrt(sz); i += THREADS){
        if(e[i] == 0){
            for(unsigned long j = ((i << 1) + 1) + i; j < sz; j += ((i << 1) + 1)){
                e[j] = 1;
            }
        }
    }
    
    return 0;
}
#endif

void display_primes(char *e, const unsigned long sz){
    //printf("2: %d\n", e[0]);
    unsigned long count = 1;
    printf("2 ");
    for(unsigned long i = 1; i < sz; ++i){
        if(e[i] == 0){
            printf("%ld ", (i << 1) + 1);
            count++;
        }
        //printf("%ld: %d\n", (i << 1) + 1, e[i]);
        //count++;
    }
    printf("\nTotal primes: %lu\n", count);
}

char* init_entries(const unsigned long sz){
    char *e = (char *)malloc(sz * sizeof(char));
    
    float bytes_req = (float)(sz * sizeof(char));
    float mbytes_req = (float)bytes_req/(1 << 20);
    char log_buf[256];
    sprintf(log_buf, "%ld members with %.3fB (%.3fMB)", sz, bytes_req, mbytes_req);

    if(e == NULL){
        fprintf(stderr, "Failed to allocate number space.\n");
        fprintf(stderr, "Attempted to allocate %s\n", log_buf);
        return NULL;
    }

    printf("Allocated %s\n", log_buf);

    return e;
}

int main(int argc, char *argv[]){
    if(argc == 2){
        sz = strtoul(argv[1], NULL, 0) >> 1;
    }else{
        fprintf(stderr, "Please provide integer limit as an argument.\nUSAGE: primes.c {LIMIT}\n");
        return EXIT_FAILURE;
    }
    e = init_entries(sz);

#if defined THREADS && THREADS > 1
    fprintf(stderr, "Starting with %d threads.\n", THREADS);
    struct thread_carrier thc[THREADS];
    
    int err = 0;
    for(size_t i = 0; i < THREADS; ++i){
        thc[i].id = i + 1;
        err = pthread_create(&thc[i].thread, NULL, &work, &thc[i]);
        
        if(err != 0){
            fprintf(stderr, "Failed to create thread.\n");
            return EXIT_FAILURE;
        }
    }
    
    err = 0;
    for(size_t i = 0; i < THREADS; ++i){
        err = pthread_join(thc[i].thread, NULL);
        
        if(err != 0){
            fprintf(stderr, "Failed to join thread.\n");
            return EXIT_FAILURE;
        }
    }

#else

    for(unsigned long i = 1; i <= (unsigned long)sqrt(sz); ++i){
        if(e[i] == 0){
            for(unsigned long j = ((i << 1) + 1) + i; j < sz; j += ((i << 1) + 1)){
                e[j] = 1;
            }
        }
    }

#endif
    
    //display_primes(e, sz);
    
    free(e);
    return 0;
}

/* Saving ompiler flags here ...
-O3 -Wunreachable-code -Wall -Wextra -Wpedantic -DTHREADS=4
*/
