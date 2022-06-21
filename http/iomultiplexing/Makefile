SERVER_NAME = server
CLIENT_NAME = client

SRCS_DIR = ./src
OBJS_DIR = ./obj
BIN_DIR = ./bin

SERVER_SRCS = AcceptTCPConeection.cpp \
			  CreateTCPSocket.cpp \
			  DieWithError.cpp \
			  RepeatClientMessage.cpp \
			  TCPEchoServer-Select.cpp \
			  $(NULL)


SERVER_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SERVER_SRCS:.cpp=.o)))

CLIENT_SRCS = TCPEchoClient.cpp \
			  DieWithError.cpp \
			  $(NULL)

CLIENT_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(CLIENT_SRCS:.cpp=.o)))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CXX) $(CFLAGS) $(SERVER_OBJS) -o $(BIN_DIR)/$@

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CXX) $(CFLAGS) $(CLIENT_OBJS) -o $(BIN_DIR)/$@

clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(RM) $(BIN_DIR)/$(SERVER_NAME)
	$(RM) $(BIN_DIR)/$(CLIENT_NAME)
re: fclean all
