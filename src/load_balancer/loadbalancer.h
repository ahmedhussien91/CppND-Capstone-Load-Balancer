#ifndef LOADBALANCER_H_
#define LOADBALANCER_H_

#include "nodes.h"
#include "requests.h"

class LoadBalancer {
public:    
    LoadBalancer(Nodes * nodes, Requests* requests);
    void sendRequestToNode();
    void run(); // load balancing algorithm

private:
    Nodes* nodes;
    Requests* requests;
    mutex* nodes_mutex;
    mutex* requests_mutex;
};

#endif