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
        cout << "Введіть: ";
        cin >> menuItem;
        cout << endl;

        switch (menuItem)
        {
        case 1:
            cout << "Введіть кількість записів: ";
            cin >> N;
            if (N <= 0) {
                cout << "Кількість записів має бути більше нуля!" << endl;
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
            cout << "Записи відсортовано за датами народження." << endl;
            Print(notes, N);
            break;
        case 4:
        {
            string search_phone;
            cout << "Введіть номер телефону для пошуку: ";
            cin >> search_phone;
            int index = SearchByPhoneNumber(notes, N, search_phone);
            if (index != -1)
                PrintNote(notes[index]);
            else
                cout << "Запис із таким номером телефону не знайдено." << endl;
        }
        break;
        case 5:
            cout << "Введіть ім'я файлу для збереження: ";
            cin >> filename;
            if (SaveToFile(notes, N, filename))
                cout << "Дані успішно збережені у файл." << endl;
            else
                cout << "Помилка при збереженні даних у файл." << endl;
            break;
        case 6:
            cout << "Введіть ім'я файлу для завантаження: ";
            cin >> filename;
            if (LoadFromFile(notes, N, filename))
                cout << "Дані успішно завантажені з файлу." << endl;
            else
                cout << "Помилка при завантаженні даних з файлу." << endl;
            break;
        case 0:
            delete[] notes;
            return 0;
        default:
            cout << "Невірний вибір! Спробуйте знову." << endl;
            break;
        }
    }
}

void Menu() {
    cout << "\nОберіть дію:" << endl;
    cout << "1 - Ввести інформацію про записи" << endl;
    cout << "2 - Вивести інформацію про записи" << endl;
    cout << "3 - Впорядкувати за датами народження" << endl;
    cout << "4 - Пошук запису за номером телефону" << endl;
    cout << "5 - Зберегти записи у файл" << endl;
    cout << "6 - Завантажити записи з файлу" << endl;
    cout << "0 - Завершити роботу програми" << endl;
}

void Create(Note* notes, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Запис №" << i + 1 << endl;
        cin.ignore();
        cout << "Прізвище: ";
        getline(cin, notes[i].last_name);
        cout << "Ім'я: ";
        getline(cin, notes[i].first_name);
        cout << "Номер телефону: ";
        getline(cin, notes[i].phone_number);
        cout << "День народження (дд мм рррр): ";
        cin >> notes[i].birth_date[0] >> notes[i].birth_date[1] >> notes[i].birth_date[2];
        cout << endl;
    }
}

void Print(const Note* notes, const int N)
{
    cout << "============================================================================" << endl;
    cout << "|  №  | Прізвище       | Ім'я           | Номер телефону | Дата народження |" << endl;
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
    cout << "Прізвище: " << note.last_name << endl;
    cout << "Ім'я: " << note.first_name << endl;
    cout << "Номер телефону: " << note.phone_number << endl;
    cout << "Дата народження: " << note.birth_date[0] << "." << note.birth_date[1] << "." << note.birth_date[2] << endl;
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
