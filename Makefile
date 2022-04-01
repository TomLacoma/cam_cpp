CLIENT = client.o
SERVER = server.o edit_html.o

all: client server

server: $(SERVER)
	c++ -o server $(SERVER) -lpthread

client: $(CLIENT)
	c++ -o client $(CLIENT)

edit_html: edit_html.o
	c++ -o edit_html edit_html.o -Wall -Wshadow -Werror -O

test: test.o
	c++ -o test test.o

-include $(CLIENT:.o=.d)
-include $(SERVER:.o=.d)

%.o: %.cpp
	c++ -c $*.cpp -o $*.o -Wall -Wshadow -Werror -O
	c++ -MM $*.cpp > $*.d
