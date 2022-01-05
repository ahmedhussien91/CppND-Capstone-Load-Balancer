#include <iostream>
#include <memory>
#include <thread>
#include "nodes.h"
#include "requests.h"
#include "loadbalancer.h"

using namespace std;

#define NODE_PORT 50001 
#define JOBS_PORT 50000

int main() {
    Nodes* nodes = new Nodes(NODE_PORT);
    thread nodesThread(&Nodes::run, nodes); // start nodes thread

    Requests* requests = new Requests(JOBS_PORT);
    thread requestsThread(&Requests::run, requests); // start requests or requests threads

    LoadBalancer * loadbalancer = new LoadBalancer(nodes, requests);
    thread balancerThread(&LoadBalancer::run, loadbalancer); // start load balancer threads
    
    requestsThread.join();
    nodesThread.join();
    balancerThread.join();
    
}
