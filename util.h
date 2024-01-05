#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void display_primes(unsigned long *e, unsigned long sz){
    unsigned long cnt = 0;
    for(unsigned long i = 0; i < sz; ++i){
        if(e[i] != 0){
            printf("%lu\n", e[i]);
            cnt++;
        }
    }
    printf("TOTAL PRIMES: %lu\n", cnt);
}

void display_entries(unsigned long *e, unsigned long sz){
    for(unsigned long i = 0; i < sz; ++i){
        printf("%lu\t%s\n", e[i], e[i] == 0 ? "marked" : "");
    }
}

void init_entries(unsigned long *e, unsigned long sz){
    e[0] = (unsigned long){2};
    for(unsigned long i = 4; i <= (sz << 1); i += 2){
        e[(i >> 1) - 1] = (unsigned long){i - 1};
    }
}