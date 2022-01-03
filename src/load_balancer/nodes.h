#include <vector>
#include <mutex>

using namespace std;

struct Node {
    int NodeID;
	int WorkLoad;
	string NodeIP;
    int NodePort;
    string InData;
    string OutData;
	bool isBusy = false;
	int NodeWeight = 1;
	int NodeWeight_const = 1;
	bool IsInReadCalled_Mutex = false;
};

class Nodes {
public:
    Nodes(int port);
    void Nodes_NodeRegisterationReceived(char* data, int len, string client_ip, int port);    
    void Nodes_RemoveNode();
    mutex* Nodes_getMutex();
    vector<Node*> Nodes_getNodeList();
    void run();
private:
    vector<Node*> nodes;
    int port;
    static int nodeCount;
    mutex mtx;
};