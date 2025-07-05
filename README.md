🎫 Online Ticketing System (DSA Project)

This C++ console-based Online Ticketing System is designed as a mini project for demonstrating the application of Data Structures and Algorithms (DSA) concepts. It manages ticket booking, cancellation, sorting, and searching, leveraging data structures like Heap, Queue, Hash Map, and Vectors, along with File Handling for persistent storage.


🔧 Features

Book Ticket:Adds a new ticket with unique ID, customer name, and priority.

Cancel Ticket: Deletes a ticket by ID using an efficient Hash Map lookup.

View All Tickets: Displays all stored tickets.

Top Priority Tickets: Uses a Max Heap to show the top 5 tickets with the highest priority.

Sort Tickets: Offers two sorting algorithms:

Bubble Sort

Quick Sort

Search Ticket: Allows searching tickets by ID using:

Linear Search

Binary Search (after sorting)


📁 Data Structures Used

priority_queue (Max Heap): For managing tickets based on priority.

queue: For maintaining the order of ticket entries.

unordered_map: For fast lookup and cancellation using ticket IDs.

vector: As a central structure for sorting and iteration.


💾 File Handling

tickets.txt: Stores all ticket records for persistence.

last_id.txt: Keeps track of the last used Ticket ID to ensure ID uniqueness across sessions.


📌 Concepts Demonstrated

Heap, Queue, Hash Map

Sorting Algorithms: Bubble Sort & Quick Sort

Searching Algorithms: Linear Search & Binary Search

File I/O operations in C++

Input validation and error handling


📷 Sample Output

====== Online Ticketing System ======
1. Book Ticket
2. Cancel Ticket
3. View All Tickets
4. View Top 5 Priority Tickets
5. Sort Tickets
6. Search Ticket
7. Exit


✅ How to Run

Compile using any C++ compiler:

g++ ticketing_system.cpp -o ticketing_system
./ticketing_system

Ensure the program has access to:

tickets.txt

last_id.txt
