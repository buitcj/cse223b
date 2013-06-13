/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef KeyValueStore_H
#define KeyValueStore_H

#include <thrift/TDispatchProcessor.h>
#include "KeyValueStore_types.h"

namespace KeyValueStore {

class KeyValueStoreIf {
 public:
  virtual ~KeyValueStoreIf() {}
  virtual void Get(GetResponse& _return, const std::string& key) = 0;
  virtual KVStoreStatus::type Put(const std::string& key, const std::string& value, const std::string& clientid) = 0;
  virtual KVStoreStatus::type PutPhase1Internal(const std::string& key, const std::string& value, const std::string& clientid, const std::vector<int32_t> & vec_timestamp) = 0;
  virtual KVStoreStatus::type PutPhase2Internal(const std::string& key, const bool commit, const std::string& clientid) = 0;
  virtual void Sync(SyncResponse& _return) = 0;
  virtual bool IsAlive() = 0;
};

class KeyValueStoreIfFactory {
 public:
  typedef KeyValueStoreIf Handler;

  virtual ~KeyValueStoreIfFactory() {}

  virtual KeyValueStoreIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(KeyValueStoreIf* /* handler */) = 0;
};

class KeyValueStoreIfSingletonFactory : virtual public KeyValueStoreIfFactory {
 public:
  KeyValueStoreIfSingletonFactory(const boost::shared_ptr<KeyValueStoreIf>& iface) : iface_(iface) {}
  virtual ~KeyValueStoreIfSingletonFactory() {}

  virtual KeyValueStoreIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(KeyValueStoreIf* /* handler */) {}

 protected:
  boost::shared_ptr<KeyValueStoreIf> iface_;
};

class KeyValueStoreNull : virtual public KeyValueStoreIf {
 public:
  virtual ~KeyValueStoreNull() {}
  void Get(GetResponse& /* _return */, const std::string& /* key */) {
    return;
  }
  KVStoreStatus::type Put(const std::string& /* key */, const std::string& /* value */, const std::string& /* clientid */) {
    KVStoreStatus::type _return = (KVStoreStatus::type)0;
    return _return;
  }
  KVStoreStatus::type PutPhase1Internal(const std::string& /* key */, const std::string& /* value */, const std::string& /* clientid */, const std::vector<int32_t> & /* vec_timestamp */) {
    KVStoreStatus::type _return = (KVStoreStatus::type)0;
    return _return;
  }
  KVStoreStatus::type PutPhase2Internal(const std::string& /* key */, const bool /* commit */, const std::string& /* clientid */) {
    KVStoreStatus::type _return = (KVStoreStatus::type)0;
    return _return;
  }
  void Sync(SyncResponse& /* _return */) {
    return;
  }
  bool IsAlive() {
    bool _return = false;
    return _return;
  }
};

typedef struct _KeyValueStore_Get_args__isset {
  _KeyValueStore_Get_args__isset() : key(false) {}
  bool key;
} _KeyValueStore_Get_args__isset;

class KeyValueStore_Get_args {
 public:

  KeyValueStore_Get_args() : key() {
  }

  virtual ~KeyValueStore_Get_args() throw() {}

  std::string key;

  _KeyValueStore_Get_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  bool operator == (const KeyValueStore_Get_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Get_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Get_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_Get_pargs {
 public:


  virtual ~KeyValueStore_Get_pargs() throw() {}

  const std::string* key;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Get_result__isset {
  _KeyValueStore_Get_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_Get_result__isset;

class KeyValueStore_Get_result {
 public:

  KeyValueStore_Get_result() {
  }

  virtual ~KeyValueStore_Get_result() throw() {}

  GetResponse success;

  _KeyValueStore_Get_result__isset __isset;

  void __set_success(const GetResponse& val) {
    success = val;
  }

  bool operator == (const KeyValueStore_Get_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Get_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Get_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Get_presult__isset {
  _KeyValueStore_Get_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_Get_presult__isset;

class KeyValueStore_Get_presult {
 public:


  virtual ~KeyValueStore_Get_presult() throw() {}

  GetResponse* success;

  _KeyValueStore_Get_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_Put_args__isset {
  _KeyValueStore_Put_args__isset() : key(false), value(false), clientid(false) {}
  bool key;
  bool value;
  bool clientid;
} _KeyValueStore_Put_args__isset;

class KeyValueStore_Put_args {
 public:

  KeyValueStore_Put_args() : key(), value(), clientid() {
  }

  virtual ~KeyValueStore_Put_args() throw() {}

  std::string key;
  std::string value;
  std::string clientid;

  _KeyValueStore_Put_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_Put_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Put_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Put_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_Put_pargs {
 public:


  virtual ~KeyValueStore_Put_pargs() throw() {}

  const std::string* key;
  const std::string* value;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Put_result__isset {
  _KeyValueStore_Put_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_Put_result__isset;

class KeyValueStore_Put_result {
 public:

  KeyValueStore_Put_result() : success((KVStoreStatus::type)0) {
  }

  virtual ~KeyValueStore_Put_result() throw() {}

  KVStoreStatus::type success;

  _KeyValueStore_Put_result__isset __isset;

  void __set_success(const KVStoreStatus::type val) {
    success = val;
  }

  bool operator == (const KeyValueStore_Put_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Put_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Put_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Put_presult__isset {
  _KeyValueStore_Put_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_Put_presult__isset;

class KeyValueStore_Put_presult {
 public:


  virtual ~KeyValueStore_Put_presult() throw() {}

  KVStoreStatus::type* success;

  _KeyValueStore_Put_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_PutPhase1Internal_args__isset {
  _KeyValueStore_PutPhase1Internal_args__isset() : key(false), value(false), clientid(false), vec_timestamp(false) {}
  bool key;
  bool value;
  bool clientid;
  bool vec_timestamp;
} _KeyValueStore_PutPhase1Internal_args__isset;

class KeyValueStore_PutPhase1Internal_args {
 public:

  KeyValueStore_PutPhase1Internal_args() : key(), value(), clientid() {
  }

  virtual ~KeyValueStore_PutPhase1Internal_args() throw() {}

  std::string key;
  std::string value;
  std::string clientid;
  std::vector<int32_t>  vec_timestamp;

  _KeyValueStore_PutPhase1Internal_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  void __set_vec_timestamp(const std::vector<int32_t> & val) {
    vec_timestamp = val;
  }

  bool operator == (const KeyValueStore_PutPhase1Internal_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    if (!(vec_timestamp == rhs.vec_timestamp))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_PutPhase1Internal_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_PutPhase1Internal_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_PutPhase1Internal_pargs {
 public:


  virtual ~KeyValueStore_PutPhase1Internal_pargs() throw() {}

  const std::string* key;
  const std::string* value;
  const std::string* clientid;
  const std::vector<int32_t> * vec_timestamp;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_PutPhase1Internal_result__isset {
  _KeyValueStore_PutPhase1Internal_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_PutPhase1Internal_result__isset;

class KeyValueStore_PutPhase1Internal_result {
 public:

  KeyValueStore_PutPhase1Internal_result() : success((KVStoreStatus::type)0) {
  }

  virtual ~KeyValueStore_PutPhase1Internal_result() throw() {}

  KVStoreStatus::type success;

  _KeyValueStore_PutPhase1Internal_result__isset __isset;

  void __set_success(const KVStoreStatus::type val) {
    success = val;
  }

  bool operator == (const KeyValueStore_PutPhase1Internal_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_PutPhase1Internal_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_PutPhase1Internal_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_PutPhase1Internal_presult__isset {
  _KeyValueStore_PutPhase1Internal_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_PutPhase1Internal_presult__isset;

class KeyValueStore_PutPhase1Internal_presult {
 public:


  virtual ~KeyValueStore_PutPhase1Internal_presult() throw() {}

  KVStoreStatus::type* success;

  _KeyValueStore_PutPhase1Internal_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_PutPhase2Internal_args__isset {
  _KeyValueStore_PutPhase2Internal_args__isset() : key(false), commit(false), clientid(false) {}
  bool key;
  bool commit;
  bool clientid;
} _KeyValueStore_PutPhase2Internal_args__isset;

class KeyValueStore_PutPhase2Internal_args {
 public:

  KeyValueStore_PutPhase2Internal_args() : key(), commit(0), clientid() {
  }

  virtual ~KeyValueStore_PutPhase2Internal_args() throw() {}

  std::string key;
  bool commit;
  std::string clientid;

  _KeyValueStore_PutPhase2Internal_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_commit(const bool val) {
    commit = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_PutPhase2Internal_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(commit == rhs.commit))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_PutPhase2Internal_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_PutPhase2Internal_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_PutPhase2Internal_pargs {
 public:


  virtual ~KeyValueStore_PutPhase2Internal_pargs() throw() {}

  const std::string* key;
  const bool* commit;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_PutPhase2Internal_result__isset {
  _KeyValueStore_PutPhase2Internal_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_PutPhase2Internal_result__isset;

class KeyValueStore_PutPhase2Internal_result {
 public:

  KeyValueStore_PutPhase2Internal_result() : success((KVStoreStatus::type)0) {
  }

  virtual ~KeyValueStore_PutPhase2Internal_result() throw() {}

  KVStoreStatus::type success;

  _KeyValueStore_PutPhase2Internal_result__isset __isset;

  void __set_success(const KVStoreStatus::type val) {
    success = val;
  }

  bool operator == (const KeyValueStore_PutPhase2Internal_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_PutPhase2Internal_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_PutPhase2Internal_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_PutPhase2Internal_presult__isset {
  _KeyValueStore_PutPhase2Internal_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_PutPhase2Internal_presult__isset;

class KeyValueStore_PutPhase2Internal_presult {
 public:


  virtual ~KeyValueStore_PutPhase2Internal_presult() throw() {}

  KVStoreStatus::type* success;

  _KeyValueStore_PutPhase2Internal_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class KeyValueStore_Sync_args {
 public:

  KeyValueStore_Sync_args() {
  }

  virtual ~KeyValueStore_Sync_args() throw() {}


  bool operator == (const KeyValueStore_Sync_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const KeyValueStore_Sync_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Sync_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_Sync_pargs {
 public:


  virtual ~KeyValueStore_Sync_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Sync_result__isset {
  _KeyValueStore_Sync_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_Sync_result__isset;

class KeyValueStore_Sync_result {
 public:

  KeyValueStore_Sync_result() {
  }

  virtual ~KeyValueStore_Sync_result() throw() {}

  SyncResponse success;

  _KeyValueStore_Sync_result__isset __isset;

  void __set_success(const SyncResponse& val) {
    success = val;
  }

  bool operator == (const KeyValueStore_Sync_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Sync_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Sync_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Sync_presult__isset {
  _KeyValueStore_Sync_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_Sync_presult__isset;

class KeyValueStore_Sync_presult {
 public:


  virtual ~KeyValueStore_Sync_presult() throw() {}

  SyncResponse* success;

  _KeyValueStore_Sync_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class KeyValueStore_IsAlive_args {
 public:

  KeyValueStore_IsAlive_args() {
  }

  virtual ~KeyValueStore_IsAlive_args() throw() {}


  bool operator == (const KeyValueStore_IsAlive_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const KeyValueStore_IsAlive_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_IsAlive_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_IsAlive_pargs {
 public:


  virtual ~KeyValueStore_IsAlive_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_IsAlive_result__isset {
  _KeyValueStore_IsAlive_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_IsAlive_result__isset;

class KeyValueStore_IsAlive_result {
 public:

  KeyValueStore_IsAlive_result() : success(0) {
  }

  virtual ~KeyValueStore_IsAlive_result() throw() {}

  bool success;

  _KeyValueStore_IsAlive_result__isset __isset;

  void __set_success(const bool val) {
    success = val;
  }

  bool operator == (const KeyValueStore_IsAlive_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_IsAlive_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_IsAlive_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_IsAlive_presult__isset {
  _KeyValueStore_IsAlive_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_IsAlive_presult__isset;

class KeyValueStore_IsAlive_presult {
 public:


  virtual ~KeyValueStore_IsAlive_presult() throw() {}

  bool* success;

  _KeyValueStore_IsAlive_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class KeyValueStoreClient : virtual public KeyValueStoreIf {
 public:
  KeyValueStoreClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  KeyValueStoreClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void Get(GetResponse& _return, const std::string& key);
  void send_Get(const std::string& key);
  void recv_Get(GetResponse& _return);
  KVStoreStatus::type Put(const std::string& key, const std::string& value, const std::string& clientid);
  void send_Put(const std::string& key, const std::string& value, const std::string& clientid);
  KVStoreStatus::type recv_Put();
  KVStoreStatus::type PutPhase1Internal(const std::string& key, const std::string& value, const std::string& clientid, const std::vector<int32_t> & vec_timestamp);
  void send_PutPhase1Internal(const std::string& key, const std::string& value, const std::string& clientid, const std::vector<int32_t> & vec_timestamp);
  KVStoreStatus::type recv_PutPhase1Internal();
  KVStoreStatus::type PutPhase2Internal(const std::string& key, const bool commit, const std::string& clientid);
  void send_PutPhase2Internal(const std::string& key, const bool commit, const std::string& clientid);
  KVStoreStatus::type recv_PutPhase2Internal();
  void Sync(SyncResponse& _return);
  void send_Sync();
  void recv_Sync(SyncResponse& _return);
  bool IsAlive();
  void send_IsAlive();
  bool recv_IsAlive();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class KeyValueStoreProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<KeyValueStoreIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (KeyValueStoreProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_Get(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Put(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_PutPhase1Internal(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_PutPhase2Internal(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Sync(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_IsAlive(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  KeyValueStoreProcessor(boost::shared_ptr<KeyValueStoreIf> iface) :
    iface_(iface) {
    processMap_["Get"] = &KeyValueStoreProcessor::process_Get;
    processMap_["Put"] = &KeyValueStoreProcessor::process_Put;
    processMap_["PutPhase1Internal"] = &KeyValueStoreProcessor::process_PutPhase1Internal;
    processMap_["PutPhase2Internal"] = &KeyValueStoreProcessor::process_PutPhase2Internal;
    processMap_["Sync"] = &KeyValueStoreProcessor::process_Sync;
    processMap_["IsAlive"] = &KeyValueStoreProcessor::process_IsAlive;
  }

  virtual ~KeyValueStoreProcessor() {}
};

class KeyValueStoreProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  KeyValueStoreProcessorFactory(const ::boost::shared_ptr< KeyValueStoreIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< KeyValueStoreIfFactory > handlerFactory_;
};

class KeyValueStoreMultiface : virtual public KeyValueStoreIf {
 public:
  KeyValueStoreMultiface(std::vector<boost::shared_ptr<KeyValueStoreIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~KeyValueStoreMultiface() {}
 protected:
  std::vector<boost::shared_ptr<KeyValueStoreIf> > ifaces_;
  KeyValueStoreMultiface() {}
  void add(boost::shared_ptr<KeyValueStoreIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void Get(GetResponse& _return, const std::string& key) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Get(_return, key);
    }
    ifaces_[i]->Get(_return, key);
    return;
  }

  KVStoreStatus::type Put(const std::string& key, const std::string& value, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Put(key, value, clientid);
    }
    return ifaces_[i]->Put(key, value, clientid);
  }

  KVStoreStatus::type PutPhase1Internal(const std::string& key, const std::string& value, const std::string& clientid, const std::vector<int32_t> & vec_timestamp) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->PutPhase1Internal(key, value, clientid, vec_timestamp);
    }
    return ifaces_[i]->PutPhase1Internal(key, value, clientid, vec_timestamp);
  }

  KVStoreStatus::type PutPhase2Internal(const std::string& key, const bool commit, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->PutPhase2Internal(key, commit, clientid);
    }
    return ifaces_[i]->PutPhase2Internal(key, commit, clientid);
  }

  void Sync(SyncResponse& _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Sync(_return);
    }
    ifaces_[i]->Sync(_return);
    return;
  }

  bool IsAlive() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->IsAlive();
    }
    return ifaces_[i]->IsAlive();
  }

};

} // namespace

#endif
