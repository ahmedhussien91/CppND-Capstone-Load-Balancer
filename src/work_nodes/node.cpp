#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "node.h"

using namespace std;


Node::Node(string loadBalancerIP,int loadbalancerPort, int NodeWeight):loadBalancerIP(loadBalancerIP),
    loadbalancerPort(loadbalancerPort), nodeWeight(nodeWeight){
    
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
    struct sockaddr_in localAddress;
    socklen_t addressLength = sizeof(localAddress);
    getsockname(sock, (struct sockaddr*)&localAddress,   \
                &addressLength);

    string ip(inet_ntoa(  localAddress.sin_addr));
    msg = "Register: " 
        +  ip
        + "\n port: "
        + to_string((int) ntohs(localAddress.sin_port))
        + "\n weight: " 
        + to_string(nodeWeight);
        
    sendto(sock,  msg.c_str() , msg.length(),
    MSG_CONFIRM, (const struct sockaddr *) &serv_addr, 
        sizeof(serv_addr));

    close(sock);
    return 0;
}