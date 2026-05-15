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
    int menu;
    string lanjut;
    do{
        system("cls");
        cout << "====================================================================\n";
        cout << "||         Sistem Pengelolaan Cuti Karyawan -PT. Syududu          ||\n";
        cout << "====================================================================\n";
        cout << "||     1. Tambah Data Karyawan                                    ||\n";
        cout << "||     2. Tampilkan Data Karyawan                                 ||\n";
        cout << "||     3. Pengajuan Cuti                                          ||\n";
        cout << "||     4. Hapus Data Karyawan                                     ||\n";
        cout << "||     5. Undo Aksi                                               ||\n";
        cout << "||     6. Tampilkan Antrian Cuti Karyawan                         ||\n";
        cout << "||     7. Keluar                                                  ||\n";
        cout << "====================================================================\n";
        cout << "Pilih menu: ";
        cin >> menu;
    } while(lanjut == "Y" || lanjut == "y");
}