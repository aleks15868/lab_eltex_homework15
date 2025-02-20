BIN_CLIENT = client
BIN_SERVER = server

CC = gcc
LIBRARY = -pthread -lncurses

PREF_SRC_GRAP = ./create_client/graphic/
PREF_SRC_LOGIC = ./create_client/logic/
PREF_OBJ = ./object_client/

PREF_SERVER_SRC = ./create_server/
PREF_SERVER_OBJ = ./object_server/

SRC_SERVER = $(wildcard $(PREF_SERVER_SRC)*.c)
OBJ_SERVER = $(patsubst $(PREF_SERVER_SRC)%.c, $(PREF_SERVER_OBJ)%.o, $(SRC_SERVER))


SRC_GRAP = $(wildcard $(PREF_SRC_GRAP)*.c)
SRC_LOGIC = $(wildcard $(PREF_SRC_LOGIC)*.c)
OBJ_GRAP = $(patsubst $(PREF_SRC_GRAP)%.c, $(PREF_OBJ)%.o, $(SRC_GRAP))
OBJ_LOGIC = $(patsubst $(PREF_SRC_LOGIC)%.c, $(PREF_OBJ)%.o, $(SRC_LOGIC))

.PHONY : all clean_server
.PHONY : all clean_client
.PHONY : all clean

$(BIN_SERVER) : $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) $(LIBRARY) -o $(BIN_SERVER) 

$(BIN_CLIENT) : $(OBJ_GRAP) $(OBJ_LOGIC)
	$(CC) $(OBJ_GRAP) $(OBJ_LOGIC) $(LIBRARY) -o $(BIN_CLIENT) 

$(PREF_OBJ)%.o : $(PREF_SRC_GRAP)%.c
	$(CC) -c $< -o $@

$(PREF_OBJ)%.o : $(PREF_SRC_LOGIC)%.c
	$(CC) -c $< -o $@

$(PREF_SERVER_OBJ)%.o : $(PREF_SERVER_SRC)%.c
	$(CC) -c $< -o $@

clean_server : 
	rm $(BIN_SERVER) $(PREF_SERVER_OBJ)*.o 

clean_client : 
	rm $(BIN) $(PREF_OBJ)*.o 

clean : 
	rm $(BIN_CLIENT) $(BIN_SERVER) $(PREF_OBJ)*.o $(PREF_SERVER_OBJ)*.o 