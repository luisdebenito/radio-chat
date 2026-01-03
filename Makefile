TARGET := transmitter

SOURCES := \
	main.cpp \
	src/common/idGenerator.cpp \
	src/common/message.cpp \
	src/common/crcGenerator.cpp \
	src/common/package.cpp \
	src/transmission/packageBuilder.cpp \
	src/transmission/waveFormEncoder.cpp \
	src/transmission/transmissionManager.cpp \
	src/transmission/waveFormQueue.cpp \
	src/reception/waveFormDecoder.cpp

.PHONY: all run clean

all:
	clang++ -std=c++20 -Iinclude $(SOURCES) -o $(TARGET)
	./$(TARGET)
clean:
	rm -f $(TARGET)
