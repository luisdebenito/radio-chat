TARGET := build/transmitter
CONF := build/config.conf
SOURCES := $(shell find . -name '*.cpp')

.PHONY: all run clean

all:
	clang++ -std=c++20 -Iinclude $(SOURCES) -o $(TARGET) -lX11
	./$(TARGET)

clean:
	rm -f $(TARGET)
	
run:
	./$(TARGET)

config:
	rm -f $(CONF)
	@echo "maxInputSize=80" >> $(CONF)
	@echo "maxChatHistory=30" >> $(CONF)
	@echo "windowWidth=800" >> $(CONF)
	@echo "windowHeight=400" >> $(CONF)
	@echo "devicePort=/dev/ttyUSB0" >> $(CONF)
	@echo "baudRate=9600" >> $(CONF)
