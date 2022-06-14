SERVER_NAME = server
CLIENT_NAME = client

SRCS_DIR = ./src
OBJS_DIR = ./obj
BIN_DIR = ./bin

SERVER_SRCS = TCPEchoServer.c \
			  HandleTCPClient.c \
			  DieWithError.c \
			  PrintHostInfo.c \
			  $(NULL)

SERVER_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SERVER_SRCS:.c=.o)))

CLIENT_SRCS = TCPEchoClient.c \
			  DieWithError.c \
			  ResolveName.c \
			  PrintHostInfo.c \
			  $(NULL)

CLIENT_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(CLIENT_SRCS:.c=.o)))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(BIN_DIR)/$@

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(BIN_DIR)/$@

clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(RM) $(BIN_DIR)/$(SERVER_NAME)
	$(RM) $(BIN_DIR)/$(CLIENT_NAME)
