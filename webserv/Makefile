NAME=a.out

CXX = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -pedantic-errors -g -std=c++98 -I./includes
LDFLAGS =-fsanitize=address -fsanitize=undefined -ljson.a

SRC = main.cpp Logger.cpp itos.cpp Ahttp.cpp AHttpRequest.cpp HttpResponse.cpp\
		HttpHeaders.cpp HttpFactory.cpp FdStream.cpp
METHODS = Get.cpp

FILES = $(SRC)
FILES += $(METHODS)

JSONSRC = JsonToken.cpp JsonArray.cpp JsonExceptions.cpp JsonObject.cpp JsonReader.cpp JsonValue.cpp JsonContainer.cpp
JSONOBJ = $(JSONSRC:%.cpp=$(OUTPUTDIR)/json/%.o)

VPATH = ./src/ ./src/Methods ./src/json

OUTPUTDIR = ./bin

OBJ=$(FILES:%.cpp=$(OUTPUTDIR)/%.o)

$(OUTPUTDIR)/%.o: %.cpp
	mkdir -p $(OUTPUTDIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OUTPUTDIR)/json/%.o: %.cpp
	mkdir -p $(OUTPUTDIR)
	mkdir -p $(OUTPUTDIR)/json
	$(CXX) -c $(CXXFLAGS) $< -o $@

all: $(NAME)

json.a: $(JSONOBJ)
	ar rvs json.a $(JSONOBJ)

$(NAME): json.a $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	-rm -f $(OBJ)
	-rm -f $(JSONOBJ)
	-rm -d $(OUTPUTDIR)/json
	-rm -d $(OUTPUTDIR)

fclean: clean
	-rm -f $(NAME)
	-rm -f json.a

re: fclean all

syntax:
	$(CXX) -fsyntax-only -I./includes/ -std=c++98 -Weverything \
	-Wno-suggest-override -Wno-suggest-destructor-override \
	-Wno-padded $(SRC:%=./src/%) $(METHODS:%=./src/Methods/%)

.PHONEY: fclean clean all re syntax json