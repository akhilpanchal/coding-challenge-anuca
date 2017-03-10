#ifndef STREAMREADER_H
#define STREAMREADER_H

/////////////////////////////////////////////////////////////////////////////
// StreamReader.h - Reads the incoming message stream from the binary file //
//					and stores the messages in the Message Store provided  //
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
*	StreamReader(string filePath, MessageStore* ds);
*	- Parameterized constructor that accepts the path of the file which
*	  has the excange messages in binary form, along with the Message store
*     where the messages are to be stored after parsing.
*
*	void saveToStore();
*	- Saves messages to the Message Store.
*
* Required Files:
* ---------------
*	Message.h, ,Message.cpp,
*	MessageStore.h, MessageStore.cpp,
*	MessageTypes.h, MessageTypes.cpp
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

#include<string>
#include<fstream>
#include<unordered_map>

#include "MessageStore.h"
#include "Message.h"
#include "MessageTypes.h"

using namespace std;

class StreamReader {
public:
	StreamReader(string filePath, MessageStore* ds);
	~StreamReader();
	void saveToStore();

private:
	MessageStore* _ds;
	string file;
	ifstream *inputFile;
	ofstream *outputFile;

	void saveOrderEntryMessage(headerPtr header);
	void saveOrderAckMessage(headerPtr header);
	void saveOrderFillMessage(headerPtr header);
	
};


#endif