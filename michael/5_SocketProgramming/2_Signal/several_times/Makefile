NAME = sigaction

SRCS_DIR = ./src
OBJS_DIR = ./obj
BIN_DIR = ./bin

SRCS = SigAction.c \
			 DieWithError.c \
			 $(NULL)

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN_DIR)/$@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(BIN_DIR)/$(NAME)
