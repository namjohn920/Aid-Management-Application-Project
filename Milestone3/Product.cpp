//HyunKyu Nam
//141031161
//hnam7@myseneca.ca

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>

#include "Product.h"
#include "ErrorState.h"

namespace AMA {


	/* ---------------PROTECTED MEMBER FUNCTIONS---------------*/
	
	void Product::name(const char* pname) {
		//stores the name in dynamically allocated memory
		//replaces any name previously stored
		//If the incoming parameter holds the nullptr address, 
		//this function removes the name of the product, if any, from memory.
		if (pname != nullptr) {
			int length = strlen(pname);
			product_name = new char[length + 1];

			for (int i = 0; i < length; i++) {
				product_name[i] = pname[i];
			}

			product_name[length] = '\0';
		}

	}

	const char* Product::name() const {
		//If product name is not nullptr, return product name. Otherwise return nullptr
		if (product_name != nullptr)
			return product_name;
		else
			return nullptr;

	}

	const char* Product::sku() const {
		//return product sku
		return product_sku;
	}

	const char* Product::unit() const {
		//return product unit
		return product_unit;
	}

	bool Product::taxed() const {
		//return taxable status
		return taxable;

	}

	double Product::price() const {
		//return price before tax
		return price_untaxed;

	}

	double Product::cost() const {
		// it it taxable, it returns price times 1.13 otherwise it just returns the untaxed price
		if (taxable)
			return (price() * (1+TAX));
		else
			return price();
	}

	void Product::message(const char* emessage) {
		// input error message into message function of errorstate object
		err.message(emessage);

	}

	bool Product::isClear() const {
		//return if it is cleared or not
		return err.isClear();


	}

	/*--------------PUBLIC MEMBER FUNCTIONS ------------------- */


	//stores the character receives in an instance variable
	//sets the current object to a safe recognizable empty state.
	Product::Product(char type) {
		//safe empty state
		product_type = type;
		product_sku[0] = '\0';
		product_unit[0] = '\0';
		product_name = nullptr;
		quantity_hand = 0;
		quantity_need = 0;
		price_untaxed = 0.0;
		taxable = false;

	}

	Product::Product(const char* sku, const char* pname, const char * unit, int qtyhand, bool taxstatus, double beforeTax, int qtyneed) {
		//7 argument constructor
		name(pname);

		strncpy(product_sku, sku, (MAXCHAR_SKU + 1));
		product_sku[MAXCHAR_SKU] = '\0';

		strncpy(product_unit, unit, (MAXCHAR_UNIT + 1));
		product_unit[MAXCHAR_UNIT] = '\0';

		quantity_hand = qtyhand;

		quantity_need = qtyneed;

		price_untaxed = beforeTax;

		taxable = taxstatus;


	}

	Product::Product(const Product& pdt) {

		//copy constructor. copy the members of pdt
		name(pdt.product_name);

		product_type = pdt.product_type;
		
		strncpy(product_sku, pdt.product_sku, (MAXCHAR_SKU + 1));
		product_sku[MAXCHAR_SKU] = '\0';

		strncpy(product_unit, pdt.product_unit, (MAXCHAR_UNIT + 1));
		product_unit[MAXCHAR_UNIT] = '\0';

		quantity_hand = pdt.quantity_hand;

		quantity_need = pdt.quantity_need;

		price_untaxed = pdt.price_untaxed;

		taxable = pdt.taxable;
		
	}

	Product& Product::operator=(const Product& pdt) {
		//copy assignment
		if (this != &pdt) {
			product_type = pdt.product_type;

			strncpy(product_sku, pdt.product_sku, (MAXCHAR_SKU + 1));
			product_sku[MAXCHAR_SKU] = '\0';

			strncpy(product_unit, pdt.product_unit, (MAXCHAR_UNIT + 1));
			product_unit[MAXCHAR_UNIT] = '\0';

			quantity_hand = pdt.quantity_hand;

			quantity_need = pdt.quantity_need;

			price_untaxed = pdt.price_untaxed;

			taxable = pdt.taxable;

			delete[] product_name;
			
			name(pdt.product_name);
			
		}

		return *this;

	}

	Product::~Product() {
		//deallocate the memory allocated to product name
		delete[] product_name;
		err.clear();

	}

	

	std::fstream& Product::store(std::fstream& file, bool newLine) const {
		//inserts into the fstream object the character that identifies the product type as the first field in the record
		//inserts into the fstream object the data for the current object in comma separated fields
		//if the bool parameter is true, inserts a newline at the end of the record.

		file << product_type << ',' << product_sku << ',' << product_unit << ',' << product_name << ',' << quantity_hand << ',' << taxable << ',' << price_untaxed << ',' << quantity_need;
		if (newLine)
			file << endl;
		file.clear();
		file.close();
		return file;

	}

	

	std::fstream& Product::load(std::fstream& file) {
		//extracts the fields for a single record from the fstream object
		//creates a temporary object from the extracted field data
		//copy assigns the temporary object to the current object.

		Product temp;

		temp.product_name = new char[MAXCHAR_NAME + 1];

		if (file.is_open()) {

			file >> temp.product_type >> temp.product_type >> temp.product_unit >> temp.product_name >> temp.quantity_hand >> temp.taxable >> temp.price_untaxed >> temp.quantity_need;
			*this = temp;

		}

		delete[] temp.product_name;
		temp.product_name = nullptr;

		return file;

	}

	
	std::ostream& Product::write(std::ostream& os, bool linear) const {

		if (linear) {			
						
			os << setw(MAXCHAR_SKU) << left << product_sku << "|"
			<< setw(20) << left << product_name << "|"
			<< setw(7) << fixed << setprecision(2) << right << cost() << "|"
			<< setw(4) << right << quantity_hand << "|"
			<< setw(10) << left << product_unit << "|"
			<< setw(4) << right << quantity_need << "|";
		}
		else {			

			os << "SKU: " << product_sku << endl
			<< "Name: " << product_name << endl
			<< "Price: " << price() << endl;

			if (taxed())
				os << "Price after tax: " << cost() << endl;
			else
				os << "N/A" << endl;

			os << "Quantity on hand: " << quantity_hand << endl
				<< "Quantity Needed: " << quantity_need << endl;
		}
		return os;

	}

	std::istream& Product::read(std::istream& is) {

		char sku2[MAXCHAR_SKU + 1];
		char *name2 = new char[MAXCHAR_NAME + 1];
		char unit2[MAXCHAR_UNIT];
		int qtyhand2;
		int qtyneed2;
		double untaxed;
		char tax2;
		bool taxable2;

		cout << " Sku: ";
		is >> sku2;

		cout << " Name (no spaces): ";
		is >> name2;

		cout << " Unit: ";
		is >> unit2;

		cout << " Taxed? (y/n): ";
		is >> tax2;

		//depending on the user input, the taxable status would change
		if (tax2 == 'Y' || tax2 == 'y') {

			taxable2 = true;

		}else if (tax2 == 'N' || tax2 == 'n') {

			taxable2 = false;

		}else {

			is.setstate(ios::failbit);		
			err.message("Only (Y)es or (N)o are acceptable");
		}

		if (!is.fail()) {
			cout << " Price: ";
			is >> untaxed;
			if (is.fail()) {
				err.message("Invalid Price Entry");
			}

		}

		if (!is.fail()) {
			cout << " Quantity on hand: ";
			is >> qtyhand2;
			if (is.fail()) {
				err.message("Invalid Quantity Entry");
			}
		}

		if (!is.fail()) {
			cout << " Quantity needed: ";
			is >> qtyneed2;
			if (is.fail()) {
				err.message("Invalid Quantity Needed Entry");
			}
		}

		if (!is.fail()) {
			
			*this = Product(sku2, name2, unit2, qtyhand2, taxable2, untaxed, qtyneed2);

		}

		return is;

	}

	bool Product::operator==(const char* address) const {
	
		if (strcmp(address, product_sku) == 0)
			return true;
		else
			return false;
	}
	
	double Product::total_cost() const {

		double total = quantity() * cost();

		return total;

	}
	
	void Product::quantity(int units) {

		quantity_hand = units;

	}
	
	bool Product::isEmpty() const {

		if (product_name == nullptr)
			return true;
		else
			return false;
	}
	
	int Product::qtyNeeded() const {

		return quantity_need;

	}
	
	int Product::quantity() const {

		return quantity_hand;

	}

	
	bool Product::operator>(const char* address) const {

		if (strcmp(product_sku, address) > 0)
			return true;
		else
			return false;
	}
	
	bool Product::operator>(const Product& pdt) const {

		if (strcmp(product_name, pdt.product_name) > 0)
			return true;
		else
			return false;

	}
	
	int Product::operator+=(int units) {
		
		if (units > 0) {
			quantity_hand += units;
			return quantity_hand;
		}
		else
			return quantity_hand;		

	}

	/*----------HELPER FUNCTIONS----------------*/

	std::ostream& operator<<(std::ostream& os, const Product& pdt) {

		return pdt.write(os, true);

	}
	
	std::istream& operator>>(std::istream& is, Product& pdt) {

		pdt.read(is);
		return is;

	}
	
	double operator+=(double& total, const Product& pdt) {

		return total + pdt.total_cost();

	}


}