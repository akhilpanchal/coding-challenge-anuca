#ifndef EXCHANGE_ANALYZER_H
#define EXCHANGE_ANALYZER_H

/////////////////////////////////////////////////////////////////////////////
// ExchangeAnalyzer.h - Performs Analysis of the messages and answers the  //
//						questions given in the challenge				   //
// version 1.0                                                             //
// ----------------------------------------------------------------------- //
// Copyright © Akhil Panchal, 2016                                         //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:		Visual C++, Visual Studio 2015 Enterprise			   //
// Platform:		Dell Inspiron 17R 5721, Intel Core i5, Windows 10	   //
// Application:		CSE 687 Project #4, Spring 2015                        //
// Author:			Akhil Panchal, Syracuse University			           //
//					(408) 921-0731, ahpancha@syr.edu	                   //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* -------------------
* ExchangeAnalyzer(MessageStore* _ds);
*	- Parameterzed constructor which accepts MessageStore to be analyzed.
*
*	string getMostActiveTrader();
*	- Returns Most active trader tag.
*
*	string getMostLiquidityProvider();
*	- Return most liquidity provider's trader tag.
*
*	map<string, size_t> getVolumeOfTradesPerInstrument();
*	- Returns a map consisting of Instrument as the key and the trade volume as value.
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
#include<map>
#include<unordered_map>
#include"MessageStore.h"
#include"Message.h"
#include"MessageTypes.h"

using namespace std;

class ExchangeAnalyzer {
public:
	ExchangeAnalyzer(MessageStore* _ds);
	~ExchangeAnalyzer();

	string getMostActiveTrader();
	string getMostLiquidityProvider();
	map<string, size_t> getVolumeOfTradesPerInstrument();

private:
	MessageStore *_ds;

	void populateTraders(unordered_map<uint64_t, string>& traders);
	void populateClients(unordered_map<uint32_t, uint64_t>& clients);
	void populateTraderFills(unordered_map<uint64_t, string>& traders,
							unordered_map<uint32_t, uint64_t>& clients,
							unordered_map<string, size_t>& traderFills);
	size_t getFillQty(shared_ptr<OrderFillMessage> fill_msg);

	void populateInstruments(unordered_map<uint64_t, string>& traders);
	map<string, size_t> getTradePerInstrument(unordered_map<uint64_t, string>& instruments,
						unordered_map<uint32_t, uint64_t> clients);
};

#endif