#include <string>
#include "../device/Device.h"

class Server{

private:
    /* data */
public:
    int serve(int , const char*, Device*);
    const char* getHttpResponse(const char*);
};
