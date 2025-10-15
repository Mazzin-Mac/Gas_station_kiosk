#include <iostream>
#include <string>
using namespace std;

#include <ctime>
#include <vector>
#include <list>

struct {
	double regular = 1.63;
	double mid_grade = 1.75;
	double premium = 1.93;
	double diesel = 1.67;
} fuel_grade_prices;

class Fuel_bill {
	private:
		double fuel_total;
		double grade_price;
		double fuel_tax = 0.05;

		int member_number;
		time_t timestamp;

	public:
		Fuel_bill(double litres, double gas_price, int member_num) {
		/* Calculate sale total and create the bill */
			double sales_tax = (litres * gas_price) * fuel_tax;
			fuel_total = (litres * gas_price) + sales_tax;

			grade_price = gas_price;
			member_number = member_num;
			time(&timestamp);
		}

		double get_fuel_bill_total() { return fuel_total; }

		double get_fuel_bill_grade_price() { return grade_price; }

		int get_fuel_bill_member_number() { return member_number; }

		time_t get_fuel_bill_timestamp() { return timestamp; }
};

class Gas_pump {
	private:
		// global to track number of created pumps
		static int pump_count;

		/* Specific pump details */
		int pump_number;
		list<Fuel_bill> recent_bills;
		int recent_bills_max = 5;
		int recent_bills_count = 0;

	public:
		Gas_pump() {
			pump_count += 1;
			pump_number = pump_count;
		}

		static int get_pump_count() { return pump_count; }

		int get_gas_pump_number() { return pump_number; }

		list<Fuel_bill> get_recent_bill_list() { return recent_bills; }

		void add_recent_bill(Fuel_bill recent_bill) {
		/* Track the gas pumps recent bills in a list with a max length */
			if (recent_bills_max == recent_bills_count) {
				recent_bills.pop_back();
				recent_bills.push_front(recent_bill);
			} else {
				recent_bills.push_front(recent_bill);
				recent_bills_count += 1;
			}
		}

		void print_recent_bills() {
		/* Cannot iterate list with a standard for loop */
			for (Fuel_bill bill : recent_bills) {
				cout << bill.get_fuel_bill_member_number() << endl;
			}
		}

		Fuel_bill retrieve_bill_at(int index) {
		/* Find and retrieve bill, if not found chuck exception
			Exception should never occur as gui is intended use. */
			int position = 0;
			for (Fuel_bill bill: recent_bills) {
				if (position == index) {
					cout << bill.get_fuel_bill_member_number() << endl;
					return bill;
				}
				position++;
			}
			throw out_of_range("Index out of range");
		}
};

/* pump_count variable lives in global/static memory
	but must still belong to the Gas_pump class. */
int Gas_pump::pump_count = 0;

int main() {

	Gas_pump gas_pump1 = Gas_pump();
	Gas_pump gas_pump2 = Gas_pump();

	for (int i = 0; i < 20; i++) {
		Fuel_bill bill = Fuel_bill(10, fuel_grade_prices.regular, i);
		gas_pump1.add_recent_bill(bill);
	}


	return 0;
}

