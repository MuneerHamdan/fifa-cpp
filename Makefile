file=futcplusplus

all:
	g++ $(file).cpp -Wall -Werror -fsanitize=address,undefined -g -lsfml-graphics -lsfml-window -lsfml-system -std=c++23
	./*.out
