# Customer Service Management Module (C++)

This is a command-line based **Customer Service System** developed in C++. It simulates user account management and complaint handling through efficient data structures such as hash maps, priority queues, and linked lists. It is designed to provide fast operations for searching, grouping, and managing customer records and service complaints.

---

## Features

- **User Management:**
  - Add and remove users
  - Search users by ID, name, email, country, or customer type
  - Group users by country or customer type

- **Complaint Handling:**
  - Register complaints with automatic priority assignment based on user type
  - Service the highest priority complaint using a max heap
  - Increase complaint priority dynamically (e.g., upgrading a user to platinum)
  - View complaints by user or by country

- **Data Indexing:**
  - Custom hash maps and group hash maps for fast lookup
  - Linear probing, quadratic probing, and double hashing for collision resolution

---

## Technologies Used

- Language: C++
- STL: `<list>`, `<string>`, `<cstdlib>`, `<ctime>`
- Concepts: Hashing, Linked Lists, Custom Comparators, Priority Queue (Heap), Operator Overloading

---

## Program Structure
- User Class
Represents a customer with fields like ID, name, email, country, and user type (e.g., gold, silver).

- Complaint Class
Represents a user complaint with a unique ID, type, description, and country. Priority is assigned based on user type.

- HashMap, HashMap2, GroupHashMap Classes
Used for indexing users and complaints by various attributes such as ID, name, country, or type.

- UserList Class
Manages the complete user directory and coordinates indexing using hash maps.

- PriorityQueue Class
Maintains and services complaints based on priority using heap operations.

- Demonstrated Use Cases
The main() function includes detailed demonstrations of the following:

-> Inserting and Displaying Users<br>
-> Searching by ID, Name, Email<br>
-> Deleting Users and Verifying Deletion<br>
-> Displaying and Deleting Grouped Users (By Country / Type)<br>
-> Registering Multiple Complaints<br>
-> Displaying and Servicing Complaints<br>
-> Increasing Complaint Priority<br>
-> Displaying Complaints by Country or User<br>

Each operation is accompanied by output messages to demonstrate system behavior.

## Example Commands Used Internally
-> Insert(User)<br>
-> Search(id / name / email / country / type)<br>
-> Delete(id / name / email / country / type)<br>
-> RegisterComplaint(Complaint)<br>
-> ServiceComplaint()<br>
-> IncreasePriority(Complaint*)<br>

## License
This project is for academic and personal educational use only. Not for commercial distribution without permission.

## Author
Lumia Noman Qureshi<br>
BSCS – Computer Science Student<br>
FAST NUCES LHR<br>
