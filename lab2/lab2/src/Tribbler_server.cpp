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
    
  const string USER_PREFIX = "jbu_user_";
  const string SET_PREFIX = "jbu_set_";

  TribblerHandler(std::string storageServer, int storageServerPort) {
    // Your initialization goes here
    _storageServer = storageServer;
    _storageServerPort = storageServerPort;
  }

  TribbleStatus::type CreateUser(const std::string& userid) {
    // Your implementation goes here
    printf("CreateUser\n");

    // determine if user exists, if not create the json, put the json

    // determine if user already exists
    KeyValueStore::GetResponse get_ret_val = Get(userid);
    if(get_ret_val.status == KVStoreStatus::OK || get_ret_val.value.length() != 0)
    {
       return TribbleStatus::EEXISTS; 
    } 

    // user does not exist, so create the json and put it
    Json::Value root;
    root["curSetNum"] = 0;
    root["listOfSubscribers"] = Json::nullValue; 
    
    Json::StyledWriter writer;
    string value = writer.write(root);

    string key = string("jbu_user_").append(userid);

    // put the json
    KVStoreStatus::type put_ret_val = Put(key, value);

    if(put_ret_val == KVStoreStatus::OK)
    {
        return TribbleStatus::OK;
    }
    else
    {
       return TribbleStatus::NOT_IMPLEMENTED; 
    }

    /*
    KVStoreStatus::type Put(std::string key, std::string value) {
    KeyValueStore::GetResponse Get(std::string key)
    GetListResponse glr = GetList(key); 
    if(glr.status != KVStoreStatus::OK)
        KVStoreStatus::type kvss = AddToList(key, userid);
    */
  }

  TribbleStatus::type AddSubscription(const std::string& userid, const std::string& subscribeto) {
    // Your implementation goes here
    printf("AddSubscription\n");

    // get the user info, parse the json, add the subscription, put the json

    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(get_ret_val.status == KVStoreStatus::EKEYNOTFOUND ||
       get_ret_val.status == KVStoreStatus::EITEMNOTFOUND) // NOT SURE WE NEED THIS*************************************** 
    {
        return TribbleStatus::INVALID_USER;
    }

    KeyValueStore::GetResponse get_subscribe_ret_val = Get(string(USER_PREFIX).append(subscribeto)); 
    if(get_subscribe_ret_val.status == KVStoreStatus::EKEYNOTFOUND ||
       get_subscribe_ret_val.status == KVStoreStatus::EITEMNOTFOUND) // NOT SURE WE NEED THIS*************************************** 
    {
        return TribbleStatus::INVALID_SUBSCRIBETO;
    }

    Json::Value user_info;
    Json::Reader reader;
    bool parse_ret_value = reader.parse(get_ret_val.value, user_info);
    if(parse_ret_value)
    {
        return TribbleStatus::NOT_IMPLEMENTED; //***************   
    }
    const Json::Value list_of_subscribers = user_info["listOfSubscribers"];
    Json::Value list_of_subscribers_copy = list_of_subscribers;
    Json::Value new_list_of_subscribe_tos = list_of_subscribers_copy.append(subscribeto);
    user_info["listOfSubscribers"] = new_list_of_subscribe_tos;

    Json::StyledWriter writer;
    string value = writer.write(user_info);

    // put the json
    KVStoreStatus::type put_ret_val = Put(string(USER_PREFIX).append(userid), value);
    if(put_ret_val != KVStoreStatus::OK)
    {
        return TribbleStatus::NOT_IMPLEMENTED; //*************
    } 

    return TribbleStatus::OK;
  }

  TribbleStatus::type RemoveSubscription(const std::string& userid, const std::string& subscribeto) {
    // Your implementation goes here
    printf("RemoveSubscription\n");

    // get user info for userid, look thru his subscribers and if subscsribeto is found, then remove it and put

    // get user info
    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(get_ret_val.status == KVStoreStatus::EKEYNOTFOUND ||
       get_ret_val.status == KVStoreStatus::EITEMNOTFOUND) // NOT SURE WE NEED THIS*************************************** 
    {
        return TribbleStatus::INVALID_USER;
    }

    
    // find the subscriber in question
    // TODO: IMPLEMENT THIS***************************
    Json::Value user_info;
    Json::Reader reader;
    bool parse_ret_value = reader.parse(get_ret_val.value, user_info);
    if(parse_ret_value)
    {
        return TribbleStatus::NOT_IMPLEMENTED; //***************   
    }
    const Json::Value list_of_subscribers = user_info["listOfSubscribers"];
    
    Json::Value new_list_of_subscribers;
    bool changed = false;
    // populate new list

    // if subscribeto wasn't found then return error
    if(!changed)
    {
       return TribbleStatus::INVALID_SUBSCRIBETO; 
    }

    // if subscribe to was found, then put the new user info
    user_info["listOfSubscribers"] = new_list_of_subscribers;

    // write the new json
    Json::StyledWriter writer;
    string value = writer.write(user_info);
    
    // put the new json
    KVStoreStatus::type put_ret_val = Put(string(USER_PREFIX).append(userid), value);
    if(put_ret_val != KVStoreStatus::OK)
    {
        return TribbleStatus::NOT_IMPLEMENTED; //*************
    } 

    return TribbleStatus::OK;
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
