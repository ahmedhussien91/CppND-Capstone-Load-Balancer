#include <iostream>
#include <memory>
#include "node.h"

using namespace std;


#define LOAD_BALANCER_IP  "127.0.0.1"
#define LOAD_BALANCER_PORT 20000

int main() {
    int nodeWeight = 0;
    cout << "please enter Node Weight";
    cin >> nodeWeight;
    cout << "connecting to " << LOAD_BALANCER_IP << "on port " << LOAD_BALANCER_PORT << endl;

    unique_ptr<Node> node = make_unique<Node>(LOAD_BALANCER_IP, LOAD_BALANCER_PORT, nodeWeight);
    if (node->error_flag == -1)
        return -1;

    if (!node->loadbalancerRegisteration()){
        cout << "node registered";

    } else {
        return -1;
    }

    
    return 0;
}