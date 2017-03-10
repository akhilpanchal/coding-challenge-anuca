#ifndef MESSAGESTORE_H
#define MESSAGESTORE_H

/////////////////////////////////////////////////////////////////////////////
// MessageStore.h - Stores all the order messages from the exchange stream //
//																		   //
// version 1.0                                                             //
// ----------------------------------------------------------------------- //
// Copyright © Akhil Panchal, 2016                                         //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:		Visual C++, Visual Studio 2015 Enterprise			   //
// Platform:		Dell Inspiron 17R 5721, Intel Core i5, Windows 10	   //
// Application:		Akuna Research Capital Coding Challenge                //
// Author:			Akhil Panchal, Syracuse University			           //
//					(408) 921-0731, ahpancha@syr.edu	                   //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
*	MessageStore();
*		- Default Constructor;
*	void saveOrderEntry(msgPtr msg);
*		- Saves an order entry message, pointed to by a
*		  base message smart pointer
*
*	void saveOrderAck(msgPtr msg);
*		- Saves an order acknowledgement message, pointed to by a
*		  base message smart pointer
*
*	void saveOrderFill(msgPtr msg);
*		- Saves an order fill message, pointed to by a
*	      base message smart pointer
*
*	vector<msgPtr> getOrderEntries()
*	vector<msgPtr> getOrderAcks()
*	vector<msgPtr> getOrderFills()
*		- Getters for each of the message type containers.
*
*	int getCountByMsgType(int type = 0);
*		- Getter for message count for each type. 
*		- Returns total count if no argument/0 is passed.
*		- Returns -1 if invlid message type passed.
*
* Required Files:
* ---------------
*	Message.h, ,Message.cpp
*	MessageStore.h, MessageStore.cpp
*
* Build Process:
* --------------
*	devenv AcunaCodingChallenge.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.0 : 21 April 2016
* - first release
*
*/
#include<memory>
#include<vector>
#include<unordered_map>
#include<iostream>
#include"Message.h"

using namespace std;

typedef shared_ptr<Message> msgPtr;

class MessageStore {
public:
	MessageStore();
	void saveOrderEntry(msgPtr msg);
	void saveOrderAck(msgPtr msg);
	void saveOrderFill(msgPtr msg);

	vector<msgPtr> getOrderEntries(){ return orderEntries; }
	vector<msgPtr> getOrderAcks() { return orderAcks; }
	vector<msgPtr> getOrderFills() { return orderFills; }

	int getCountByMsgType(int type = 0);
private:
	vector<msgPtr> orderEntries;
	vector<msgPtr> orderAcks;
	vector<msgPtr> orderFills;
	unordered_map<uint8_t, int> msg_type_count;
	int total_count;

};



#endif