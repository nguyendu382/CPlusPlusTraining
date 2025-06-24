#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class BankAccount {
	string accountNumber;
	double balance;
public:
	BankAccount(const string& accNum, double initialBalance) 
		: accountNumber(accNum), balance(initialBalance) {}
	void deposit(double amount) {
		if (amount > 0) {
			this->balance += amount;
			cout << "Deposited: " << amount << ", New Balance: " << this->balance << endl;
		} else {
			cout << "Deposit amount must be positive." << endl;
		}
	}
	void withdraw(double amount) {
		if (amount > 0 && amount <= this->balance) {
			this->balance -= amount;
			cout << "Withdrew: " << amount << ", New Balance: " << this->balance << endl;
		} else {
			cout << "Invalid withdrawal amount." << endl;
		}
	}
	void printStatement() const {
		cout << "Account Number: " << this->accountNumber << ", Balance: " << this->balance << endl;
	}
	friend void transfer(BankAccount& from, BankAccount& to, double amount) {
		if (amount > 0 && amount <= from.balance) {
			from.withdraw(amount);
			to.deposit(amount);
			cout << "Transferred " << amount << " from " << from.accountNumber 
				 << " to " << to.accountNumber << endl;
		} else {
			cout << "Transfer failed: Invalid amount." << endl;
		}
	}
};

int main() {
	vector<unique_ptr<BankAccount>> accounts;
	accounts.push_back(make_unique<BankAccount>("123", 100));
	accounts.push_back(make_unique<BankAccount>("456", 200));
	accounts.push_back(make_unique<BankAccount>("789", 300));
	for (const auto& acc : accounts) {
		acc->printStatement();
	}
	accounts[0]->deposit(50);
	accounts[1]->withdraw(30);
	transfer(*accounts[2], *accounts[1], 100);
	cout << "After transactions:" << endl;
	for (const auto& acc : accounts) {
		acc->printStatement();
	}
	return 0;
}