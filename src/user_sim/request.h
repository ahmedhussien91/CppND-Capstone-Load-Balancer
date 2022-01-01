#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include <cstring>
#include <iostream>

using namespace std;

class Request {
public:

    Request(string ip, int port);
    void setRequestTime(int seconds);
    int sendJobRequest();


private:
    static int counter;
    int requestTime;
    string msg;
    string serverIP;
    int serverPort;    
};