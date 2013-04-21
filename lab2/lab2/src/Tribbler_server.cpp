// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.


#include <stdio.h>
#include <errno.h>
#include <iostream>
#include "Tribbler.h"
#include "KeyValueStore.h"
#include <transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#define JSON_IS_AMALGAMATION
#include <json/json.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace std;
using namespace Tribbler;
using namespace KeyValueStore;

class TribblerHandler : virtual public TribblerIf {
 public:

  TribblerHandler(std::string storageServer, int storageServerPort) {
    // Your initialization goes here
    _storageServer = storageServer;
    _storageServerPort = storageServerPort;
  }

  TribbleStatus::type CreateUser(const std::string& userid) {
    // Your implementation goes here
    printf("CreateUser\n");
    string key = "user_list_jbu";
    GetListResponse glr = GetList(key); 
    if(glr.status != KVStoreStatus::OK)
    {
        // first time: we need to insert the list
        // just add the list

        // try to add it to the list
        KVStoreStatus::type kvss = AddToList(key, userid);
        if(kvss == KVStoreStatus::OK)
        {
            return TribbleStatus::OK;
        }
        else
        {
            // wtf ??? no corresponding error message *********************
            return TribbleStatus::NOT_IMPLEMENTED;
        }
    }
    else
    {
        // list exists
        
        // check if user exists
        vector<string>& values= glr.values;
        vector<string>::iterator iter;
        bool found = false;
        for(iter = values.begin(); iter != values.end(); iter++)
        {
            if(iter->compare(userid) == 0)
            {
                found = true;
                break;
            }
        }

        // user exists, don't do anything
        if(found == true)
        {
            return TribbleStatus::EEXISTS;
        }
        // user doesn't exist, add it to the list
        else
        {
            // try to add it to the list
            KVStoreStatus::type kvss = AddToList(key, userid);
            if(kvss == KVStoreStatus::OK)
            {
                return TribbleStatus::OK;
            }
            else
            {
                // wtf ??? no corresponding error message *********************
                return TribbleStatus::NOT_IMPLEMENTED;
            }
        }
    }
  }

  TribbleStatus::type AddSubscription(const std::string& userid, const std::string& subscribeto) {
    // Your implementation goes here
    printf("AddSubscription\n");

    Json::Value root;
    root["timestamp"] = Json::Value(555);


    Json::StyledWriter writer;
    string output_json = writer.write(root);

    return TribbleStatus::NOT_IMPLEMENTED;
  }

  TribbleStatus::type RemoveSubscription(const std::string& userid, const std::string& subscribeto) {
    // Your implementation goes here
    printf("RemoveSubscription\n");
    return TribbleStatus::NOT_IMPLEMENTED;
  }

  TribbleStatus::type PostTribble(const std::string& userid, const std::string& tribbleContents) {
    // Your implementation goes here
    printf("PostTribble\n");
    return TribbleStatus::NOT_IMPLEMENTED;
  }

  void GetTribbles(TribbleResponse& _return, const std::string& userid) {
    // Your implementation goes here
    _return.status = TribbleStatus::NOT_IMPLEMENTED;
    printf("GetTribbles\n");
  }

  void GetTribblesBySubscription(TribbleResponse& _return, const std::string& userid) {
    // Your implementation goes here
    _return.status = TribbleStatus::NOT_IMPLEMENTED;
    printf("GetTribblesBySubscription\n");
  }

  void GetSubscriptions(SubscriptionResponse& _return, const std::string& userid) {
    // Your implementation goes here
    _return.status = TribbleStatus::NOT_IMPLEMENTED;
    printf("GetSubscriptions\n");
  }

  // Functions from interacting with the storage RPC server
  KeyValueStore::GetListResponse GetList(std::string key) {
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient kv_client(protocol);
    // Making the RPC Call
    KeyValueStore::GetListResponse glr;
    transport->open();
    kv_client.GetList(glr, key);
    transport->close();
    return glr;
  }

  KVStoreStatus::type AddToList(std::string key, std::string value) {
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient kv_client(protocol);
    // Making the RPC Call
    KVStoreStatus::type st;
    transport->open();
    st = kv_client.AddToList(key, value);
    transport->close();
    return st;
  }

  KVStoreStatus::type RemoveFromList(std::string key, std::string value) {
    // Making the RPC Call to the Storage server
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    KVStoreStatus::type st;
    transport->open();
    st = client.RemoveFromList(key, value);
    transport->close();
    return st;
  }

  KVStoreStatus::type Put(std::string key, std::string value) {
    // Making the RPC Call to the Storage server
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    KVStoreStatus::type st;
    transport->open();
    st = client.Put(key, value);
    transport->close();
    return st;
  }

  KeyValueStore::GetResponse Get(std::string key) {
    KeyValueStore::GetResponse response;
    // Making the RPC Call to the Storage server
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    transport->open();
    client.Get(response, key);
    transport->close();
    return response;
  }

 private:
  std::string _storageServer;
  int _storageServerPort;
};

int main(int argc, char **argv) {
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " <storageServerIP> <storageServerPort> <tribbleServerPort>" << endl;
    exit(0);
  }
  std::string storageServer = std::string(argv[1]);
  int storageServerPort = atoi(argv[2]);
  int tribblerPort = atoi(argv[3]);

  shared_ptr<TribblerHandler> handler(new TribblerHandler(storageServer, storageServerPort));
  shared_ptr<TProcessor> processor(new TribblerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(tribblerPort));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  cout << "Starting Tribbler Server" << endl;
  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
