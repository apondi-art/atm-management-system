# ATM Management System

## Project Overview

The objective of this project is to create a comprehensive ATM management system in C that simulates real-world banking operations, providing users with a robust and intuitive banking experience.

## Functionalities

### 1. User Authentication

**Registration**: New users can create an account by providing:

Unique username

Secure password

**Login**: Registered users can access the system's features after successful authentication.

### 2. Account Creation

After logging in, users can create a bank account with the following details:

Bank account number

Date of account creation

User's country

Initial deposit amount

Account type selection

### 3. Account Management

View Account Details

Explore accounts created under the user's ID

Check account types:

Fixed-term accounts

Savings accounts

Current accounts

View potential interest earnings for each account type

Update Account Information

Modify:

Country

Phone number

Account Listing

View all accounts owned by the user

### 4. Financial Transactions

Deposit Funds

Withdraw Money

Withdrawal restricted to available account balance

Prevents overdrawing

## System Requirements

Prerequisites

GCC Compiler

Make utility

SQLite3 development libraries

### Setup Instructions

**1. Clone the Repository**
```go
git clone "your-repository-url"
cd atm-management-system
```

**2. Prepare SQLite Installation Script**

```go
chmod +x install_sqlite.sh
./install_sqlite.sh
```

**3. Compile the Project**

```go
make
```

**4. Run the Application**
```go

./atm
```



## Data Storage

The ATM management system uses SQLite3 as its storage system instead of text files.

Users Table: Stores user authentication information

Schema: users(user_id INTEGER PRIMARY KEY, username TEXT UNIQUE, password TEXT)

Accounts Table: Stores detailed account records

Schema: accounts(account_id INTEGER PRIMARY KEY, user_id INTEGER, creation_date TEXT, country TEXT, phone TEXT, balance REAL, account_type TEXT, FOREIGN KEY(user_id) REFERENCES users(user_id))

Security Considerations

Unique username validation

Basic authentication mechanism

Limited account information modification

### Limitations

Fixed-term accounts have transaction restrictions

Only country and phone number can be updated

Simplified banking model implementation

### Contributing

### How to Contribute

Fork the repository

Create a feature branch

git checkout -b feature/your-feature-name

Commit your changes

git commit -m "Add specific feature"

Push to the branch

git push origin feature/your-feature-name

Open a Pull Request

### Contribution Guidelines

Follow existing code style

Write clear, well-documented code

Add unit tests for new features

Update documentation accordingly

### License

This project is licensed under the MIT License. See the LICENSE file for detailed information.

Support and Contact

For questions, issues, or suggestions, please open an issue in the GitHub repository.

Acknowledgments

SQLite Development Team

Open-source community contributors

