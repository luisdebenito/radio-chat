TARGET := build/transmitter
CONF := build/config.conf
SOURCES := \
	main.cpp \
	src/common/idGenerator.cpp \
	src/common/message.cpp \
	src/common/crcGenerator.cpp \
	src/common/package.cpp \
	src/common/config.cpp \
	src/transmission/packageBuilder.cpp \
	src/transmission/transmissionManager.cpp \
	src/transmission/packageQueue.cpp  \
	src/transmission/loRaSender.cpp 

.PHONY: all run clean

all:
	clang++ -std=c++20 -Iinclude $(SOURCES) -o $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	
run:
	./$(TARGET)

config:
	@echo "maxBytes=64" > $(CONF)
	@echo "devicePort=/dev/ttyUSB0" >> $(CONF)
	@echo "baudRate=9600" >> $(CONF)
