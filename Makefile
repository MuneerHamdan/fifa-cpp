file=futcplusplus

all:
	g++ $(file).cpp -o $(file).out -Wall -Werror -fsanitize=address,undefined -g -lsfml-graphics -lsfml-window -lsfml-system
	./$(file).out
