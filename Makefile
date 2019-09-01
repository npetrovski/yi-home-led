CC=arm-hisiv300-linux-gcc
USER_CFLAGS=-march=armv5te -mcpu=arm926ej-s -I/opt/hisi-linux/x86-arm/arm-hisiv300-linux/target/usr/include -L/opt/hisi-linux/x86-arm/arm-hisiv300-linux/target/usr/lib
USER_LDFLAGS=
AR=arm-hisiv300-linux-ar
RANLIB=arm-hisiv300-linux-ranlib
STRIP=arm-hisiv300-linux-strip

TARGET = led

BUILD_DIR =   dist
SRC_DIR =     src
INCLUDE_DIR = include

CFLAGS = -Os 
LIBS = 

.PHONY: default all clean directories

default: directories $(TARGET)
all: default

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $(BUILD_DIR)/$@
	$(STRIP) $(BUILD_DIR)/$(TARGET)
	
directories:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/$(TARGET)
