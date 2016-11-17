CXX=			g++ $(CCGLAGS)
CCFLAGS= -g -std=c++11 -Wall
LIBS=

UNIX_SERVER_MAIN=	unix_server_main.o unix_server.o
UNIX_CLIENT_MAIN=	unix_client_main.o unix_client.o
OBJS=			$(UNIX_SERVER_MAIN) $(UNIX_CLIENT_MAIN)

all:	unix_server_main unix_client_main

unix_server_main:$(UNIX_SERVER_MAIN)
		$(CXX) -o server $(UNIX_SERVER_MAIN) $(LIBS)

unix_client_main:$(UNIX_CLIENT_MAIN)
		$(CXX) -o client $(UNIX_CLIENT_MAIN) $(LIBS)

clean:
		rm -f $(OBJS)

allclean:
		rm -f $(OBJS)  server client

