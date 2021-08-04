//-----------------------------------------------------
// Purpose    : Implementation of FileHandler class.
//-----------------------------------------------------
// Clas       : FileHandler class
//-----------------------------------------------------

#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace CsvAnalyzer;

namespace CsvAnalyzer {

	fstream g_file;		// Global file name descriptor.

	// purpose : FileHandler constructor.
	FileHandler::FileHandler() {
		//Initialize and clear the input and output table.
		in_table = new list<inputData>;
		out_table = new list<outputData>;
		in_table->clear();
		out_table->clear();
	}

	// purpose: Open csv file.
	// @param : file_name - file's name to be read/write.
	int FileHandler::openFile(string file_name) {
		g_file.open(file_name);

		if (!g_file.is_open()) {
			Debug::WriteLine("File open error!");
			return PROCESS_OPEN_ERR;
		}

		return PROCESS_OK;
	}

	// purpose : Close the opened csv file.
	void FileHandler::closeFile(void) {
		g_file.close();
	}

	// purpose: Analyze and sorts the data.
	// @param : file_name - file's name to be read/write.
	int FileHandler::startAnalyzeCSVFile(string file_name) {
		int ret = PROCESS_OK;
		list<string> phoneList;
		list<inputData>::iterator it;
		list<string>::iterator itPhoneNum;
		outputData out_data;

		memset(&out_data, 0x00, sizeof(outputData));

		//Open file
		ret = openFile(file_name);
		if (ret != PROCESS_OK) {
			Debug::WriteLine("File open error!");
			return ret;
		}

		readFile();
		sortPhoneList(&phoneList);

		// Set output table
		for (itPhoneNum = phoneList.begin(); itPhoneNum != phoneList.end(); itPhoneNum++) {
			out_data.phone_num		= (*itPhoneNum);
			out_data.total_sent		= getTotalSentMsg(*itPhoneNum);
			out_data.total_received	= getTotalReceivedMsg(*itPhoneNum);
			out_data.day_highest	= getDayHighestMsg(*itPhoneNum);
			out_data.receiver_num	= getNumHighSent(*itPhoneNum, phoneList);
			out_data.interlocutor	= getInterlocutor(*itPhoneNum, phoneList);
			out_table->push_back(out_data);
		}
		return ret;
	}

	// purpose: read the csv iput file.
	void FileHandler::readFile(void) {
		inputData in_data;
		vector<string> row_data;
		int count = 0;
		string row, cell_data;

		memset(&in_data, 0x00, sizeof(inputData));

		//Read file by line.
		while (getline(g_file, row)) {
			stringstream ss(row);

			//extract every data on the current line
			while (getline(ss, cell_data, ',')) {
				row_data.push_back(cell_data);
			}

			in_data.timestamp		= (string)row_data[0];
			in_data.date_sent		= (string)row_data[1];
			in_data.date_received	= (string)row_data[2];
			in_data.sender			= formatPhoneNumber(row_data[3]);
			in_data.receiver		= formatPhoneNumber(row_data[4]);
			in_table->push_back(in_data);

			//clear vector for next row
			row_data.clear();
		}

		//Close file after read.
		closeFile();
	}

	// purpose: Remove characters in a phone number and set to all digits only.
	// @param : phone_num - sender/receiver's phone_number
	string FileHandler::formatPhoneNumber(string phone_num) {
		string phone = "";
		int length = phone_num.length();
		
		for (int i = 0; i < length; i++) {
			if ((phone_num[i] == '0') || (phone_num[i] == '1') || (phone_num[i] == '2') || (phone_num[i] == '3') || (phone_num[i] == '4') ||
				(phone_num[i] == '5') || (phone_num[i] == '6') || (phone_num[i] == '7') || (phone_num[i] == '8') || (phone_num[i] == '9')){
				phone += phone_num[i];
			}
		}
	
		return phone;
	}

	// purpose: Sort the list of phone numbers with no duplicate.
	// @[aram : phone_list - list of all numbers base on send and receive columns.
	void FileHandler::sortPhoneList(list<string> *phone_list) {
		set<string> set;
		list<double> tempList;
		
		//Get the list of numbers both sender and receiver.
		for (auto itInput = in_table->begin(); itInput != in_table->end(); itInput++) {
			phone_list->push_back(itInput->sender);
			phone_list->push_back(itInput->receiver);
		}

		//Remove duplicates in the phone list
		for (auto itPhone = phone_list->begin(); itPhone != phone_list->end(); itPhone++) {
			set.insert(*itPhone);
		}

		//clear the data list and update the list without duplicates
		phone_list->clear();
		for (auto iterator = set.begin(); iterator != set.end(); iterator++) {
			phone_list->push_back(*iterator);
		}

		// Convert the phone numbers to digits and then sort it.
		for (auto itPhone = phone_list->begin(); itPhone != phone_list->end(); itPhone++) {
			tempList.push_back(stod(*itPhone));
		}

		tempList.sort();
		
		// Clear the phone list before updating it with the sorted list.
		string num = "";
		int pos;
		phone_list->clear();
		for (auto itNum = tempList.begin(); itNum != tempList.end(); itNum++) {
			//Remove the decimal.
			num = to_string(*itNum);
			pos = num.find('.');
			num = num.substr(0, pos);
			phone_list->push_back(num);
		}
	}

	// purpose: Get the total number that a number has sent a message.
	// @param : phone_num - phone number of the user
	int FileHandler::getTotalSentMsg(string phone_num) {
		int count = 0;

		//Check how many times the number appeared on the sender column.
		for (auto it = in_table->begin(); it != in_table->end(); it++) {
			if (phone_num.compare(it->sender) == 0) {
				count++;
			}
		}

		return count;
	}

	// purpose: Get the total number that a number has received a message.
	// @param : phone_num - phone number of the user
	int FileHandler::getTotalReceivedMsg(string user){
		int count = 0;

		//Check how many times the number appeared on the receiver column.
		for (auto it = in_table->begin(); it != in_table->end(); it++) {
			if (user.compare(it->receiver) == 0) {
				count++;
			}
		}
		
		return count;
	}

	// purpose: Get the date that has the highest number of messages sent.
	// @param : phone_num - phone number of the user
	string FileHandler::getDayHighestMsg(string phone_num) {
		list<string> date;
		map<string, unsigned> occur;				//list of phone numbers with how many times they received.
		unsigned count = 0;

		//Get the dates a message sent.
		for (auto it = in_table->begin(); it != in_table->end(); it++) {
			if (phone_num.compare(it->sender) == 0) {
				date.push_back(it->date_sent);
			}
		}

		//Get the number of dates.
		for (auto itDate = date.begin(); itDate != date.end(); itDate++) {
			count = ::count(date.begin(), date.end(), *itDate);
			occur.insert(pair<string, unsigned>(*itDate, count));
		}

		auto itMap = max_element(occur.begin(), occur.end());

		return itMap->first;
	}

	// purpose: Get the phone number to which the most messages were sent
	// @param : sender		- current phone number
	// @param : phone_list	- inventory of phone numbers.
	string FileHandler::getNumHighSent(string phone_num, list<string> phone_list) {
		unsigned int uiCounter = 0;
		string receiver = "";
		map<string, unsigned> occur;				//list of phone numbers with how many times they received.
		
		//Iterate throughout the list of phone numbers.
		for (auto itPhone = phone_list.begin(); itPhone != phone_list.end(); itPhone++) {
			receiver = *itPhone;
			// Exclude sender.
			if (phone_num.compare(receiver) != 0) {
				//Check how many times the receiver occurred in the receiver column.
				for (auto itInput = in_table->begin(); itInput != in_table->end(); itInput++) {
					if (receiver.compare(itInput->receiver) == 0) {
						uiCounter++;
					}
				}
				occur.insert(pair<string, unsigned>(receiver, uiCounter));
			}
		}

		auto itMap = max_element(occur.begin(), occur.end());

		return itMap->first;; //Return the phone number of the max value.
	}

	// purpose: Get the phone number of the interlocutor for whom the difference between received
	//           and sent messages from sender is the greatest
	// @param : sender - current phone number
	// @param : phone_list - invetory of phone numbers
	string FileHandler::getInterlocutor(string phone_num, list<string> phone_list) {
		unsigned int uiTimeDiff = 0;
		string receiver = "";
		map<string, unsigned> occur;				//list of phone numbers with how many times they received.

		//Iterate throughout the list of phone numbers.
		for (auto itPhone = phone_list.begin(); itPhone != phone_list.end(); itPhone++) {
			receiver = *itPhone;
			// Exclude sender.
			if (phone_num.compare(receiver) != 0) {
				//Get the total time difference of the receiver.
				for (auto itInput = in_table->begin(); itInput != in_table->end(); itInput++) {
					if (receiver.compare(itInput->receiver) == 0) {
						uiTimeDiff += stoi(itInput->date_received) - stoi(itInput->date_sent);
					}
				}
				occur.insert(pair<string, unsigned>(receiver, uiTimeDiff));
			}
		}

		auto itMap = max_element(occur.begin(), occur.end());

		return itMap->first;; //Return the phone number of the max value.
	}

	// purpose: Return the output table.
	list<outputData>* FileHandler::getOutputData(void) {
		return out_table;
	}

} // namespace CsvAnalyzer


