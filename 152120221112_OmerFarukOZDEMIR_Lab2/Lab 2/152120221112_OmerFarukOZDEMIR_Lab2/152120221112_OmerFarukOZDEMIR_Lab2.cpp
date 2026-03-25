#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node() {
        data = "";
        next = NULL;
    }

    Node(string data) {
        this->data = data;
        this->next = NULL;
    }
};

class Linkedlist {
    Node* head;

public:
    Linkedlist() {
        head = NULL;
    }

    void insertAtHead(string data) {

        Node* newNode = new Node(data);

        if (head == NULL) {
            head = newNode;
            return;
        }

        newNode->next = this->head;
        this->head = newNode;
    }

    void print() {
        Node* temp = head;

        if (head == NULL) {
            cout << "List is empty" << endl;
            return;
        }

        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    bool search(string song) {
        Node* temp = head;

        while (temp != NULL) {
            if (temp->data == song) {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }
};

int main()
{
    Linkedlist list;
    string ad;
    int secim;
    do {
        cout << "Choose an option: \n1: Add\n2: Search\n3: List\n4: Exit\n";
        cin >> secim;
        cin.ignore();

        switch (secim)
        {
            case 1:
                cout << "Enter the song of the name that you want to add to list: ";
                getline(cin, ad);
                list.insertAtHead(ad);
                break;
            case 2:
                cout << "Enter the song of the name that you want to search in the list: ";
                getline(cin, ad);

                if (list.search(ad)) {
                    cout << "Song exists in the list" << endl;
                }
                else {
                    cout << "Song does not exist in the list" << endl;
                }
                break;
            case 3:
                cout << "Your whole list is here: ";
                list.print();
                break;
            default:
                cout << "";
        }
    } while (secim != 4);
}