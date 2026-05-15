#include <iostream>
using namespace std;

struct NodePTB{
    NodePTB* kiri;
    NodePTB* kanan;
    int nip;
    string nama;
    string divisi;
    bool cuti;

    NodePTB(int id, string x, string div, bool cuti){
        nip = id;
        nama = x;
        divisi = div;
        cuti = cuti;
    };
};

struct NodeQueue{
    int nip;
    string nama;
    NodeQueue* next;

    NodeQueue(int id, string x){
        nip = id;
        nama = x;
        next = nullptr;
    };
};

struct NodeStack{
    int nip;
    string nama;
    NodeStack* next;
    string aksi;

    NodeStack(int id, string x, string a){
        nip = id;
        nama = x;
        aksi = a;
        next = nullptr;
    };
};

//var global
NodePTB* root = nullptr;
NodeQueue* depan = nullptr;
NodeQueue* belakang = nullptr;
NodeStack* top = nullptr;


int main(){
    cout << "Ya Allah, baru juga submit satu, nongol baru lagi\n";   
}