#pragma once
#include <libpq-fe.h>


class PQWrapper {
private:
    PGconn *conn;
public:
    PQWrapper(const char *connInfo);

    PGresult* Query(const char *query);


};
