#ifndef EXECUTIVE_H
#define EXECUTIVE_H

/////////////////////////////////////////////////////////////////////////////
// Executive.h - Client code that demonstrates that the requirements have  //
//					been met.											   //
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

#include<string>
#include"StreamReader.h"
#include"MessageStore.h"
#include"Message.h"
#include"ExchangeAnalyzer.h"

using namespace std;

class Executive {
public:
	Executive(string input);
	~Executive();
	void showAnalysis();

private:
	MessageStore *_msgStore;
	StreamReader *_reader;
	ExchangeAnalyzer *_analyzer;

};

#endif