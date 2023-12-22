#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class TRAINS {
    friend ostream &operator<<(ostream &cout, const TRAINS &t) {
        cout << t.num << " " << t.punkt << " " << t.type << " " << t.time << " " << t.way;
        return cout;
    }

private:
    int num;
    string punkt;
    string type;
    string way;
    string time;

public:
    void SetTrain(stringstream &ss) {
        string temp;
        getline(ss, temp, ' ');
        num = stoi(temp);
        temp = "";
        getline(ss, temp, ' ');
        punkt = temp;
        temp = "";
        getline(ss, temp, ' ');
        type = temp;
        temp = "";
        getline(ss, temp, ' ');
        time = temp;
        temp = "";
        getline(ss, temp, '.');
        way = temp;
    }

    ///p.3
    int GetTime() {
        int i = time.find(':');
        int h = static_cast<int>(stoi(time));
        string ms = time.substr(i + 1);
        int m = static_cast<int>(stoi(ms));
        int min = h * 60 + m;
        return min;
    }


    ///p.4
    int ArrTime(string arr) {
        int i = arr.find(':');
        int h = static_cast<int>(stoi(arr));
        string ms = arr.substr(i + 1);
        int m = static_cast<int>(stoi(ms));
        int min = h * 60 + m;
        return min;
    }


    ///p.5
    string GetPunkt() {
        return punkt;
    }


    ///p.6
    string GetFast() {
        return way;
    }


    ///p.7
    int SortTime() {
        int i = way.find(':');
        int h = static_cast<int>(stoi(way));
        string ms = way.substr(i + 1);
        int m = static_cast<int>(stoi(ms));
        int min = h * 60 + m;
        return min;
    }
};

int ArrTim(string arr) {
    int i = arr.find(':');
    int h = static_cast<int>(stoi(arr));
    string ms = arr.substr(i + 1);
    int m = static_cast<int>(stoi(ms));
    int min = h * 60 + m;
    return min;
}






int main() {
    ifstream fin("input.txt");
    string s;





    ///вод данных в vector из текстового файла
    vector<TRAINS> t;
    while (getline(fin, s)) {
        TRAINS tr;
        stringstream ss(s);
        tr.SetTrain(ss);
        t.push_back(tr);
    }

    ///упорядочение данных по времени отправления поездов

    bool sorted = true;
    do
    {
        sorted = true;
        TRAINS temp;
        for (int i = 0; i < t.size() - 1; i++)
        {
            int j = t[i].GetTime();
            int j1 = t[i + 1].GetTime();
            if (j > j1)
            {
                temp = t[i+1];
                t[i+1] = t[i];
                t[i] = temp;
                sorted = false;
            }
        }
    } while (!sorted);
    for (int i = 0; i < t.size(); i++) {
        cout << t[i] << endl;
    }


    ///вывод на экран информации обо всех поездах из заданного диапазона времени


        string begin;
    string end;  //cout сделать
    cout << "Введите диапазон времени в формате ЧЧ:ММ";
    cin >> begin >> end;
    int beg1, en1;
    beg1 = ArrTim(begin);
    en1 = ArrTim(end);
    bool q = false;
    for (int i = 0; i < t.size(); i++) {
        if (beg1 < t[i].GetTime() && t[i].GetTime() < en1) {
            cout << t[i] << endl;
            q = true;
        }
    }
    if (!q)
        cout << "There is no train" << endl;



    ///вывод на экран информации о всех поездах, направляющихся в заданный пункт назначения

  string punkt;
     cout << "Введите пункт назначения для поиска: ";
     cin >> punkt;
     cout << "Поезда, направляющиеся в " << punkt << ":" << endl;

     for (int i = 0; i < t.size(); i++) {
          if (punkt == t[i].GetPunkt()) {
              cout << t[i] << endl;
              q = true;
          }
     }
    if (!q)
        cout << "There is no train" << endl;



    ///вывод на экран всех скорых поездов, направляющихся в заданный пункт назначения;

    string fast;
    cout << "Введите пункт назначения для поиска: ";
    cin >> fast;
    cout << "Поезда, направляющиеся в " << punkt<< ":" << endl;

    for (int i = 0; i < t.size(); i++) {
        if (fast == t[i].GetFast()) {
            cout << t[i] << endl;
            q = true;
        }
    }
    if (!q)
        cout << "There is no train" << endl;



    ///нахождение самого быстрого поезда, следующего в заданный пункт назначения.

    vector<TRAINS> w;
    for (int i = 0; i < t.size(); i++) {
        if (punkt == t[i].GetPunkt()) {
            w.push_back(t[i]);
        }
    }
    sorted = true;
    do
    {
        sorted = true;
        TRAINS temp;
        for (int i = 0; i < t.size() - 1; i++)
        {
            int j = t[i].SortTime();
            int j1 = t[i + 1].SortTime();
            if (j > j1)
            {
                temp = t[i + 1];
                t[i + 1] = t[i];
                t[i] = temp;
                sorted = false;
            }
        }
    } while (!sorted);
    if (w.size()){
        cout << "САмый быстрый: ";
        cout << w[0];}
    else
        cout << "There is no train";

    return 0;
}