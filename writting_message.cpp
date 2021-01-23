#include <iostream>
#include <fstream>
#include <string>
#include "google/protobuf/util/json_util.h"
#include "addressbook.pb.h"

using namespace std;
using namespace tutorial;
void PromptForAddress(Person* person)
{
	cout << "enter person id: ";
	int id;
	cin >> id;
	person->set_id(id);
	cin.ignore(256, '\n');
	cout << "personid=";
	cout << person->id() << endl;
	
	cout << "enter name: ";
	getline(cin, *person->mutable_name());
	cout << "name=" << person->name() << endl;

	cout << "enter email address (blank for none): ";
	string email;
	getline(cin, email);
	if(!email.empty())
	{
		person->set_email(email);
	}
	cout << "email=" << email << endl;

	while(true)
	{
		cout << "enter a phone number (or leave blank to finish): ";
		string number;
		getline(cin, number);
		if(number.empty())
		{
			break;
		}

		Person::PhoneNumber* phone_number = person->add_phones();
		phone_number->set_number(number);

		cout << "is this a mobile, home, or work phone? ";
		string type;
		getline(cin, type);
		if (type == "mobile") {
			phone_number->set_type(Person::MOBILE);
		} else if (type == "home") {
			phone_number->set_type(Person::HOME);
		} else if (type == "work") {
			phone_number->set_type(Person::WORK);
		} else {
			cout << "unknown phone type" << endl;
		}
		cout << "phone=" << phone_number->number() << " type=" << phone_number->type() << endl;
	}
}


int main(int argc, char* argv[]) {
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
		return -1;
	}

	AddressBook address_book;

	{
		//read the existing address book
		fstream input(argv[1], ios::in | ios::binary);
		if(!input) {
			cout << argv[1] << ": file not found. Creating a new file" << endl;
		} else if (!address_book.ParseFromIstream(&input)) {
			cerr << "failed to parse address book" << endl;
			return -1;
		}

	}


	PromptForAddress(address_book.add_people());

	{
		//write the new address book back to disk
		fstream output(argv[1], ios::out | ios::trunc | ios::binary);
		string str;
		google::protobuf::util::JsonPrintOptions options;
		options.add_whitespace = true;
		options.always_print_primitive_fields = false;
		google::protobuf::util::MessageToJsonString(address_book, &str, options);
		output << str << endl;
/*		if (!address_book.SerializeToOstream(&output)) {
			cerr << "failed to write address book" << endl;
			return -1;
		}
*/
	}

	google::protobuf::ShutdownProtobufLibrary();


	return 0;
}










