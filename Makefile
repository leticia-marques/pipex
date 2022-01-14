NAME		= pipex
BONUS_NAME = pipex_bonus

SRC_DIR 	= ./sources
UTILS_DIR	= utils
SHARED_DIR	= shared
BONUS_DIR	= ./sources
BIN_DIR		= ./bin

MANDATORY_FILE = $(addprefix $(BIN_DIR)/,$(NAME))
BONUS_FILE = $(addprefix $(BIN_DIR)/, $(BONUS_NAME))

SHARED_FILES = find_command_path.c errors.c  get_path.c
SHARED_PATH  = $(addprefix $(SHARED_DIR)/, $(SHARED_FILES))

UTILS_FILES	= ft_putendl_fd.c ft_split_free.c ft_strjoin.c ft_strncmp.c
UTILS_FILES+= ft_strdup.c ft_strchr.c ft_strlen.c ft_strlcpy.c
UTILS_FILES+= ft_substr.c ft_split.c ft_strcmp.c get_next_line.c
UTILS_PATH  = $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

SRC_FILES	= pipex.c $(SHARED_PATH) $(UTILS_PATH)
BONUS_FILES = pipex_bonus.c main_bonus.c
BONUS_FILES+= $(SHARED_PATH) $(UTILS_PATH)

OBJ_DIR  = ./objs
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

BONUS_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.c=.o))

INC = -I ./includes
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM  = rm -rf

MKDIR = mkdir -p $(@D)

.DEFAULT_GOAL = all

all : $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(MKDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):    $(MANDATORY_FILE)

$(MANDATORY_FILE): $(OBJ_FILES)
	$(MKDIR)
	$(RM) $(BONUS_FILE)
	$(CC) $(CFLAGS) $(INC) $(OBJ_FILES) -o $(MANDATORY_FILE)
	cp $(MANDATORY_FILE) $(NAME)

bonus:	$(BONUS_NAME)

$(BONUS_NAME):	$(BONUS_FILE)

$(BONUS_FILE):	$(BONUS_OBJ_FILES)
	$(MKDIR)
	$(RM) $(MANDATORY_FILE)
	$(CC) $(CFLAGS) $(INC) $(BONUS_OBJ_FILES) -o $(BONUS_FILE)
	cp $(BONUS_FILE) $(NAME)
clean:
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	$(RM) $(BIN_DIR)

re: fclean all

rebonus: fclean bonus
