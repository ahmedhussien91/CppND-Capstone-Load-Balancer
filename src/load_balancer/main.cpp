#include <iostream>
#include <memory>
#include <thread>
#include "nodes.h"
#include "jobs.h"

using namespace std;

#define NODE_PORT 50001 
#define JOBS_PORT 50000

int main() {
    Nodes* nodes = new Nodes(NODE_PORT);
    thread nodesThread(&Nodes::run, nodes); // start nodes thread

    Jobs* jobs = new Jobs(JOBS_PORT);
    thread jobsThread(&Jobs::run, jobs); // start jobs or requests threads

    // LoadBalancer * loadbalancer = new LoadBalancer(jobs, nodes);
    // thread balancerThread(&LoadBalancer::run, loadbalancer); // start load balancer threads
}
