/**********************************
 * FILE NAME: MP2Node.h
 *
 * DESCRIPTION: MP2Node class header file
 **********************************/

#ifndef MP2NODE_H_
#define MP2NODE_H_

/**
 * Header files
 */
#include "EmulNet.h"
#include "HashTable.h"
#include "Log.h"
#include "Message.h"
#include "Node.h"
#include "Params.h"
#include "Queue.h"
#include "stdincludes.h"

/**
 * Holds current transaction until they terminate by:
 * - Quorum of okCount
 * - Quorum of failCount
 * - Timeout (ie: sentTime < now() - TFAIL)
 * 'preVal' holds a previous reply value for comparaison.
 */
class TransactionState {
public:
    string msgString; // The sent message that this transaction wraps
    long sentTime;
    int okCount;
    int failCount;
    string prevVal;

    TransactionState(string msg, long now);
};

/**
 * CLASS NAME: MP2Node
 *
 * DESCRIPTION: This class encapsulates all the key-value store functionality
 * 				including:
 * 				1) Ring
 * 				2) Stabilization Protocol
 * 				3) Server side CRUD APIs
 * 				4) Client side CRUD APIs
 */
class MP2Node {
private:
    // Vector holding the next two neighbors in the ring who have my replicas
    vector<Node> hasMyReplicas;
    // Vector holding the previous two neighbors in the ring whose replicas I have
    vector<Node> haveReplicasOf;
    // Ring
    vector<Node> ring;
    // Hash Table
    HashTable *ht;
    // Member representing this member
    Member *memberNode;
    // Params object
    Params *par;
    // Object of EmulNet
    EmulNet *emulNet;
    // Object of Log
    Log *log;
    // Transaction data string(transactionId) : string(transactionData) 
    map<int, TransactionState*> *transData;

public:
    MP2Node(Member *memberNode, Params *par, EmulNet *emulNet, Log *log,
            Address *addressOfMember);

    Member *getMemberNode() {
        return this->memberNode;
    }

    // ring functionalities
    void updateRing();
    vector<Node> getMembershipList();
    size_t hashFunction(string key);
    void findNeighbors();

    // client side CRUD APIs
    void clientCreate(string key, string value);
    void clientRead(string key);
    void clientUpdate(string key, string value);
    void clientDelete(string key);

    // receive messages from Emulnet
    bool recvLoop();
    static int enqueueWrapper(void *env, char *buff, int size);

    // handle messages from receiving queue
    void checkMessages();

    // coordinator dispatches messages to corresponding nodes
    void dispatchMessages(Message message);

    // find the addresses of nodes that are responsible for a key
    vector<Node> findNodes(string key);

    // server
    bool createKeyValue(string key, string value, ReplicaType replica);
    string readKey(string key);
    bool updateKeyValue(string key, string value, ReplicaType replica);
    bool deletekey(string key);

    // stabilization protocol - handle multiple failures
    void stabilizationProtocol();

    long now();
    void handleCreate(Message *msg);
    void handleUpdate(Message *msg);
    void handleRead(Message *msg);
    void handleDelete(Message *msg);
    void handleReply(Message *msg);
    void handleReadReply(Message *msg);
    
    // coordinator handles timeout transactions (no quorum reached)
    void handleTimeouts();

    ~MP2Node();
};


#endif /* MP2NODE_H_ */
