CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -O3
LDFLAGS=-lm

SRC=primes.c

PHONY: all
all: 3

1:
	@echo "Compiling for single-thread."
	$(CC) $(SRC) -o primes $(LDFLAGS) $(CFLAGS) -DOMP=0

2:
	@echo "Compiling for multi-thread."
	$(CC) $(SRC) -o primes -fopenmp $(LDFLAGS) $(CFLAGS) -DOMP=1

3:
	@echo "Compiling all."
	$(CC) $(SRC) -o primes_single $(LDFLAGS) $(CFLAGS) -DOMP=0
	$(CC) $(SRC) -o primes_multi -fopenmp $(LDFLAGS) $(CFLAGS) -DOMP=1

clean:
	rm primes primes_single primes_multi
