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

