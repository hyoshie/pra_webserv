SERVER_NAME = server

CFLAGS	=	-g

SRCS_DIR = ./src
OBJS_DIR = ./obj

SERVER_SRCS = AcceptTCPConeection.c \
			  CreateTCPSocket.c \
			  DieWithError.c \
			  Main.c \
			  HttpServer.c \
			  $(NULL)

SERVER_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SERVER_SRCS:.c=.o)))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS_DIR) $(SERVER_NAME) $(CLIENT_NAME)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $@

clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_NAME)

re: fclean all
