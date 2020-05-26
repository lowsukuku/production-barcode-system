#ifndef DB_SCANER_H
#define DB_SCANER_H


using namespace std;
#include <string>


class DeviceScaner {
private:
    long long int scanerAPI;

public:
    DeviceScaner();

    void *setAPI(long long int scanerAPI);
    string getAPI();
};


#endif //DB_SCANER_H
