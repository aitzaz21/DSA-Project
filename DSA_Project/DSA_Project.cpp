#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Ticket {
    int id;
    string name;
    int priority;

    bool operator<(const Ticket& other) const {
        return priority < other.priority; // Max heap
    }
};

priority_queue<Ticket> ticketHeap;
queue<Ticket> ticketQueue;
unordered_map<int, Ticket> ticketMap;
vector<Ticket> ticketList;

int lastTicketID = 1000;

// ------------------ Helper Functions ------------------
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c)) return false;
    }
    return !name.empty();
}

// ------------------ File Handling ------------------
void loadLastTicketID() {
    ifstream fin("last_id.txt");
    if (fin >> lastTicketID) lastTicketID++;
    else lastTicketID = 1001;
    fin.close();
}

void saveLastTicketID() {
    ofstream fout("last_id.txt");
    fout << lastTicketID;
    fout.close();
}

void loadTickets() {
    ifstream fin("tickets.txt");
    if (!fin) return;

    Ticket t;
    while (fin >> t.id >> t.name >> t.priority) {
        ticketHeap.push(t);
        ticketQueue.push(t);
        ticketMap[t.id] = t;
        ticketList.push_back(t);
    }
    fin.close();
}

void saveTickets() {
    ofstream fout("tickets.txt");
    for (const Ticket& t : ticketList) {
        fout << t.id << " " << t.name << " " << t.priority << endl;
    }
    fout.close();
}

// ------------------ Sorting ------------------
void bubbleSort(vector<Ticket>& list) {
    int n = list.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (list[j].priority > list[j + 1].priority)
                swap(list[j], list[j + 1]);
}

void quickSort(vector<Ticket>& list, int low, int high) {
    if (low < high) {
        int pivot = list[high].priority;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (list[j].priority <= pivot) {
                i++;
                swap(list[i], list[j]);
            }
        }
        swap(list[i + 1], list[high]);
        int pi = i + 1;
        quickSort(list, low, pi - 1);
        quickSort(list, pi + 1, high);
    }
}

// ------------------ Searching ------------------
int linearSearch(const vector<Ticket>& list, int id) {
    for (int i = 0; i < list.size(); i++)
        if (list[i].id == id) return i;
    return -1;
}

int binarySearch(vector<Ticket>& list, int id) {
    int low = 0, high = list.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (list[mid].id == id) return mid;
        else if (list[mid].id < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ------------------ Operations ------------------
void addTicket() {
    Ticket t;
    t.id = lastTicketID++;

    cout << "Enter Name (letters only): ";
    cin >> t.name;
    while (!isValidName(t.name)) {
        cout << "Invalid name! Try again: ";
        cin >> t.name;
    }

    cout << "Enter Priority (1-10): ";
    while (!(cin >> t.priority) || t.priority < 1 || t.priority > 10) {
        cout << "Invalid priority! Enter a number between 1 and 10: ";
        clearInputBuffer();
    }

    ticketHeap.push(t);
    ticketQueue.push(t);
    ticketMap[t.id] = t;
    ticketList.push_back(t);
    saveTickets();
    saveLastTicketID();

    cout << "Ticket booked successfully. Ticket ID: " << t.id << "\n";
}

void cancelTicket() {
    int id;
    cout << "Enter Ticket ID to cancel: ";
    while (!(cin >> id)) {
        cout << "Invalid input! Enter numeric ID: ";
        clearInputBuffer();
    }

    auto it = ticketMap.find(id);
    if (it != ticketMap.end()) {
        ticketMap.erase(it);
        ticketList.erase(remove_if(ticketList.begin(), ticketList.end(),
            [id](Ticket& t) { return t.id == id; }), ticketList.end());
        saveTickets();
        cout << "Ticket canceled.\n";
    }
    else {
        cout << "Ticket not found.\n";
    }
}

void viewAllTickets() {
    cout << "\n--- All Tickets ---\n";
    for (auto& t : ticketList)
        cout << "ID: " << t.id << ", Name: " << t.name << ", Priority: " << t.priority << "\n";
}

void viewTopPriorityTickets() {
    cout << "\n--- Top 5 Priority Tickets ---\n";
    priority_queue<Ticket> temp = ticketHeap;
    int count = 0;
    while (!temp.empty() && count < 5) {
        Ticket t = temp.top(); temp.pop();
        cout << "ID: " << t.id << ", Name: " << t.name << ", Priority: " << t.priority << "\n";
        count++;
    }
    if (count == 0) cout << "No tickets available.\n";
}

void sortTickets() {
    vector<Ticket> temp = ticketList;
    int choice;
    cout << "1. Bubble Sort\n2. Quick Sort\nChoose sorting method: ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Enter 1 or 2: ";
        clearInputBuffer();
    }

    if (choice == 1) bubbleSort(temp);
    else quickSort(temp, 0, temp.size() - 1);

    for (auto& t : temp)
        cout << "ID: " << t.id << ", Name: " << t.name << ", Priority: " << t.priority << "\n";
}

void searchTicket() {
    int id;
    cout << "Enter Ticket ID to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input! Enter numeric ID: ";
        clearInputBuffer();
    }

    int choice;
    cout << "1. Linear Search\n2. Binary Search\nChoose method: ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Enter 1 or 2: ";
        clearInputBuffer();
    }

    int index = -1;
    if (choice == 1)
        index = linearSearch(ticketList, id);
    else {
        sort(ticketList.begin(), ticketList.end(),
            [](Ticket& a, Ticket& b) { return a.id < b.id; });
        index = binarySearch(ticketList, id);
    }

    if (index != -1)
        cout << "Found: ID: " << ticketList[index].id << ", Name: " << ticketList[index].name
        << ", Priority: " << ticketList[index].priority << "\n";
    else
        cout << "Ticket not found.\n";
}

// ------------------ Main ------------------
int main() {
    loadTickets();
    loadLastTicketID();

    int choice;
    do {
        cout << "\n====== Online Ticketing System ======\n";
        cout << "1. Book Ticket\n2. Cancel Ticket\n3. View All Tickets\n";
        cout << "4. View Top 5 Priority Tickets\n5. Sort Tickets\n6. Search Ticket\n7. Exit\n";
        cout << "Enter choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid option! Enter number between 1-7: ";
            clearInputBuffer();
        }

        switch (choice) {
        case 1: addTicket(); break;
        case 2: cancelTicket(); break;
        case 3: viewAllTickets(); break;
        case 4: viewTopPriorityTickets(); break;
        case 5: sortTickets(); break;
        case 6: searchTicket(); break;
        case 7: cout << "Goodbye!\n"; break;
        }

    } while (choice != 7);

    return 0;
}
