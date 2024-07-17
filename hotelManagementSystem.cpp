#include <iostream>
#include <cstring>

#define MAX 100
using namespace std;

// Class Customer
class Customer {
public:
    char name[100];
    char address[100];
    char phone[12];
    char from_date[20];
    char to_date[20];
    float payment_advance;
    int booking_id;
};

// Class Room
class Room {
public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    Customer cust;

    Room addRoom(int);
    void searchRoom(int);
    void deleteRoom(int);
    void displayRoom(Room);
};

// Global Declarations
Room rooms[MAX];
int count = 0;

// Member functions for Room class
Room Room::addRoom(int rno) {
    Room room;
    room.roomNumber = rno;
    cout << "\nType AC/Non-AC (A/N): ";
    cin >> room.ac;
    cout << "\nType Comfort (S/N): ";
    cin >> room.type;
    cout << "\nType Size (B/S): ";
    cin >> room.stype;
    cout << "\nDaily Rent: ";
    cin >> room.rent;
    room.status = 0;

    cout << "\nRoom Added Successfully!";
    return room;
}

void Room::searchRoom(int rno) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == rno) {
            found = 1;
            if (rooms[i].status == 1) {
                cout << "\nRoom is Reserved";
            } else {
                cout << "\nRoom is available";
            }
            displayRoom(rooms[i]);
            break;
        }
    }
    if (found == 0) {
        cout << "\nRoom not found";
    }
}

void Room::deleteRoom(int rno) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == rno) {
            for (int j = i; j < count - 1; j++) {
                rooms[j] = rooms[j + 1];
            }
            count--;
            found = 1;
            cout << "\nRoom Deleted Successfully!";
            break;
        }
    }
    if (found == 0) {
        cout << "\nRoom not found";
    }
}

void Room::displayRoom(Room tempRoom) {
    cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    cout << "\nType AC/Non-AC (A/N): " << tempRoom.ac;
    cout << "\nType Comfort (S/N): " << tempRoom.type;
    cout << "\nType Size (B/S): " << tempRoom.stype;
    cout << "\nRent: " << tempRoom.rent;
}

// Class Hotel Management
class HotelMgnt: protected Room {
public:
    void checkIn();
    void getAvailRoom();
    void searchCustomer(char *);
    void checkOut(int);
    void guestSummaryReport();
};

// Member functions for HotelMgnt class
void HotelMgnt::guestSummaryReport() {
    if (count == 0) {
        cout << "\nNo Guest in Hotel!!";
    } else {
        for (int i = 0; i < count; i++) {
            if (rooms[i].status == 1) {
                cout << "\nCustomer First Name: " << rooms[i].cust.name;
                cout << "\nRoom Number: " << rooms[i].roomNumber;
                cout << "\nAddress (only city): " << rooms[i].cust.address;
                cout << "\nPhone: " << rooms[i].cust.phone;
                cout << "\n---------------------------------------";    
            }
        }
    }
}

// Hotel management reservation of room
void HotelMgnt::checkIn() {
    int rno;
    cout << "\nEnter Room number: ";
    cin >> rno;
    for (int i = 0; i < count; i++) {
        if (rooms[i].roomNumber == rno) {
            if (rooms[i].status == 1) {
                cout << "\nRoom is already Booked";
                return;
            }
            cout << "\nEnter booking id: ";
            cin >> rooms[i].cust.booking_id;
            cout << "\nEnter Customer Name (First Name): ";
            cin >> rooms[i].cust.name;
            cout << "\nEnter Address (only city): ";
            cin >> rooms[i].cust.address;
            cout << "\nEnter Phone: ";
            cin >> rooms[i].cust.phone;
            cout << "\nEnter From Date: ";
            cin >> rooms[i].cust.from_date;
            cout << "\nEnter to Date: ";
            cin >> rooms[i].cust.to_date;
            cout << "\nEnter Advance Payment: ";
            cin >> rooms[i].cust.payment_advance;
            rooms[i].status = 1;
            cout << "\nCustomer Checked-in Successfully..";
            return;
        }
    }
    cout << "\nRoom not found.";
}

// Hotel management shows available rooms
void HotelMgnt::getAvailRoom() {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 0) {
            displayRoom(rooms[i]);
            cout << "\n\nPress enter for next room\n";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nAll rooms are reserved";
    }
}

// Hotel management shows all persons that have booked room
void HotelMgnt::searchCustomer(char *pname) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 1 && strcmp(rooms[i].cust.name, pname) == 0) {
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].roomNumber;
            cout << "\n\nPress enter for next record\n";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nPerson not found.\n";
    }
}

// Hotel management generates the bill of the expenses
void HotelMgnt::checkOut(int roomNum) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 1 && rooms[i].roomNumber == roomNum) {
            int days;
            float billAmount = 0;
            cout << "\nEnter Number of Days: ";
            cin >> days;
            billAmount = days * rooms[i].rent;
            cout << "\n\t######## CheckOut Details ########\n";
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].roomNumber;
            cout << "\nAddress: " << rooms[i].cust.address;
            cout << "\nPhone: " << rooms[i].cust.phone;
            cout << "\nTotal Amount Due: " << billAmount << " /";
            cout << "\nAdvance Paid: " << rooms[i].cust.payment_advance << " /";
            cout << "\n*** Total Payable: " << billAmount - rooms[i].cust.payment_advance << "/ only\n";
            rooms[i].status = 0;
            return;
        }
    }
    if (found == 0) {
        cout << "\nRoom not found.";
    }
}

// Managing rooms (adding, searching, and deleting available rooms)
void manageRooms() {
    Room room;
    int opt, rno;
    do {
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Delete Room";
        cout << "\n4. Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt) {
            case 1:
                cout << "\nEnter Room Number: ";
                cin >> rno;
                for (int i = 0; i < count; i++) {
                    if (rooms[i].roomNumber == rno) {
                        cout << "\nRoom Number is Present.\nPlease enter unique Number";
                        break;
                    }
                }
                rooms[count] = room.addRoom(rno);
                count++;
                break;
            case 2:
                cout << "\nEnter room number: ";
                cin >> rno;
                room.searchRoom(rno);
                break;
            case 3:
                cout << "\nEnter room number to delete: ";
                cin >> rno;
                room.deleteRoom(rno);
                break;
            case 4:
                break;
            default:
                cout << "\nPlease Enter correct option";
                break;
        }
    } while (opt != 4);
}

int main() {
    HotelMgnt hm;
    int opt, rno;
    char pname[100];

    do {
        cout << "######## Hotel Management #########\n";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In Room";
        cout << "\n3. Available Rooms";
        cout << "\n4. Search Customer";
        cout << "\n5. Check-Out Room";
        cout << "\n6. Guest Summary Report";
        cout << "\n7. Exit";
        cout << "\n\nEnter Option: ";
        cin >> opt;
        switch (opt) {
            case 1:
                manageRooms();
                break;
            case 2:
                if (count == 0) {
                    cout << "\nRooms data is not available.\nPlease add the rooms first.";
                } else {
                    hm.checkIn();
                }
                break;
            case 3:
                if (count == 0) {
                    cout << "\nRooms data is not available.\nPlease add the rooms first.";
                } else {
                    hm.getAvailRoom();
                }
                break;
            case 4:
                if (count == 0) {
                    cout << "\nRooms are not available.\nPlease add the rooms first.";
                } else {
                    cout << "Enter Customer Name: ";
                    cin >> pname;
                    hm.searchCustomer(pname);
                }
                break;
            case 5:
                if (count == 0) {
                    cout << "\nRooms are not available.\nPlease add the rooms first.";
                } else {
                    cout << "Enter Room Number: ";
                    cin >> rno;
                    hm.checkOut(rno);
                }
                break;
            case 6:
                hm.guestSummaryReport();
                break;
            case 7:
                cout << "\nTHANK YOU! FOR USING SOFTWARE\n";
                break;
            default:
                cout << "\nPlease Enter correct option";
                break;
        }
    } while (opt != 7);

    return 0;
}
