
namespace cpp BackupServer

/**
 * Enum type for returning status of a RPC request made to the
 * the storage server.
 */

enum BackupServerStatus {
    OK = 0,
    FAILED = 1
}

/**
 * Return type for a Get(key) RPC call to the storage server.
 */

struct ThriftGeoPoint {
    1: double xCoord,
    2: double yCoord,
    3: string message
}

struct GetPointsResponse
{
    1: BackupServerStatus status,
    2: list<ThriftGeoPoint> pts
}

/**
 * RPC services offered by the BackupServer
 */

service BackupServer {
    GetPointsResponse GetPointsInRegion(1:ThriftGeoPoint ul, 2:ThriftGeoPoint lr),
    BackupServerStatus AddPoint(1:ThriftGeoPoint p, 2:string desc)
}
