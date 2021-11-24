
.PHONY: all

export DEBUG ?= true
export SERVER_NAME := calc_server
export CLIENT_NAME := calc_client

export SRC_DIR   := $(CURDIR)/src
export INC_DIR   := $(CURDIR)/include
export BUILD_DIR := $(CURDIR)/build

export IP_SERVER := 127.0.0.1
export PORT_SERVER := 5054

all:
	$(MAKE) -C $(SRC_DIR) all

clean:
	$(MAKE) -C $(SRC_DIR) clean

server:
	@exec $(BUILD_DIR)/$(SERVER_NAME) -p $(PORT_SERVER)

client:
	@exec $(BUILD_DIR)/$(CLIENT_NAME) -a $(IP_SERVER) -p $(PORT_SERVER)

test: all
	make server &
	make client &