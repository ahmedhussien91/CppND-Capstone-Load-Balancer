#include <iostream>
#include <memory>
#include <limits>

#include "node.h"

using namespace std;


#define LOAD_BALANCER_IP  "127.0.0.1"
#define LOAD_BALANCER_PORT 50001

int main() {
    int nodeWeight = 0;
    cout << "please enter Node Weight: ";
    cin >> nodeWeight;
    if (cin.fail())
    {
        cout << "ERROR -- You did not enter an integer";
        // get rid of failure state
        cin.clear(); 
        // discard 'bad' character(s) 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        cout << "connecting to ip: " << LOAD_BALANCER_IP << "on port: " << LOAD_BALANCER_PORT << " weight: " << nodeWeight << endl;
        unique_ptr<Node> node = make_unique<Node>(LOAD_BALANCER_IP, LOAD_BALANCER_PORT, nodeWeight);

        if (node->error_flag == -1)
            return -1;

        if (!node->loadbalancerRegisteration()){
            cout << "node registered";
            int n = 1;
            while(n > 0) {
                n = node->loadbalancerRegisteration(); // halts here waiting on reception of request
                std::thread t(&Node::executeRequest,  node.get(), n); // execute request in a separate thread
            }

        } else {
            return -1;
        }
    }

    return 0;
}