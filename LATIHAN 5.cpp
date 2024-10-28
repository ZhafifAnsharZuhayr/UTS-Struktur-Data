#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct Buku {
    string ISBN;
    string judul;
    string pengarang;
    int tahunTerbit;
};

// Stack untuk riwayat peminjaman buku
stack<Buku*> riwayatPeminjaman;

// Queue untuk antrian peminjaman buku
queue<Buku*> antrianPeminjaman;

void tambahBuku(vector<Buku*>& koleksi, Buku* buku);
void cariBuku(const vector<Buku*>& koleksi, const string& ISBN);
void tampilkanKoleksi(const vector<Buku*>& koleksi);
void pinjamBuku(vector<Buku*>& koleksi, const string& ISBN);
void kembalikanBuku();

int main() {
    vector<Buku*> koleksi;
    int pilihan;
    string ISBN;

    do {
        cout << "Menu:\n1. Tambah Buku\n2. Cari Buku\n3. Tampilkan Koleksi Buku\n4. Pinjam Buku\n5. Kembalikan Buku\n6. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                Buku* buku = new Buku;
                cout << "Masukkan ISBN: ";
                getline(cin, buku->ISBN);
                cout << "Masukkan Judul: ";
                getline(cin, buku->judul);
                cout << "Masukkan Pengarang: ";
                getline(cin, buku->pengarang);
                cout << "Masukkan Tahun Terbit: ";
                cin >> buku->tahunTerbit;
                cin.ignore();
                tambahBuku(koleksi, buku);
                break;
            }
            case 2:
                cout << "Masukkan ISBN untuk mencari: ";
                getline(cin, ISBN);
                cariBuku(koleksi, ISBN);
                break;
            case 3:
                tampilkanKoleksi(koleksi);
                break;
            case 4:
                cout << "Masukkan ISBN buku yang ingin dipinjam: ";
                getline(cin, ISBN);
                pinjamBuku(koleksi, ISBN);
                break;
            case 5:
                kembalikanBuku();
                break;
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    // Hapus data buku dari koleksi untuk menghindari memory leak
    for (Buku* buku : koleksi) {
        delete buku;
    }

    return 0;
}

void tambahBuku(vector<Buku*>& koleksi, Buku* buku) {
    koleksi.push_back(buku);
    cout << "Buku berhasil ditambahkan ke koleksi.\n";
}

void cariBuku(const vector<Buku*>& koleksi, const string& ISBN) {
    for (Buku* buku : koleksi) {
        if (buku->ISBN == ISBN) {
            cout << "Buku ditemukan:\n";
            cout << "ISBN: " << buku->ISBN << "\nJudul: " << buku->judul << "\nPengarang: " << buku->pengarang << "\nTahun Terbit: " << buku->tahunTerbit << endl;
            return;
        }
    }
    cout << "Buku dengan ISBN " << ISBN << " tidak ditemukan.\n";
}

void tampilkanKoleksi(const vector<Buku*>& koleksi) {
    cout << "Daftar Koleksi Buku:\n";
    for (Buku* buku : koleksi) {
        cout << "ISBN: " << buku->ISBN << ", Judul: " << buku->judul << ", Pengarang: " << buku->pengarang << ", Tahun Terbit: " << buku->tahunTerbit << endl;
    }
}

void pinjamBuku(vector<Buku*>& koleksi, const string& ISBN) {
    for (auto it = koleksi.begin(); it != koleksi.end(); ++it) {
        if ((*it)->ISBN == ISBN) {
            cout << "Buku \"" << (*it)->judul << "\" telah ditambahkan ke dalam antrian peminjaman.\n";
            antrianPeminjaman.push(*it);
            koleksi.erase(it);
            return;
        }
    }
    cout << "Buku dengan ISBN " << ISBN << " tidak ditemukan di koleksi.\n";
}

void kembalikanBuku() {
    if (!antrianPeminjaman.empty()) {
        Buku* buku = antrianPeminjaman.front();
        antrianPeminjaman.pop();
        riwayatPeminjaman.push(buku);
        cout << "Buku \"" << buku->judul << "\" telah dikembalikan dan dicatat dalam riwayat peminjaman.\n";
    } else {
        cout << "Tidak ada buku dalam antrian peminjaman.\n";
    }
}
