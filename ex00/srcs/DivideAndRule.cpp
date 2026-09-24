#include <iostream>
#include <vector>
#include <stdexcept>
#include "../includes/Bank.hpp"

// Account methods
Bank::Account::Account(int id) : _id(-1), _value(0) , _debt(0) { }

Bank::Account::~Account(){}

const int& Bank::Account::getId() const {
	return(this->_id);
}
const int& Bank::Account::getValue() const {
	return(this->_value);
}
const int& Bank::Account::getDebt() const {
	return(this->_debt);
}

std::ostream& operator<<(std::ostream& os, Bank::Account& account){
	os <<"[" << account.getId() <<"] - [" << account.getValue() << "]" << " (debt: " << account.getDebt() << ")";
	return os;
}

// Bank methods
Bank::Bank(int initialLiquidity) : _liquidity(initialLiquidity), _nextId(0){
	if (initialLiquidity < 0)
		throw std::invalid_argument("Initial Liquidity cannot be negative");
}

Bank::~Bank() {
	for (AccountMap::iterator it = _accounts.begin(); it != _accounts.end(); ++it){
		delete it->second;
	}
}

void Bank::checkPositive(int amount) { 
	if (amount < 0)
		throw std::invalid_argument("Amount can't be negative");
}

Bank::Account& Bank::operator[](int id) {
	AccountMap::iterator it = _accounts.find(id);
	if (it == _accounts.end())
		throw std::out_of_range("No account with this ID");
	return *it->second;
}
const Bank::Account& Bank::operator[](int id) const {
	AccountMap::const_iterator it = _accounts.find(id);
	if (it == _accounts.end())
		throw std::out_of_range("No account with this ID");
	return *it->second;
}

const int& Bank::getLiquidity() const {
	return _liquidity;
}

int Bank::createAccount() {
	int id = _nextId++;
	_accounts[id] = new Account(id);
	return id;
}

void Bank::deleteAccount(int id) {
	Account& account = (*this)[id];
	if(account._debt > 0)
		throw std::runtime_error("Can't close an account in debt");
	delete &account;
	_accounts.erase(id);
}

void Bank::deposit(int id, int amount) {
	checkPositive(amount);
	Account& account = (*this)[id];
	int fee = amount * FEE_PERCENT / 100;
	_liquidity += fee;
	account._value += amount - fee;
}

void Bank::withdraw(int id, int amount) {
	checkPositive(amount);
	Account& account = (*this)[id];
	if(amount > account._value)
		throw std::runtime_error("Can't withdraw more money than what you have in your bank account");
	account._value -= amount;
}

void Bank::giveLoan(int id, int amount) {
	checkPositive(amount);
	if(amount > _liquidity)
		throw std::runtime_error("The bank's treasury doesn't have enough funds to give the loan");
	Account& account = (*this)[id];
	_liquidity -= amount;
	account._value += amount;
	account._debt += amount;
}

void Bank::repayLoan(int id, int amount) {
	checkPositive(amount);
	Account& account = (*this)[id];
	if(amount > account._debt)
		throw std::runtime_error("Can't repay more than current debt");
	if(amount > account._value)
		throw std::runtime_error("Insufficient funds to repay loan");
	_liquidity += amount;
	account._value -= amount;
	account._debt -= amount;
}
