/**********************************
 * FILE NAME: MP1Node.cpp
 *
 * DESCRIPTION: Membership protocol run by this Node.
 * 				Header file of MP1Node class.
 **********************************/

#ifndef _MP1NODE_H_
#define _MP1NODE_H_

#include "stdincludes.h"
#include "Log.h"
#include "Params.h"
#include "Member.h"
#include "EmulNet.h"
#include "Queue.h"

/**
 * Macros
 */
#define TREMOVE 20
#define TFAIL 5

/*
 * Note: You can change/add any functions in MP1Node.{h,cpp}
 */

/**
 * Message Types
 */
enum MsgTypes{
    JOINREQ,
    SWIMPING,
    SWIMPONG,
    DUMMYLASTMSGTYPE
};

/**
 * STRUCT NAME: MessageHdr
 *
 * DESCRIPTION: Header and content of a message
 */
typedef struct MessageHdr {
	enum MsgTypes msgType;
}MessageHdr;

/**
 * CLASS NAME: MP1Node
 *
 * DESCRIPTION: Class implementing Membership protocol functionalities for failure detection
 */
class MP1Node {
private:
        int myId; // This Node's Id
	EmulNet *emulNet;
	Log *log;
	Params *par;
	Member *memberNode;
	char NULLADDR[6];

public:
	MP1Node(Member *, Params *, EmulNet *, Log *, Address *);
	Member * getMemberNode() {
		return memberNode;
	}
	int recvLoop();
	static int enqueueWrapper(void *env, char *buff, int size);
	void nodeStart(char *servaddrstr, short serverport);
	int initThisNode(Address *joinaddr);
	int introduceSelfToGroup(Address *joinAddress);
	int finishUpThisNode();
	void nodeLoop();
	void checkMessages();
	bool recvCallBack(void *env, char *data, int size);
	void nodeLoopOps();
	int isNullAddress(Address *addr);
	Address getJoinAddress();
	void initMemberListTable(Member *memberNode);
	void printAddress(Address *addr);
	virtual ~MP1Node();
        
        // added ---------------
        
        void addMember(Address *address);
        void dumpMem(char *pointer, int size);
        Address makeAddress(int id, short port);
        // Get Fresh(recent state change) membership data to be sent on swim msgs.
        char* membershipData(); 
        long now();
        // Find a random node in mebership list, NULL if none available. 
        int randomNode(int exclude1, int exclude2);
        void recvJoinReq(char *payload);
        void recvPing(char *payload);
        void recvPong(char *payload);
        // Handles membership data received from another node.
        void recvMembershipData(char *payload);
        // Update a member when we here from it(pong), update state & timestamp
        void updateMember(Address *from);
        // sends a swim message (ping from "from" to "to") via "via".
        void swimMsg(MsgTypes type, Address *from, Address *to, Address *via);
};

#endif /* _MP1NODE_H_ */
