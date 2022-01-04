#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <chrono>
#include "node.h"

using namespace std;

#define MAX_DATA_SIZE 1024 


Node::Node(string loadBalancerIP,int loadbalancerPort, int NodeWeight):loadBalancerIP(loadBalancerIP),
    loadbalancerPort(loadbalancerPort), nodeWeight(NodeWeight){
    
    // open socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        cout << "\n Socket creation error \n";
        error_flag = -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(loadbalancerPort);
    inet_pton(AF_INET, loadBalancerIP.c_str(), &(serv_addr.sin_addr));

    //serv_addr.sin_addr.s_addr = INADDR_ANY;
};
    
int Node::loadbalancerRegisteration() {
    // send UDP Request
    msg = "weight: " + to_string(nodeWeight);
        
    sendto(sock,  msg.c_str() , msg.length(),
    MSG_CONFIRM, (const struct sockaddr *) &serv_addr, 
        sizeof(serv_addr));
    
    return 0;
}

int Node::readJobFromLoadBalancer() {
    char buf[MAX_DATA_SIZE];
    int number_of_seconds;
    socklen_t len;
    int n = recvfrom(sock, (char *) buf, MAX_DATA_SIZE, MSG_WAITALL, 
        (struct sockaddr *) &serv_addr, &len);
    if(n>0) {
        string s(buf), word;
        stringstream ss(s);
        ss >> word >> number_of_seconds;
#ifdef DEBUG    
        cout << "Received: "<< s << endl;
#endif
        return number_of_seconds;
    } else {
        return 0;
    }
}

void Node::executeRequest(int request_no_of_seconds) {
    // wait for requested number of seconds to complete
    std::this_thread::sleep_for(std::chrono::seconds(request_no_of_seconds));
}