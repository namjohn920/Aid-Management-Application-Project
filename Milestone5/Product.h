//HyunKyu Nam
//141031161
//hnam7@myseneca.ca

#ifndef _product_h
#define _product_h

#include<iostream>
#include "iProduct.h"
#include "ErrorState.h"


namespace AMA
{
	const int MAX_CHAR_SKU = 7;
	const int MAX_CHAR_UNIT = 10;
	const int MAX_CHAR_NAME = 75;
	const double TAX_RATE = 0.13;

	const int max_sku_length = MAX_CHAR_SKU;
	const int max_name_length = MAX_CHAR_NAME;
	const int max_unit_length = MAX_CHAR_UNIT;

	class Product : public iProduct
	{
		char productType;
		char productSku[MAX_CHAR_SKU];
		char productUnit[MAX_CHAR_UNIT];
		char* productName;
		int productQty;
		int productNeeded;
		double productPrice;
		bool productTaxable;

	protected:
		ErrorState er;
		void name(const char* name);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char* errorMessage);
		bool isClear() const;

	public:
		Product(char type = 'N');
		Product(const char* sku, const char* name, const char* unit, int quantity = 0, bool taxable = true, double price = 0.0, int needed = 0);
		Product(const Product& other);
		Product& operator=(const Product& other);
		~Product();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char* rhs) const;
		double total_cost() const;
		void quantity(int quantity);
		void price(double price);
		void needed(int needed);
		bool isEmpty() const;
		char type() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char* rhs) const;
		bool operator>(const iProduct& rhs) const;
		int operator+=(int units);
	};

	std::ostream& operator<<(std::ostream& os, const iProduct& other);
	std::istream& operator>>(std::istream& is, iProduct& other);
	double operator+=(double& total, const iProduct& other);
	iProduct* CreateProduct();
}

#endif // !_product_h

