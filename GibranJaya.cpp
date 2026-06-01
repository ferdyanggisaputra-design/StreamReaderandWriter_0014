#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <vector>
using namespace std;

// 1. STRUKTUR KELAS TOKOELEKTRONIK (OOP & ENKAPSULASI)
class TokoElektronik {
private:
    // Array berkapasitas 3 elemen untuk barang di etalase (Enkapsulasi)
    array<string, 3> etalase;

public:
    // Constructor untuk mengisi data awal secara otomatis
    TokoElektronik() {
        etalase[0] = "Laptop ASUS ROG";
        etalase[1] = "Smartphone Samsung S24";
        etalase[2] = "Smart TV LG 43 Inch";
    }

    // Method Public untuk mengambil produk berdasarkan nomorRak dengan Exception Handling
    string ambilProdukDariEtalase(size_t nomorRak) {
        try {
            // Menggunakan .at() untuk memicu out_of_range jika indeks tidak valid
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            // 2. MEKANISME EXCEPTION HANDLING (Melemparkan pesan error kustom)
            throw runtime_error("Gagal Mengambil Barang : Rak nomor [" + to_string(nomorRak) + "] kosong atau tidak tersedia!");
        }
    }
};

// 3. FITUR MANAJEMEN GUDANG BERBASIS FILE (CRUD & FILE I/O)
const string NAMA_FILE = "gudang.txt";

// Fungsi Helper untuk membaca semua barang dari file ke dalam vector
vector<string> bacaSemuaBarang() {
    vector<string> daftarBarang;
    ifstream fileInput(NAMA_FILE);
    string barang;
    
    if (fileInput.is_open()) {
        while (getline(fileInput, barang)) {
            if (!barang.empty()) {
                daftarBarang.push_back(barang);
            }
        }
        fileInput.close();
    }
    return daftarBarang;
}

// Fungsi Helper untuk menulis ulang vector barang kembali ke file
void tulisSemuaBarang(const vector<string>& daftarBarang) {
    ofstream fileOutput(NAMA_FILE, ios::out | ios::trunc);
    if (fileOutput.is_open()) {
        for (const auto& barang : daftarBarang) {
            fileOutput << barang << endl;
        }
        fileOutput.close();
    }
}

// [R] READ: Membaca dan menampilkan daftar barang secara otomatis
void tampilkanGudang() {
    vector<string> daftarBarang = bacaSemuaBarang();
    cout << "\n=== DAFTAR BARANG DI GUDANG (FILE I/O) ===" << endl;
    if (daftarBarang.empty()) {
        cout << "[Gudang Kosong / File Belum Dibuat]" << endl;
    } else {
        for (size_t i = 0; i < daftarBarang.size(); ++i) {
            cout << i + 1 << ". " << daftarBarang[i] << endl;
        }
    }
    cout << "==========================================" << endl;
}

// [C] CREATE: Menambahkan data barang baru ke dalam file .txt
void tambahBarang() {
    string barangBaru;
    cout << "\nMasukkan nama barang baru: ";
    cin.ignore();
    getline(cin, barangBaru);

    ofstream fileOutput(NAMA_FILE, ios::app); // Mode append (menambah di akhir)
    if (fileOutput.is_open()) {
        fileOutput << barangBaru << endl;
        fileOutput.close();
        cout << "Sukses: Barang \"" << barangBaru << "\" berhasil ditambahkan ke gudang!" << endl;
    } else {
        cout << "Error: Gagal membuka file gudang!" << endl;
    }
}

// [U] UPDATE: Memperbarui/mengubah data barang tertentu di dalam file
void updateBarang() {
    tampilkanGudang();
    vector<string> daftarBarang = bacaSemuaBarang();
    if (daftarBarang.empty()) return;

    size_t nomor;
    cout << "Pilih nomor barang yang ingin diubah: ";
    cin >> nomor;

    if (nomor > 0 && nomor <= daftarBarang.size()) {
        string barangBaru;
        cout << "Masukkan nama baru untuk \"" << daftarBarang[nomor - 1] << "\": ";
        cin.ignore();
        getline(cin, barangBaru);

        daftarBarang[nomor - 1] = barangBaru;
        tulisSemuaBarang(daftarBarang);
        cout << "Sukses: Data barang berhasil diperbarui!" << endl;
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
}

// [D] DELETE: Menghapus data barang dari dalam file .txt
void hapusBarang() {
    tampilkanGudang();
    vector<string> daftarBarang = bacaSemuaBarang();
    if (daftarBarang.empty()) return;

    size_t nomor;
    cout << "Pilih nomor barang yang ingin dihapus: ";
    cin >> nomor;

    if (nomor > 0 && nomor <= daftarBarang.size()) {
        cout << "Sukses: Barang \"" << daftarBarang[nomor - 1] << "\" berhasil dihapus!" << endl;
        daftarBarang.erase(daftarBarang.begin() + (nomor - 1));
        tulisSemuaBarang(daftarBarang);
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
}

// 4. SIMULASI ETALASE (PENGUJIAN EXCEPTION HANDLING)
void jalankanSimulasiEtalase(TokoElektronik& toko) {
    cout << "\n=== MEMULAI SIMULASI ETALASE ===" << endl;

    // Skenario 1: Pengambilan barang di rak indeks ke-1 (Harus sukses)
    cout << "\n[Skenario 1] Mencoba mengambil barang di rak indeks 1..." << endl;
    try {
        string barang = toko.ambilProdukDariEtalase(1);
        cout << "Hasil Skenario 1 (Sukses): Mengambil -> " << barang << endl;
    }
    catch (const runtime_error& e) {
        cout << "Hasil Skenario 1 (Gagal): " << e.what() << endl;
    }

    // Skenario 2: Pengambilan barang di rak indeks ke-5 (Harus gagal)
    cout << "\n[Skenario 2] Mencoba mengambil barang di rak indeks 5..." << endl;
    try {
        string barang = toko.ambilProdukDariEtalase(5);
        cout << "Hasil Skenario 2 (Sukses): Mengambil -> " << barang << endl;
    }
    catch (const runtime_error& e) {
        cout << "Hasil Skenario 2 (Tertangkap): " << e.what() << endl;
    }
    cout << "================================\n" << endl;
}

// MAIN FUNCTION (MENU UTAMA INTERAKTIF)
int main() {
    TokoElektronik tokoGibranJaya;
    int pilihanMenu;

    do {
        // Otomatis membaca dan menampilkan daftar barang dari file teks setiap kali menu dibuka
        tampilkanGudang();

        cout << "\n=== SISTEM MANAJEMEN TOKO ELEKTRONIK \"GIBRAN JAYA\" ===" << endl;
        cout << "1. Tambah Barang ke Gudang (Create)" << endl;
        cout << "2. Ubah Barang di Gudang (Update)" << endl;
        cout << "3. Hapus Barang dari Gudang (Delete)" << endl;
        cout << "4. Jalankan Simulasi Etalase (Exception Handling)" << endl;
        cout << "5. Keluar Aplikasi" << endl;
        cout << "Pilih menu (1-5): ";
        cin >> pilihanMenu;

        switch (pilihanMenu) {
            case 1:
                tambahBarang();
                break;
            case 2:
                updateBarang();
                break;
            case 3:
                hapusBarang();
                break;
            case 4:
                jalankanSimulasiEtalase(tokoGibranJaya);
                break;
            case 5:
                cout << "\nTerima kasih telah menggunakan sistem manajemen Gibran Jaya!" << endl;
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan masukkan angka 1-5." << endl;
        }
        
        if (pilihanMenu != 5) {
            cout << "\nTekan Enter untuk kembali ke menu utama...";
            cin.ignore();
            cin.get();
        }

    } while (pilihanMenu != 5);

    return 0;
}