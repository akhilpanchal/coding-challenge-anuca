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

#include"Executive.h"

Executive::Executive(string input) {
	_msgStore = new MessageStore;
	_reader = new StreamReader(input, _msgStore);
	_analyzer = new ExchangeAnalyzer(_msgStore);
}

Executive::~Executive() {
	delete _msgStore; 
	delete _reader;
	delete _analyzer;
}

void Executive::showAnalysis() {
	
	_reader->saveToStore();
	cout << "======Analysis Information======" << endl << endl;
	cout << "\n\nTotal Message Count:\t\t" << _msgStore->getCountByMsgType() << endl;	// No argument gets the total message count
	cout << "Order Entry Count:\t\t" << _msgStore->getCountByMsgType(1) << endl;
	cout << "Order Ack Count:\t\t" << _msgStore->getCountByMsgType(2) << endl;
	cout << "Order Fill Count:\t\t" << _msgStore->getCountByMsgType(3) << endl;
	cout << "Most Active Trader:\t\t" << _analyzer->getMostActiveTrader() << endl;
	cout << "Most Liquidity Provider:\t" << _analyzer->getMostLiquidityProvider() << endl;
	cout << "Volume of trades per Instrument:\n" << endl;
	cout << "\tInstrument\t\tVolume\n" << endl;
	for (auto instrument : _analyzer->getVolumeOfTradesPerInstrument()) {
		cout << "\t" << instrument.first << "\t:\t" << instrument.second << endl;
	}

}

#ifdef TEST_EXECUTIVE

#include<iostream>
using namespace std;

int main(int argc, char* args[]) {

	if (argc < 2) {
		cout << "\nGive input file spec as a command-line argument!" << endl;
		return 1;
	}
	Executive executive(args[1]);
	executive.showAnalysis();

	return 0;
}

#endif