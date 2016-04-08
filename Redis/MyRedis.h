#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits>

#include <hiredis/hiredis.h>

#define	IP_ADDRESS	"127.0.0.1"
#define	PORT_NUM	6379

class MyRedis {
public:
	MyRedis();
	MyRedis(const char* hostname, int port);
	~MyRedis();
	/*-------Utility Functions-------*/
	void initialize(const char* hostname, int port);
	void pingServer();
	bool setData(char* key, size_t ksize, char* value, size_t vsize);
	bool setData(char* key, char* value);

	/*-------Testing Functions-------*/
	bool t_singleInsert(size_t dsize);
	bool t_multiInsert(int amount, size_t dsize);

	bool t_test();
private:
	redisContext *c;
	redisReply *reply;
};
