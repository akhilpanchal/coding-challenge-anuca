#ifndef MESSAGE_H
#define MESSAGE_H

/////////////////////////////////////////////////////////////////////////////
// Message.h - Abstract base class that stores the common properties of   //
//				a message i.e. the header								   //
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
#include<memory>
#include<string>
#include<iostream>

using namespace std;

struct Header;

typedef shared_ptr<Header> headerPtr;

struct Header {
	uint16_t marker;
	uint8_t msg_type;
	uint64_t sequence_id;
	uint64_t timestamp;
	uint8_t msg_direction;
	uint16_t msg_len;
	void buildHeaderFromBuffer(char*);
	string show();
	
};

class Message {
public:
	virtual ~Message();
	friend ostream& operator<<(ostream& ostrm, const Message& a);

	headerPtr getHeader() { return _header; }
	void setHeader(headerPtr header) { this->_header = header; }
	string showHeader() { return _header->show(); }
	virtual string showBody() = 0;
protected:
	headerPtr _header;
};

inline ostream& operator<<(ostream& ostrm, const Message& b) {
	ostrm << b._header->show();
	return ostrm;
}
#endif