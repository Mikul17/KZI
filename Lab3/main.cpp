#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <valarray>

using namespace std;

struct Zadanie{
    int index;
    int waga;
    vector<int>zadania;
};


void wczytajDane(const string& dane, vector<Zadanie>& zadania){
    ifstream f("../neh.data.txt");
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
        int w=0;
        zad.index=i;
        for(int i=0; i<ilosc_maszyn; i++){
            int tmp=0;
            f>>tmp;
            w+=tmp;
            zad.zadania.push_back(tmp);
        }
        zad.waga=w;
        zadania.push_back(zad);
    }
}

int obliczCmax(const vector<Zadanie>& zadania) {
    int liczbaMaszyn = zadania.front().zadania.size();
    vector<int> czasyZakonczeniaMaszyn(liczbaMaszyn, 0);

    for (const Zadanie& zad : zadania) {
        for (int m = 0; m < liczbaMaszyn; m++) {
            int czasZakonczeniaPoprzedniegoZadania = (m == 0) ? 0 : czasyZakonczeniaMaszyn[m - 1];
            int czasZakonczeniaNaPoprzedniejMaszynie = czasyZakonczeniaMaszyn[m];
            czasyZakonczeniaMaszyn[m] = max(czasZakonczeniaPoprzedniegoZadania, czasZakonczeniaNaPoprzedniejMaszynie) + zad.zadania[m];
        }
    }

    return czasyZakonczeniaMaszyn.back();
}

int neh(const vector<Zadanie>& dane) {
    vector<Zadanie> posortowane = dane;
    sort(posortowane.begin(), posortowane.end(), [](const Zadanie& a, const Zadanie& b) {
        if (a.waga == b.waga) {
            return a.index < b.index;
        }
        return a.waga > b.waga;
    });

    vector<Zadanie> najlepszaKolejnosc;
    int bestCmax = INT_MAX;

    for (const Zadanie& zad : posortowane) {
        int najlepszeMiejsce = -1;
        int aktualnyNajlepszyCmax = INT_MAX;

        for (size_t i = 0; i <= najlepszaKolejnosc.size(); i++) {
            najlepszaKolejnosc.insert(najlepszaKolejnosc.begin() + i, zad);
            int tempCmax = obliczCmax(najlepszaKolejnosc);

            if (tempCmax < aktualnyNajlepszyCmax) {
                aktualnyNajlepszyCmax = tempCmax;
                najlepszeMiejsce = i;
            }

            najlepszaKolejnosc.erase(najlepszaKolejnosc.begin() + i);
        }


        najlepszaKolejnosc.insert(najlepszaKolejnosc.begin() + najlepszeMiejsce, zad);
        bestCmax = aktualnyNajlepszyCmax;
    }

    return bestCmax;
}

void wyciagnijDane(){
    ifstream input("../neh.data.txt");
    ofstream output("../odpowiedzi.txt");

    string line;
    string data;
    string cmax;
    bool neh = false;

    while(getline(input, line)){
        if(line.find("data.") != string::npos){
            data = line.substr(0, line.find(':'));
            neh = false;
        } else if(line.find("neh:") != string::npos){
            neh = true;
        } else if(neh){
            cmax = line.substr(line.find(':')+1);
            output << data << ": | NEH: " << cmax << '\n';
            neh = false;
        }
    }
}

void zamiana(vector<Zadanie>& zadania){
    int zakres = zadania.size();
    int indexPierwszy = rand() % zakres;
    int indexDrugi = rand() % zakres;


    swap(zadania.at(indexPierwszy), zadania.at(indexDrugi));
}

int symulowaneWyzarzanie(vector<Zadanie>& zadania){
    int Cmax = obliczCmax(zadania);
    int noweCmax = INT_MAX;
    vector<Zadanie> kopia = zadania;
    double T = 100;
    ofstream f ("../wyzarzanie.csv");
    f<<"Operacja;Cmax;T;"<<endl;
    for(int i=0; i< 100000; i++){
        zamiana(kopia);
        noweCmax = obliczCmax(kopia);
        int diff = noweCmax-Cmax;
        double warunek = exp(-diff/T);
        double r = static_cast<double>(rand()) / RAND_MAX;
        if(i%100==0){
            f<<i<<";"<<Cmax<<";"<<T<<endl;
        }
        if(noweCmax<Cmax || r<warunek){
            Cmax = noweCmax;
            zadania=kopia;
        }else{
            kopia=zadania;
        }

        /*Zmiana wartosci T tylko cztery razy
        if(i%25000==0){
            T=T*0.175;
        }
         */

        T=T*0.99995;
    }
    return Cmax;
}

int main(){
    vector<Zadanie> zadaniaNeh;
    vector<Zadanie> zadaniaWyzarzanie;
    wyciagnijDane();
    ifstream f("../odpowiedzi.txt");
    chrono::milliseconds czasNeh(0),czasWyz(0),czas(0);
    for(int i=0; i<= 120; i++){
        stringstream ss;
        ss << "data.";
        ss << setw(3) << setfill('0') << i;
        //Windows
        //string fileName = ss.str()+":";
        //MacOS
        string fileName = ss.str()+":\r";

        wczytajDane(fileName, zadaniaNeh);
        zadaniaWyzarzanie = zadaniaNeh;

        auto start = chrono::high_resolution_clock::now();
        auto Cmax = neh(zadaniaNeh);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
        czasNeh += duration;
        czas+=duration;

        auto startWyz = chrono::high_resolution_clock::now();
        auto CmaxWyzarzanie = symulowaneWyzarzanie(zadaniaWyzarzanie);
        auto stopWyz = chrono::high_resolution_clock::now();
        auto durationWyz = chrono::duration_cast<chrono::milliseconds>(stopWyz-startWyz);
        czasWyz+=durationWyz;
        czas+=durationWyz;



        string line;
        getline(f, line);
        string cmax = line.substr(line.find("NEH: ")+5);

        //Windows
//        cout<<fileName<<" | Neh: "<<Cmax<<" | Wyz: "<<CmaxWyzarzanie<<" | Oczekiwane: "<<cmax<<" | Diff Wyz: "<<(CmaxWyzarzanie- stoi(cmax))
//            <<" | Czas trwania Neh: "<<duration.count()<<" ms"<< " |  Wyz: "<<durationWyz.count()<<" ms"<<endl;
        //MacOS
        cout<<fileName.substr(0,fileName.length()-2)<<" | Neh: "<<Cmax<<" | Wyz: "<<CmaxWyzarzanie<<" | Oczekiwane: "<<cmax.substr(0,cmax.length()-1)<<" | Diff Wyz: "<<(CmaxWyzarzanie- stoi(cmax))
        <<" | Czas trwania Neh: "<<duration.count()<<" ms"<< " |  Wyz: "<<durationWyz.count()<<" ms"<<endl;

        zadaniaNeh.clear();
        zadaniaWyzarzanie.clear();
    }
    cout<<"Czas wykonania Neh: "<<chrono::duration_cast<chrono::seconds>(czasNeh).count() <<" s"<<endl;
    cout<<"Czas wykonania Wyzarzanie: "<<chrono::duration_cast<chrono::seconds>(czasWyz).count()<<" s"<<endl;
    cout<<"Czas wykonania: "<<chrono::duration_cast<chrono::seconds>(czas).count()<<" s"<<endl;
    return 0;
}