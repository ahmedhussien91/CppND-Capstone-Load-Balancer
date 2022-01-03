#include "requests.h"
#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAX_DATA_SIZE 1024

int Requests::jobsCounter=0;

Requests::Requests(int port) {
    this->port = port;
}

void Requests::Jobs_ReceiveJobs(int job_info, string client_ip, int port) {
    Job* J = new Job();
    jobsCounter++;
    J->JobID = jobsCounter;
    J->JobInfo = job_info;
    J->ClientIP = client_ip;
    J->ClientPort = port;
    J->startTime = std::chrono::system_clock::now();
    {
        std::lock_guard<std::mutex> lock1(mtx);
        requests.push_back(J);
    }
}

void Requests::run() {
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
        string s(buffer);
        string ip(inet_ntoa(cliaddr.sin_addr));
        
        Jobs_ReceiveJobs(stoi(s), ip, cliaddr.sin_port);

#ifdef DEBUG        
        cout << "Received: " << s << "\n from ip: " << ip << " port: " << cliaddr.sin_port << endl;
#endif
    }

}

void Requests::sortByRemainingTime(vector<Job> &job_list) {
    
}
void Requests::updateRemainingTimeForNewElements(vector<Job> & job_list) {

}
int Requests::calculateTQ(vector<Job> &job_list) {

}
void Requests::CalculateWaitTurnAroundContextTime(vector<Job> &job_list) {

}
