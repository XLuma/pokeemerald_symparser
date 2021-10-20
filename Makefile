NAME = sym_parser

all: $(NAME)

$(NAME):
	$(MAKE) -C ./42-libft
	gcc sym_parser.c 42-libft/libft.a -o $(NAME)