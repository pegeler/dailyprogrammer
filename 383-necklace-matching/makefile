CC = gcc
CCFLAGS = -O2

.PHONY: all

all: necklace repeats bonus2

necklace: necklace.c
	$(CC) $(CCFLAGS) $^ -o $@

repeats: repeats.c
	$(CC) $(CCFLAGS) $^ -o $@

bonus2: bonus2.c
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm necklace repeats bonus2
