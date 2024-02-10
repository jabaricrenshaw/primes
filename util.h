#include <stdio.h>

void display_primes(char *e, unsigned long sz){
    unsigned long cnt = 1;

    printf("%d \t %d\n", 2, 1);
    for(unsigned long i = 1; i < sz; ++i){
        if(e[i] != 0){
            printf("%lu\n", (i << 1) + 1);
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
