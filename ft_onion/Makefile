all:	install start

start:
	docker-compose -f docker-compose.yml up

stop:
	docker-compose -f docker-compose.yml stop

clean:
	docker-compose -f docker-compose.yml down

totalclean: 
	docker system prune -a
re: stop clean all 

	
.PHONY: install start stop clean all re
