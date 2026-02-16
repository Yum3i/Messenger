CC=g++
CFLAGS=-std=c++11 -Wall -Wextra
SOURCES=main.cpp Connection.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=client2
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)