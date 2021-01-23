CXX = g++

CXX_FLAGS = -g -Wall -DDEBUG
LIBS = -lprotobuf
INCS =

BIN = mybin

export LD_LIBRARY_PATH=/usr/local/lib
 
CC_SRCS = $(wildcard *.cc)
CPP_SRCS = $(wildcard *.cpp)
 
CC_OBJS = $(CC_SRCS:.cc=.o)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)
OBJS = $(CC_OBJS) $(CPP_OBJS)
 
all : $(BIN)
 
$(BIN) : $(OBJS)
	$(CXX) -std=c++11 $(CXX_FLAGS) $(LIBS) -o $@ $^
     
$(CC_OBJS) : %.o : %.cc
	$(CXX) -std=c++11 $(CXX_FLAGS) $(INCS) -c $<
     
$(CPP_OBJS) : %.o : %.cpp
	$(CXX) -std=c++11 $(CXX_FLAGS) $(INCS) -c $<
     
.PHONY : clean
clean:
	@rm -f *.o $(BIN)
