CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I../../src

SOURCES = math_module.cpp tests.cpp
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET =	tests

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
