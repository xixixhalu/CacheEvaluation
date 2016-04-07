#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <hiredis/hiredis.h>

redisContext *c;
redisReply *reply;

/*-------Test Functions-------------*/
void singleInsert();
void multiInsert();

/*-------Utility Functions----------*/
void initialize(int argc, char **argv);
void pingServer();
bool setData(char* key, size_t ksize, char* value, size_t vsize);

int main(int argc, char **argv) {
    
    initialize(argc, argv);

    pingServer();
	
	//singleInsert();
	multiInsert();

    /* Disconnects and frees the context */
    redisFree(c);

    return 0;
}

/*-------Test Functions-------------*/
void singleInsert() {
	int i = 0;
	char key[10];
	char value[10];
	sprintf(key, "%d", i);
	sprintf(value, "%d", i);
	if (!setData(key, 10, value, 990)) {
		printf("Cannot insert Key: %d\n", i);
	}
}

void multiInsert() {
	int i;
	for (i = 0; i < 1000; i++) {
		char key[10];
		char value[10];
		sprintf(key, "%d", i);
		sprintf(value, "%d", i);
		if (!setData(key, 10, value, 990)) {
			printf("Cannot insert Key: %d\n", i);
			break;
		}
	}
}

/*-------Utility Functions-------------*/

/* Initialize Client */
void initialize(int argc, char **argv) {
	const char *hostname = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
}

/* PING server */
void pingServer() {
    reply = redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);
}

/* Set a key using binary safe API */
bool setData(char* key, size_t ksize, char* value, size_t vsize) {
	/* Set a key */
	/*
    reply = redisCommand(c,"SET %s %s", "foo", "hello world");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);
	*/
    /* Set a key using binary safe API */
    reply = redisCommand(c,"HSET user: %b %b", key, ksize, value, vsize);
    printf("SET (binary API): %s\n", reply->str);
	if (reply->type == REDIS_REPLY_ERROR) {
		freeReplyObject(reply);
		return false;
	}
    freeReplyObject(reply);
	return true;
}
