//HyunKyu Nam
//141031161
//hnam7@myseneca.ca

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Product.h"
using namespace std;

namespace AMA
{

	Product::Product(char type)
	{
		productType = type;
		productSku[0] = '\0';
		productUnit[0] = '\0';
		productName = nullptr;
		productQty = 0;
		productNeeded = 0;
		productPrice = 0.0;
		productTaxable = false;
	}

	Product::Product(const char * sku, const char * name, const char * unit, int quantity, bool taxable, double price, int needed)
	{
		bool notNull = sku != nullptr && name != nullptr && unit != nullptr;

		if (notNull)
		{
			strncpy(productSku, sku, strlen(sku));
			productSku[strlen(sku)] = '\0';

			Product::name(name);

			strncpy(productUnit, unit, strlen(unit));
			productUnit[strlen(unit)] = '\0';
		}

		productQty = quantity;
		productTaxable = taxable;
		productPrice = price;
		productNeeded = needed;
	}

	Product::Product(const Product & other)
	{
		*this = other;
	}

	Product & Product::operator=(const Product & other)
	{
		if (this != &other)
		{
			int sku_l = strlen(other.productSku);
			int unit_l = strlen(other.productUnit);

			productType = other.productType;
			productQty = other.productQty;
			productNeeded = other.productNeeded;
			productPrice = other.productPrice;
			productTaxable = other.productTaxable;

			name(other.productName);

			strncpy(productSku, other.productSku, sku_l);
			productSku[sku_l] = '\0';

			strncpy(productUnit, other.productUnit, unit_l);
			productUnit[unit_l] = '\0';
		}

		return *this;
	}

	Product::~Product()
	{
		delete[] productName;
	}
	std::fstream & Product::store(std::fstream & file, bool newLine) const
	{
		file << productType << ',' << productSku << ',' << productName << ',' << productUnit << ',' << productTaxable << ',' << productPrice << ',' << productQty << ',' << productNeeded;
		if (newLine)
			file << endl;
		return file;
	}
	std::fstream & Product::load(std::fstream & file)
	{
		char sku_[MAX_CHAR_SKU];
		char name_[MAX_CHAR_NAME];
		char unit_[MAX_CHAR_UNIT];
		double price;
		int qty, needed;
		char tax;
		bool taxable;

		if (file.is_open())
		{
			file.getline(sku_, MAX_CHAR_SKU, ',');
			sku_[strlen(sku_)] = '\0';

			file.getline(name_, MAX_CHAR_NAME, ',');
			name_[strlen(name_)] = '\0';

			file.getline(unit_, MAX_CHAR_UNIT, ',');
			unit_[strlen(unit_)] = '\0';

			file >> tax;

			if (tax == '1')
				taxable = true;
			else if (tax == '0')
				taxable = false;

			file.ignore();

			file >> price;
			file.ignore();

			file >> qty;
			file.ignore();

			file >> needed;
			file.ignore();

			*this = Product(sku_, name_, unit_, qty, taxable, price, needed);
		}

		return file;
	}
	std::ostream & Product::write(std::ostream & os, bool linear) const
	{
		if (!(er.isClear()))
		{
			os << er.message();
		}

		else if (linear)
		{
			os << setw(MAX_CHAR_SKU) << left << productSku << '|'
				<< setw(20) << left << productName << '|'
				<< setw(7) << right << fixed << setprecision(2) << cost() << '|'
				<< setw(4) << right << productQty << '|'
				<< setw(10) << left << productUnit << '|'
				<< setw(4) << right << productNeeded << '|';
		}
		else
		{
			os << " Sku: " << productSku << endl
				<< " Name (no spaces): " << productName << endl
				<< " Price: " << productPrice << endl;

			if (productTaxable)
				os << " Price after tax: " << cost() << endl;
			else
			{
				os << " Price after tax:  N/A" << endl;
			}

			os << " Quantity on Hand: " << productQty << ' ' << productUnit << endl
				<< " Quantity needed: " << productNeeded;
		}

		return os;
	}
	std::istream & Product::read(std::istream & is)
	{
		char taxed;
		char * address = new char[MAX_CHAR_NAME + 1];
		int qty, need;
		double _price;

		if (!is.fail())
		{
			cout << " Sku: ";
			is >> productSku;
			cin.ignore();

			cout << " Name (no spaces): ";
			is >> address;
			name(address);

			cout << " Unit: ";
			is >> productUnit;

			cout << " Taxed? (y/n): ";
			is >> taxed;

			if (!is.fail())
			{
				er.clear();

				if (taxed)
				{
					bool y_valid = taxed == 'y' || taxed == 'Y';
					bool n_valid = taxed == 'n' || taxed == 'N';

					if (y_valid)
						productTaxable = true;

					if (n_valid)
						productTaxable = false;

					if (!(y_valid || n_valid))
					{
						is.setstate(std::ios::failbit);
						er.message("Only (Y)es or (N)o are acceptable");
						return is;
					}
				}
			}
			else
			{
				is.setstate(std::ios::failbit);
				er.message("Only (Y)es or (N)o are acceptable");
				return is;
			}

			cout << " Price: ";
			is >> _price;

			if (is.fail())
			{
				er.clear();
				is.setstate(ios::failbit);
				er.message("Invalid Price Entry");
				return is;
			}
			else
				price(_price);

			cout << " Quantity on hand: ";
			is >> qty;


			if (is.fail())
			{
				er.clear();
				er.message("Invalid Quantity Entry");
				is.setstate(ios::failbit);
				return is;
			}
			else
				quantity(qty);

			cout << " Quantity needed: ";
			is >> need;
			cin.ignore();

			if (is.fail())
			{
				er.clear();
				er.message("Invalid Quantity Needed Entry");
				is.setstate(ios::failbit);
				return is;
			}
			else
				needed(need);

			if (!is.fail())
			{
				er.clear();
			}
		}

		return is;
	}
	bool Product::operator==(const char * rhs) const
	{
		if (rhs == sku())
			return true;
		else
			return false;
	}
	double Product::total_cost() const
	{
		return productQty * cost();
	}
	void Product::quantity(int quantity)
	{
		productQty = quantity;
	}
	void Product::price(double price)
	{
		productPrice = price;
	}
	void Product::needed(int needed)
	{
		productNeeded = needed;
	}
	bool Product::isEmpty() const
	{
		if (productName == nullptr)
			return true;
		else
			return false;
	}
	char Product::type() const
	{
		return productType;
	}
	int Product::qtyNeeded() const
	{
		return productNeeded;
	}
	int Product::quantity() const
	{
		return productQty;
	}
	bool Product::operator>(const char * rhs) const
	{
		if (strcmp(productSku, rhs) > 0)
			return true;
		else
			return false;
	}
	bool Product::operator>(const iProduct & rhs) const
	{
		if (strcmp(productName, rhs.name()) > 0)
			return true;
		else
			return false;
	}
	int Product::operator+=(int units)
	{
		if (units > 0)
		{
			productQty += units;
			return productQty;
		}
		else
			return productQty;
	}
	void Product::name(const char * name)
	{
		if (name != nullptr)
		{
			int length = strlen(name);

			productName = new char[length + 1];
			for (int i = 0; i < length; i++)
			{
				productName[i] = name[i];
			}
			productName[length] = '\0';
		}
		else if (name == nullptr)
		{
			delete[] productName;
			productName = nullptr;
		}
	}

	const char * Product::name() const
	{
		if (productName != nullptr)
			return productName;
		else
			return nullptr;
	}
	const char * Product::sku() const
	{
		return productSku;
	}
	const char * Product::unit() const
	{
		return productUnit;
	}
	bool Product::taxed() const
	{
		return productTaxable;
	}
	double Product::price() const
	{
		return productPrice;
	}
	double Product::cost() const
	{
		if (productTaxable)
			return price() * (TAX_RATE + 1);
		else
			return price();
	}
	void Product::message(const char * errorMessage)
	{
		if (errorMessage != nullptr)
			er.message(errorMessage);
	}
	bool Product::isClear() const
	{
		return er.isClear();
	}
	std::ostream& operator<<(std::ostream& os, const iProduct& other)
	{
		return other.write(os, true);
	}
	std::istream& operator>>(std::istream& is, iProduct& other)
	{
		return other.read(is);
	}
}


