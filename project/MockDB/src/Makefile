LOCAL_INCLUDE_DIR := /usr/local/include
INCLUDE := ../include
MOCKDB_SERVER_SRC := MockDB_server.cpp MockDB_types.cpp MockDB_constants.cpp MockDB.cpp GeoPoint.cpp
MOCKDB_SERVER_OBJ := $(patsubst %.cpp,%.o, $(BACKUP_SERVER_SRC))

INC := -I$(LOCAL_INCLUDE_DIR) -I/usr/local/include/thrift -I$(INCLUDE)

DEFINES := -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H

.PHONY: all clean

all: mockdb_server 

mockdb_server: 
	g++ $(DEFINES) -o mockdb_server $(INC) $(MOCKDB_SERVER_SRC) -L/usr/local/lib -L/usr/lib -lthrift 

clean:
	$(RM) *.o mockdb_server 

