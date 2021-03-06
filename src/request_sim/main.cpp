#include <iostream>
#include <memory>
#include <iostream>
#include <string>
#include <limits>
#include "request.h"

using namespace std;

#define LOAD_BALANCER_IP "127.0.0.1"
#define LOAD_BALANCER_PORT 50000


int main() {
    // TODO Auto-generated method stub
    //Scanner scan = new Scanner(System.in);
    int requestCounter = 0;
    int requestTime;	
    while(true) {
        unique_ptr<Request> request = make_unique<Request>(LOAD_BALANCER_IP, LOAD_BALANCER_PORT);
        requestCounter++;
        cout << "Please Enter Job Duration(in Seconds) - Job-" << requestCounter << ": ";
        cin >> requestTime; // halts here if no input
        if (cin.fail())
        {
            cout << "ERROR -- You did not enter an integer";
            // get rid of failure state
            cin.clear(); 
            // discard 'bad' character(s) 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            request->setRequestTime(requestTime);
            request->sendJobRequest();
        }
    }
    return 0;
}