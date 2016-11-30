#include <stdio.h>
#include <hiredis.h>

static void printfRedisReply(redisReply *r) {
    int i;

    if (r == NULL) {
        fprintf(stderr, "Invalid argument. r must be not NULL.");
        return;
    }

    printf("len: %ld, elements: %ld, type: %d\n", r->len, r->elements, r->type);
    if (r->type == REDIS_REPLY_ARRAY) {
        for (i = 0; i < r->elements; i++) {
            printf("\t%s\n", r->element[i]->str);
        }
    }
}

int main (int argc, char **argv) {
    redisContext *c = NULL;
    void *reply = NULL;
    int redis_err = 0;

    c = redisConnect("127.0.0.1", 6379);

    if (!c) {
        fputs("Failed to redisConnect()", stderr);
        return 1;
    } else if (c->err) {
        fprintf(stderr, "Failed to redisConnect(%s)\n", c->errstr);
        redisFree(c);
        return 1;
    } else if ((reply = redisCommand(c, "SUBSCRIBE channel_foo")) == NULL) {
        fprintf(stderr, "Failed to redisCommand(%s)\n", c->errstr);
        redisFree(c);
        return 1;
    } else {
        printfRedisReply((redisReply *)reply);
        freeReplyObject(reply);

        puts("subscribing...");

        while ((redis_err = redisGetReply(c, &reply)) == REDIS_OK) {
            printfRedisReply((redisReply *)reply);
            freeReplyObject(reply);
        }

        redisFree(c);

        return 0;
    }
}
