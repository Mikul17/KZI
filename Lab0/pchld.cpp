////
//// Created by Miłosz Mikulski on 14/03/2024.
////
//#include <iostream>
//#include <fstream>
//
//using namespace std;
//
//struct Obiekt{
//    int r;
//    int p;
//    int q;
//    int id;
//
//    Obiekt(int _r = 0, int _p = 0, int _q = 0, int _id = -1) : r(_r), p(_p), q(_q), id(_id) {}
//};
//
//void wczytajDane(int& n, int r[], int p[], int q[], const string& dane) {
//    ifstream f("/Users/miql/Desktop/Cpp/Lab0/rpq.data.txt");
//    string tmp;
//
//    while(getline(f, tmp)) {
//        if(tmp == dane) {
//            break;
//        }
//    }
//
//    f >> n;
//    for(int i = 0; i < n; i++) {
//        f >> r[i] >> p[i] >> q[i];
//
//    }
//}
//Obiekt* wczytajDane(const string& dane, int& n){
//    ifstream f("/Users/miql/Desktop/Cpp/Lab0/rpq.data.txt");
//    string tmp;
//
//    while(getline(f,tmp)){
//        if(tmp == dane){
//            break;
//        }
//    }
//
//    f>>n;
//    Obiekt* obiekty = new Obiekt[n];
//
//    for(int i=0; i<n; i++){
//        f>>obiekty[i].r>>obiekty[i].p>>obiekty[i].q;
//        obiekty[i].id=i;
//    }
//
//    return obiekty;
//}
//
//void wyswietlDane(int& n,int r[], int p[], int q[]){
//    cout<<n<<endl;
//    for(int i=0;i<n;i++){
//        cout<<r[i]<<" | "<<p[i]<<" | "<<q[i]<<endl;
//    }
//}
//void wyswietlDane(Obiekt* obiekty, int& n){
//    for(int i=0; i<n; i++){
//        cout<<"["<<obiekty[i].id<<"]: "<<"r: "<<obiekty[i].r<<" p: "<<obiekty[i].p<<" q: "<<obiekty[i].q<<endl;
//    }
//}
//
//int algorytm123(int &n, int r[], int p[], int q[]){
//    int t, Cmax =0;
//    for(int i=0; i<n; i++){
//        t = max(t,r[i])+p[i];
//        Cmax=max(Cmax,t+q[i]);
//    }
//
//    cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
//    return Cmax;
//}
//int algorytm123(Obiekt* obiekty, int& n){
//    int  Cmax=0;
//    int  t=0;
//    for(int i=0; i<n; i++){
//        t = max(t,obiekty[i].r)+obiekty[i].p;
//        Cmax=max(Cmax, t+obiekty[i].q);
//    }
//    cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
//    return Cmax;
//}
//
//int odwrotnyAlgorytm123(int &n, int r[], int p[], int q[]){
//    int t, Cmax =0;
//    for(int i=n-1; i>=0 ; i--){
//        t = max(t,r[i])+p[i];
//        Cmax=max(Cmax,t+q[i]);
//    }
//    cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
//    return Cmax;
//}
//int odwrotnyAlgorytm123(Obiekt* obiekty, int& n){
//    int  Cmax=0;
//    int t=0;
//    for(int i=n; i>=0; i--){
//        t = max(t,obiekty[i].r)+obiekty[i].p;
//        Cmax=max(Cmax, t+obiekty[i].q);
//    }
//    cout<<"t: "<<t<<" | Cmax: "<<Cmax<<endl;
//    return Cmax;
//}
//
//int obliczDlaWycinka(Obiekt* obiekty, int& n, int indeksy[]){
//    int t=0, Cmax=0;
//    for(int k=0; k<n;k++){
//        t = max(t,obiekty[indeksy[k]].r)+obiekty[indeksy[k]].p;
//        Cmax=max(Cmax, t+obiekty[indeksy[k]].q);
//    }
//    cout<<"Cmax: "<<Cmax<<endl;
//    return Cmax;
//}
//
//void zamiana(Obiekt obiekty[], int p, int q){
//    Obiekt temp;
//    temp = obiekty[p];
//    obiekty[p]=obiekty[q];
//    obiekty[q]=temp;
//}
//
//void sortR(Obiekt* obiekty, int& n){
//    sort(obiekty, obiekty + n, [](const Obiekt& a, const Obiekt& b) {
//        return a.r < b.r;
//    });
//
//    int indeksy[n];
//
//    for(int i=0; i<n; i++){
//        indeksy[i]=obiekty[i].id;
//    }
//
//    for(int i=0; i<n; i++){
//        cout<<indeksy[i]<<" ";
//    }
//
//    //obliczDlaWycinka(obiekty,n,indeksy);
//    algorytm123(obiekty,n);
//}
//
//
//
//int main() {
//    int n, r[100], p[100], q[100];
//    Obiekt* obiekty = wczytajDane("data.1",n);
//    wyswietlDane(obiekty, n);
//    //algorytm123(obiekty,n);
//    //odwrotnyAlgorytm123(obiekty,n);
//
//    int wycinek[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
//    int wycinekLength = sizeof(wycinek)/sizeof(int);
//    //cout<<wycinekLength<<endl;
//    //obliczDlaWycinka(obiekty,wycinekLength, wycinek);
//    sortR(obiekty,n);
//
//
//
//    return 0;
//}
//
////skrot nazwy przedmiotu, nr cwiczenia
////KZW_Lab1
////sprawozdanie + kod zrodlowy