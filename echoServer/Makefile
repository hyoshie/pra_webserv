SERVER_NAME = server
CLIENT_NAME = client

SRCS_DIR = ./src
OBJS_DIR = ./obj

SERVER_SRCS = Server.cpp \
			  Selector.cpp \
			  main.cpp \
			  $(NULL)


SERVER_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SERVER_SRCS:.cpp=.o)))

CLIENT_SRCS = TCPEchoClient.cpp \
			  DieWithError.cpp \
			  $(NULL)

CLIENT_OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(CLIENT_SRCS:.cpp=.o)))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

.PHONY: all
all: $(OBJS_DIR) $(SERVER_NAME) $(CLIENT_NAME)

$(OBJS_DIR):
	mkdir $@

$(SERVER_NAME): $(SERVER_OBJS)
	$(CXX) $(CFLAGS) $(SERVER_OBJS) -o $@

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CXX) $(CFLAGS) $(CLIENT_OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

.PHONY: fclean
fclean: clean
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_NAME)

.PHONY: re
re: fclean all

.PHONY: lint
LINT_TARGET = $(shell find src -type f \( -name '*.cpp' -o -name '*.hpp' \))
lint:
	@cpplint --filter=-build/include_subdir,-legal/copyright \
			$(LINT_TARGET)
	@echo "$(GREEN)Clean Code:)$(END)"

## Color
END		= \e[0m
BOLD	= \e[1m
THIN	= \e[2m
ITALIC	= \e[3m
U_LINE	= \e[4m
BLACK	= \e[30m
RED		= \e[31m
GREEN	= \e[32m
YELLOW	= \e[33m
BLUE	= \e[34m
PURPLE	= \e[35m
CYAN	= \e[36m
WHITE	= \e[37m
