#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>
using namespace std;

struct Kendaraan {
    string platNomor;
    string jenisKendaraan;
    string jenisModel;
    string merk;
    int jamMasuk;
    int menitMasuk;
};

const int MAKS_SLOT_PARKIR = 10;
Kendaraan slotParkir[MAKS_SLOT_PARKIR];

void siapkanDataParkir() {
    for(int i = 0; i < MAKS_SLOT_PARKIR; i++) {
        slotParkir[i].platNomor = "kosong";
        slotParkir[i].jenisKendaraan = "kosong";
        slotParkir[i].jenisModel = "kosong";
        slotParkir[i].merk = "kosong";
        slotParkir[i].jamMasuk = -1;
        slotParkir[i].menitMasuk = -1;
    }
}

void tungguEnter() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void tampilkanStatusParkir() {
    system("cls"); 
    cout << "\n--- KONDISI PARKIR SAAT INI ---" << endl;
    for (int i = 0; i < MAKS_SLOT_PARKIR; ++i) {
        cout << "Slot " << (i + 1) << ": ";
        if (slotParkir[i].platNomor == "kosong") {
            cout << "KOSONG" << endl;
        } else {
            cout << "Terisi - Plat: " << slotParkir[i].platNomor
                      << ", Jenis: " << slotParkir[i].jenisKendaraan
                      << ", Model: " << slotParkir[i].jenisModel
                      << ", Merk: " << slotParkir[i].merk
                      << ", Masuk: " << slotParkir[i].jamMasuk << ":"
                      << (slotParkir[i].menitMasuk < 10 ? "0" : "") << slotParkir[i].menitMasuk << endl;
        }
    }
    cout << "-----------------------------" << endl;
    tungguEnter(); 
}

void tambahKendaraan() {
    system("cls"); 
    string plat, kendaraan, model, merkKendaraan;
    int jam, menit;

    cout << "\n--- TAMBAH KENDARAAN ---" << endl;
    cout << "Plat Nomor: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, plat);

    cout << "Jenis Kendaraan (Mobil/Motor): ";
    getline(cin, kendaraan);

    cout << "Jenis Model (misal: Sedan/Matic): ";
    getline(cin, model);

    cout << "Merk Kendaraan: ";
    getline(cin, merkKendaraan);

    cout << "Jam Masuk (0-23): ";
    cin >> jam;
    cout << "Menit Masuk (0-59): ";
    cin >> menit;

    int slotKosong = -1;
    for (int i = 0; i < MAKS_SLOT_PARKIR; ++i) {
        if (slotParkir[i].platNomor == "kosong") {
            slotKosong = i;
            break;
        }
    }

    if (slotKosong != -1) {
        slotParkir[slotKosong].platNomor = plat;
        slotParkir[slotKosong].jenisKendaraan = kendaraan;
        slotParkir[slotKosong].jenisModel = model;
        slotParkir[slotKosong].merk = merkKendaraan;
        slotParkir[slotKosong].jamMasuk = jam;
        slotParkir[slotKosong].menitMasuk = menit;
        cout << "Kendaraan " << plat << " (" << kendaraan << ") berhasil diparkir di slot " << (slotKosong + 1) << endl;
    } else {
        cout << "Maaf, parkir penuh!" << endl;
    }
    tungguEnter(); 
}

int cariKendaraan(const string& plat) {
    for (int i = 0; i < MAKS_SLOT_PARKIR; ++i) {
        if (slotParkir[i].platNomor == plat) {
            return i;
        }
    }
    return -1;
}

void keluarKendaraan() {
    system("cls"); 
    string plat;
    int jamKeluar, menitKeluar;

    cout << "\n--- KELUAR KENDARAAN ---" << endl;
    cout << "Plat Nomor kendaraan yang keluar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, plat);

    int indeksDitemukan = cariKendaraan(plat);

    if (indeksDitemukan != -1) {
        cout << "Kendaraan ditemukan di slot " << (indeksDitemukan + 1) << endl;
        cout << "Detail: Plat: " << slotParkir[indeksDitemukan].platNomor
             << ", Jenis: " << slotParkir[indeksDitemukan].jenisKendaraan
             << ", Model: " << slotParkir[indeksDitemukan].jenisModel
             << ", Merk: " << slotParkir[indeksDitemukan].merk
             << ", Masuk: " << slotParkir[indeksDitemukan].jamMasuk << ":"
             << (slotParkir[indeksDitemukan].menitMasuk < 10 ? "0" : "") << slotParkir[indeksDitemukan].menitMasuk << endl;

        cout << "Jam Keluar (0-23): ";
        cin >> jamKeluar;
        cout << "Menit Keluar (0-59): ";
        cin >> menitKeluar;

        int totalMenitMasuk = (slotParkir[indeksDitemukan].jamMasuk * 60) + slotParkir[indeksDitemukan].menitMasuk;
        int totalMenitKeluar = (jamKeluar * 60) + menitKeluar;

        int durasiMenit = totalMenitKeluar - totalMenitMasuk;

        if (durasiMenit < 0) {
            durasiMenit += (24 * 60);
        }

        int durasiJam = durasiMenit / 60;
        int sisaMenit = durasiMenit % 60;

        double tarifPerJamMobil = 3000.0;
        double tarifPerJamMotor = 1500.0;
        double biayaParkir = 0.0;

        int jamDihitung = durasiJam;
        if (sisaMenit > 0) {
            jamDihitung++;
        }

        if (slotParkir[indeksDitemukan].jenisKendaraan == "Mobil") {
            biayaParkir = jamDihitung * tarifPerJamMobil;
        } else if (slotParkir[indeksDitemukan].jenisKendaraan == "Motor") {
            biayaParkir = jamDihitung * tarifPerJamMotor;
        } else {
            cout << "Jenis kendaraan tidak dikenali, biaya parkir dihitung default (tarif mobil)." << endl;
            biayaParkir = jamDihitung * tarifPerJamMobil;
        }

        cout << "\n--- RINCIAN BIAYA PARKIR---" << endl;
        cout << "Durasi Parkir: " << durasiJam << " jam " << sisaMenit << " menit" << endl;
        cout << "Total Biaya Parkir: Rp " << fixed << setprecision(0) << biayaParkir << endl;

        slotParkir[indeksDitemukan].platNomor = "kosong";
        slotParkir[indeksDitemukan].jenisKendaraan = "kosong";
        slotParkir[indeksDitemukan].jenisModel = "kosong";
        slotParkir[indeksDitemukan].merk = "kosong";
        slotParkir[indeksDitemukan].jamMasuk = -1;
        slotParkir[indeksDitemukan].menitMasuk = -1;

        cout << "Slot " << (indeksDitemukan + 1) << " kosong." << endl;

    } else {
        cout << "Kendaraan dengan plat " << plat << " tidak ditemukan." << endl;
    }
    tungguEnter(); 
}

int hitungKendaraanParkirRekursif(int indeks) {
    if (indeks >= MAKS_SLOT_PARKIR) {
        return 0;
    }

    if (slotParkir[indeks].platNomor != "kosong") {
        return 1 + hitungKendaraanParkirRekursif(indeks + 1);
    } else {
        return hitungKendaraanParkirRekursif(indeks + 1);
    }
}

void tukarKendaraan(Kendaraan* a, Kendaraan* b) {
    Kendaraan temp = *a;
    *a = *b;
    *b = temp;
}

void urutkanKendaraan() {
    system("cls"); 
    cout << "\n--- MENGURUTKAN KENDARAAN BERDASARKAN JENIS DAN PLAT NOMOR ---" << endl;
    for (int i = 0; i < MAKS_SLOT_PARKIR - 1; ++i) {
        for (int j = 0; j < MAKS_SLOT_PARKIR - i - 1; ++j) {

            if (slotParkir[j].platNomor != "kosong" && slotParkir[j+1].platNomor != "kosong") {

                string jenis1 = slotParkir[j].jenisKendaraan;
                string jenis2 = slotParkir[j+1].jenisKendaraan;
                bool perluTukar = false;

                if (jenis1 == "Mobil" && jenis2 == "Motor") {
                    perluTukar = true;
                } else if (jenis1 == jenis2) {

                    if (slotParkir[j].platNomor > slotParkir[j+1].platNomor) {
                        perluTukar = true;
                    }
                }

                if (perluTukar) {
                    tukarKendaraan(&slotParkir[j], &slotParkir[j+1]);
                }
            } else if (slotParkir[j].platNomor == "kosong" && slotParkir[j+1].platNomor != "kosong") {
                tukarKendaraan(&slotParkir[j], &slotParkir[j+1]);
            }
        }
    }
    cout << "Parkir berhasil diurutkan berdasarkan jenis kendaraan dan plat nomor." << endl;
    tungguEnter(); 
    tampilkanStatusParkir(); 
}

void simpanDataParkir(const string& namaFile) {
    system("cls"); 
    ofstream fileOutput(namaFile);

    if (fileOutput.is_open()) {
        for (int i = 0; i < MAKS_SLOT_PARKIR; ++i) {
            fileOutput << slotParkir[i].platNomor << endl;
            fileOutput << slotParkir[i].jenisKendaraan << endl;
            fileOutput << slotParkir[i].jenisModel << endl;
            fileOutput << slotParkir[i].merk << endl;
            fileOutput << slotParkir[i].jamMasuk << endl;
            fileOutput << slotParkir[i].menitMasuk << endl;
        }
        cout << "Data parkir berhasil disimpan ke " << namaFile << endl;
        fileOutput.close();
    } else {
        cout << "Gagal menyimpan data ke file." << endl;
    }
    tungguEnter(); 
}

void muatDataParkir(const string& namaFile) {
    ifstream fileInput(namaFile); 

    if (fileInput.is_open()) { 
        for (int i = 0; i < MAKS_SLOT_PARKIR; ++i) {
            getline(fileInput, slotParkir[i].platNomor);
            getline(fileInput, slotParkir[i].jenisKendaraan);
            getline(fileInput, slotParkir[i].jenisModel);
            getline(fileInput, slotParkir[i].merk);
            fileInput >> slotParkir[i].jamMasuk;
            fileInput >> slotParkir[i].menitMasuk;
            fileInput.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        fileInput.close(); 
    } else {
        siapkanDataParkir();
    }
}

void Menu() {
    system("cls"); 
    cout << "\n--- SISTEM INFORMASI PARKIR ---" << endl;
    cout << "--- Mall Informatika Bukan Wibu ---" << endl;
    cout << "1. Kendaraan Masuk Parkir" << endl;
    cout << "2. Kendaraan Keluar" << endl;
    cout << "3. Slot Parkir Tersedia" << endl;
    cout << "4. Mencari Kendaraan (Berdasarkan Plat Nomor)" << endl;
    cout << "5. Total Kendaraan Parkir" << endl;
    cout << "6. Urutkan Kendaraan (Berdasarkan Jenis Kendaraan)" << endl;
    cout << "7. Simpan Data (ke file)" << endl;
    cout << "8. Muat Data (dari file)" << endl;
    cout << "9. Keluar" << endl;
    cout << "Pilih Opsi: ";
}

int main() {
    muatDataParkir("data_parkir.txt");

    int pilihan;
    do {
        Menu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahKendaraan();
                break;
            case 2:
                keluarKendaraan();
                break;
            case 3:
                tampilkanStatusParkir(); 
                break;
            case 4: {
                system("cls"); 
                string platCari;
                cout << "Plat Nomor yang dicari: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, platCari);
                int indeksDitemukan = cariKendaraan(platCari);
                if (indeksDitemukan != -1) {
                    cout << "Kendaraan ditemukan di slot " << (indeksDitemukan + 1) << endl;
                    cout << "Detail: Plat: " << slotParkir[indeksDitemukan].platNomor
                         << ", Jenis: " << slotParkir[indeksDitemukan].jenisKendaraan
                         << ", Model: " << slotParkir[indeksDitemukan].jenisModel
                         << ", Merk: " << slotParkir[indeksDitemukan].merk << endl;
                } else {
                    cout << "Kendaraan tidak ditemukan." << endl;
                }
                tungguEnter(); 
                break;
            }
            case 5: {
                system("cls"); 
                cout << "\nTotal kendaraan yang sedang parkir: "
                          << hitungKendaraanParkirRekursif(0) << endl;
                tungguEnter(); 
                break;
            }
            case 6:
                urutkanKendaraan();
                break;
            case 7:
                simpanDataParkir("data_parkir.txt");
                break;
            case 8:
                muatDataParkir("data_parkir.txt");
                break;
            case 9:
                system("cls"); 
                cout << "Terima kasih! Kami Menunggu kedatangan Anda selanjutnya." << endl;
                break;
            default:
                cout << "Pilihanmu tidak valid." << endl;
                tungguEnter(); 
                break;
        }
    } while (pilihan != 9);

    return 0;
}
