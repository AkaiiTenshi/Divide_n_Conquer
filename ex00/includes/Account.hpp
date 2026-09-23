#pragma once

#include <iostream>

class Bank;

class Account
{
	friend class Bank;

	private:
		int _id;
		int _value;
		int _debt;

		explicit Account(int id);

		Account(const Account&);
		Account& operator=(const Account&);

		void setCredit(int amount);
		void setDebit(int amount);
		void addDebt(int amount);
		void reducDebt(int amount);

	public:
		const int& getId() const;
		const int& getValue() const;
		const int& getDebt() const;
	
	friend std::ostream& operator<<(std::ostream& os, const Account& account);
};
