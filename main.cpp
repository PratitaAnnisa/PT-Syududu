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

    NodePTB(int id, string x, string div, bool c){
        nip    = id;
        nama   = x;
        divisi = div;
        cuti   = c;
        kiri   = nullptr;
        kanan  = nullptr;
    };
};

struct NodeQueue{
    int nip;
    string nama;
    NodeQueue* next;

    NodeQueue(int id, string x){
        nip  = id;
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
        nip  = id;
        nama = x;
        aksi = a;
        next = nullptr;
    };
};

NodePTB*   root        = nullptr;
NodeQueue* depan       = nullptr;
NodeQueue* belakang    = nullptr;
NodeStack* top         = nullptr;

//wadah, hanya 1 orang yang bisa cuti di satu waktu
int nipSedangCuti = 0;

NodePTB* insert(NodePTB* root, int id, string x, string div){
    if(root == nullptr) return new NodePTB(id, x, div, false);
    if(id < root->nip)       root->kiri  = insert(root->kiri,  id, x, div);
    else if(id > root->nip)  root->kanan = insert(root->kanan, id, x, div);
    else cout << "NIP sudah terdaftar!\n";
    return root;
}

NodePTB* search(NodePTB* root, int id){
    if(root == nullptr || root->nip == id) return root;
    if(id < root->nip) return search(root->kiri,  id);
    return                     search(root->kanan, id);
}

NodePTB* nilaiMin(NodePTB* node){
    while(node->kiri != nullptr) node = node->kiri;
    return node;
}

NodePTB* hapus(NodePTB* root, int id){
    if(root == nullptr) return root;
    if(id < root->nip){
        root->kiri  = hapus(root->kiri,  id);
    } else if(id > root->nip){
        root->kanan = hapus(root->kanan, id);
    } else {
        if(root->kiri == nullptr){
            NodePTB* temp = root->kanan; delete root; return temp;
        } else if(root->kanan == nullptr){
            NodePTB* temp = root->kiri;  delete root; return temp;
        }
        NodePTB* temp = nilaiMin(root->kanan);
        root->nip    = temp->nip;
        root->nama   = temp->nama;
        root->divisi = temp->divisi;
        root->cuti   = temp->cuti;
        root->kanan  = hapus(root->kanan, temp->nip);
    }
    return root;
}

// Ambil & hapus node paling depan dari antrian, kembalikan NIP-nya
// Kembalikan -1 jika antrian kosong
int deQueue(){
    if(depan == nullptr) return -1;
    NodeQueue* del = depan;
    int nipKeluar  = del->nip;
    depan          = depan->next;
    if(depan == nullptr) belakang = nullptr;
    delete del;
    return nipKeluar;
}

// Cek apakah ada NIP yang double
bool adaDiAntrian(int id){
    NodeQueue* bantu = depan;
    while(bantu != nullptr){
        if(bantu->nip == id) return true;
        bantu = bantu->next;
    }
    return false;
}

void inOrder(NodePTB* node, int& no);
void enQueue(int id, string x);
void tambahDataKaryawan();
void tampilkanDataKaryawan(NodePTB* root);
void pengajuanCuti();
void selesaiCuti();
void hapusDataKaryawan();
void undoAksi();
void tampilkanAntrianCuti();
void pop();
void push(string aksi, int id, string x);

int main(){
    int    menu;
    string lanjut;

    do {
        system("cls");
        cout << "====================================================================\n";
        cout << "||         Sistem Pengelolaan Cuti Karyawan -PT. Syududu          ||\n";
        cout << "====================================================================\n";
        cout << "||     1. Tambah Data Karyawan                                    ||\n";
        cout << "||     2. Tampilkan Data Karyawan                                 ||\n";
        cout << "||     3. Pengajuan Cuti                                          ||\n";
        cout << "||     4. Selesai Cuti                                            ||\n";
        cout << "||     5. Hapus Data Karyawan                                     ||\n";
        cout << "||     6. Undo Aksi                                               ||\n";
        cout << "||     7. Tampilkan Antrian Cuti Karyawan                         ||\n";
        cout << "||     0. Keluar                                                  ||\n";
        cout << "====================================================================\n";
        cout << "Pilih menu: ";
        cin  >> menu;

        switch(menu){
            case 1: tambahDataKaryawan();        break;
            case 2: tampilkanDataKaryawan(root); break;
            case 3: pengajuanCuti();             break;
            case 4: selesaiCuti();               break;
            case 5: hapusDataKaryawan();         break;
            case 6: undoAksi();                  break;
            case 7: tampilkanAntrianCuti();      break;
            case 0:
                cout << "Program Keluar\n";
                return 0;
            default:
                cout << "Opsi menu tidak valid.\n";
        }

        cout << "\nKembali ke Menu (Y/N): ";
        cin  >> lanjut;

    } while(lanjut == "Y" || lanjut == "y");

    return 0;
}

void inOrder(NodePTB* node, int& no){
    if(node == nullptr) return;
    inOrder(node->kiri, no);
    cout << left
         << "||  " << setw(5)  << no++
         << setw(12) << node->nip
         << setw(25) << node->nama
         << setw(20) << node->divisi
         << setw(15) << (node->cuti ? "Cuti" : "Tidak Cuti")
         << endl;
    inOrder(node->kanan, no);
}

void enQueue(int id, string x){
    NodeQueue* newNode = new NodeQueue(id, x);
    if(depan == nullptr){
        depan = belakang = newNode;
    } else {
        belakang->next = newNode;
        belakang       = newNode;
    }
}

void tambahDataKaryawan(){
    system("cls");
    int    id, jmlh;
    string nama, divisi;
    cout << "====================================================================\n";
    cout << "||              Tambah Data Karyawan                              ||\n";
    cout << "====================================================================\n";
    cout << "Jumlah data yang ingin ditambahkan: ";
    cin  >> jmlh;

    for(int i = 0; i < jmlh; i++){
        cout << "\nData ke-" << i+1 << endl;
        cout << "NIP    : ";
        cin  >> id;
        cin.ignore();
        cout << "Nama   : ";
        getline(cin, nama);
        cout << "Divisi : ";
        getline(cin, divisi);

        if(search(root, id) != nullptr){
            cout << "NIP " << id << " sudah terdaftar, data dilewati.\n";
            continue;
        }
        root = insert(root, id, nama, divisi);
        cout << "Data karyawan berhasil ditambahkan.\n";
    }
}

void tampilkanDataKaryawan(NodePTB* root){
    system("cls");
    cout << "====================================================================\n";
    cout << "||              Data Karyawan PT. Syududu                        ||\n";
    cout << "====================================================================\n";
    cout << left
         << "||  " << setw(5)  << "No"
         << setw(12) << "NIP"
         << setw(25) << "Nama"
         << setw(20) << "Divisi"
         << setw(15) << "Status"
         << endl;
    cout << "--------------------------------------------------------------------\n";

    if(root == nullptr){
        cout << "Belum ada data karyawan.\n";
    } else {
        int no = 1;
        inOrder(root, no);
    }
    cout << "====================================================================\n";

    // Tampilkan siapa yang sedang cuti
    if(nipSedangCuti != 0){
        NodePTB* yCuti = search(root, nipSedangCuti);
        if(yCuti != nullptr)
            cout << ">> Sedang cuti saat ini : " << yCuti->nama
                 << " (NIP: " << nipSedangCuti << ")\n";
    } else {
        cout << ">> Tidak ada karyawan yang sedang cuti saat ini.\n";
    }
    cout << "====================================================================\n";
}

void pengajuanCuti(){
    system("cls");
    int id;
    cout << "====================================================================\n";
    cout << "||              Pengajuan Cuti Karyawan                          ||\n";
    cout << "====================================================================\n";
    cout << "Masukkan NIP karyawan: ";
    cin  >> id;

    NodePTB* karyawan = search(root, id);
    if(karyawan == nullptr){ //error handling: karyawan dengan nip - tidak ada
        cout << "Karyawan tidak ditemukan!\n";
        return;
    }

    // error handling: yang sedang cuti tidak dapat melakukan pengjuan cuti
    if(karyawan->cuti){ 
        cout << "Karyawan sedang cuti, tidak bisa mengajukan cuti lagi.\n";
        return;
    }

    // Tolak jika karyawan ini sudah ada di antrian
    if(adaDiAntrian(id)){
        cout << "Karyawan sudah ada di dalam antrian cuti.\n";
        return;
    }

    // Cek apakah ada yang sedang cuti
    if(nipSedangCuti == 0){
        // Tidak ada yang cuti, cuti = acc
        karyawan->cuti = true;
        nipSedangCuti  = id;
        push("AJUKAN", id, karyawan->nama);
        cout << "Pengajuan cuti berhasil.\n";
    } else {
        // kuota cuti penuh, masuk ke antrian cuti
        enQueue(id, karyawan->nama);
        cout << "Karyawan sedang cuti, pengajuan masuk ke dalam antrian.\n";

        // Tampilkan posisi antrian
        NodeQueue* bantu = depan;
        int posisi = 1;
        while(bantu != nullptr){
            if(bantu->nip == id){ cout << "Posisi antrian: " << posisi << endl; break; }
            posisi++;
            bantu = bantu->next;
        }
    }
}

void selesaiCuti(){
    system("cls");
    int id;
    cout << "====================================================================\n";
    cout << "||              Selesai Cuti Karyawan                            ||\n";
    cout << "====================================================================\n";
    cout << "Masukkan NIP karyawan: ";
    cin  >> id;

    NodePTB* karyawan = search(root, id);
    if(karyawan == nullptr){
        cout << "Karyawan tidak ditemukan!\n";
        return;
    }
    if(!karyawan->cuti){
        cout << "Karyawan tidak sedang cuti.\n";
        return;
    }
    if(nipSedangCuti != id){
        cout << "Karyawan ini tidak melakukan cuti.\n";
        return;
    }

    // menyelesaikan cuti 
    karyawan->cuti = false;
    nipSedangCuti  = 0;   //wadah cuti kosong
    push("SELESAI", id, karyawan->nama);
    cout << "Cuti berhasil diselesaikan.\n";

    // Ambil orang pertama dari antrian (FIFO)
    if(depan != nullptr){
        int      nipBerikut   = depan->nip;
        string   namaBerikut  = depan->nama;
        NodePTB* berikut      = search(root, nipBerikut);

        deQueue();   // keluarkan dari antrian

        if(berikut != nullptr){
            berikut->cuti = true;
            nipSedangCuti = nipBerikut;
            push("AJUKAN", nipBerikut, namaBerikut);
            cout << "Pengajuan cuti berikutnya langsung diproses dari antrian.\n";
            cout << ">> " << namaBerikut << " (NIP: " << nipBerikut << ") sekarang sedang cuti.\n";
        }
    } else {
        cout << "Tidak ada antrian. Slot cuti kosong.\n";
    }
}

void hapusDataKaryawan(){
    system("cls");
    cout << "====================================================================\n";
    cout << "||              Hapus Data Karyawan                              ||\n";
    cout << "====================================================================\n";
    int id;
    cout << "Masukkan NIP karyawan yang ingin dihapus: ";
    cin  >> id;

    if(search(root, id) == nullptr){
        cout << "Karyawan tidak ditemukan!\n";
        return;
    }

    // Jika karyawan yang dihapus sedang cuti, maka status cuti dilepas
    if(nipSedangCuti == id){
        nipSedangCuti = 0;
        cout << "Peringatan: Karyawan ini sedang cuti\nStatus cuti free\n";
    }

    root = hapus(root, id);
    cout << "Data karyawan berhasil dihapus.\n";
}

void undoAksi(){
    system("cls");
    cout << "====================================================================\n";
    cout << "||              Undo Aksi Terakhir                               ||\n";
    cout << "====================================================================\n";

    if(top == nullptr){
        cout << "Tidak ada aksi untuk di-undo.\n";
        return;
    }

    string   aksi     = top->aksi;
    int      id       = top->nip;
    NodePTB* karyawan = search(root, id);

    if(aksi == "AJUKAN"){
        // Batalkan pengajuan: kembalikan status tidak cuti
        if(karyawan != nullptr) karyawan->cuti = false;
        if(nipSedangCuti == id) nipSedangCuti  = 0;
        cout << "Undo: Status cuti karyawan dibatalkan.\n";
    } else if(aksi == "SELESAI"){
        // Batalkan selesai cuti: kembalikan ke status cuti
        if(karyawan != nullptr) karyawan->cuti = true;
        nipSedangCuti = id;
        cout << "Undo: Status cuti karyawan dikembalikan menjadi cuti.\n";
    } else {
        cout << "Tidak ada aksi untuk di-undo.\n";
    }

    pop();
}

void tampilkanAntrianCuti(){
    system("cls");
    cout << "====================================================================\n";
    cout << "||              Antrian Cuti Karyawan                            ||\n";
    cout << "====================================================================\n";

    // Tampilkan siapa yang sedang cuti sekarang
    if(nipSedangCuti != 0){
        NodePTB* yCuti = search(root, nipSedangCuti);
        if(yCuti != nullptr)
            cout << ">> Sedang cuti : " << yCuti->nama
                 << " (NIP: " << nipSedangCuti << ")\n";
        cout << "--------------------------------------------------------------------\n";
    }

    if(depan == nullptr){
        cout << "Antrian kosong.\n";
    } else {
        cout << left << setw(6) << "No" << setw(12) << "NIP" << "Nama\n";
        cout << "--------------------------------------------------------------------\n";
        NodeQueue* current = depan;
        int no = 1;
        while(current != nullptr){
            cout << left << setw(6) << no++
                 << setw(12) << current->nip
                 << current->nama << " menunggu giliran cuti.\n";
            current = current->next;
        }
    }
    cout << "====================================================================\n";
}

void pop(){
    if(top == nullptr) return;
    NodeStack* del = top;
    top = top->next;
    delete del;
}

void push(string aksi, int id, string x){
    NodeStack* newNode = new NodeStack(id, x, aksi);
    newNode->next = top;
    top           = newNode;
}
