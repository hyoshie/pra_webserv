build:
	@echo "### Compiling ###"
	@gcc client.c -o client
	@gcc iserver1.c -o server

.PHONY: server
server: 
	@gcc iserver1.c -o server
	@./server

.PHONY: client
client: 
	@gcc client.c -o client
	@./client

clean:
	rm -f client server a.out

re: clean build
