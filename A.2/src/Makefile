include $(BUILD_DIR)/makefile.config

SERVER_SRC = server.c
CLIENT_SRC = client.c
COMMON_SCR = common.c

SERVER_OBJ = $(SERVER_SRC:.c = .o)
SERVER_OBJ += $(COMMON_SCR:.c = .o)
CLIENT_OBJ = $(CLIENT_SRC:.c = .o)
CLIENT_OBJ += $(COMMON_SCR:.c = .o)


include $(BUILD_DIR)/makefile.build