PROJ_DIR = $(shell pwd)
SRC_DIR = $(PROJ_DIR)/src
INC_DIR = $(PROJ_DIR)/include
OBJ_DIR = $(PROJ_DIR)/obj
BIN_DIR = $(PROJ_DIR)/bin


# $@: target $^: all dependecies $<: first dependency
$(BIN_DIR)/myshell: $(OBJ_DIR)/myshell.o | $(BIN_DIR)
	gcc -o $@ $^ 

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# -c : compile only -I: include directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc -c -o $@ $< -I$(INC_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell

distclean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell
	rm -rf $(OBJ_DIR) $(BIN_DIR)