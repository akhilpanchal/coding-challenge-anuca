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
// Application:		Akuna Research Capital Coding Challenge                //
// Author:			Akhil Panchal, Syracuse University			           //
//					(408) 921-0731, ahpancha@syr.edu	                   //
/////////////////////////////////////////////////////////////////////////////

#include"ExchangeAnalyzer.h"

ExchangeAnalyzer::ExchangeAnalyzer(MessageStore* ds) : _ds(ds){

}

ExchangeAnalyzer::~ExchangeAnalyzer() {

}

string ExchangeAnalyzer::getMostActiveTrader() {
	/*
	TODO:
	1. Traverse over MSG_TYP_1 and store client_assigned_id as keys and trader name as value.
	2. Traverse over MSG_TYP_2 and store order_id as key and client_id as value.
	3. Traverse over MSG_TYP_3 and for each entry, find total fill_qty and find the original trader by looking up client_id from order_id,
		and then lookup trader name by client_id.
	4. Update the fill_qty for that trader.
	*/
	unordered_map<uint64_t, string> traders;
	unordered_map<uint32_t, uint64_t> clients;
	unordered_map<string, size_t> traderFills;
	populateTraders(traders);
	populateClients(clients);
	populateTraderFills(traders, clients, traderFills);
	string result = "";
	int max = 0;
	for (auto entry : traderFills) {			// Find Max in TraderFills
		if (entry.second > max)
			result = entry.first;
	}
	return result;
}

void ExchangeAnalyzer::populateTraders(unordered_map<uint64_t, string>& traders) {
	for (auto msg : _ds->getOrderEntries()) {
		shared_ptr<OrderEntryMessage> entry_msg = static_pointer_cast<OrderEntryMessage>(msg);  // downcast for accessing message specific info
		traders[entry_msg->client_assigned_id] = entry_msg->trader_tag;
	}
}

void ExchangeAnalyzer::populateClients(unordered_map<uint32_t, uint64_t>& clients) {
	for (auto msg : _ds->getOrderAcks()) {
		shared_ptr<OrderAcknowledgementMessage> ack_msg = static_pointer_cast<OrderAcknowledgementMessage>(msg);  // downcast for accessing message specific info
		clients[ack_msg->order_id] = ack_msg->client_id;
	}
}

void ExchangeAnalyzer::populateTraderFills( unordered_map<uint64_t, string>& traders,
											unordered_map<uint32_t, uint64_t>& clients,
											unordered_map<string, size_t>& traderFills
											) {
	for (auto msg : _ds->getOrderFills()) {
		shared_ptr<OrderFillMessage> fill_msg = static_pointer_cast<OrderFillMessage>(msg);  // downcast for accessing message specific info
		
		uint64_t t = clients[fill_msg->order_id];
		string trader_name = traders[t];				// lookup in clients and traders to get tradername.
		size_t total_qty = getFillQty(fill_msg);
		
		if (traderFills.find(trader_name) == traderFills.end())
			traderFills[trader_name] = total_qty;
		else
			traderFills[trader_name] += total_qty;
	}
}

size_t ExchangeAnalyzer::getFillQty(shared_ptr<OrderFillMessage> fill_msg) {
	size_t total_qty = 0;// fill_msg->fill_qty;
	for (auto group : fill_msg->groups) {
		total_qty += group->qty;
	}
	return total_qty;
}

string ExchangeAnalyzer::getMostLiquidityProvider() {
	/*
	TODO:
	1. Traverse over MSG_TYP_1 and maintain a map for Trader_name and the GFD qty that they provided
	2. Find Max by traversing the map;
	*/
	unordered_map<string, size_t> trader_GFD_volume;
	for (auto entry : _ds->getOrderEntries()) {
		shared_ptr<OrderEntryMessage> entry_msg = static_pointer_cast<OrderEntryMessage>(entry);  // downcast for accessing message specific info

		if (trader_GFD_volume.find(entry_msg->trader_tag) == trader_GFD_volume.end())
			trader_GFD_volume[entry_msg->trader_tag] = entry_msg->qty;
		else
			trader_GFD_volume[entry_msg->trader_tag] += entry_msg->qty;
	}
	size_t max = 0;
	string result = "";
	for (auto trader : trader_GFD_volume) {
		if (trader.second > max) {
			max = trader.second;
			result = trader.first;
		}
	}
	return result;
}

map<string, size_t> ExchangeAnalyzer::getVolumeOfTradesPerInstrument() {
	/*
	TODO:
	1. Traverse over MSG_TYP_1 and store client_assigned_id as keys and instrument name as value.
	2. Traverse over MSG_TYP_2 and store order_id as key and client_id as value.
	3. Traverse over MSG_TYP_3 and for each entry, find total fill_qty and find the instrument by looking up client_id from order_id,
	and then lookup the instrument by client_id.
	4. Update the fill_qty for that instrument.
	*/
	unordered_map<uint64_t, string> instruments;
	unordered_map<uint32_t, uint64_t> clients;

	populateInstruments(instruments);
	populateClients(clients);
	return std::move(getTradePerInstrument(instruments, clients));
}

void ExchangeAnalyzer::populateInstruments(unordered_map<uint64_t, string>& traders) {
	for (auto msg : _ds->getOrderEntries()) {
		shared_ptr<OrderEntryMessage> entry_msg = static_pointer_cast<OrderEntryMessage>(msg);  // downcast for accessing message specific info
		traders[entry_msg->client_assigned_id] = entry_msg->instrument;
	}
}

map<string, size_t> ExchangeAnalyzer::getTradePerInstrument(unordered_map<uint64_t, string>& instruments,
											unordered_map<uint32_t, uint64_t> clients) {
	map<string, size_t> tradePerInstrument;

	for (auto msg : _ds->getOrderFills()) {
		shared_ptr<OrderFillMessage> msg_fill = static_pointer_cast<OrderFillMessage>(msg);  // downcast for accessing message specific info
		string instrument = instruments[clients[msg_fill->order_id]];
		size_t volume = msg_fill->fill_qty;

		if (tradePerInstrument.find(instrument) == tradePerInstrument.end())
			tradePerInstrument[instrument] = volume;
		else
			tradePerInstrument[instrument] += volume;
	}

	return std::move(tradePerInstrument);
}