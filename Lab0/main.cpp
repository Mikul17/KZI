    #include <iostream>
    #include <fstream>
    #include <vector>
#include <algorithm>
#include <limits>
#include <chrono>

    using namespace std;

    struct Obiekt{
        int r;
        int p;
        int q;
        int id;

        Obiekt(int _r = 0, int _p = 0, int _q = 0, int _id = -1) : r(_r), p(_p), q(_q), id(_id) {}
    };

    vector<Obiekt> wczytajDane(const string& dane){
        vector<Obiekt> obiekty;
        //ifstream f ("/Users/miql/Desktop/Cpp/Lab0/rpq.data.txt");
        ifstream f ("C:\\Users\\miql\\Desktop\\KZI\\Lab0\\rpq.data.txt");
        string tmp;
        int n=0;

        while(getline(f,tmp)){
            if(tmp==dane){
                break;
            }
        }

        f>>n;

        for(int i=0;i<n;i++){
            Obiekt ob;
            f>>ob.r>>ob.p>>ob.q;
            ob.id=i+1;
            obiekty.push_back(ob);
        }
        return obiekty;
    }

    void wyswietlDane(vector<Obiekt> obiekty){
        for(int i=0; i<obiekty.size();i++){
            cout<<"["<<obiekty[i].id<<"]: "<<"r: "<<obiekty[i].r<<" p: "<<obiekty[i].p<<" q: "<<obiekty[i].q<<endl;
        }
    }

    int algorytm123(vector<Obiekt> obiekty){
        int t=0, Cmax=0;
        for(auto & i : obiekty){
            t = max(t,i.r)+i.p;
            Cmax=max(Cmax, t+i.q);
        }
        //cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
        return Cmax;
    }

    int odwrotnyAlgorytm123(vector<Obiekt> obiekty){
        int t=0,Cmax=0;

        for(int i=obiekty.size()-1; i>=0; i--){
            t=max(t,obiekty.at(i).r)+obiekty.at(i).p;
            Cmax=max(Cmax, t+obiekty.at(i).q);
        }
        cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
        return Cmax;
    }

    int obliczDlaWycinka(vector<Obiekt> obiekty, int indeksy[], int& size){
        int t=0, Cmax=0;

        for(int k=0; k<size; k++){
            t = max(t, obiekty.at(indeksy[k]).r)+obiekty.at(indeksy[k]).p;
            Cmax = max(Cmax, t+obiekty[indeksy[k]].q);
        }
        cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
        return Cmax;
    }

    void sortR(vector<Obiekt> obiekty){
        vector<Obiekt> posortowane = obiekty;
        sort(posortowane.begin(), posortowane.end(), [](const Obiekt& a, const Obiekt& b) {
            return a.r < b.r;
        });

        int indeksy[posortowane.size()];

        for(int i=0; i<posortowane.size();i++) {
            indeksy[i] = posortowane.at(i).id-1;
        }

        int size = sizeof(indeksy)/sizeof(int);

        obliczDlaWycinka(obiekty,indeksy,size);
    }

    bool operator==(const Obiekt& lhs, const Obiekt& rhs) {
        return lhs.r == rhs.r && lhs.p == rhs.p && lhs.q == rhs.q && lhs.id == rhs.id;
    }
    bool operator==(const vector<Obiekt>& lhs, const vector<Obiekt>& rhs) {
        if (lhs.size() != rhs.size()) return false;
        for (size_t i = 0; i < lhs.size(); ++i) {
            if (!(lhs[i] == rhs[i])) return false;
        }
        return true;
    }

    vector<Obiekt> tabuSearch(vector<Obiekt>& tasks) {
        const int tabuListSize = 5;
        const int maxIterations = 5;
        // Initial solution (could be improved)

        vector<Obiekt> currentSolution = tasks; // This could be a sorted list as per your existing methods
        sort(currentSolution.begin(), currentSolution.end(), [](const Obiekt& a, const Obiekt& b) {
            return a.r < b.r;
        });
        vector<Obiekt> bestSolution = currentSolution;
        int bestCmax = algorytm123(currentSolution); // Assuming algorytm123 calculates the Cmax for the given sequence

        // Initialize Tabu List
        vector<vector<Obiekt>> tabuList;

        for (int iteration = 0; iteration < maxIterations; ++iteration) {
            vector<Obiekt> bestCandidate;
            int bestCandidateCmax = std::numeric_limits<int>::max();

            // Explore Neighborhood
            for (int i = 0; i < currentSolution.size(); ++i) {
                for (int j = i + 1; j < currentSolution.size(); ++j) {
                    // Generate a neighbor solution by swapping two tasks
                    vector<Obiekt> candidateSolution = currentSolution;
                    std::swap(candidateSolution[i], candidateSolution[j]);

                    if (std::find(tabuList.begin(), tabuList.end(), candidateSolution) == tabuList.end()) { // Not in Tabu List
                        int candidateCmax = algorytm123(candidateSolution);
                        if (candidateCmax < bestCandidateCmax) {
                            bestCandidate = candidateSolution;
                            bestCandidateCmax = candidateCmax;
                        }
                    }
                }
            }

            // Update current solution and Tabu List
            currentSolution = bestCandidate;
            if (bestCandidateCmax < bestCmax) {
                bestSolution = bestCandidate;
                bestCmax = bestCandidateCmax;
            }

            tabuList.push_back(bestCandidate);
            if (tabuList.size() > tabuListSize) tabuList.erase(tabuList.begin());

            // Additional stopping criteria can be added here
        }

        return bestSolution;
    }




    int main() {
        //vector<Obiekt> dane = wczytajDane("data.1");
        //wyswietlDane(dane);
        //algorytm123(dane);
        //int wycinek[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
        //int size = sizeof(wycinek)/sizeof(int);
        //obliczDlaWycinka(dane,wycinek,size);
        //sortR(dane);
        //sortRQratio(dane);
        //sortQ(dane);
        //wyswietlDane(tabuSearch(dane));
        int totalCmax = 0;
        auto start = chrono::high_resolution_clock::now();
        vector<string> nazwyPlikow = {"data.1", "data.2", "data.3", "data.4"};

        for (auto &nazwaPliku : nazwyPlikow) {
            cout << "Przetwarzanie " << nazwaPliku << endl;

            // Wczytanie danych z aktualnego pliku
            vector<Obiekt> dane = wczytajDane(nazwaPliku);

            // Wyświetlenie wczytanych danych
            wyswietlDane(dane);

            // Wykonanie algorytmu tabu search na wczytanych danych
            vector<Obiekt> wynik = tabuSearch(dane);

            // Wyświetlenie wyniku algorytmu tabu search
            cout << "Wynik algorytmu tabu search dla " << nazwaPliku << ":" << endl;
            wyswietlDane(wynik);
            totalCmax += algorytm123(wynik);
        }
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "Czas wykonania: " << duration.count() << " milisekund" << endl;
        cout<<"Total Cmax: "<<totalCmax<<endl;


        return 0;
    }

    //skrot nazwy przedmiotu, nr cwiczenia
    //KZW_Lab1
    //sprawozdanie + kod zrodlowy