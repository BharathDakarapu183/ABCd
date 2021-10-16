all: Server Client

Server:
	gcc server.c -o server

Client:
	gcc client.c -o client
	
clean: cS cC

cS:
	$(RM) server

cC:
	$(RM) client
 
