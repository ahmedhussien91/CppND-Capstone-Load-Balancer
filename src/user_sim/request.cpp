#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include <cstring>
#include <iostream>
#include "request.h"

using namespace std;

int Request::counter = 0;

Request::Request(string ip, int port) {
        serverIP = ip;
        serverPort = port;
}

void Request::setRequestTime(int seconds) {
    requestTime = seconds;
}

int Request::sendJobRequest() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // open socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        cout << "\n Socket creation error \n";
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIP.c_str(), &(serv_addr.sin_addr));

    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // send UDP Request
    msg = std::to_string(requestTime);
    sendto(sock,  msg.c_str() , msg.length(),
    MSG_CONFIRM, (const struct sockaddr *) &serv_addr, 
        sizeof(serv_addr));

    cout << "request: " << counter+1 << " time: " << requestTime << endl;
    counter++;

    close(sock);
    return 0;
}