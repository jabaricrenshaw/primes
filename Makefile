CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -O3
LDFLAGS=-lm

SRC=primes.c

PHONY: all
all: 3

1:
	@echo "Compiling for single-thread."
	$(CC) $(SRC) -o primes $(LDFLAGS) $(CFLAGS)

2:
	@echo "Compiling for multi-thread."
	$(CC) $(SRC) -o primes -lpthread $(LDFLAGS) $(CFLAGS) -DTHREADS=12

3:
	@echo "Compiling all."
	$(CC) $(SRC) -o primes_single $(LDFLAGS) $(CFLAGS)
	$(CC) $(SRC) -o primes_multi -lpthread $(LDFLAGS) $(CFLAGS) -DTHREADS=12

clean:
	rm primes primes_single primes_multi
