NAME		=	kmeans    
LD			=	$(CC)
DEBUG		+=	#-DDEBUG
CFLAGS		+=	-O0 -lm $(DEBUG)
CXXFLAGS	+=	$(CFLAGS)
LDFLAGS		+=

EXE			=	$(NAME)
CFILES		=	$(wildcard *.c)
CXXFILES	=	$(wildcard *.cpp)
OBJECTS		=	$(CFILES:.c=.o) $(CXXFILES:.cpp=.o)

all : $(EXE)
	@echo "Building..."

$(EXE) : $(OBJECTS)
	$(LD) -pthread $^ $(CFLAGS) $(LDFLAGS) -o $@ 

%.o : %.c
	$(CC) -pthread $(CFLAGS) -c $< -o $@ 

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm -fr $(EXE) $(OBJECTS)

run: $(EXE)
	./$(EXE) < input.txt > output.txt
