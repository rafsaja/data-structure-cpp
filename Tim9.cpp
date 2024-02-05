#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <conio.h>


using namespace std;

struct KendaraanParkir {
    string platNomor;
    enum JenisKendaraan { Mobil, Motor, Truck } jenisKendaraan;
    string waktuMasuk;
    string waktuKeluar;
    int durasiParkir;
    double tarifParkir;
    bool statusParkir;
    int slotParkir;
    int tarifjam;
};

vector<KendaraanParkir> dataParkir;
int kapasitasParkir = 3;

void tampilkanSelamatDatang() {
    cout << "============================================" << endl;
    cout << "        SELAMAT DATANG DI PROGRAM PARKIR     " << endl;
    cout << "============================================" << endl;
}

int login() {
    std::string username, password;
    std::cout << "Masukkan username: ";
    std::cin >> username;

    std::cout << "Masukkan password: ";
    char ch;
    while ((ch = getch()) != '\r') {
        password.push_back(ch);
        std::cout << "*";
    }
    std::cout << std::endl;

    if (username == "123" && password == "123") {
        return 1; // Login berhasil
    } else {
        std::cout << "Password salah. Login gagal." << std::endl;
        return 0; // Password salah
    }
}

// Fungsi untuk menambah data kendaraan parkir
void tambahDataParkir() {
    KendaraanParkir kendaraan;

    cin.ignore();
    cout << "Plat Nomor: ";
    getline(cin, kendaraan.platNomor);

    int jenisKendaraan;
    cout << "Jenis Kendaraan (1: Mobil, 2: Motor, 3: Truck/bus): ";
    cin >> jenisKendaraan;
    kendaraan.jenisKendaraan = static_cast<KendaraanParkir::JenisKendaraan>(jenisKendaraan - 1);

    cout << "Waktu Masuk (hh:mm): ";
    cin >> kendaraan.waktuMasuk;

    stringstream ss(kendaraan.waktuMasuk);
    string jammasuk, menitmasuk;
    getline(ss, jammasuk, '.');
    getline(ss, menitmasuk);
    int jammasukk = stoi(jammasuk);
    int menitmasukk = stoi(menitmasuk);
    int totalmenitmasuk = (jammasukk * 60) + menitmasukk;

    cout << "Waktu Keluar (hh:mm): ";
    cin >> kendaraan.waktuKeluar;

    stringstream iss(kendaraan.waktuKeluar);
    string jamkeluar, menitkeluar;
    getline(iss, jamkeluar, '.');
    getline(iss, menitkeluar);
    int jamkeluarr = stoi(jamkeluar);
    int menitkeluarr = stoi(menitkeluar);
    int totalmenitkeluar = (jamkeluarr * 60) + menitkeluarr;

    kendaraan.durasiParkir = totalmenitkeluar - totalmenitmasuk;
    if(kendaraan.durasiParkir%60 !=0){
        kendaraan.tarifjam=kendaraan.durasiParkir/60;
    }
    else{
        kendaraan.tarifjam=kendaraan.durasiParkir/60;
    }

    // Menetapkan tarif parkir berdasarkan jenis kendaraan
    switch (kendaraan.jenisKendaraan) {
        case KendaraanParkir::Mobil:
            kendaraan.tarifParkir = 5000 * kendaraan.tarifjam;
            break;
        case KendaraanParkir::Motor:
            kendaraan.tarifParkir = 3000 * kendaraan.tarifjam;
            break;
        case KendaraanParkir::Truck:
            kendaraan.tarifParkir = 8000 * kendaraan.tarifjam;
            break;
        default:
            cout << "Jenis kendaraan tidak valid." << endl;
            return;
    }

    // Cek kapasitas parkir tersedia
    if (dataParkir.size() >= kapasitasParkir) {
        cout << "Kapasitas parkir penuh." << endl;
        return;
    }

    kendaraan.statusParkir = true;
    kendaraan.slotParkir = dataParkir.size() + 1;
    dataParkir.push_back(kendaraan);

    cout << "Data parkir berhasil ditambahkan." << endl;
}

// Fungsi untuk mencetak data kendaraan parkir
void cetakDataParkir() {
    if (dataParkir.empty()) {
        cout << "Belum ada data parkir." << endl;
        return;
    }

    cout << "============================================" << endl;
    cout << "          DATA KENDARAAN PARKIR           " << endl;
    cout << "============================================" << endl;

    cout << "+----+------------+------------------+--------------+---------------+----------------+------------------+" << endl;
    cout << "| No | Plat Nomor |  Jenis Kendaraan |  Waktu Masuk |  Waktu Keluar |  Durasi Parkir |    Tarif Parkir  |" << endl;
    cout << "+----+------------+------------------+--------------+---------------+----------------+------------------+" << endl;

    for (int i = 0; i < dataParkir.size(); i++) {
        cout << "| " << setw(2) << i + 1 << " | ";
        cout << setw(9) << right << dataParkir[i].platNomor << "  " << "|";
        cout << setw(16) << left << (dataParkir[i].jenisKendaraan == KendaraanParkir::Mobil ? "Mobil" :
            (dataParkir[i].jenisKendaraan == KendaraanParkir::Motor ? "Motor" : "Truck ")) << "  " << "|";
        cout << setw(12) << right << dataParkir[i].waktuMasuk << "  " << "|";
        cout << setw(13) << right << dataParkir[i].waktuKeluar << "  " << "|";
        cout << setw(8) << dataParkir[i].durasiParkir << " menit  " << "|";
        cout << setw(9) << "Rp " <<fixed << setprecision(2) << right << dataParkir[i].tarifParkir << "|" << endl;
    }
    cout << "+----+------------+------------------+--------------+---------------+----------------+---------------+" << endl;
}

// Fungsi untuk menghapus data kendaraan parkir
void hapusDataParkir() {
    if (dataParkir.empty()) {
        cout << "Belum ada data parkir." << endl;
        return;
    }

    int nomorData;
    cout << "Nomor data yang akan dihapus: ";
    cin >> nomorData;

    if (nomorData >= 1 && nomorData <= dataParkir.size()) {
        dataParkir.erase(dataParkir.begin() + nomorData - 1);
        cout << "Data parkir berhasil dihapus." << endl;
    }
    else {
        cout << "Nomor data tidak valid." << endl;
    }
}

// Fungsi untuk menghitung total pendapatan parkir
double hitungTotalPendapatan() {
    double totalPendapatan = 0;

    for (int i = 0; i < dataParkir.size(); i++) {
        totalPendapatan += dataParkir[i].tarifParkir;
    }

    return totalPendapatan;
}

int main() {
    tampilkanSelamatDatang();

    if (login()) {
        int pilihan;
        do {
            cout << "============================================" << endl;
            cout << "               MENU UTAMA                   " << endl;
            cout << "============================================" << endl;
            cout << "1. Tambah Data Parkir" << endl;
            cout << "2. Cetak Data Parkir" << endl;
            cout << "3. Hapus Data Parkir" << endl;
            cout << "4. Hitung Total Pendapatan Parkir" << endl;
            cout << "0. Keluar" << endl;
            cout << "Pilihan: ";
            cin >> pilihan;
            cout<< endl;

            switch (pilihan) {
            case 1:
                tambahDataParkir();
                break;
            case 2:
                cetakDataParkir();
                break;
            case 3:
                hapusDataParkir();
                break;
            case 4:
                cout << "Total pendapatan parkir: Rp " << hitungTotalPendapatan() << endl;
                break;
            case 0:
                cout << "Terima kasih." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
            }
        } while (pilihan != 0);
    }

    return 0;
}
