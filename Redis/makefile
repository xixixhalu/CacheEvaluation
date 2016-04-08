client: client.cpp MyRedis.o
	g++ client.cpp MyRedis.o -o client -L/usr/local/lib/ -lhiredis

MyRedis.o: MyRedis.cpp MyRedis.h
	g++ -c MyRedis.cpp -o MyRedis.o -L/usr/local/lib/ -lhiredis

clean:
	rm -f *.o client

# Remove backup of Redis-server
cdb:
	rm -f ./config/*.rdb *.rdb
