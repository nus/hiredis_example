CC := gcc
HIREDIS_CFLAGS := -D_FILE_OFFSET_BITS=64 -I/usr/local/include/hiredis
HIREDIS_LIBS := -L/usr/local/lib -lhiredis
CFLAGS := -g -Wall

.PHONY: all
all: publish subscribe

publish: publish.c
	$(CC) -o publish.out publish.c $(CFLAGS) $(HIREDIS_CFLAGS) $(HIREDIS_LIBS)

subscribe: subscribe.c
	$(CC) -o subscribe.out subscribe.c $(CFLAGS) $(HIREDIS_CFLAGS) $(HIREDIS_LIBS)

clean:
	$(RM) *.out

