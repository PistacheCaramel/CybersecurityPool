
build	: 
	docker build -t env_spider .
run	: 
	docker run -v ./src:/arachnida -it env_spider

all	:	build run
clean	:
		rm -rf ./src/*
		docker stop env_spider
		docker rm env_spider


re	:	clean all
		

.PHONY	:	all build run clean re
