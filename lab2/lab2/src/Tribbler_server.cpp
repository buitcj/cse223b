// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include "Tribbler.h"
#include "KeyValueStore.h"
#include <transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <list>
#include <cctype>

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

struct TribbleHelper
{
    Json::Value tribble_set;
    string userid;
    uint64_t ts;
    int set;
    int idx;
};

class TribblerHandler : virtual public TribblerIf {
 public:
    
  string USER_PREFIX;
  string SET_PREFIX;
  unsigned int MAX_SET_SIZE;

  string TIMESTAMP;
  string MSG;

  string CUR_SET_NUM;
  string LIST_OF_SUBSCRIBERS;

  int MAX_MSGS;

  bool compare(const TribbleHelper& lhs, const TribbleHelper& rhs)
  {
      return (lhs.tribble_set[lhs.idx][TIMESTAMP].asUInt64() < rhs.tribble_set[rhs.idx][TIMESTAMP].asUInt64());
  }

  void addTribbleHelper(list<TribbleHelper>& ths, TribbleHelper& th)
  {
    list<TribbleHelper>::iterator iter = ths.begin();
    while(iter != ths.end() && iter->ts < th.ts)
    {
        iter++;
    }    
    ths.insert(iter, th);
    
    list<TribbleHelper>::iterator  it = ths.begin();
    while(it != ths.end())
    {
        cout << "\t" << it->ts << endl;
        it++;
    }
    cout << "---" << endl;
  }

  TribblerHandler(std::string storageServer, int storageServerPort) {
    // Your initialization goes here
    USER_PREFIX = "jbu_user_";
    SET_PREFIX = "jbu_set_";
    MAX_SET_SIZE = 5;
    TIMESTAMP = "timestamp";
    MSG = "msg";
    CUR_SET_NUM = "curSetNum";
    LIST_OF_SUBSCRIBERS = "listOfSubscribers";
    MAX_MSGS = 10;
    _storageServer = storageServer;
    _storageServerPort = storageServerPort;
  }

  TribbleStatus::type CreateUser(const std::string& userid) {
    printf("CreateUser\n");

    // determine if user exists, if not create the json, put the json

    // determine if user already exists
    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(get_ret_val.status == KVStoreStatus::OK || get_ret_val.value.length() != 0)
    {
       return TribbleStatus::EEXISTS; 
    } 

    // user does not exist, so create the json and put it
    Json::Value root;
    root[CUR_SET_NUM] = 0;
    root[LIST_OF_SUBSCRIBERS] = Json::Value(Json::arrayValue); 
    
    Json::StyledWriter writer;
    string value = writer.write(root);

    string key = string(USER_PREFIX).append(userid);

    // put the json
    KVStoreStatus::type put_ret_val = Put(key, value);

    if(put_ret_val == KVStoreStatus::OK)
    {
        return TribbleStatus::OK;
    }
    else
    {
        cout << "CreateUser couldn't store the key/val" << endl;
       return TribbleStatus::STORE_FAILED; 
    }
  }

  TribbleStatus::type AddSubscription(const std::string& userid, const std::string& subscribeto) {
    printf("AddSubscription\n");

    // get the user info, parse the json, add the subscription, put the json

    if(userid.compare(subscribeto) == 0) 
    {
        cout << "AddSubscription same user/subscribeto" << endl;
        return TribbleStatus::INVALID_SUBSCRIBETO;
    }

    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(userid.length() == 0 || get_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
    {
        cout << "AddSubscription user doesn't exist" << endl;
        return TribbleStatus::INVALID_USER;
    }

    KeyValueStore::GetResponse get_subscribe_ret_val = Get(string(USER_PREFIX).append(subscribeto)); 
    if(subscribeto.length() == 0 || get_subscribe_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
    {
        cout << "AddSubscription subscribeto doesn't exist" << endl;
        return TribbleStatus::INVALID_SUBSCRIBETO;
    }

    Json::Value user_info;
    Json::Reader reader;
    bool parse_ret_value = reader.parse(get_ret_val.value, user_info);
    if(parse_ret_value == false)
    {
        cout << "AddSubscription parsing failed" << endl;
        return TribbleStatus::FAILED; // for lack of a better enum
    }
    const Json::Value list_of_subscribers = user_info[LIST_OF_SUBSCRIBERS];
    Json::Value list_of_subscribers_copy = list_of_subscribers;
    
    bool found = false;
    for(unsigned int i = 0; i < list_of_subscribers_copy.size(); i++)
    {
        string subscriber = list_of_subscribers_copy[i].asString();
        if(subscriber.compare(subscribeto) == 0)
        {
            found = true;
            break;
        }
    }

    if(found == true)
    {
        cout << "AddSubscription failed to add a duplicate subscribeto" << endl;
        return TribbleStatus::EEXISTS;
    }

    list_of_subscribers_copy.append(subscribeto);
    user_info[LIST_OF_SUBSCRIBERS] = list_of_subscribers_copy;

    Json::StyledWriter writer;
    string value = writer.write(user_info);

    // put the json
    KVStoreStatus::type put_ret_val = Put(string(USER_PREFIX).append(userid), value);
    if(put_ret_val != KVStoreStatus::OK)
    {
        cout << "AddSubscription put the json failed" << endl;
        return TribbleStatus::STORE_FAILED;
    } 

    return TribbleStatus::OK;
  }

  TribbleStatus::type RemoveSubscription(const std::string& userid, const std::string& subscribeto) {
    printf("RemoveSubscription\n");

    // get user info for userid, look thru his subscribers and if subscsribeto is found, then remove it and put

    // get user info
    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(get_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
    {
        cout << "RemoveSubscription user not found" << endl;
        return TribbleStatus::INVALID_USER;
    }

    
    // find the subscriber in question
    Json::Value user_info;
    Json::Reader reader;
    bool parse_ret_value = reader.parse(get_ret_val.value, user_info);
    if(parse_ret_value == false)
    {
        cout << "RemoveSubscription parsing failed" << endl;
        return TribbleStatus::FAILED;
    }

    const Json::Value list_of_subscribers = user_info["listOfSubscribers"];
    Json::Value new_list_of_subscribers = Json::Value(Json::arrayValue);
    bool found = false;
    for(unsigned int i = 0; i < list_of_subscribers.size(); i++)
    {
        const string& subscriber = list_of_subscribers[i].asString();
        if(subscriber.compare(subscribeto) == 0)
        {
            found = true;
        }
        else
        {
            new_list_of_subscribers.append(subscriber);
        }
    }
    
    // if subscribe to was found, then put the new user info
    if(found == true)
    {
        user_info["listOfSubscribers"] = new_list_of_subscribers;
    }
    else
    {
        cout << "RemoveSubscription subscribeto not found" << endl;
        return TribbleStatus::INVALID_SUBSCRIBETO;
    }

    // write the new json
    Json::StyledWriter writer;
    string value = writer.write(user_info);
    
    // put the new json
    KVStoreStatus::type put_ret_val = Put(string(USER_PREFIX).append(userid), value);
    if(put_ret_val != KVStoreStatus::OK)
    {
        cout << "RemoveSubscription put json failed" << endl;
        return TribbleStatus::STORE_FAILED;
    } 

    return TribbleStatus::OK;
  }

  TribbleStatus::type PostTribble(const std::string& userid, const std::string& tribbleContents) {
    printf("PostTribble\n");

    // get user id, check if it exists, find the cur set number, retrieve the current set, add the tribble, store the set, if the set is larger than the max set size, update the cur set number

    // get user info
    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(get_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
    {
        cout << "PostTribble user doesn't exist" << endl;
        return TribbleStatus::INVALID_USER;
    }

    // get the current set number
    Json::Value user_info;
    Json::Reader reader;
    bool parse_ret_value = reader.parse(get_ret_val.value, user_info);
    if(parse_ret_value == false)
    {
        cout << "PostTribble parsing failed" << endl;
        return TribbleStatus::FAILED; 
    }
    const Json::Value cur_set_num_val = user_info[CUR_SET_NUM];
    int cur_set_num = cur_set_num_val.asInt();

    // set up the tribble
    Json::Value tribble;
    tribble[TIMESTAMP] = Json::Value((Json::UInt64) time(NULL));
    tribble[MSG] = tribbleContents;

    // retrieve the current set
    char buf[10];
    sprintf(buf, "%d", cur_set_num);
    KeyValueStore::GetResponse get_set_ret_val = Get(string(SET_PREFIX).append(buf).append("_").append(userid));
    Json::Value tribble_set;
    if(get_set_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
    {
        // if a key was not found, it could be because we're starting a new set
        tribble_set.append(tribble);
    }
    else
    {
        Json::Reader reader;
        bool parse_ret_value = reader.parse(get_set_ret_val.value, tribble_set);
        if(parse_ret_value == false)
        {
            return TribbleStatus::FAILED; // for lack of a better enum
        }

        // figure out where to put the tribble
        tribble_set.append(tribble);

        // if the tribble set is maxed out, we need to update the user's set num
        if(tribble_set.size() == MAX_SET_SIZE)
        {
            user_info[CUR_SET_NUM] = cur_set_num + 1;

            Json::StyledWriter writer;
            string value = writer.write(user_info);
            KVStoreStatus::type put_ret_val = Put(string(USER_PREFIX).append(userid), value);
            if(put_ret_val != KVStoreStatus::OK)
            {
                // do nothing for now 
            }
        }
    }

    Json::StyledWriter writer;
    string value = writer.write(tribble_set);
    KVStoreStatus::type put_set_ret_val = Put(string(SET_PREFIX).append(buf).append("_").append(userid), value);
    if(put_set_ret_val != KVStoreStatus::OK)
    {
        cout << "PostTribble put set failed" << endl;
        return TribbleStatus::STORE_FAILED;
    }

    return TribbleStatus::OK;
  }

  void GetTribbles(TribbleResponse& _return, const std::string& userid) {
    printf("GetTribbles\n");

    // get the user, if it doesn't exist, then return error, if it does exist then get the curSetNumber and work backwards down to 0
    
    // get the user info
    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(get_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
    {
        cout << "GetTribbles user not found" << endl;
        _return.status = TribbleStatus::INVALID_USER;
        return;
    }

    // get the curSetNumber and work backwards to return the tribbles
    Json::Reader reader;
    Json::Value user_info;
    bool parse_ret_value = reader.parse(get_ret_val.value, user_info);
    if(parse_ret_value == false)
    {
        cout << "GetTribbles parsing failed" << endl;
        _return.status = TribbleStatus::FAILED; 
        return;
    }

    const Json::Value cur_set_num_val = user_info[CUR_SET_NUM];
    int cur_set_num = cur_set_num_val.asInt();
    
    int count = 0;
    for(int i = cur_set_num; i >= 0 && count < MAX_MSGS; i--)
    {
        char buf[10];
        sprintf(buf, "%d", i);
        KeyValueStore::GetResponse get_set_ret_val = Get(string(SET_PREFIX).append(buf).append("_").append(userid));
        if(get_set_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
        {
            // user has no tribble posts yet so he won't have a set
            continue;
        }

        Json::Reader reader;
        Json::Value tribble_set;
        bool parse_ret_value = reader.parse(get_set_ret_val.value, tribble_set);
        if(parse_ret_value == false)
        {
            cout << "GetTribbles parsing part 2 failed" << endl;
            _return.status = TribbleStatus::FAILED; 
            return;
        }

        // put every tribble in the set into the list
        for(unsigned int j = 0; j < tribble_set.size() && count < MAX_MSGS; j++)
        {
            Tribble t;
            t.posted = tribble_set[tribble_set.size() - j - 1][TIMESTAMP].asUInt64();
            t.contents = tribble_set[tribble_set.size() - j - 1][MSG].asString();
            t.userid = userid;
            _return.tribbles.push_back(t);
            count++;
        }
    }
    _return.status = TribbleStatus::OK;
  }

  void GetTribblesBySubscription(TribbleResponse& _return, const std::string& userid) {
    printf("GetTribblesBySubscription\n");

    _return.tribbles.clear();

    // get user, if it doesnt exist return, if it does exist, get the subscriptions, for each subcribeTo

    // get the user info
    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(get_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
    {
        cout << "GetSubscriptions user not found" << endl;
        _return.status = TribbleStatus::INVALID_USER;
        return;
    }
    
    // user was found, so let's just take the subscribeTo list out of the object
    Json::Reader reader;
    Json::Value user_info;
    bool parse_ret_value = reader.parse(get_ret_val.value, user_info);
    if(parse_ret_value == false)
    {
        cout << "GetSubscriptions parsing failed" << endl;
        _return.status = TribbleStatus::FAILED; 
        return;
    }

    Json::Value subscribeToList = user_info[LIST_OF_SUBSCRIBERS];

    cout << "GetTribblesBySubscription pt 1 size subcribeTo list : " << subscribeToList.size() << endl;

    if(subscribeToList.size() == 0)
    {
        // empty, so put nothing in the return value
        cout << "GetTribblesBySubscription pt 1.1, subscribeToList.size() was 0" << endl;
        _return.tribbles.clear();
        _return.status = TribbleStatus::OK;
    }
    else
    {
        list<TribbleHelper> ths;
        for(unsigned int i = 0; i < subscribeToList.size(); i++)
        {
            cout << "GetTribblesBySubscription pt 1.2, inside for loop" << endl;
            // get all the information to create a lhs 
            TribbleHelper th;
            th.userid = subscribeToList[i].asString();

            // get the user info
            KeyValueStore::GetResponse get_sub_ret_val = Get(string(USER_PREFIX).append(th.userid));
            if(get_sub_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
            {
                cout << "GetTribblesBySubscription pt 2 couldnt find subscribeto " << subscribeToList.size() << endl;
                _return.status = TribbleStatus::INVALID_SUBSCRIBETO;
            }
            
            Json::Reader reader;
            Json::Value subscribeto_user_info;
            bool parse_ret_value = reader.parse(get_sub_ret_val.value, subscribeto_user_info);
            if(parse_ret_value == false)
            {
                cout << "GetTribblesBySubscription pt 3 couldnt parse" << subscribeToList.size() << endl;
                continue;
            }

            const Json::Value cur_set_num_val = subscribeto_user_info[CUR_SET_NUM];
            int cur_set_num = cur_set_num_val.asInt();
            
            // get the current set
            th.set = cur_set_num;

            // get the current index by getting the set and then examining and store the tribble_set
            char buf[10];
            sprintf(buf, "%d", th.set);
            KeyValueStore::GetResponse get_set_ret_val = Get(string(SET_PREFIX).append(buf).append("_").append(th.userid));

            Json::Value tribble_set;
            parse_ret_value = reader.parse(get_set_ret_val.value, tribble_set);
            if(parse_ret_value == false)
            {
                cout << "GetTribblesBySubscription pt 3.1 couldnt parse: " << get_set_ret_val.value << endl;
                continue; // subscribeto hasn't pospted anything yet
            }
            th.idx = tribble_set.size() - 1;
            th.tribble_set = tribble_set;

            addTribbleHelper(ths, th);
            cout << "GetTribblesBySubscription pt 3.2, added th" << endl;
        }
                
        cout << "GetTribblesBySubscription pt 4" << endl;
        cout << "ths.size(): " << ths.size() << endl;

        // until the return vector's size is 100 or there is nothing else in the list
            // for the smallest one, create its tribbler and add it to the list
        while(_return.tribbles.size() < 100 && ths.size() > 0)
        {
            cout << "GetTribblesBySubscription pt 4.1 inside while" << subscribeToList.size() << endl;

            Tribble t; 
            t.posted = ths.front().ts;
            t.userid = ths.front().userid;
            t.contents = ths.front().tribble_set[ths.front().idx][MSG].asString();
            ths.front().idx = ths.front().idx - 1;
            _return.tribbles.push_back(t);

            // make sure tribble helper stays consistent
            TribbleHelper front = ths.front();
            ths.pop_front();

            if(front.idx < 0)
            {
                if(front.set == 0) 
                {
                    // done with this set
                    continue;
                }
                else
                {
                    front.set = front.set - 1;
                    front.idx = MAX_SET_SIZE - 1;
                    // now get the new set

                    // retrieve the current set
                    char buf[10];
                    sprintf(buf, "%d", front.set);
                    KeyValueStore::GetResponse get_newset_ret_val = Get(string(SET_PREFIX).append(buf).append("_").append(front.userid));
                    if(get_newset_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
                    {
                        cout << "***Could not find set, should never happen" << endl;
                    }

                    Json::Reader reader;
                    Json::Value tribble_set;
                    bool parse_newset_ret_value = reader.parse(get_newset_ret_val.value, tribble_set);
                    if(parse_newset_ret_value == false)
                    {
                        cout << "GetTribblesBySubscription pt 5 couldnt parse" << subscribeToList.size() << endl;
                        continue; // WHAT DO???
                    }
                    
                    front.tribble_set = tribble_set;
                }
            }

            // ensure that the timestamp is updated to the new 
            front.ts = front.tribble_set[front.idx][TIMESTAMP].asUInt64();

            addTribbleHelper(ths, front); // since th has new timestamp, we need to insert it back in sorted order

            // done with consistency check
        }

        cout << "GetTribblesBySubscription pt 6" << endl;
        cout << "GetTribblesBySubscription return tribbles size: " << _return.tribbles.size() << endl;
        _return.status = TribbleStatus::OK;
    }
  }

  void GetSubscriptions(SubscriptionResponse& _return, const std::string& userid) {
    printf("GetSubscriptions\n");
    // get the user, if it doesn't exist, then return error, if it does exist, then get the list of subscribeTos and stick it in the return

    // get the user info
    KeyValueStore::GetResponse get_ret_val = Get(string(USER_PREFIX).append(userid));
    if(get_ret_val.status == KVStoreStatus::EKEYNOTFOUND)
    {
        cout << "GetSubscriptions user not found" << endl;
        _return.status = TribbleStatus::INVALID_USER;
        return;
    }
    
    cout << "GetSubscriptions GET returned: " << get_ret_val.status << endl;

    // user was found, so let's just take the subscribeTo list out of the object
    Json::Reader reader;
    Json::Value user_info;
    bool parse_ret_value = reader.parse(get_ret_val.value, user_info);
    if(parse_ret_value == false)
    {
        cout << "GetSubscriptions parsing failed" << endl;
        _return.status = TribbleStatus::FAILED; 
        return;
    }

    Json::Value subscribeToList = user_info[LIST_OF_SUBSCRIBERS];

    if(subscribeToList.size() == 0)
    {
        // empty, so put nothing in the return value
        _return.subscriptions.clear();
        _return.status = TribbleStatus::OK;
    }
    else
    {
        for(unsigned int i = 0; i < subscribeToList.size(); i++)
        {
            // add the string to the return value
            _return.subscriptions.push_back(subscribeToList[i].asString());
        }
        _return.status = TribbleStatus::OK;
    }
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
    cout << "PUT key: " << key << " value: " << value << endl;
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
    cout << "GET key: " << key << endl;
    KeyValueStore::GetResponse response;
    // Making the RPC Call to the Storage server
    boost::shared_ptr<TSocket> socket(new TSocket(_storageServer, _storageServerPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    KeyValueStoreClient client(protocol);
    transport->open();
    client.Get(response, key);
    transport->close();
    cout << "GET status was: " << response.status << endl;
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
