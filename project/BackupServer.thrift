
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

struct Point {
    1: double x,
    2: double y
}

struct GetPointsResponse
{
    1: BackupServerStatus status,
    2: list<Point> pts
}

/**
 * RPC services offered by the BackupServer
 */

service BackupServer {
    GetPointsResponse GetPointsInRegion(1:Point ul, 2:Point lr),
    i32 AddPoint(1:Point p, 2:string desc),
    void Commit(1:Point p, 2:i32 id)
}
