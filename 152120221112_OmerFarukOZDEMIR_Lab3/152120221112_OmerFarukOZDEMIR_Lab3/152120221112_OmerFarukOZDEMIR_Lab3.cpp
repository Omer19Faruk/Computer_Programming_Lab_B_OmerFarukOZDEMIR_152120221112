#include <iostream>
#include <string>
#include <locale.h>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;

    Page(string url, string title, int hour, int minute, int second) {
        this->url = url;
        this->title = title;
        this->accessTime[0] = hour;
        this->accessTime[1] = minute;
        this->accessTime[2] = second;
        this->next = NULL;
        this->prev = NULL;
    }
};

void DeleteForwardHistory(Page* current) {
    if (current == NULL) return;

    Page* temp = current->next;
    while (temp != NULL) {
        Page* sil = temp;
        temp = temp->next;
        delete sil;
    }

    current->next = NULL;
}

void Visit(Page*& head, Page*& tail, Page*& current, string url, string title, int hour, int minute, int second) {
    Page* yeni = new Page(url, title, hour, minute, second);

    // Hiç sayfa yoksa ilk düğüm olur
    if (head == NULL) {
        head = yeni;
        tail = yeni;
        current = yeni;
        return;
    }

    // Tarayıcı mantığı: ortadayken yeni sayfa açılırsa ileri geçmiş silinir
    if (current != tail) {
        DeleteForwardHistory(current);
        tail = current;
    }

    tail->next = yeni;
    yeni->prev = tail;
    tail = yeni;
    current = yeni;
}

void Back(Page*& current) {
    if (current == NULL) {
        cout << "Gecmiste hic sayfa yok.\n";
        return;
    }

    if (current->prev == NULL) {
        cout << "Daha geri gidemezsin.\n";
        return;
    }

    current = current->prev;
    cout << "Geri gidildi: " << current->title << " - " << current->url << "\n";
}

void Forward(Page*& current) {
    if (current == NULL) {
        cout << "Gecmiste hic sayfa yok.\n";
        return;
    }

    if (current->next == NULL) {
        cout << "Daha ileri gidemezsin.\n";
        return;
    }

    current = current->next;
    cout << "Ileri gidildi: " << current->title << " - " << current->url << "\n";
}

void DeleteCurrent(Page*& head, Page*& tail, Page*& current) {
    if (current == NULL) {
        cout << "Silinecek sayfa yok.\n";
        return;
    }

    Page* sil = current;

    // Tek dugum varsa
    if (head == tail) {
        head = NULL;
        tail = NULL;
        current = NULL;
        delete sil;
        cout << "Mevcut sayfa silindi. Gecmis bosaldi.\n";
        return;
    }

    // Bastaki dugumse
    if (sil == head) {
        head = head->next;
        head->prev = NULL;
        current = head;
        delete sil;
        cout << "Mevcut sayfa silindi. Yeni mevcut sayfa: " << current->title << "\n";
        return;
    }

    // Sondaki dugumse
    if (sil == tail) {
        tail = tail->prev;
        tail->next = NULL;
        current = tail;
        delete sil;
        cout << "Mevcut sayfa silindi. Yeni mevcut sayfa: " << current->title << "\n";
        return;
    }

    // Ortadaki dugumse
    sil->prev->next = sil->next;
    sil->next->prev = sil->prev;
    current = sil->next;
    delete sil;
    cout << "Mevcut sayfa silindi. Yeni mevcut sayfa: " << current->title << "\n";
}

void DisplayHistory(Page* head, Page* current) {
    if (head == NULL) {
        cout << "Gecmis bos.\n";
        return;
    }

    cout << "\n========== BROWSER HISTORY ==========\n";

    Page* temp = head;
    int index = 1;

    while (temp != NULL) {
        if (temp == current) {
            cout << "[CURRENT PAGE]\n";
        }

        cout << index << ". URL   : " << temp->url << "\n";
        cout << "   Title : " << temp->title << "\n";
        cout << "   Time  : ";

        for (int i = 0; i < 3; i++) {
            if (temp->accessTime[i] < 10) {
                cout << "0";
            }
            cout << temp->accessTime[i];
            if (i != 2) {
                cout << ":";
            }
        }

        cout << "\n";
        cout << "-------------------------------------\n";

        temp = temp->next;
        index++;
    }
}

void ClearAll(Page*& head, Page*& tail, Page*& current) {
    Page* temp = head;

    while (temp != NULL) {
        Page* sil = temp;
        temp = temp->next;
        delete sil;
    }

    head = NULL;
    tail = NULL;
    current = NULL;
}

void Menu() {
    cout << "\n========== MENU ==========\n";
    cout << "1. Visit Page\n";
    cout << "2. Back\n";
    cout << "3. Forward\n";
    cout << "4. Delete Current Entry\n";
    cout << "5. Display History\n";
    cout << "6. Exit\n";
    cout << "Secim: ";
}

int main() {
    setlocale(LC_ALL, "Turkish");

    Page* head = NULL;
    Page* tail = NULL;
    Page* current = NULL;

    int secim;

    do {
        Menu();
        cin >> secim;
        cin.ignore();

        if (secim == 1) {
            string url, title;
            int hour, minute, second;

            cout << "URL gir: ";
            getline(cin, url);

            cout << "Baslik gir: ";
            getline(cin, title);

            cout << "Saat gir (HH MM SS): ";
            cin >> hour >> minute >> second;
            cin.ignore();

            Visit(head, tail, current, url, title, hour, minute, second);
            cout << "Sayfa eklendi ve mevcut sayfa yapildi.\n";
        }
        else if (secim == 2) {
            Back(current);
        }
        else if (secim == 3) {
            Forward(current);
        }
        else if (secim == 4) {
            DeleteCurrent(head, tail, current);
        }
        else if (secim == 5) {
            DisplayHistory(head, current);
        }
        else if (secim == 6) {
            ClearAll(head, tail, current);
            cout << "Tum dugumler silindi. Program kapatiliyor.\n";
        }
        else {
            cout << "Gecersiz secim.\n";
        }

    } while (secim != 6);

    return 0;
}