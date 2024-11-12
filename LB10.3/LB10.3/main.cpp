#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Note
{
    string last_name;
    string first_name;
    string phone_number;
    int birth_date[3]; // [0] - day, [1] - month, [2] - year
};

void Create(Note* notes, const int N);
void Print(const Note* notes, const int N);
void SortByBirthDate(Note* notes, const int N);
int SearchByPhoneNumber(const Note* notes, const int N, const string& phone_number);
void PrintNote(const Note& note);
bool LoadFromFile(Note*& notes, int& N, const string& filename);
bool SaveToFile(const Note* notes, const int N, const string& filename);
void Menu();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N = 0;
    Note* notes = nullptr;
    int menuItem;
    string filename;

    while (true)
    {
        Menu();
        cout << "������: ";
        cin >> menuItem;
        cout << endl;

        switch (menuItem)
        {
        case 1:
            cout << "������ ������� ������: ";
            cin >> N;
            if (N <= 0) {
                cout << "ʳ������ ������ �� ���� ����� ����!" << endl;
                break;
            }
            notes = new Note[N];
            Create(notes, N);
            break;
        case 2:
            Print(notes, N);
            break;
        case 3:
            SortByBirthDate(notes, N);
            cout << "������ ����������� �� ������ ����������." << endl;
            Print(notes, N);
            break;
        case 4:
        {
            string search_phone;
            cout << "������ ����� �������� ��� ������: ";
            cin >> search_phone;
            int index = SearchByPhoneNumber(notes, N, search_phone);
            if (index != -1)
                PrintNote(notes[index]);
            else
                cout << "����� �� ����� ������� �������� �� ��������." << endl;
        }
        break;
        case 5:
            cout << "������ ��'� ����� ��� ����������: ";
            cin >> filename;
            if (SaveToFile(notes, N, filename))
                cout << "��� ������ �������� � ����." << endl;
            else
                cout << "������� ��� ��������� ����� � ����." << endl;
            break;
        case 6:
            cout << "������ ��'� ����� ��� ������������: ";
            cin >> filename;
            if (LoadFromFile(notes, N, filename))
                cout << "��� ������ ���������� � �����." << endl;
            else
                cout << "������� ��� ����������� ����� � �����." << endl;
            break;
        case 0:
            delete[] notes;
            return 0;
        default:
            cout << "������� ����! ��������� �����." << endl;
            break;
        }
    }
}

void Menu() {
    cout << "\n������ ��:" << endl;
    cout << "1 - ������ ���������� ��� ������" << endl;
    cout << "2 - ������� ���������� ��� ������" << endl;
    cout << "3 - ������������ �� ������ ����������" << endl;
    cout << "4 - ����� ������ �� ������� ��������" << endl;
    cout << "5 - �������� ������ � ����" << endl;
    cout << "6 - ����������� ������ � �����" << endl;
    cout << "0 - ��������� ������ ��������" << endl;
}

void Create(Note* notes, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "����� �" << i + 1 << endl;
        cin.ignore();
        cout << "�������: ";
        getline(cin, notes[i].last_name);
        cout << "��'�: ";
        getline(cin, notes[i].first_name);
        cout << "����� ��������: ";
        getline(cin, notes[i].phone_number);
        cout << "���� ���������� (�� �� ����): ";
        cin >> notes[i].birth_date[0] >> notes[i].birth_date[1] >> notes[i].birth_date[2];
        cout << endl;
    }
}

void Print(const Note* notes, const int N)
{
    cout << "============================================================================" << endl;
    cout << "|  �  | �������       | ��'�           | ����� �������� | ���� ���������� |" << endl;
    cout << "----------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(4) << right << i + 1 << " ";
        cout << "|" << setw(16) << left << notes[i].last_name;
        cout << "|" << setw(16) << left << notes[i].first_name;
        cout << "|" << setw(16) << left << notes[i].phone_number;
        cout << "|" << setw(2) << right << notes[i].birth_date[0] << ".";
        cout << setw(2) << right << notes[i].birth_date[1] << ".";
        cout << setw(4) << right << notes[i].birth_date[2] << "       |" << endl;
    }
    cout << "============================================================================" << endl << endl;
}

void SortByBirthDate(Note* notes, const int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (notes[j].birth_date[2] > notes[j + 1].birth_date[2] ||
                (notes[j].birth_date[2] == notes[j + 1].birth_date[2] &&
                    notes[j].birth_date[1] > notes[j + 1].birth_date[1]) ||
                (notes[j].birth_date[2] == notes[j + 1].birth_date[2] &&
                    notes[j].birth_date[1] == notes[j + 1].birth_date[1] &&
                    notes[j].birth_date[0] > notes[j + 1].birth_date[0]))
            {
                swap(notes[j], notes[j + 1]);
            }
        }
    }
}

int SearchByPhoneNumber(const Note* notes, const int N, const string& phone_number)
{
    for (int i = 0; i < N; i++)
    {
        if (notes[i].phone_number == phone_number)
            return i;
    }
    return -1;
}

void PrintNote(const Note& note)
{
    cout << "�������: " << note.last_name << endl;
    cout << "��'�: " << note.first_name << endl;
    cout << "����� ��������: " << note.phone_number << endl;
    cout << "���� ����������: " << note.birth_date[0] << "." << note.birth_date[1] << "." << note.birth_date[2] << endl;
}

bool SaveToFile(const Note* notes, const int N, const string& filename)
{
    ofstream file(filename, ios::binary);
    if (!file) return false;
    file.write((char*)&N, sizeof(N));
    file.write((char*)notes, N * sizeof(Note));
    file.close();
    return true;
}

bool LoadFromFile(Note*& notes, int& N, const string& filename)
{
    ifstream file(filename, ios::binary);
    if (!file) return false;
    file.read((char*)&N, sizeof(N));
    delete[] notes;
    notes = new Note[N];
    file.read((char*)notes, N * sizeof(Note));
    file.close();
    return true;
}
