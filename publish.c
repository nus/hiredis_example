#include <stdio.h>
#include <hiredis.h>

int main (int argc, char **argv) {
    redisContext *c = NULL;
    void *reply = NULL;

    c = redisConnect("127.0.0.1", 6379);

    if (!c) {
        fputs("Failed to redisConnect()", stderr);
        return 1;
    } else if (c->err) {
        fprintf(stderr, "Failed to redisConnect(%s)\n", c->errstr);
        redisFree(c);
        return 1;
    } else {
        puts("connected");
        reply = redisCommand(c, "PUBLISH channel_foo bar");

        freeReplyObject(reply);
        redisFree(c);

        return 0;
    }
}
