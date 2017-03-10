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

#include"StreamReader.h"

StreamReader::StreamReader(string filePath, MessageStore* dataStore) {
	_ds = dataStore;
	file = filePath;
	inputFile = new ifstream(file, ifstream::in | ios::binary);
	outputFile = new ofstream("messages.txt", ofstream::out);
}

void StreamReader::saveToStore() {
	try {
		while(!inputFile->eof()) {
			char buffer[22];
			inputFile->read(buffer, 22);
			headerPtr header = make_shared<Header>();
			header->buildHeaderFromBuffer(buffer);
			if (!inputFile->good() || inputFile->eof())
				break;
			switch (header->msg_type) {
				case 1:
					this->saveOrderEntryMessage(header);
					break;
				case 2:
					this->saveOrderAckMessage(header);
					break;
				case 3:
					this->saveOrderFillMessage(header);
					break;
				default:
					throw invalid_argument("Invalid Message Type detected!");
					break;
			}
		}
		inputFile->close();
		outputFile->close();
	} catch (exception e) {
		cout << e.what() << endl;
	}
}

void StreamReader::saveOrderEntryMessage(headerPtr header) {
	char *body = new char[header->msg_len];
	inputFile->read(body, header->msg_len);
	shared_ptr<Message> msg = make_shared<OrderEntryMessage>(header, body);
	_ds->saveOrderEntry(msg);
	//*outputFile << msg;					// Uncomment to see Messages in the output file.
	delete[] body;
}

void StreamReader::saveOrderAckMessage(headerPtr header) {
	char* body = new char[header->msg_len];
	inputFile->read(body, header->msg_len);
	shared_ptr<Message> msg = make_shared<OrderAcknowledgementMessage>(header, body);
	_ds->saveOrderAck(msg);
	//*outputFile << msg;					// Uncomment to see Messages in the output file.
	delete[] body;
}

void StreamReader::saveOrderFillMessage(headerPtr header) {
	char* body = new char[header->msg_len];
	inputFile->read(body, header->msg_len);
	shared_ptr<Message> msg = make_shared<OrderFillMessage>(header, body);
	_ds->saveOrderFill(msg);
	//*outputFile << msg;					// Uncomment to see Messages in the output file.
	delete[] body;
}

StreamReader::~StreamReader() {
	delete inputFile;
	delete outputFile;
}