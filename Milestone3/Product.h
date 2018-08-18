//HyunKyu Nam
//141031161
//hnam7@myseneca.ca

#ifndef _AMA_PRODUCT_H_
#define _AMA_PRODUCT_H_

#include"ErrorState.h"


namespace AMA {
	//Maximum number of characters in a sku(stock keeping unit) – 7.
	//Maximum number of characters in the units’ descriptor for a product – 10.
	//Maximum number of characters in the user’s name descriptor for a product length – 75.
	//The current tax rate – 13 %

	const int MAXCHAR_SKU = 7;
	const int MAXCHAR_UNIT = 10;
	const int MAXCHAR_NAME = 75;
	const double TAX = 0.13;

	const int max_sku_length = MAXCHAR_SKU;
	const int max_unit_length = MAXCHAR_UNIT;
	const int max_name_length = MAXCHAR_NAME;

	class Product {
		//A character that indicates the type of the product – for use in the file record
		char product_type;
		//A character array that holds the product’s sku(stock keeping unit) – the maximum number of characters excluding the null byte is defined by the namespace constant.
		char product_sku[MAXCHAR_SKU + 1];
		//A character array that describes the product’s unit – the maximum number of characters excluding the null byte is defined by the namespace constant.
		char product_unit[MAXCHAR_UNIT + 1];
		//A pointer that holds the address of a C - style string in dynamic memory containing the name of the product.
		char* product_name;
		//An integer that holds the quantity of the product currently on hand; that is, the number of units currently on hand.
		int quantity_hand;
		//An integer that holds the quantity of the product needed; that is, the number of units needed.
		int quantity_need;
		//A double that holds the price of a single unit of the product before any taxes.
		double price_untaxed;
		//A bool that identifies the taxable status of the product; its value is true if the product is taxable.
		bool taxable;
		//An ErrorState object that holds the error state of the Product object.
		ErrorState err;
		
	protected:

		//This function receives the address of a C-style null-terminated string that holds the name of the product.
		void name(const char* pname);
		//This query returns the address of the C-style string that holds the name of the product. If the product has no name, this query returns nullptr.
		const char* name() const;
		//This query returns the address of the C-style string that holds the sku of the product.
		const char* sku() const;
		//This query returns the address of the C-style string that holds the unit of the product.
		const char* unit() const;
		//This query returns the taxable status of the product.
		bool taxed() const;
		//This query returns the price of a single item of the product.
		double price() const;
		//This query returns the price of a single item of the product plus any tax that applies to the product.
		double cost() const;
		//This function receives the address of a C-style null-terminated string holding an error message and stores that message in the ErrorState object.
		void message(const char* emessage);
		//This query returns true if the ErrorState object is clear; false otherwise.
		bool isClear() const;

	public:

		//This constructor optionally receives a character that identifies the product type. The default value is ‘N’. This function
		Product(char type = 'N');
		//Seven argument constructor
		Product(const char* sku, const char* name, const char * unit, int onHand = 0, bool taxstatus = true, double beforeTax = 0.0, int qtyneed = 0);
		//COPY CONSTRUCTOR: This constructor receives an unmodifiable reference to a Product object and copies the object referenced to the current object.
		Product(const Product& pdt);
		//COPY ASSIGNMENT OPERATOR: This operator receives an unmodifiable reference to a Product object and replaces the current object with a copy of the object referenced.
		Product& operator=(const Product& pdt);
		//DESTRUCTOR
		~Product();
		// This query receives a reference to an fstream object and an optional bool and returns a reference to the fstream object
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		// This modifier receives a reference to an fstream object and returns a reference to that fstream object
		std::fstream& load(std::fstream& file);
		// This query receives a reference to an ostream object and a bool and returns a reference to the ostream object
		std::ostream& write(std::ostream& os, bool linear) const;
		// This modifier receives a reference to an istream object and returns a reference to the istream object
		std::istream& read(std::istream& is);
		// This query receives the address of an unmodifiable C-style null-terminated string and returns true if the string is identical to the sku of the current object
		bool operator==(const char* address) const;
		// This query that returns the total cost of all items of the product on hand, taxes included
		double total_cost() const;
		// This modifier that receives an integer holding the number of units of the Product that are on hand
		void quantity(int units);
		// This query returns true if the object is in a safe empty state
		bool isEmpty() const;
		// returns the number of units of the product that are needed
		int qtyNeeded() const;
		// returns the number of units of the product that are on hand
		int quantity() const;
		// This query receives the address of a C-style null-terminated string holding a product sku and returns true if the sku of the current object is greater than the string stored at the received address
		bool operator>(const char* address) const;
		// This query receives an unmodifiable reference to a Product object and returns true if the name of the current object is greater than the name of the referenced Product object
		bool operator>(const Product& pdt) const;
		// This modifier receives an integer identifying the number of units to be added to the Product and returns the updated number of units on hand
		int operator+=(int units);

	};

	// This helper receives a reference to an ostream object and an unmodifiable reference to a Product object and returns a reference to the ostream object 
	std::ostream& operator<<(std::ostream& os, const Product& pdt);
	// This helper receives a reference to an istream object and a reference to a Product object and returns a reference to the istream object
	std::istream& operator>>(std::istream& is, Product& pdt);
	// This helper receives a reference to a double and an unmodifiable reference to a Product object and returns a double
	double operator+=(double& total, const Product& pdt);



}



#endif // !_AMA_PRODUCT_H_
