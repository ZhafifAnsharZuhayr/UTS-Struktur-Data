#include <iostream>
#include <string>

using namespace std;

struct Mahasiswa {
    string NIM;
    string nama;
    float IPK;
};

void tambahMahasiswa(Mahasiswa* mahasiswa[], int& jumlah);
void hapusMahasiswa(Mahasiswa* mahasiswa[], int& jumlah, string nim);
void tampilkanMahasiswa(Mahasiswa* mahasiswa[], int jumlah);
void urutkanMahasiswa(Mahasiswa* mahasiswa[], int jumlah);

int main() {
    const int MAX = 10;
    Mahasiswa* mahasiswa[MAX] = {nullptr};
    int jumlah = 0;
    
    // Menu utama
    int pilihan;
    do {
        cout << "Menu:\n1. Tambah Mahasiswa\n2. Hapus Mahasiswa\n3. Tampilkan Mahasiswa\n4. Urutkan Mahasiswa\n5. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tambahMahasiswa(mahasiswa, jumlah);
                break;
            case 2: {
                string nim;
                cout << "Masukkan NIM untuk dihapus: ";
                getline(cin, nim);
                hapusMahasiswa(mahasiswa, jumlah, nim);
                break;
            }
            case 3:
                tampilkanMahasiswa(mahasiswa, jumlah);
                break;
            case 4:
                urutkanMahasiswa(mahasiswa, jumlah);
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    // Hapus semua data mahasiswa untuk membersihkan memori
    for (int i = 0; i < jumlah; i++) {
        delete mahasiswa[i];
    }

    return 0;
}

void tambahMahasiswa(Mahasiswa* mahasiswa[], int& jumlah) {
    if (jumlah < 10) {
        mahasiswa[jumlah] = new Mahasiswa;
        cout << "Masukkan NIM: ";
        getline(cin, mahasiswa[jumlah]->NIM);
        cout << "Masukkan Nama: ";
        getline(cin, mahasiswa[jumlah]->nama);
        cout << "Masukkan IPK: ";
        cin >> mahasiswa[jumlah]->IPK;
        cin.ignore();

        jumlah++;
    } else {
        cout << "Kapasitas penuh, tidak bisa menambah mahasiswa.\n";
    }
}

void hapusMahasiswa(Mahasiswa* mahasiswa[], int& jumlah, string nim) {
    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++) {
        if (mahasiswa[i]->NIM == nim) {
            delete mahasiswa[i];
            for (int j = i; j < jumlah - 1; j++) {
                mahasiswa[j] = mahasiswa[j + 1];
            }
            mahasiswa[jumlah - 1] = nullptr;
            jumlah--;
            ditemukan = true;
            cout << "Mahasiswa dengan NIM " << nim << " berhasil dihapus.\n";
            break;
        }
    }
    if (!ditemukan) {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

void tampilkanMahasiswa(Mahasiswa* mahasiswa[], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        cout << "NIM: " << mahasiswa[i]->NIM << ", Nama: " << mahasiswa[i]->nama << ", IPK: " << mahasiswa[i]->IPK << endl;
    }
}

void urutkanMahasiswa(Mahasiswa* mahasiswa[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (mahasiswa[j]->IPK < mahasiswa[j + 1]->IPK) {
                Mahasiswa* temp = mahasiswa[j];
                mahasiswa[j] = mahasiswa[j + 1];
                mahasiswa[j + 1] = temp;
            }
        }
    }
    cout << "Data mahasiswa telah diurutkan berdasarkan IPK.\n";
}
