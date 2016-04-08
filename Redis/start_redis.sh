cd ./config
gnome-terminal --tab --title="server" -e "redis-server redis.conf"
cd ..
gnome-terminal --tab --title="client" -e "redis-cli"

#config set maxmemory 1m
#config set maxmemory-policy noeviction #allkeys-lru

