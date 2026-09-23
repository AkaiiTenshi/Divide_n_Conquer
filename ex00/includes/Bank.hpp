#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "../includes/Account.hpp"


class Bank
{
	private:
		typedef std::map<int, Account*> AccountMap;

		int _liquidity;
		int _nextId;
		AccountMap _accounts;

		static const int FEE_PERCENT = 5;

		Bank(const Bank&);
		Bank& operator=(const Bank&);

		Account& findAccount(int id);
		static void checkPositive(int amount);

	public:
		explicit Bank(int initialLiquidity = 0);
		~Bank() = default;

		const int& getLiquidity() const;
		const Account& getAccount(int id) const;

		int createAccount();
		void deleteAccount(int id);

		void deposit(int id, int amount);
		void withdraw(int id, int amount);
		
		void giveLoan(int id, int amount);
		void repayLoan(int id, int amount);

		friend std::ostream& operator<<(std::ostream& os, const Bank& bank);
};
