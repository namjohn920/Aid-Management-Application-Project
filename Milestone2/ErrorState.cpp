//HyunKyu Nam
//141031161
//hnam7@myseneca.ca

#include <iostream>
#include <cstring>
#include "ErrorState.h"

namespace AMA {

	ErrorState::ErrorState(const char* errorMessage) {
		//if the errorMessage received is nullptr, eMessage is initialized to nullptr
		if (errorMessage == nullptr) {

			eMessage = nullptr;

		} // if the errorMessage is not nullptr, then the character string is copied to eMessage
		//and at the end of the eMessage, terminating sequence is added to make sure.
		else {

			eMessage = new char[strlen(errorMessage) + 1];
			strcpy(eMessage, errorMessage);
			eMessage[strlen(errorMessage)] = '\0';

		}

	}

	ErrorState::~ErrorState() {
		//deallocates the resources for eMessage and initialize it to nullptr
		delete[] eMessage;
		eMessage = nullptr;

	}

	void ErrorState::clear() {
		//deallocates the resources for current object eMessage and set it to nullptr
		delete[] this->eMessage;
		eMessage = nullptr;

	}

	bool ErrorState::isClear() const {
		//clear is set to false, so if emessage is not nullptr, it is just returned. Otherwise it becomes true and returned
		bool clear = false;
		if (eMessage == nullptr) {
			clear = true;
		}
		return clear;

	}

	void ErrorState::message(const char* str) {
		//deallocate the memory previously assigned and allocate dynamic memory then, copy str to eMessage
		delete[] eMessage;
		eMessage = new char[strlen(str) + 1];
		strcpy(eMessage, str);
		eMessage[strlen(str)] = '\0';

	}

	const char* ErrorState::message()const {
		//return eMessage
		return eMessage;

	}

	ostream & operator<< (std::ostream & os, ErrorState& em) {
		//if the value from isClear() is false, message will be returned.
		if (em.isClear() == false) {
			os << em.message();
		}

		return os;

	}

}