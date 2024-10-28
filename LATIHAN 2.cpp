#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Peralatan {
    string kode;
    string nama;
    int jumlah;
    string kondisi;
};

// Fungsi untuk menambah data peralatan ke dalam vector dan file
void tambahPeralatan(vector<Peralatan>& inventaris);
void ubahPeralatan(vector<Peralatan>& inventaris, string kode);
void hapusPeralatan(vector<Peralatan>& inventaris, string kode);
void simpanKeFile(const vector<Peralatan>& inventaris, const string& namaFile);
void bacaDariFile(vector<Peralatan>& inventaris, const string& namaFile);
void tampilkanInventaris(const vector<Peralatan>& inventaris);

int main() {
    vector<Peralatan> inventaris;
    string namaFile = "inventaris.txt";
    
    // Membaca data dari file jika ada
    bacaDariFile(inventaris, namaFile);

    // Menu utama
    int pilihan;
    do {
        cout << "Menu:\n1. Tambah Peralatan\n2. Ubah Peralatan\n3. Hapus Peralatan\n4. Tampilkan Inventaris\n5. Simpan & Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tambahPeralatan(inventaris);
                break;
            case 2: {
                string kode;
                cout << "Masukkan kode peralatan yang ingin diubah: ";
                getline(cin, kode);
                ubahPeralatan(inventaris, kode);
                break;
            }
            case 3: {
                string kode;
                cout << "Masukkan kode peralatan yang ingin dihapus: ";
                getline(cin, kode);
                hapusPeralatan(inventaris, kode);
                break;
            }
            case 4:
                tampilkanInventaris(inventaris);
                break;
            case 5:
                simpanKeFile(inventaris, namaFile);
                cout << "Data telah disimpan. Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}

void tambahPeralatan(vector<Peralatan>& inventaris) {
    Peralatan alat;
    cout << "Masukkan kode peralatan: ";
    getline(cin, alat.kode);
    cout << "Masukkan nama peralatan: ";
    getline(cin, alat.nama);
    cout << "Masukkan jumlah: ";
    cin >> alat.jumlah;
    cin.ignore();
    cout << "Masukkan kondisi: ";
    getline(cin, alat.kondisi);
    inventaris.push_back(alat);
    cout << "Peralatan berhasil ditambahkan.\n";
}

void ubahPeralatan(vector<Peralatan>& inventaris, string kode) {
    for (auto& alat : inventaris) {
        if (alat.kode == kode) {
            cout << "Masukkan nama peralatan baru: ";
            getline(cin, alat.nama);
            cout << "Masukkan jumlah baru: ";
            cin >> alat.jumlah;
            cin.ignore();
            cout << "Masukkan kondisi baru: ";
            getline(cin, alat.kondisi);
            cout << "Data peralatan berhasil diubah.\n";
            return;
        }
    }
    cout << "Peralatan dengan kode " << kode << " tidak ditemukan.\n";
}

void hapusPeralatan(vector<Peralatan>& inventaris, string kode) {
    auto it = remove_if(inventaris.begin(), inventaris.end(), [&](const Peralatan& alat) {
        return alat.kode == kode;
    });
    if (it != inventaris.end()) {
        inventaris.erase(it, inventaris.end());
        cout << "Peralatan dengan kode " << kode << " berhasil dihapus.\n";
    } else {
        cout << "Peralatan dengan kode " << kode << " tidak ditemukan.\n";
    }
}

void simpanKeFile(const vector<Peralatan>& inventaris, const string& namaFile) {
    ofstream file(namaFile);
    for (const auto& alat : inventaris) {
        file << alat.kode << "\n" << alat.nama << "\n" << alat.jumlah << "\n" << alat.kondisi << "\n";
    }
    file.close();
}

void bacaDariFile(vector<Peralatan>& inventaris, const string& namaFile) {
    ifstream file(namaFile);
    if (file) {
        Peralatan alat;
        while (getline(file, alat.kode)) {
            getline(file, alat.nama);
            file >> alat.jumlah;
            file.ignore();
            getline(file, alat.kondisi);
            inventaris.push_back(alat);
        }
        file.close();
    }
}

void tampilkanInventaris(const vector<Peralatan>& inventaris) {
    auto sortedInventaris = inventaris;
    sort(sortedInventaris.begin(), sortedInventaris.end(), [](const Peralatan& a, const Peralatan& b) {
        return a.kode < b.kode;
    });
    for (const auto& alat : sortedInventaris) {
        cout << "Kode: " << alat.kode << ", Nama: " << alat.nama << ", Jumlah: " << alat.jumlah << ", Kondisi: " << alat.kondisi << endl;
    }
}
