NAME=a.out

CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -pedantic-errors -Wno-newline-eof -g -std=c++98
LDFLAGS =-fsanitize=address -fsanitize=undefined

FILES = main.cpp

VPATH = ./src

OUTPUTDIR = ./bin

OBJ=$(FILES:%.cpp=$(OUTPUTDIR)/%.o)

$(OUTPUTDIR)/%.o: %.cpp
	mkdir -p $(OUTPUTDIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	-rm -f $(OBJ)
	-rm -d $(OUTPUTDIR)

fclean: clean
	-rm -f $(NAME)

re: fclean all

syntax:
	$(CXX) -fsyntax-only -I./libft/ -Weverything -Wno-newline-eof -Wno-padded $(FILES)

.PHONEY: fclean clean all re syntax