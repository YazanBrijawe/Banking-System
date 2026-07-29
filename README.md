# 🏦 Bank System Console Application (C++)

A simple yet functional banking system built from scratch in C++. This project lets you manage client accounts through a command-line interface—adding, updating, deleting, searching, and performing transactions like deposits and withdrawals. All data is stored in a plain text file (`Clients.txt`), so it’s lightweight and easy to back up or inspect.

---

🚨 **Note : Feel free to fork, modify, or use this as a learning resource!** 🛠️

---

## ✨ Features

- **📋 Main Menu**  
  - 👥 Show all clients (list view)  
  - ➕ Add new clients (with duplicate account number check)  
  - 🗑️ Delete an existing client (with confirmation)  
  - ✏️ Update client information (name, phone, PIN, balance)  
  - 🔍 Find a client by account number  
  - 💰 Enter the Transactions sub‑menu  

- **💳 Transactions Menu**  
  - 💵 Deposit money to an account (validates existence)  
  - 💸 Withdraw money (prevents overdraft)  
  - 📊 View total balances of all clients (summed at the bottom)  

- **💾 Data Persistence**  
  - Reads from and writes to `Clients.txt` using a custom delimiter (`#//#`)  
  - 🏷️ Mark‑for‑delete technique (records are not physically removed until save)  

- **🖥️ Clean Console Output**  
  - Formatted tables with `iomanip` for readable client lists  

---

## 🛠️ How to Compile & Run

1. Save the source code as `Bank_System.cpp`.  
2. Compile with any C++ compiler (e.g., g++):  
   ```bash
