#include <vector>
#include <mutex>

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
	long startTime = 0;
	long EndTime = 0;
	long TurnAroundTime = 0;
	long contextTime = 0;
};

class Jobs {
public:    
    Jobs(int port);
    void Jobs_ReceiveJobs(int job_info);
    //mutex Jobs_getMutex() {return mtx;}
    vector<Job> Jobs_getJobsList() {return jobs;}
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
    vector<Job> jobs;
};