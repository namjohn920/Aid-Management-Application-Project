//HyunKyu Nam
//141031161
//hnam7@myseneca.ca

#ifndef _ErrorState_h_
#define _ErrorState_h_

#include <iostream>
using namespace std;

namespace AMA {

	class ErrorState {

		char* eMessage;

	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& em) = delete;
		ErrorState& operator=(const ErrorState& em) = delete;
		virtual ~ErrorState();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message()const;


	};

	std::ostream & operator<< (std::ostream & os, ErrorState&);



}


#endif // !_ErrorState_h_
