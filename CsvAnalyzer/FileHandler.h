//-----------------------------------------------------
// Purpose    : Header of FileHandler class.
//-----------------------------------------------------
// Clas       : FileHandler class
//-----------------------------------------------------

#include "FileHandler_Define.h"
#include <stdlib.h>
#include <string>
#include <list>


namespace CsvAnalyzer {
	using namespace std;
	using namespace System::Diagnostics;

	//Input data structure from csv file
	typedef struct inputData{
		string timestamp;			// Message timestamp. Value in increasing.
		string date_sent;			// Date message sent timestamp, more or lesss than timestamp.
		string date_received;		// Date message received timestamp, more or same with sent timestamp.
		string sender;				// Phone number of sender.
		string receiver;			// Phone number of receiver.
	};

	//Output data structure for output file
	typedef struct outputData {
		string phone_num;			// Phone number.
		int total_sent;				// Total messages sent.
		int total_received;			// Total messages received.
		string day_highest;			// Day where has the highest number of messages sent.
		string receiver_num;		// Phone number to which the most messages were sent.
		string interlocutor;		// Number of interlocutor with greatest time spent.
	};

	ref class FileHandler {
	public:
		FileHandler();
		int startAnalyzeCSVFile(string file_name);
		list<outputData> *getOutputData(void);
		int openFile(string file_name);
		void closeFile(void);
	private:
		list<outputData>* out_table;
		list<inputData>* in_table;

		void readFile(void);
		string formatPhoneNumber(string phone_num);
		void sortPhoneList(list<string> *phone_list);
		int getTotalSentMsg(string phone_num);
		int getTotalReceivedMsg(string phone_num);
		string getDayHighestMsg(string phone_num);
		string getNumHighSent(string phone_num, list<string> phone_list);
		string getInterlocutor(string phone_num, list<string> phone_list);
	}; // class FileHandler
} // namespace CsvAnalyzer
