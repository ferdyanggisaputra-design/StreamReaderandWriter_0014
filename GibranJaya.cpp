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

