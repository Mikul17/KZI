#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Zadanie{
    int index;
    vector<int>zadania;
};

void wczytajDane(const string& dane, vector<Zadanie>& zadania){
    //ifstream f("neh.data.txt");
    ifstream f("D:\\Studia\\ISA\\SEMESTR 6\\KZI\\Lab3\\neh.data.txt");
    string tmp;
    int ilosc_zadan;
    int ilosc_maszyn;

    while(getline(f,tmp)){
        if(tmp==dane){
            break;
        }
    }

    f>>ilosc_zadan>>ilosc_maszyn;
    for(int i=0;i<ilosc_zadan;i++){
        Zadanie zad;
        zad.index=i+1;
        for(int i=0; i<ilosc_maszyn; i++){
            int tmp=0;
            f>>tmp;
            zad.zadania.push_back(tmp);
        }
        zadania.push_back(zad);
    }
}

void wyswietlDane(vector<Zadanie>& zadania){
    for(Zadanie zad : zadania){
        for(int z : zad.zadania){
            cout<<z<<" ";
        }
        cout<<endl;
    }
}

int obliczCmax(const vector<Zadanie>& zadania, const vector<int>& kolejnosc) {
    int liczbaMaszyn = zadania.front().zadania.size();
    vector<int> czasyZakonczeniaMaszyn(liczbaMaszyn, 0);

    for (int idx : kolejnosc) {
        vector<int> noweCzasyZakonczeniaMaszyn(liczbaMaszyn, 0);
        for (int m = 0; m < liczbaMaszyn; m++) {
            int czasZakonczeniaPoprzedniegoZadania = (m == 0) ? 0 : noweCzasyZakonczeniaMaszyn[m - 1];
            int czasZakonczeniaNaPoprzedniejMaszynie = czasyZakonczeniaMaszyn[m];
            noweCzasyZakonczeniaMaszyn[m] = max(czasZakonczeniaPoprzedniegoZadania, czasZakonczeniaNaPoprzedniejMaszynie) + zadania[idx - 1].zadania[m];
        }
        czasyZakonczeniaMaszyn = noweCzasyZakonczeniaMaszyn;
    }

    return czasyZakonczeniaMaszyn.back();
}


int main() {
    vector<Zadanie> zadania;
    string dane = "data.000:";
    //wersja MacOS
    //string dane = "data.000\r:";
    wczytajDane(dane,zadania);
    wyswietlDane(zadania);
    cout<<obliczCmax(zadania,{1,2,3,4})<<endl;
    return 0;
}
