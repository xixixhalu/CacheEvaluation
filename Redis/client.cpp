#include "MyRedis.h"

int main(int argc, char **argv) {
    
	const char *hostname = (argc > 1) ? argv[1] : IP_ADDRESS;
    int port = (argc > 2) ? atoi(argv[2]) : PORT_NUM;

	MyRedis r(hostname, port);

    r.pingServer();
	
	r.t_singleInsert(1000);
	//r.t_multiInsert(1000, 1000);

    return 0;
}
