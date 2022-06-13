VERSION = -std=c++14
CFLAGS = -pedantic -Wall -Wextra -fno-elide-constructors $(VERSION) $(DEBUG)
LFLAGS = -Wall $(VERSION) $(DEBUG)

INCS = stack.h
SRCS = stacksearch.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = search

all: $(SRCS) $(EXEC)

# To make an object from source
#.cpp.o: 
%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) 
	$(CXX) $(LFLAGS) $(OBJS) -o $@
   
# for Windows
clean:
	del *.o  $(EXEC).exe
	@echo clean done
   
# for UNIX / Linux 
#remove:
#	\rm -f *.o  $(EXEC)
#	@echo clean done
