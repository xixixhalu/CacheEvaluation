client: client.cpp MyRedis.o
	g++ client.cpp MyRedis.o -o client -L/usr/local/lib/ -lhiredis

MyRedis.o: MyRedis.cpp MyRedis.h
	g++ -c MyRedis.cpp -o MyRedis.o -L/usr/local/lib/ -lhiredis

clean:
	rm *.o
	rm client

cdb:
	rm ./config/dump.rdb
