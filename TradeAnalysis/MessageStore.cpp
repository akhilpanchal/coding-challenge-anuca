/////////////////////////////////////////////////////////////////////////////
// MessageStore.cpp - Stores all the order messages from the exchange	   //
//					  stream											   //
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

#include "MessageStore.h"

MessageStore::MessageStore() {
	msg_type_count[0] = 0;
	msg_type_count[1] = 0;
	msg_type_count[2] = 0;
	msg_type_count[3] = 0;
}

int MessageStore::getCountByMsgType(int type) {
	if (type > 3 || type < 0)
		return -1;
	return msg_type_count[type];
}

void MessageStore::saveOrderEntry(msgPtr msg) {
	orderEntries.push_back(msg);
	msg_type_count[0]++;
	msg_type_count[1]++;
}

void MessageStore::saveOrderAck(msgPtr msg) {
	orderAcks.push_back(msg);
	msg_type_count[0]++;
	msg_type_count[2]++;
}

void MessageStore::saveOrderFill(msgPtr msg) {
	orderFills.push_back(msg);
	msg_type_count[0]++;
	msg_type_count[3]++;
}

#ifdef TEST_DATASTORE

#include"Message.h"
void main() {
	DataStore<Message> ds;
	auto msg = make_shared<Message>();
	ds.add(msg);
	ds.show();
}

#endif
