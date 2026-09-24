#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>


class Bank
{
	public:
		class Account
		{
			friend class Bank;

			private:
			int _id;
			int _value;
			int _debt;

			explicit Account(int id);
			~Account();

			Account(const Account&);
			Account& operator=(const Account&);

			public:
			const int& getId() const;
			const int& getValue() const;
			const int& getDebt() const;

			friend std::ostream& operator<<(std::ostream& os, const Account& account);
		};
	private:
		typedef std::map<int, Account*> AccountMap;

		int _liquidity;
		int _nextId;
		AccountMap _accounts;

		static const int FEE_PERCENT = 5;

		Bank(const Bank&);
		Bank& operator=(const Bank&);

		static void checkPositive(int amount);

	public:
		explicit Bank(int initialLiquidity = 0);
		~Bank();

		Account& operator[](int id);
		const Account& operator[](int id) const;

		const int& getLiquidity() const;

		int createAccount();
		void deleteAccount(int id);

		void deposit(int id, int amount);
		void withdraw(int id, int amount);
		
		void giveLoan(int id, int amount);
		void repayLoan(int id, int amount);


		friend std::ostream& operator<<(std::ostream& os, const Bank& bank);
};


