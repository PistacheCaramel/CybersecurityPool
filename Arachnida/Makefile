
all	:	build run

build	: 
	docker build -t env_spider .
run	: 
	docker run -v ./src:/arachnida -it env_spider

clean	:
		docker stop $$(docker ps -a -q)
		docker rm $$(docker ps -a -q)
		docker rmi $$(docker images -a -q)


re	:	clean all
		

.PHONY	:	all build run clean re
