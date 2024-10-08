NAME = minishell

GREEN		=	\033[1;32m
RED			=	\033[1;31m
DEFAULT		=	\033[0m

OBJ_DIR		=	objs
INC_DIR		=	include
SRC_DIR		=	$(shell find srcs -type d)

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

RM			= /usr/bin/rm -rf

SRCS		=	main.c	\
				ft_env.c	\
				ft_env_utils.c	\
				utils3.c	\
				parsing_token.c	\
				parsing_rec.c	\
				parsing_rec_utils.c	\
				utils.c	\
				free.c	\
				utils2.c	\
				expand_quote.c \
				expand_utils.c \
				expand_quote_parsing_utils.c \
				expand_var.c \
				expand_spaces.c \
				ft_itoa.c		\
				exec.c		\
				exec_end.c		\
				pre_exec_utils.c	\
				redir_fct.c		\
				redir_heredoc.c		\
				redir_utils.c		\
				exec_utils.c		\
				exec_utils2.c		\
				cmd_utils.c			\
				pwd.c				\
				echo.c				\
				cd.c	\
				env.c	\
				unset.c	\
				exit.c	\
				shlvl.c	\
				signal.c	\
				export.c	\
				expand_ambigous_redirect.c	\
				export_utils.c	\
				export_utils2.c	\
				heredoc_quotes.c	\
				heredoc_quotes_utils.c	\
				redir_heredoc_utils.c


OBJS		=	$(SRCS:%.c=${OBJ_DIR}/%.o)

CC			=	clang
CFLAGS		=	-Werror -Wall -Wextra -g3

all:	${NAME}

$(NAME):	${OBJS} $(INC_DIR)/minishell.h

		@echo "$(YELLOW)Compiling in progress...$(RESET)"
		@{ ${CC} ${CFLAGS} -lreadline ${OBJS} -I ${INC_DIR} -o ${NAME} || \
			(echo "$(RED)Compilation failed.$(RESET)"; exit 1)}
		@echo -n "$(GREEN)[                    ]$(RESET)"
		@echo -n "\r$(GREEN)[=>                  ]$(RESET)"
		@sleep 0.1
		@echo -n "\r$(GREEN)[===>                ]$(RESET)"
		@sleep 0.1
		@echo -n "\r$(GREEN)[=====>              ]$(RESET)"
		@sleep 0.1
		@echo -n "\r$(GREEN)[========>           ]$(RESET)"
		@sleep 0.1
		@echo -n "\r$(GREEN)[===========>        ]$(RESET)"
		@sleep 0.1
		@echo -n "\r$(GREEN)[==============>     ]$(RESET)"
		@sleep 0.1
		@echo -n "\r$(GREEN)[==================>  ]$(RESET)"
		@sleep 0.1
		@echo "\r$(GREEN)[=====================$(RESET)"
		@echo "$(GREEN)Compilation completed.$(RESET)"
		@echo "$(CYAN)          _____    __ ____   __          __  __    __  $(RESET)"
		@echo "$(CYAN)  /\/\    \_  _\/\ \ \\_  _\ / __\ /\  /\/__\/ /   / /  $(RESET)"
		@echo "$(CYAN) /    \    / / /  \/ / / /  \ \  / /_/ /_\ / /   / /   $(RESET)"
		@echo "$(CYAN)/ /\/\ \/\/ /_/ /\  /\/ /_ __\ \/ __  //__/ /___/ /___ $(RESET)"
		@echo "$(CYAN)\/    \/\____/\_\ \/\____/ \___/\/ /_/\__/\____/\____/ $(RESET)"
		@echo "$(CYAN)                                                       $(RESET)"

$(OBJ_DIR)/%.o: %.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIR) :
	mkdir -p $@

clean:
		${RM} -r $(OBJ_DIR)

fclean:		clean
		${RM} ${NAME}

re:			fclean
		$(MAKE) all -j

.PHONY:		all clean fclean re
