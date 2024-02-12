NAME=a.out

CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -pedantic-errors -Wno-newline-eof -g -std=c++98 -I./includes
LDFLAGS =-fsanitize=address -fsanitize=undefined

FILES = main.cpp Logger.cpp

VPATH = ./src/

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
	$(CXX) -fsyntax-only -I./includes/ -Weverything -Wno-newline-eof -Wno-padded $(FILES:%=./src/%)

.PHONEY: fclean clean all re syntax