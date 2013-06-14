/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MockDB_TYPES_H
#define MockDB_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>



namespace MockDBServer {

struct ServerStatus {
  enum type {
    OK = 0,
    FAILED = 1
  };
};

extern const std::map<int, const char*> _ServerStatus_VALUES_TO_NAMES;

typedef struct _ThriftGeoPoint__isset {
  _ThriftGeoPoint__isset() : xCoord(false), yCoord(false) {}
  bool xCoord;
  bool yCoord;
} _ThriftGeoPoint__isset;

class ThriftGeoPoint {
 public:

  static const char* ascii_fingerprint; // = "EA2086D2BB14222991D7B0497DE7B58B";
  static const uint8_t binary_fingerprint[16]; // = {0xEA,0x20,0x86,0xD2,0xBB,0x14,0x22,0x29,0x91,0xD7,0xB0,0x49,0x7D,0xE7,0xB5,0x8B};

  ThriftGeoPoint() : xCoord(0), yCoord(0) {
  }

  virtual ~ThriftGeoPoint() throw() {}

  double xCoord;
  double yCoord;

  _ThriftGeoPoint__isset __isset;

  void __set_xCoord(const double val) {
    xCoord = val;
  }

  void __set_yCoord(const double val) {
    yCoord = val;
  }

  bool operator == (const ThriftGeoPoint & rhs) const
  {
    if (!(xCoord == rhs.xCoord))
      return false;
    if (!(yCoord == rhs.yCoord))
      return false;
    return true;
  }
  bool operator != (const ThriftGeoPoint &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ThriftGeoPoint & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(ThriftGeoPoint &a, ThriftGeoPoint &b);

typedef struct _GetPointsResponse__isset {
  _GetPointsResponse__isset() : status(false), pts(false) {}
  bool status;
  bool pts;
} _GetPointsResponse__isset;

class GetPointsResponse {
 public:

  static const char* ascii_fingerprint; // = "671E4DE9FBAA549FF6625A8B38B682DB";
  static const uint8_t binary_fingerprint[16]; // = {0x67,0x1E,0x4D,0xE9,0xFB,0xAA,0x54,0x9F,0xF6,0x62,0x5A,0x8B,0x38,0xB6,0x82,0xDB};

  GetPointsResponse() : status((ServerStatus::type)0) {
  }

  virtual ~GetPointsResponse() throw() {}

  ServerStatus::type status;
  std::vector<ThriftGeoPoint>  pts;

  _GetPointsResponse__isset __isset;

  void __set_status(const ServerStatus::type val) {
    status = val;
  }

  void __set_pts(const std::vector<ThriftGeoPoint> & val) {
    pts = val;
  }

  bool operator == (const GetPointsResponse & rhs) const
  {
    if (!(status == rhs.status))
      return false;
    if (!(pts == rhs.pts))
      return false;
    return true;
  }
  bool operator != (const GetPointsResponse &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GetPointsResponse & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(GetPointsResponse &a, GetPointsResponse &b);

} // namespace

#endif
