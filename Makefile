TARGET := build/transmitter

SOURCES := \
	main.cpp \
	src/common/idGenerator.cpp \
	src/common/message.cpp \
	src/common/crcGenerator.cpp \
	src/common/package.cpp \
	src/transmission/packageBuilder.cpp \
	src/transmission/transmissionManager.cpp \
	src/transmission/packageQueue.cpp 

.PHONY: all run clean

all:
	clang++ -std=c++20 -Iinclude $(SOURCES) -o $(TARGET)
	./$(TARGET)
clean:
	rm -f $(TARGET)
