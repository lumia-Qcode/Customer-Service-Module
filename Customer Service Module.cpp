#include<iostream>
#include<string>
#include<list>
#include<cstdlib>
#include<ctime>
using namespace std;


//------------------------------USER CLASS---------------------------------
class User {
private:
	int Id;
	string name;
	string email;
	string country;
	string type;
public:
	User(int id, string n = "", string mail = "", string c = "", string t = "regular") : Id(id), name(n), email(mail), country(c), type(t) {}

	int GetId() {
		return Id;
	}

	void PrintUser() {
		cout << "\nUser ID:\t" << Id;
		cout << "\nUser Name:\t" << name;
		cout << "\nEmail:\t" << email;
		cout << "\nCountry:\t" << country;
		cout << "\nUser Type:\t" << type;
		cout << "\n--------------------------------";
	}

	string GetName() {
		return name;
	}

	string GetEmail() {
		return email;
	}

	string GetCountry() {
		return country;
	}

	string GetType() {
		return type;
	}

	bool operator<(const User& other) const {
		return Id < other.Id;
	}

	 static bool isEqual(const User* obj, int id)  {
		return obj->Id == id;
	 }

};

class HashMap
{
private:
	struct HashItem {
		int key;
		int status;		// 0 for empty, 1 for deleted, 2 for occupied
		User* userPtr;
	};
	HashItem* hashArray;
	int tableSize;
	int a;
	int b;
	int p;

	int findPrime(int num) {
		for (int i = num - 1; i >= 2; --i) {
			if (isPrime(i)) {
				return i;
			}
		}
		return 2;
	}

	bool isPrime(int num) {
		if (num < 2) {
			return false;
		}
		for (int i = 2; i * i <= num; ++i) {
			if (num % i == 0) {
				return false;
			}
		}
		return true;
	}

	int doubleHashing(int k, int i) {
		int h1 = universalHashFunction(k);
		int h2 = p - (k % p);
		return h1 + (h2 * i) % tableSize;
	}

	int universalHashFunction(int k) {
		return ((a * k + b) % p) % tableSize;
	}

public:
	HashMap(int size = 10) : tableSize(size) {
		hashArray = new HashItem[tableSize];

		for (int i = 0; i < tableSize; ++i) {
			hashArray[i].status = 0;
			hashArray[i].key = -1;
		}
		srand(time(0));
		p = findPrime(tableSize);
		a = rand() % (p - 1) + 1;    // 1 <= a < p
		b = rand() % p;              // 0 <= b < p
	}

	void insert(int const k, User* ptr) {
		// a) calculating index
		int probe = 1;
		int index = universalHashFunction(k);

		// b) insertion and collision detection
		for (int i = 0; (hashArray[index].key != k) && (hashArray[index].status == 2); i++) {
			probe++;
			index = doubleHashing(k, probe);
		}

		hashArray[index].key = k;
		hashArray[index].status = 2;
		hashArray[index].userPtr = ptr;

	}

	void deleteKey(int const k) {
		int probe = 1;
		int index = universalHashFunction(k);
		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				hashArray[index].status = 1;
				cout << "User with id " << k << " deleted from Hash Index\n";
				return;
			}
			probe++;
			index = doubleHashing(k, probe);
		}
		cout << "User with id " << k << " not found\n";
	}

	User* Search(int const k) {
		int probe = 1;
		int index = universalHashFunction(k);
		for (int i = 0; hashArray[index].status != 0; i++) {
			if ((hashArray[index].key == k) && (hashArray[index].status == 2)) {
				return hashArray[index].userPtr;
			}
			probe++;
			index = doubleHashing(k, probe);
		}
		return nullptr;
	}

	~HashMap() {
		//delete[] hashArray;
	}
};

template<class T>
class HashMap2 {
private:
	struct HashItem2 {
		string key;
		T* userPtr;
		int status; // 0 for empty, 1 for deleted, 2 for occupied

		HashItem2() : key(""), userPtr(nullptr), status(0) {}
	};

	list<HashItem2>* hashArray;
	int tableSize;

	unsigned int hash(const string& key, int size) {
		unsigned int hashVal = 0;
		for (char ch : key)
			hashVal = 37 * hashVal + ch;
		return hashVal % size;
	}

public:

	HashMap2(int size) : tableSize(size) {
		hashArray = new list<HashItem2>[tableSize];
	}

	void insert(const string& k, T* ptr) {
		int index = hash(k, tableSize);
		list<HashItem2>& bucket = hashArray[index];

		for (typename list<HashItem2>::iterator itr = bucket.begin(); itr != bucket.end(); ++itr) {
			if (itr->key == k && itr->status == 2) {
				itr->userPtr = ptr;
				itr->status = 2;
				itr->key = k;
				return;
			}
		}

		HashItem2 newItem;
		newItem.key = k;
		newItem.userPtr = ptr;
		newItem.status = 2;
		bucket.push_front(newItem);
	}


	T* Search(string k) {
		int index = hash(k, tableSize);
		list<HashItem2>& bucket = hashArray[index];

		for (typename list<HashItem2>::iterator itr = bucket.begin(); itr != bucket.end(); ++itr) {
			if (itr->key == k && itr->status == 2) {
				return itr->userPtr;
			}
		}

		return nullptr;
	}

	void deleteKey(string k) {
		int index = hash(k, tableSize);
		list<HashItem2>& bucket = hashArray[index];

		for (typename list<HashItem2>::iterator itr = bucket.begin(); itr != bucket.end(); ++itr) {
			if (itr->key == k && itr->status == 2) {
				itr->status = 1;
				cout << "User " << k << " deleted from HashMap.\n";
				return;
			}
		}

		cout << "User " << k << " not found in Hash Map.\n";
	}


	~HashMap2() {
		// delete[] hashArray;  // Free the array of lists
	}
};


class Complaint {
private:
	int complaintId;
	int userId;
	string userType;
	string complaint;
	string country;
public:
	Complaint() :complaintId(0), userId(0), userType(""), complaint(""), country("") {}
	Complaint(int c, int user, string type, string description, string cy) :complaintId(c), userId(user), userType(type), complaint(description), country(cy) {}

	bool operator<(const Complaint& rhs) const {
		int lhsPriority = 0;
		int rhsPriority = 0;

		if (userType == "platinum") {
			lhsPriority = 1;
		}
		else if (userType == "gold") {
			lhsPriority = 2;
		}
		else if (userType == "silver") {
			lhsPriority = 3;
		}
		else if (userType == "new") {
			lhsPriority = 4;
		}
		else if (userType == "regular") {
			lhsPriority = 5;
		}

		if (rhs.userType == "platinum") {
			rhsPriority = 1;
		}
		else if (rhs.userType == "gold") {
			rhsPriority = 2;
		}
		else if (rhs.userType == "silver") {
			rhsPriority = 3;
		}
		else if (rhs.userType == "new") {
			rhsPriority = 4;
		}
		else if (rhs.userType == "regular") {
			rhsPriority = 5;
		}

		if (lhsPriority == rhsPriority) {
			return complaintId > rhs.complaintId;
		}
		return lhsPriority > rhsPriority;
	}

	bool operator==(const Complaint& rhs)const {
		return this->userType == rhs.userType;
	}

	string GetUserType() {
		return userType;
	}

	void SetUserType(string type) {
		userType = type;
	}

	int GetUserID() {
		return userId;
	}

	string GetCountry() {
		return country;
	}

	void DisplayComplaint() {
		cout << "Complaint ID:\t" << complaintId;
		cout << "\nUser ID:\t" << userId;
		cout << "\nUser Type:\t" << userType;
		cout << "\nCountry:\t" << country;
		cout << "\nIssue:\t" << complaint;
		cout << "\n--------------------------------\n";
	}

	void DisplayUserComplaint() {
		cout << "Complaint ID: " << complaintId;
		cout << "\n\tComplaint Descriptions: " << complaint;
		cout << "\n\t-------------------------------------------------\n";
	}

	void DisplayByCountry() {
		cout << "Complaint ID:\t" << complaintId;
		cout << "\n\tUser ID:\t" << userId;
		cout << "\n\tUser Type:\t" << userType;
		cout << "\n\tIssue:\t" << complaint;
		cout << "\n\t--------------------------------\n";
	}

	static bool isEqual(const Complaint* obj1, const Complaint* obj2) {
		if (obj1->complaintId == obj2->complaintId && obj1->userId == obj2->userId && obj1->userType == obj2->userType && obj1->complaint == obj2->complaint && obj1->country == obj2->country) {
			return true;
		}
		return false;
	}
};


template<class T, typename d>
class GroupHashMap {
private:
	struct HashItem3 {
		d key;
		list<T*> users;
		int status;		// 0 for empty, 1 for deleted, 2 for occupied

		HashItem3() : key(d()), status(0) {}
	};

	HashItem3* hashArray;
	int tableSize;
	int a, b, p;

	unsigned int hash(const string& key, int size) {
		unsigned int hashVal = 0;
		for (char ch : key)
			hashVal = 37 * hashVal + ch;
		return hashVal % size;
	}

	int linearProbing(int index, int i) {
		return (index + i) % tableSize;
	}

	int quadraticProbing(int index, int i) {
		return (index + i * i) % tableSize;
	}

	int findPrime(int num) {
		for (int i = num - 1; i >= 2; --i) {
			if (isPrime(i)) {
				return i;
			}
		}
		return 2;
	}

	bool isPrime(int num) {
		if (num < 2) {
			return false;
		}
		for (int i = 2; i * i <= num; ++i) {
			if (num % i == 0) {
				return false;
			}
		}
		return true;
	}

	int doubleHashing(int k, int i) {
		int h1 = universalHashFunction(k);
		int h2 = p - (k % p);
		return h1 + (h2 * i) % tableSize;
	}

	int universalHashFunction(int k) {
		return ((a * k + b) % p) % tableSize;
	}


public:
	GroupHashMap(int size) :tableSize(size) {
		hashArray = new HashItem3[tableSize];

		for (int i = 0; i < tableSize; i++) {
			hashArray[i].status = 0;
		}

		srand(time(0));
		p = findPrime(tableSize);
		a = rand() % (p - 1) + 1;    // 1 <= a < p
		b = rand() % p;              // 0 <= b < p
	}

	void insertCountry(string k, T* ptr) {
		int probe = 1;
		int index = hash(k, tableSize);

		for (int i = 0; hashArray[index].key != k && hashArray[index].status == 2; i++) {
			probe++;
			index = linearProbing(index, probe);
		}

		if (hashArray[index].status != 2) {
			hashArray[index].key = k;
			hashArray[index].status = 2;
		}

		hashArray[index].users.push_front(ptr);
	}

	void insertType(string k, T* ptr) {
		int probe = 1;
		int index = hash(k, tableSize);

		for (int i = 0; hashArray[index].key != k && hashArray[index].status == 2; i++) {
			probe++;
			index = quadraticProbing(index, probe);
		}

		if (hashArray[index].status != 2) {
			hashArray[index].key = k;
			hashArray[index].status = 2;
		}

		hashArray[index].users.push_front(ptr);
	}

	void insertId(int k, T* ptr) {
		int probe = 1;
		int index = universalHashFunction(k);

		// b) insertion and collision detection
		for (int i = 0; (hashArray[index].key != k) && (hashArray[index].status == 2); i++) {
			probe++;
			index = doubleHashing(k, probe);
		}

		if (hashArray[index].status != 2) {
			hashArray[index].key = k;
			hashArray[index].status = 2;
		}
		hashArray[index].users.push_back(ptr);

	}

	void ListUsersOfCountry(string k) {
		int probe = 1;
		int index = hash(k, tableSize);

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				for (typename list<T*>::iterator itr = hashArray[index].users.begin(); itr != hashArray[index].users.end(); ++itr) {
					User* u = *itr;
					u->PrintUser();
				}
				return;
			}
			probe++;
			index = linearProbing(index, probe);
		}
		cout << "Users for country " << k << " not found\n";
	}

	void ListUsersOfType(string k) {
		int probe = 1;
		int index = hash(k, tableSize);
		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				for (typename list<T*>::iterator itr = hashArray[index].users.begin(); itr != hashArray[index].users.end(); ++itr) {
					User* u = *itr;
					u->PrintUser();
				}
				return;
			}
			probe++;
			index = quadraticProbing(index, probe);
		}
		cout << "Users for Type " << k << " not found\n";
	}

	void ListComplaintsOfUserId(int k) {
		int probe = 1;
		int index = universalHashFunction(k);
		int count = 1;

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {	// As some complaints maybe deleted and their status is 1
				for (typename list<T*>::iterator itr = hashArray[index].users.begin(); itr != hashArray[index].users.end(); ++itr) {
					cout << "\n" << count << ")\t";
					Complaint* c = *itr;
					c->DisplayUserComplaint();
					count++;
				}
				return;
			}
			probe++;
			index = doubleHashing(k, probe);
		}
		cout << "No complaints found in record\n";
	}

	void ListComplaintsOfCountry(string k) {
		int probe = 1;
		int index = hash(k, tableSize);
		int count = 1;

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {	// As some complaints maybe deleted and their status is 1
				for (typename list<T*>::iterator itr = hashArray[index].users.begin(); itr != hashArray[index].users.end(); ++itr) {
					cout << "\n" << count << ")\t";
					Complaint* c = *itr;
					c->DisplayByCountry();
					count++;
				}
				return;
			}
			probe++;
			index = linearProbing(index, probe);
		}
		cout << "No complaints found in record\n";
	}

	void displayIndices() {
		for (int i = 0; i < tableSize; i++) {
			cout << "\nIndex " << i << ":\t";
			if (hashArray[i].status == 0) {
				cout << "Empty";
			}
			else if (hashArray[i].status == 1) {
				cout << "Deleted";
			}
			else {
				cout << "Ocupied (" << hashArray[i].key << ")";
			}
		}
	}

	void deleteCountry(string k) {
		int probe = 1;
		int index = hash(k, tableSize);

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				hashArray[index].status = 1;
				cout << "Deleted Country index for " << k << endl;
				return;
			}
			probe++;
			index = linearProbing(index, probe);
		}
		cout << "Country " << k << " not found in HashMap\n";
	}

	void deleteType(string k) {
		int probe = 1;
		int index = hash(k, tableSize);

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				hashArray[index].status = 1;
				cout << "Deleted Type index for " << k << endl;
				return;
			}
			probe++;
			index = quadraticProbing(index, probe);
		}
		cout << "Type " << k << " not found in HashMap\n";
	}

	void deleteCountryComplaint(string k, T* ptr) {
		int probe = 1;
		int index = hash(k, tableSize);

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				for (typename list<T*>::iterator itr = hashArray[index].users.begin(); itr != hashArray[index].users.end(); ++itr) {
					if (Complaint::isEqual(*itr, ptr)) {
						hashArray[index].users.erase(itr);
						cout << "Complaint removed from HashMap\n";
						return;
					}
				}
			}
			probe++;
			index = linearProbing(index, probe);
		}
		cout << "Complaint not found in HashMap\n";
	}

	void deleteIdComplaint(int k, Complaint* ptr) {
		int probe = 1;
		int index = universalHashFunction(k);

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				for (typename list<Complaint*>::iterator itr = hashArray[index].users.begin(); itr != hashArray[index].users.end(); ++itr) {
					if (Complaint::isEqual(*itr, ptr)) {
						hashArray[index].users.erase(itr);
						cout << "Complaint removed from HashMap\n";
						return;
					}
				}
			}
			probe++;
			index = doubleHashing(k, probe);
		}
		cout << "Complaint not found in HashMap\n";
	}

	void deleteCountryUserId(string k, int id) {
		int probe = 1;
		int index = hash(k, tableSize);

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				for (typename list<User*>::iterator itr = hashArray[index].users.begin(); itr != hashArray[index].users.end(); ++itr) {
					if (User::isEqual(*itr, id)) {
						hashArray[index].users.erase(itr);
						cout << "Country " << k <<" removed from HashMap\n";
						return;
					}
				}
			}
			probe++;
			index = linearProbing(index, probe);
		}
		cout << "Country " << k << " not found in HashMap\n";
	}

	void deleteTypeUserId(string k, int id) {
		int probe = 1;
		int index = hash(k, tableSize);

		for (int i = 0; hashArray[index].status != 0; i++) {
			if (hashArray[index].key == k && hashArray[index].status == 2) {
				for (typename list<User*>::iterator itr = hashArray[index].users.begin(); itr != hashArray[index].users.end(); ++itr) {
					if (User::isEqual(*itr, id)) {
						hashArray[index].users.erase(itr);
						cout << "Type " << k << " removed from HashMap\n";
						return;
					}
				}
			}
			probe++;
			index = quadraticProbing(index, probe);
		}
		cout << "Type " << k << " not found in HashMap\n";
	}

	~GroupHashMap() {

	}

};

class UserList {
private:
	list<User> userList;
	HashMap idIndex;
	HashMap2<User> nameIndex;
	HashMap2<User> emailIndex;
	GroupHashMap<User, string> countryIndex;
	GroupHashMap<User, string> typeIndex;

public:
	UserList(int size) : idIndex(size), nameIndex(size), emailIndex(size), countryIndex(size), typeIndex(size) {}

	void Insert(User& u) {
		userList.push_back(u);
		userList.sort();
		idIndex.insert(u.GetId(), &u);
		nameIndex.insert(u.GetName(), &u);
		emailIndex.insert(u.GetEmail(), &u);
		countryIndex.insertCountry(u.GetCountry(), &u);
		typeIndex.insertType(u.GetType(), &u);
	}

	void Search(int id) {
		User* u = idIndex.Search(id);
		if (u) {
			u->PrintUser();
		}
		else {
			cout << "\nUser with id " << id << " not found\n";
		}
	}

	void SearchName(string name) {
		User* u = nameIndex.Search(name);
		if (u) {
			u->PrintUser();
		}
		else {
			cout << "\nUser with name " << name << " not found in HashMap\n";
			for (list<User>::iterator itr = userList.begin(); itr != userList.end(); ++itr) {
				if (itr->GetName() == name) {
					cout << "User found in list\n";
					itr->PrintUser();
					return;
				}
			}
			cout << "User with name " << name << " not found in list\n";
		}
	}

	void SearchEmail(string email) {
		User* u = emailIndex.Search(email);
		if (u) {
			u->PrintUser();
		}
		else {
			cout << "\nUser with email " << email << " not found in HashMap\n";
			for (list<User>::iterator itr = userList.begin(); itr != userList.end(); ++itr) {
				if (itr->GetEmail() == email) {
					cout << "User found in list\n";
					itr->PrintUser();
					return;
				}
			}
			cout << "User with email " << email << " not found in list\n";
		}
	}

	void SearchCountry(string country) {
		countryIndex.ListUsersOfCountry(country);
	}

	void SearchType(string type) {
		typeIndex.ListUsersOfType(type);
	}

	void Delete(int id) {
		idIndex.deleteKey(id); // Delete from the hash table
		for (list<User>::iterator itr = userList.begin(); itr != userList.end(); ++itr) {
			if (itr->GetId() == id) {
				nameIndex.deleteKey(itr->GetName());
				emailIndex.deleteKey(itr->GetEmail());
				countryIndex.deleteCountryUserId(itr->GetCountry(), id);
				typeIndex.deleteTypeUserId(itr->GetType(), id);
				userList.erase(itr);
				cout << "User with ID " << id << " deleted from the list.\n";
				return;
			}
		}
		cout << "User with ID " << id << " not found in the list.\n";
	}

	void DeleteName(string name) {
		nameIndex.deleteKey(name);
	}

	void DeleteEmail(string email) {
		emailIndex.deleteKey(email);
	}

	void DeleteCountry(string country) {
		countryIndex.deleteCountry(country);
	}

	void DeleteType(string type) {
		typeIndex.deleteType(type);
	}

	// Print all users
	void printAllUsers() {
		for (list<User>::iterator itr = userList.begin(); itr != userList.end(); ++itr) {
			itr->PrintUser();
		}
	}

	void DisplayCountries() {
		countryIndex.displayIndices();
	}

	void DisplayTypes() {
		typeIndex.displayIndices();
	}
};

class PriorityQueue {
private:
	Complaint* arr;		// heap as array
	int capacity;		// maximum capacity
	int size;			// current size
	GroupHashMap<Complaint, int> idIndex;
	GroupHashMap<Complaint, string> countryIndex;

	void ReheapUp(int root, int last) {
		int parent;
		if (last > root) {
			parent = (last - 1) / 2;
			if (arr[parent] < arr[last]) {
				swap(arr[last], arr[parent]);
				ReheapUp(root, parent);
			}
		}
	}

	void ReheapDown(int cnode, int last) {
		int maxChild, rightChild, leftChild;
		leftChild = 2 * cnode + 1;
		rightChild = 2 * cnode + 2;
		if (leftChild <= last) { // left child is part of the heap

			if (leftChild == last) { // only one child
				maxChild = leftChild;
			}

			else {
				if (arr[leftChild] < arr[rightChild]) {
					maxChild = rightChild;
				}

				else if (arr[leftChild] == arr[rightChild]) {
					maxChild = rightChild;
				}

				else {
					maxChild = leftChild;
				}

			}
			if (arr[cnode] < arr[maxChild]) {
				swap(arr[cnode], arr[maxChild]);
				ReheapDown(maxChild, last);
			}
		}
	}

public:
	PriorityQueue(int c = 100) : capacity(c), size(0), idIndex(c), countryIndex(c) {
		arr = new Complaint[capacity];
	}

	bool isEmpty() {
		return size == 0;
	}

	bool isFull() {
		return size == capacity;
	}

	void RegisterComplaint(Complaint& c) {
		if (isFull()) {
			cout << "\nQueue is full.....Try again later!\n";
		}
		else {
			arr[size] = c;
			idIndex.insertId(c.GetUserID(), &c);
			countryIndex.insertCountry(c.GetCountry(), &c);
			size++;
			ReheapUp(0, size - 1);
		}
	}

	Complaint ServiceComplaint() {
		if (isEmpty()) {
			cout << "\nQueue is empty.....No complaint to extract!\n";
		}
		Complaint temp = arr[0];
		arr[0] = arr[size - 1];
		size--;
		Complaint* tempPtr = &temp;
		idIndex.deleteIdComplaint(temp.GetUserID(), tempPtr);
		countryIndex.deleteCountryComplaint(temp.GetCountry(), tempPtr);
		ReheapDown(0, size - 1);
		return temp;
	}

	void IncreasePriority(Complaint* ptr) {
		int pos = -1;
		for (int i = 0; i < size; i++) {
			if (arr[i].GetUserID() == ptr->GetUserID()) {
				pos = i;
				arr[i].SetUserType("platinum");
				break;
			}
		}

		if (pos != -1) {
			ReheapUp(0, pos);
		}
	}

	void DisplayComplaintsByUser(int id) {
		cout << "Complaints by User " << id << " are listed below:\n";
		idIndex.ListComplaintsOfUserId(id);
	}

	void DisplayAllComplaints() {
		for (int i = 0; i < size; i++) {
			arr[i].DisplayComplaint();
			cout << "\n";
		}
	}

	void DisplayComplaintsByCountry(string c) {
		cout << "Complaints of country " << c << " are listed below:\n";
		countryIndex.ListComplaintsOfCountry(c);
	}

	~PriorityQueue() {
		if (arr) {
			delete[] arr;
		}
	}
};



int main() {
	User u1(23, "Sarah", "sara@gmail.com", "Pakistan", "gold");
	User u2(40, "Maha", "crimepatner@hotmail.com", "USA", "premium");
	User u3(12, "Alizeh", "liz@nugget.com", "USA", "gold");
	User u4(30, "Ahmad", "ahmed@joyaa.com", "India", "silver");
	User u5(33, "Sahar", "sehar@gmail.com", "Pakistan", "regular");
	User u6(56, "Joy", "imurjoy@yahoo.com", "Korea", "gold");
	User u7(3, "Esha", "propoanda@yahoo.com", "Kenya", "silver");

	UserList list(15);
	list.Insert(u2);
	list.Insert(u5);
	list.Insert(u3);
	list.Insert(u1);
	list.Insert(u6);
	list.Insert(u4);
	list.Insert(u7);
	cout << "-------------------------------------------------------\n";
	cout << "\t\t******SAMPLE 01*****\n";
	cout << "-------------------------------------------------------\n";
	list.printAllUsers();
	cout << endl;

	cout << "\n***Searching User with ID 12:\n";
	list.Search(12);
	cout << "\n***Deleting User with ID 12:\n";
	list.Delete(12);
	cout << "\n***Searching User with ID 12 after deletion:";
	list.Search(12);
	cout << "\n***Searching User with ID 55 ( Such ID was never inserted):";
	list.Search(55);

	cout << "-------------------------------------------------------\n";
	cout << "\t\t*****SAMPLE 02*****\n";
	cout << "-------------------------------------------------------\n";

	cout << "\n***Searching User with Name Joy:\n";
	list.SearchName("Joy");
	cout << "\n***Deleting User with Name Joy:\n";
	list.DeleteName("Joy");
	cout << "\n***Searching User with Name Joy after deletion:";
	list.SearchName("Joy");
	cout << "\n***Searching User with Name Trevor (Such Name was never inserted):";
	list.SearchName("Trevor");

	cout << "\n***Searching User with Email ahmed@joyaa.com:\n";
	list.SearchEmail("ahmed@joyaa.com");
	cout << "\n***Deleting User with Email ahmed@joyaa.com:\n";
	list.DeleteEmail("ahmed@joyaa.com");
	cout << "\n***Searching User with Email ahmed@joyaa.com after deletion:\n";
	list.SearchEmail("ahmed@joyaa.com");
	cout << "\n***Searching User with Email liz@nugget.com after its deletion by ID:";
	list.SearchEmail("liz@nugget.com");
	cout << "\n***Searching User with Email fatima@gmail.com (Such Email was never inserted):\n";
	list.SearchEmail("fatima@gmail.com");
	cout << endl;

	cout << "-------------------------------------------------------\n";
	cout << "\t\t*****SAMPLE 03*****\n";
	cout << "-------------------------------------------------------\n";

	cout << "***Displaying Group Index Of Country:";
	list.DisplayCountries();

	cout << "\n\n***Listing Users for Country Pakistan:";
	list.SearchCountry("Pakistan");
	cout << "\n\n***Deleting Users for Country Pakistan:\n";
	list.DeleteCountry("Pakistan");
	cout << "\n***Listing Users for Country Pakistan again after deletion:\n";
	list.SearchCountry("Pakistan");


	cout << endl << endl;
	cout << "***Listing Users for Country USA:";
	list.SearchCountry("USA");
	cout << "\n\n***Deleting Users for Country USA:\n";
	list.DeleteCountry("USA");
	cout << "\n***Listing Users for Country USA again after deletion:\n";
	list.SearchCountry("USA");

	cout << "\n***Now Displaying Group Index Of Country after deletions performed:";
	list.DisplayCountries();

	cout << endl << endl;
	cout << "\n***Displaying Group Index Of Type:";
	list.DisplayTypes();

	cout << endl << endl;
	cout << "***Listing Users of Type gold:";
	list.SearchType("gold");
	cout << "\n***Deleting Users of Type gold:\n";
	list.DeleteType("gold");
	cout << "\n***Listing Users of Type gold again after deletion:\n";
	list.SearchType("gold");

	cout << "\n***Now Displaying Group Index Of Types after deletions performed:";
	list.DisplayTypes();

	cout << endl << endl;
	cout << "-------------------------------------------------------\n";
	cout << "\t\t*****SAMPLE 04*****\n";
	cout << "-------------------------------------------------------\n";

	Complaint c1(1, 23, "gold", "Webpage is down", "Pakistan");
	Complaint c2(2, 30, "silver", "Drop-down menu not working", "India");
	Complaint c3(3, 23, "gold", "Website glitching", "Pakistan");
	Complaint c4(4, 40, "platinum", "More than 5 items cannot be added to cart", "USA");
	Complaint c5(5, 3, "silver", "Website not made for mobile-view", "Pakistan");
	Complaint c6(6, 40, "platinum", "Bugs reported", "USA");
	Complaint c7(7, 23, "gold", "Buttons not working", "Pakistan");
	Complaint c8(8, 56, "gold", "Font-size too small", "Korea");
	Complaint c9(9, 33, "regular", "Scroll Bar not sliding properly", "Japan");

	PriorityQueue p(20);
	p.RegisterComplaint(c1);
	p.RegisterComplaint(c2);
	p.RegisterComplaint(c3);
	p.RegisterComplaint(c4);
	p.RegisterComplaint(c5);
	p.RegisterComplaint(c6);
	p.RegisterComplaint(c7);
	p.RegisterComplaint(c8);
	p.RegisterComplaint(c9);

	cout << "\n***Displaying all Complaints Reported:\n";
	p.DisplayAllComplaints();

	cout << "\n***Displaying all Complaints by UserId 23:\n";
	p.DisplayComplaintsByUser(23);

	cout << "\n***After Servicing Highest Priority Complaint:\n";
	p.ServiceComplaint();
	cout << endl;
	p.DisplayAllComplaints();

	cout << "\n***Displaying all Complaints of UserId 40 after servcing their complaint:\n";
	p.DisplayComplaintsByUser(40);

	cout << "\n***Increasing priority of Complaint ID 9 from regular to premium:\n";
	p.IncreasePriority(&c9);
	p.DisplayAllComplaints();

	cout << "\n***Displaying all Complaints of Country Pakistan:\n";
	p.DisplayComplaintsByCountry("Pakistan");

	return 0;
}
