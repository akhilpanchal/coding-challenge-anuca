#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

/////////////////////////////////////////////////////////////////////////////
// MessageTypes.h - Stores information for different message types		   //
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
*	All Message types are struct. Therefore, publicly accessible
*
* Required Files:
* ---------------
*	Message.h, ,Message.cpp
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

#include "Message.h"
#include<string>
#include<vector>

struct OrderEntryMessage : public Message {
	OrderEntryMessage(headerPtr header, char*);
	friend ostream& operator<<(ostream& ostrm, shared_ptr<Message> msg);
	string showBody();
	uint64_t price;
	uint32_t qty;
	string instrument;
	uint8_t side;
	uint64_t client_assigned_id;
	uint8_t time_in_force;
	string trader_tag;
	uint8_t firm_id;
	string firm;
	string termination_string;
};

struct OrderAcknowledgementMessage : public Message {

	OrderAcknowledgementMessage(headerPtr header, char*);
	friend ostream& operator<<(ostream& ostrm, shared_ptr<Message> msg);
	string showBody();

	uint32_t order_id;
	uint64_t client_id;
	uint8_t order_status;
	uint8_t reject_code;
	string termination_string;
};

struct Group {
	Group(char*);
	uint8_t firm_id;
	string trader_tag;
	uint32_t qty;
	string show();
};

struct OrderFillMessage : public Message {

	typedef shared_ptr<Group> gPtr;
	OrderFillMessage(headerPtr header, char*);
	friend ostream& operator<<(ostream& ostrm, shared_ptr<Message> msg);
	string showBody();

	uint32_t order_id;
	uint64_t fill_price;
	uint32_t fill_qty;
	uint8_t no_of_contras;
	vector<gPtr> groups;

	void addGroup(gPtr group) { groups.push_back(group); }
};


#endif