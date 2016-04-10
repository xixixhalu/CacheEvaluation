#include "MyRedis.h"

MyRedis::MyRedis() {
	initialize(IP_ADDRESS, PORT_NUM);
}

MyRedis::MyRedis(const char* hostname, int port) {
	initialize(hostname, port);
}

MyRedis::~MyRedis() {
	/* Disconnects and frees the context */
    redisFree(c);
}

/* Initialize Client */
void MyRedis::initialize(const char* hostname, int port) {

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
void MyRedis::pingServer() {
	reply = (redisReply*)redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);
}

/* Set a key using binary safe API */
bool MyRedis::setData(char* key, size_t ksize, char* value, size_t vsize) {
    reply = (redisReply*)redisCommand(c,"SET %b %b", key, ksize, value, vsize);
    printf("SET (binary API): %s\n", reply->str);
	if (reply->type == REDIS_REPLY_ERROR) {
		freeReplyObject(reply);
		return false;
	}
    freeReplyObject(reply);
	return true;
}

/* Set a key */
bool MyRedis::setData(char* key, char* value) {
	reply = (redisReply*)redisCommand(c,"SET %s %s", key, value);
    printf("SET: %s\n", reply->str);
    if (reply->type == REDIS_REPLY_ERROR) {
		freeReplyObject(reply);
		return false;
	}
    freeReplyObject(reply);
	return true;
}

bool MyRedis::t_singleInsert(size_t dsize) {
	static int i = 0;
	char* key = (char*)malloc(10);
	char* value = (char*)malloc(dsize - 10);
	sprintf(key, "%010d", i);
	sprintf(value, "%d", i);
	if (!setData(key, 10, value, dsize - 10)) {
		printf("Cannot insert Key: %d\n", i);
		i++;
		return false;
	}
	i++;
	return true;
}

bool MyRedis::t_multiInsert(int amount, size_t dsize) {
	for (int i = 0; i < amount; i++) {
		if (!t_singleInsert(dsize)) {
			return false;
		}
	}
	return true;
}

bool MyRedis::t_test() {
	
}
