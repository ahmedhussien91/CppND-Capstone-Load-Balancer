#include "nodes.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>


#define MAX_DATA_SIZE 1024

int Nodes::nodeCount = 0;

Nodes::Nodes(int port) {
    this->port = port;

}

void Nodes::Nodes_NodeRegisterationReceived(char* data, int len,  string ip, int port) {
    nodeCount++;
    Node* node = new Node();
    node->NodeID = nodeCount;
    node->NodeIP = ip;
    node->NodePort = port;
    string s(data, len), name;
    stringstream ss(s);
    ss >> name;
    ss >> node->NodeWeight;
    std::lock_guard<std::mutex> lock(mtx);
    nodes.push_back(node);
}

void Nodes::Nodes_RemoveNode() {

}

mutex* Nodes::Nodes_getMutex() {
    return &mtx;
}

vector<Node*> Nodes::Nodes_getNodeList() {
    return nodes;
}

void Nodes::run() {
    int sock;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[MAX_DATA_SIZE];

    // create socket file descriptor
    if( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("scoket creation failed");
        exit(EXIT_FAILURE);
    }

    // fill server info
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    // bind to port
    if((bind(sock, (const struct sockaddr *) &servaddr, sizeof(servaddr))) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    while(true) {
        socklen_t len, n; 

        len = sizeof(cliaddr);
        n = recvfrom(sock, (char *)buffer, MAX_DATA_SIZE, MSG_WAITALL, 
        (struct sockaddr *) &cliaddr, &len);        
        if (n < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }
        
        // process input data
        string ip(inet_ntoa(cliaddr.sin_addr)); 
        Nodes_NodeRegisterationReceived(buffer,n, ip, cliaddr.sin_port);
        
#ifdef DEBUG
        string s(buffer);        
        cout << "Received: " << s << "\n from ip: " << ip << " port: " << cliaddr.sin_port << endl;
#endif       
    }
}