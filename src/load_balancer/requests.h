#ifndef REQUESTS_H_
#define REQUESTS_H_

#include <vector>
#include <mutex>
#include <chrono>
#include <sys/socket.h>



using namespace std;
enum JobStatus_e {INIT, RUNNING, WAITING, TERMINATED};

struct Job {
    int JobID;
	int JobInfo; // Time taken by a job //BT
	bool inProgress = false;
	JobStatus_e JobStatus = INIT; // 0 init, 1 Running, 2 Waiting, 3 Terminated
 	int NodeID = 0;
	int RemainingTime = 0;
	long WaitTime = 0;
	std::chrono::time_point<std::chrono::system_clock> startTime;
	std::chrono::time_point<std::chrono::system_clock> EndTime;
	std::chrono::time_point<std::chrono::system_clock> TurnAroundTime;
	std::chrono::time_point<std::chrono::system_clock> contextTime;
    string ClientIP;
    int ClientPort;
};

class Requests {
public:    
    Requests(int port);
    void Jobs_ReceiveJobs(int job_info, string client_ip, int port);
    //mutex Jobs_getMutex() {return mtx;}
    vector<Job*> Jobs_getJobsList() {return requests;}
    void run();
    void sortByRemainingTime(vector<Job> &job_list);
    void updateRemainingTimeForNewElements(vector<Job> & job_list);
    int calculateTQ(vector<Job> &job_list);
    void CalculateWaitTurnAroundContextTime(vector<Job> &job_list);
    bool compare(Job a, Job b) {return (a.RemainingTime > b.RemainingTime);}
private:
    int port;
    static int jobsCounter;
    mutex mtx;
    vector<Job*> requests;
};

#endif