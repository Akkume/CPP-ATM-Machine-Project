#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Account {
protected:
    long int account_No;
    string name;
    int PIN;
    double balance;
    string mobile_No;
    vector<string> transactionHistory;

public:
    Account(long int accNo, string accName, int pin, double bal, string mobNo)
        : account_No(accNo), name(accName), PIN(pin), balance(bal), mobile_No(mobNo) {}

    virtual void cashWithdraw(int amount_a) = 0;

    long int getAccountNo() const {
        return account_No;
    }

    string getName() const {
        return name;
    }

    int getPIN() const {
        return PIN;
    }

    double getBalance() const {
        return balance;
    }

    string getMobileNo() const {
        return mobile_No;
    }

    void setMobile(string mob_prev, string mob_new) {
        if (mob_prev == mobile_No) {
            mobile_No = mob_new;
            cout << endl << "Successfully Updated Mobile No.";
        } else {
            cout << endl << "Incorrect !!! Old Mobile No";
        }
    }

    void showTransactionHistory() const {
        cout << endl << "Transaction History:" << endl;
        for (const auto &transaction : transactionHistory) {
            cout << transaction << endl;
        }
    }

    void writeTransactionHistoryToFile() const {
        ofstream file(to_string(account_No) + "_transactions.txt", ios::app);
        if (file.is_open()) {
            for (const auto &transaction : transactionHistory) {
                file << transaction << endl;
            }
            file.close();
            cout << "Transaction history saved to file." << endl;
        } else {
            cout << "Unable to open file!" << endl;
        }
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(long int accNo, string accName, int pin, double bal, string mobNo)
        : Account(accNo, accName, pin, bal, mobNo) {}

    void cashWithdraw(int amount_a) override {
        if (amount_a > 0 && amount_a <= balance) {
            balance -= amount_a;
            cout << fixed << setprecision(2);
            cout << endl << "Please Collect Your Cash";
            cout << endl << "Available Balance: " << balance;
            transactionHistory.push_back("-" + to_string(amount_a));

            writeTransactionHistoryToFile(); // Writing transaction history to file
        } else {
            cout << endl << "Invalid Input or Insufficient Balance";
        }
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(long int accNo, string accName, int pin, double bal, string mobNo)
        : Account(accNo, accName, pin, bal, mobNo) {}

    void cashWithdraw(int amount_a) override {
        if (amount_a > 0 && amount_a <= balance) {
            balance -= amount_a;
            cout << fixed << setprecision(2);
            cout << endl << "Please Collect Your Cash";
            cout << endl << "Available Balance: " << balance;
            transactionHistory.push_back("-" + to_string(amount_a));

            writeTransactionHistoryToFile(); // Writing transaction history to file
        } else {
            cout << endl << "Invalid Input or Insufficient Balance";
        }
    }
};

int main() {
    // Creating objects for Savings and Checking accounts
    SavingsAccount savings(987654321, "Hardik", 1234, 50000, "9370054900");
    CheckingAccount checking(123456789, "Alice", 5678, 10000, "9876543210");

    long int enteredAccNo;
    int enteredPIN, withdrawalAmount;
    char accountType;

    cout << "Enter Account Type (S for Savings / C for Checking): ";
    cin >> accountType;

    cout << "Enter Account Number: ";
    cin >> enteredAccNo;

    cout << "Enter PIN: ";
    cin >> enteredPIN;

    if ((accountType == 'S' && enteredAccNo == savings.getAccountNo() && enteredPIN == savings.getPIN()) ||
        (accountType == 'C' && enteredAccNo == checking.getAccountNo() && enteredPIN == checking.getPIN())) {

        cout << "Enter Withdrawal Amount: ";
        cin >> withdrawalAmount;

        if (accountType == 'S') {
            savings.cashWithdraw(withdrawalAmount);
        } else {
            checking.cashWithdraw(withdrawalAmount);
        }
    } else {
        cout << "Invalid Account Number or PIN." << endl;
    }

    return 0;
}
