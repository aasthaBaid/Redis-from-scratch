# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall -Wextra -Wpedantic -O2 -g

# Directories
CLIENT_DIR = Client

# Source files
CLIENT_SRC = $(CLIENT_DIR)/main.cpp $(CLIENT_DIR)/my_redis_cli.cpp $(CLIENT_DIR)/utils.cpp 

# Target executables
CLIENT_TARGET = my_redis_cli 

# Build rules
all: $(CLIENT_TARGET)

$(CLIENT_TARGET): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean build files
clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)

# Force rebuild
re: clean all