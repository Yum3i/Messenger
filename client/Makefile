CC=g++
CFLAGS=-std=c++11 -Wall -Wextra
SOURCES=src/main.cpp src/Connection.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=client
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)