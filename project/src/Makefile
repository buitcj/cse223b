LOCAL_INCLUDE_DIR := /usr/local/include 
PQ_DIR := /usr/include/postgresql
INCLUDE := ../include
BACKUP_SERVER_SRC := BackupServer_server.cpp
BACKUP_SERVER_OBJ := $(patsubst %.cpp,%.o, $(BACKUP_SERVER_SRC))

INC := -I$(LOCAL_INCLUDE_DIR) -I/usr/local/include/thrift -I$(INCLUDE) -I$(PQ_DIR)
DEFINES := -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H

.PHONY: all clean

all: backup_server 

backup_server: 
	g++ $(DEFINES) -o backup_server $(INC) BackupServer_server.cpp BackupServer_types.cpp BackupServer_constants.cpp BackupServer.cpp -L/usr/local/lib -L/usr/lib -lthrift -lpq 

clean:
	$(RM) *.o backup_server 
