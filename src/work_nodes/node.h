#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

class Node {
public:
    Node(string loadBalancerIP,int loadbalancerPort, int NodeWeight);
    int loadbalancerRegisteration();


    int error_flag=0;
private:
        string loadBalancerIP;
        int nodeWeight;
        int sock;
        struct sockaddr_in serv_addr;
        string msg;
        int loadbalancerPort;
};