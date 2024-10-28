#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Pelanggan {
    int nomorAntrian;
    int waktuLayanan;
};

class Queue {
public:
    void enqueue(Pelanggan p) {
        q.push(p);
    }

    Pelanggan dequeue() {
        if (!q.empty()) {
            Pelanggan p = q.front();
            q.pop();
            return p;
        }
        return Pelanggan{-1, 0}; // Nilai default untuk indikasi kosong
    }

    bool isEmpty() {
        return q.empty();
    }

    int size() {
        return q.size();
    }

private:
    queue<Pelanggan> q;
};

void simulasiAntrian(Queue& antrian, int jumlahLoket);

int main() {
    Queue antrian;
    int jumlahPelanggan, waktuLayanan;
    int jumlahLoket = 3;

    cout << "Masukkan jumlah pelanggan: ";
    cin >> jumlahPelanggan;

    for (int i = 1; i <= jumlahPelanggan; i++) {
        cout << "Masukkan waktu layanan untuk pelanggan " << i << " (dalam menit): ";
        cin >> waktuLayanan;
        antrian.enqueue({i, waktuLayanan});
    }

    simulasiAntrian(antrian, jumlahLoket);

    return 0;
}

void simulasiAntrian(Queue& antrian, int jumlahLoket) {
    vector<int> loket(jumlahLoket, 0); // Waktu selesai setiap loket
    int totalWaktuTunggu = 0;
    int pelangganTerlayani = 0;

    while (!antrian.isEmpty()) {
        Pelanggan p = antrian.dequeue();
        
        // Cari loket dengan waktu selesai paling awal
        int loketTercepat = 0;
        for (int i = 1; i < jumlahLoket; i++) {
            if (loket[i] < loket[loketTercepat]) {
                loketTercepat = i;
            }
        }

        // Hitung waktu tunggu pelanggan
        int waktuTunggu = max(0, loket[loketTercepat] - pelangganTerlayani);
        totalWaktuTunggu += waktuTunggu;

        // Update waktu selesai loket tersebut
        loket[loketTercepat] += p.waktuLayanan;

        cout << "Pelanggan " << p.nomorAntrian << " dilayani di loket " << (loketTercepat + 1) << " dengan waktu tunggu " << waktuTunggu << " menit.\n";
        pelangganTerlayani++;
    }

    // Hitung dan tampilkan statistik
    cout << "\nStatistik Layanan:\n";
    cout << "Rata-rata waktu tunggu: " << (pelangganTerlayani ? totalWaktuTunggu / pelangganTerlayani : 0) << " menit.\n";
    cout << "Jumlah pelanggan terlayani: " << pelangganTerlayani << "\n";
    cout << "Sisa antrian: " << antrian.size() << "\n";
}
