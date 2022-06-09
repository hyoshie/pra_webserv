SERVER_NAME = server
CLIENT_NAME = client

CFLAGS = -g

SRCS_DIR = ./src
OBJS_DIR = ./obj
BIN_DIR = ./bin

SERVER_SRCS = UDPEchoServer.c \
			 DieWithError.c \
			 $(NULL)

SERVER_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SERVER_SRCS:.c=.o)))

CLIENT_SRCS = UDPEchoClient-Timeout.c \
			 DieWithError.c \
			 $(NULL)

CLIENT_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(CLIENT_SRCS:.c=.o)))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS_DIR) $(SERVER_NAME) $(CLIENT_NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(BIN_DIR)/$@

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(BIN_DIR)/$@

clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(RM) $(BIN_DIR)/$(SERVER_NAME)
	$(RM) $(BIN_DIR)/$(CLIENT_NAME)
