#include <vector>
#include <mutex>

using namespace std;

struct Node {
    int JobID;
	int JobInfo; // Time taken by a job //BT
	bool inProgress = false;
	int JobStatus = 0; // 0 init, 1 Running, 2 Waiting, 3 Terminated
 	int NodeID = 0;
	int RemainingTime = 0;
	long WaitTime = 0;
	long startTime = 0;
	long EndTime = 0;
	long TurnAroundTime = 0;
	long contextTime = 0;
};

class Nodes {
public:
    Nodes(int port);
    void Nodes_NodeRegisterationReceived();
    void Nodes_RemoveNode();
    void Nodes_getMutex();
    vector<Node> Nodes_getNodeList();
    void run();
private:
    vector<Node> nodes;
    int port;
    static int nodeCounter;
    mutex mtx;
};