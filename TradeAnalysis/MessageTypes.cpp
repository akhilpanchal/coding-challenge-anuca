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

#include "MessageTypes.h"

OrderEntryMessage::OrderEntryMessage(headerPtr header, char* buffer) {
	this->_header = header;
	this->price = *((uint64_t*)buffer);
	buffer += sizeof(uint64_t);
	this->qty = *((uint32_t*)buffer);
	buffer += sizeof(uint32_t);
	
	for (int i = 0; i < 10; i++)
		this->instrument += buffer[i];
	buffer += sizeof(char)*10;
	
	
	this->side = *((uint8_t*)buffer);
	buffer += sizeof(uint8_t);
	this->client_assigned_id = *((uint64_t*)buffer);
	buffer += sizeof(uint64_t);
	this->time_in_force = *((uint8_t*)buffer);
	buffer += sizeof(uint8_t);

	for (int i = 0; i < 3; i++)
		this->trader_tag += buffer[i];
	buffer += sizeof(char) * 3;

	this->firm_id = *((uint8_t*)buffer);
	buffer += sizeof(uint8_t);

	int i = 0;
	while (buffer[i] != 'D') {
		this->firm += buffer[i++];
	}
	buffer += i;
	for (int i = 0; i < 8; i++)
		this->termination_string += buffer[i];

	buffer += sizeof(char)*8;
}

string OrderEntryMessage::showBody() {
	string body = "Body:\n";

	body += "\tprice: " + to_string(price) + "\n";
	body += "\tqty: " + to_string(qty) + "\n";
	body += "\tinstrument: " + instrument + "\n";
	body += "\tside: " + to_string(side) + "\n";
	body += "\tclient_assigned_id: " + to_string(client_assigned_id) + "\n";
	body += "\ttime_in_force: " + to_string(time_in_force) + "\n";
	body += "\ttrader_tag: " + trader_tag + "\n";
	body += "\tfirm_id: " + to_string(firm_id) + "\n";
	body += "\tfirm: " + firm + "\n";
	body += "\ttermination_string: " + termination_string + "\n";

	return body;
}

ostream& operator<<(ostream& ostrm, shared_ptr<Message> msg) {
	ostrm << msg->showHeader();
	ostrm << msg->showBody();
	return ostrm;
}

OrderAcknowledgementMessage::OrderAcknowledgementMessage(headerPtr header, char* buffer) {

	this->_header = header;

	this->order_id = *((uint32_t*)buffer);
	buffer += sizeof(uint32_t);

	this->client_id = *((uint64_t*)buffer);
	buffer += sizeof(uint64_t);

	this->order_status = *((uint8_t*)buffer);
	buffer += sizeof(uint8_t);

	this->reject_code = *((uint8_t*)buffer);
	buffer += sizeof(uint8_t);

	for (int i = 0; i < 8; i++)
		this->termination_string += buffer[i];
	buffer += sizeof(char) * 8;
}

string OrderAcknowledgementMessage::showBody() {
	string body = "Body:\n";

	body += "\torder_id: " + to_string(order_id) + "\n";
	body += "\tclient_id: " + to_string(client_id) + "\n";
	body += "\torder_status: " + to_string(order_status) + "\n";
	body += "\treject_code: " + to_string(reject_code) + "\n";
	body += "\ttermination_string: " + termination_string + "\n";

	return body;
}

Group::Group(char* buffer) {
	this->firm_id = *((uint8_t*)buffer);
	buffer += sizeof(uint8_t);
	for (int i = 0; i < 3; i++)
		this->trader_tag += buffer[i];
	buffer += sizeof(char)*3;
	this->qty = *((uint32_t*)buffer);
	buffer += sizeof(uint32_t);
}

string Group::show() {
	string group = "Group:\n";
	group += "\t\tfirm_id: " + to_string(firm_id) +"\n";
	group += "\t\ttrader_tag: " + trader_tag +"\n";
	group += "\t\tqty: " + to_string(qty) + "\n\n";
	return group;
}

OrderFillMessage::OrderFillMessage(headerPtr header, char* buffer) {

	this->_header = header;
	this->order_id = *((uint32_t*)buffer);
	buffer += sizeof(uint32_t);
	this->fill_price = *((uint64_t*)buffer);
	buffer += sizeof(uint64_t);
	this->fill_qty = *((uint32_t*)buffer);
	buffer += sizeof(uint32_t);
	this->no_of_contras = *((uint8_t*)buffer);
	buffer += sizeof(uint8_t);
	for (int i = 0; i < this->no_of_contras; i++) {
		gPtr group = make_shared<Group>(buffer);
		groups.push_back(group);
	}
}

string OrderFillMessage::showBody() {
	string body = "Body:\n";

	body += "\torder_id: " + to_string(order_id) + "\n";
	body += "\tfill_price: " + to_string(fill_price) + "\n";
	body += "\tfill_qty: " + to_string(fill_qty) + "\n";
	body += "\tno_of_contras: " + to_string(no_of_contras) + "\n";
	for (auto group : groups)
		body += "\t" + group->show();
	return body;
}