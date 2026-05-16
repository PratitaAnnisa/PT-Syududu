#include <iostream>
#include <iomanip>
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

NodePTB* insert(NodePTB* root, int id, string x, string div){
    if(root == nullptr){
        return new NodePTB(id, x, div, false);
    }
    if(id < root->nip){
        root->kiri = insert(root->kiri, id, x, div);
    } else if(id > root->nip){
        root->kanan = insert(root->kanan, id, x, div);
    }
    return root;
}

NodePTB* search(NodePTB* root, int id){
    if(root == nullptr || root->nip == id){
        return root;
    }
    if(id < root->nip){
        return search(root->kiri, id);
    }
    return search(root->kanan, id);
}

NodePTB* nilaiMin(NodePTB* root){
    while (root->kiri != nullptr) root = root->kiri;
    return root;
}

NodePTB* hapus(NodePTB* root, int id){
    if(root == nullptr) return root;
    if(id < root->nip){
        root->kiri = hapus(root->kiri, id);
    } else if(id > root->nip){
        root->kanan = hapus(root->kanan, id);
    } else {
        if(root->kiri == nullptr){
            NodePTB* temp = root->kanan;
            delete root;
            return temp;
        } else if(root->kanan == nullptr){
            NodePTB* temp = root->kiri;
            delete root;
            return temp;
        }
        NodePTB* temp = nilaiMin(root->kanan);
        root->nip = temp->nip;
        root->nama = temp->nama;
        root->divisi = temp->divisi;
        root->cuti = temp->cuti;
        root->kanan = hapus(root->kanan, temp->nip);
    }
    return root;
}

void inOrder(NodePTB* root, int& no);
void enQueue(int id, string x);
void deQueue();
void push(string aksi, int id, string x);
void pop();
void tambahDataKaryawan();
void tampilkanDataKaryawan(NodePTB* root);
void pengajuanCuti();
void hapusDataKaryawan();
void undoAksi();
void tampilkanAntrianCuti();

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
        cout << "||     0. Keluar                                                  ||\n";
        cout << "====================================================================\n";
        cout << "Pilih menu: ";
        cin >> menu;

        switch(menu){
            case 1:
                tambahDataKaryawan();
                break;
            case 2:
                tampilkanDataKaryawan(root);
                break;
            case 3:
                pengajuanCuti();
                break;
            case 4:
                hapusDataKaryawan();
                break;
            case 5:
                undoAksi();
                break;
            case 6:
                tampilkanAntrianCuti();
                break;
            case 0:
                cout << "Program Keluar\nData Telah Tersimpan" << endl;
                return 0;
            default:
                cout << "Opsi menu tidak valid." << endl; 
        }
    } while(lanjut == "Y" || lanjut == "y");
}

void inOrder(NodePTB* root, int& no){
    if(root != nullptr){
        inOrder(root->kiri, no);
        cout << "||     " << no++ << ". " << root->nip << " - " << root->nama << " - " << root->divisi << " - " << (root->cuti ? "Cuti" : "Tidak Cuti") << endl;
        inOrder(root->kanan, no);
    }
}

void enQueue(int id, string x){
    NodeQueue* newNode = new NodeQueue(id, x);
    if(depan == nullptr){
        depan = belakang = newNode;
    } else {
        belakang->next = newNode;
        belakang = newNode;
    }
}

void deQueue(){
    if(depan == nullptr) return;
    NodeQueue* hapus = depan;
    depan = depan->next;
    if(depan == nullptr) belakang = nullptr;
    delete hapus;
}

void push(string aksi, int id, string x){
    NodeStack* newNode = new NodeStack(id, x, aksi);
    newNode->next = top;
    top = newNode;
}

void pop(){
    if(top == nullptr) return;
    NodeStack* hapus = top;
    top = top->next;
    delete hapus;
}

void tambahDataKaryawan(){
    system("cls");
    int id, jmlh;
    string nama, divisi;
    cout << "====================================================================\n";
    cout << "||\t\tTambah Data Karyawan          ||\n";
    cout << "====================================================================\n";
    cout << "Jumlah Data yang ingin ditambahkan: ";
    cin >> jmlh;
    for(int i = 0; i < jmlh; i++){
        cout << "Data ke-" << i+1 << endl;
        cout << "NIP: ";
        cin >> id;
        cin.ignore();
        cout << "Nama: ";
        getline(cin, nama);
        cout << "Divisi: ";
        getline(cin, divisi);
        root = insert(root, id, nama, divisi);
        push("Tambah", id, nama);
    }

    if(search(root, id) != nullptr){
        cout << "Data berhasil ditambahkan." << endl;
    } else {
        cout << "Data gagal ditambahkan." << endl;
    }
}

void tampilkanDataKaryawan(NodePTB* root){
    system("cls");
    cout << "====================================================================\n";
    cout << "||\t\tData Karyawan PT. Syududu         ||\n";
    cout << "====================================================================\n";
    cout << left << setw(5) << "No" << setw(15) << "NIP" << setw(25) << "Nama" << setw(20) << "Divisi" << setw(15) << "Status Cuti" << endl;
    cout << "---------------------------------------------------------------------\n";

    if(root == nullptr){
        cout << "Belum ada data karyawan.\n";
    } else{
        int no = 1;
        inOrder(root, no);
    }

    cout << "=====================================================================\n";
}

void pengajuanCuti(){
    system("cls");
    int id;
    cout << "====================================================================\n";
    cout << "||\t\tPengajuan Cuti Karyawan         ||\n";
    cout << "====================================================================\n";
    cout << "Masukkan NIP karyawan yang ingin mengajukan cuti: ";
    cin >> id;

    NodePTB* karyawan = search(root, id);
    if(karyawan != nullptr){
        if(karyawan->cuti){
            cout << "Karyawan dengan NIP " << id << " sudah mengajukan cuti sebelumnya." << endl;
        } else {
            karyawan->cuti = true;
            enQueue(id, karyawan->nama);
            push("Pengajuan Cuti", id, karyawan->nama);
            cout << "Pengajuan cuti berhasil\n"; 
        }
    } else {
        cout << "Karyawan dengan NIP " << id << " tidak ditemukan." << endl;
    }
}

void hapusDataKaryawan(){
    system("cls");
    cout << "====================================================================\n";
    cout << "||\t\tHapus Data Karyawan         ||\n";
    cout << "====================================================================\n";
    int id;
    cout << "Masukkan NIP karyawan yang ingin dihapus: ";
    cin >> id;

    if(search(root, id) == nullptr){
        cout << "NIP karyawan tidak ditemukan." << endl;
        return;
    }

    root = hapus(root, id);
    cout << "Data karyawan dengan NIP " << id << " berhasil dihapus." << endl;
    push("Hapus", id, "Data Karyawan");
}

void undoAksi(){
    system("cls");
    cout << "====================================================================\n";
    cout << "||\t\tUndo Aksi Terakhir         ||\n";
    cout << "====================================================================\n";

    if(top == nullptr){
        cout << "Tidak ada aksi untuk di-undo.\n";
        return;
    }

    string aksi = top->aksi;
    int id = top->nip;
    string nama = top->nama;

    NodePTB* karyawan = search(root, id);

    if(aksi == "AJUKAN"){
        if(karyawan != nullptr) karyawan->cuti = false;
        cout << "Undo: Status cuti karyawan dibatalkan.\n";
    } else if(aksi == "SELESAI"){
        if(karyawan != nullptr) karyawan->cuti = true;
        cout << "Undo: Status cuti karyawan dikembalikan.\n";
    }

    pop();
}

void tampilkanAntrianCuti(){
    system("cls");
    cout << "====================================================================\n";
    cout << "||\t\tAntrian Cuti Karyawan         ||\n";
    cout << "====================================================================\n";

    if(depan == nullptr){
        cout << "Tidak ada antrian pengjuan cuti.\n";
        return;
    }

    NodeQueue* current = depan;
    int no = 1;
    while(current != nullptr){
        cout << "||     " << no++ << ". " << current->nip << " - " << current->nama << endl;
        current = current->next;
    }
    cout << "====================================================================\n";
}