
namespace cpp MockDBServer

/**
 * Enum type for returning status of a RPC request made to the
 * the storage server.
 */

enum ServerStatus {
    OK = 0,
    FAILED = 1
}

/**
 * Return type for a Get(key) RPC call to the storage server.
 */

struct ThriftGeoPoint {
    1: double xCoord,
    2: double yCoord
}

struct GetPointsResponse
{
    1: ServerStatus status,
    2: list<ThriftGeoPoint> pts
}

/**
 * RPC services offered by the BackupServer
 */

service MockDB {
    GetPointsResponse GetPointsInRegion(1:ThriftGeoPoint ll, 2:ThriftGeoPoint ur),
    ServerStatus AddPoint(1:ThriftGeoPoint p),
    double GetEndXCoordinate(1:double start_x_coord, 2:i32 num_points)
}
