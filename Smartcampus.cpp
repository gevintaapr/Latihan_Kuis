#include <iostream>
#include <cstring>
using namespace std;

struct laporan{
    char nama[50];
    int nim;
    char jurusan[50];
    int thn_msk;
    float ipk;
};

laporan mhs[100];

laporan *ptr_lap = mhs;

void InputData();
void database();
void updateData();
void filterData();
void cariNim();
void quick_sort(laporan *ptr_lap, int awal, int akhir);
void binarySearch(laporan *ptr_lap, int banyak, int nim_cari);
void sequentialSearch(laporan *ptr_lap, int banyak);
void SimpanDataKeFile(laporan mhs[],int count);
void hapusData();


int count = 0;

FILE *countMhs;
FILE *data;
int cari_nim;

int main(){
    int menu;

    do{

        cout << "=========================================\n";
        cout << "|              SMARTCAMPUS++            |\n";
        cout << "=========================================\n";
        cout << "| 1. Input Data Mahasiswa               |\n";
        cout << "| 2. Database Mahasiswa                 |\n";
        cout << "| 3. Filter Data Mahasiswa              |\n";
        cout << "| 4. Pembaruan IPK Mahasiswa            |\n";
        cout << "| 5. Hapus Data Mahasiswa               |\n";
        cout << "| 6. Keluar SmartCampus++               |\n";
        cout << "=========================================\n\n";

        cout << "| Pilih Menu | : "; cin >> menu;
        cin.ignore();
        system("cls");

        switch (menu)
        {
        case 1:
            InputData();
            break;

        case 2:
            database();
            break;

        case 3:
            filterData();
            break;

        case 4:
            updateData();
            break;

        case 5:
            hapusData();
            break;

        case 6:
            exit(0);
            break;
        
        default:
        cout << "Pilihan tidak valid! silahkan coba lagi.";
            break;
        }

    } while (menu != 6);

    return 0;
}


void InputData(){
    int banyak;
   
    FILE *data = fopen("MahasiswaData.dat", "ab"); // Mode append binary

    if(data == NULL){
        cout << "Gagal membuka file!\n";
        return;
    }

    cout << "===============================================\n";
    cout << "|             INPUT DATA MAHASISWA            |\n";
    cout << "===============================================\n";
    cout << "| Input Banyak Mahasiswa : "; 
    cin >> banyak; cin.ignore();
    system("cls");

    for (int i = 0; i < banyak; i++) {
        cout << "-----------------------------------------\n";
        cout << "Data Mahasiswa Ke-" << i+1 << endl;
        cout << "-----------------------------------------\n";
        cout << "| Nama Lengkap : "; cin.getline(mhs[i].nama,50);
        cout << "| NIM          : "; cin >> mhs[i].nim; cin.ignore();
        cout << "| Jurusan      : "; cin.getline(mhs[i].jurusan,50);
        cout << "| Tahun Masuk  : "; cin >> mhs[i].thn_msk;
        cout << "| IPK          : "; cin >> mhs[i].ipk; cin.ignore();

        // Simpan ke file dalam format biner (binary write)
        fwrite(&mhs[i], sizeof(laporan), 1, data);
        count++;
    }

    // Simpan jumlah data ke file terpisah
    FILE *countMhs = fopen("JumlahData.txt", "w");
    fprintf(countMhs, "Count : %d\n", count);
    fclose(countMhs);

    fclose(data);
    cout << "| Data berhasil disimpan!\n";
    cin.ignore();
    system("cls");
}

void database(){

    countMhs = fopen("JumlahData.txt", "r");
    if (countMhs == NULL) {
        count = 0; // Jika file tidak ada, set count = 0
    } else {
        fscanf(countMhs, "Count : %d", &count);
        fclose(countMhs);
    }

    FILE *data = fopen("MahasiswaData.dat", "rb");
    fread(mhs, sizeof(laporan), count, data);

    if(data == NULL){
        cout << "Gagal membuka file\n";
        return;
    } else {
        cout << "=========================================\n";
        cout << "|           DATABASE MAHASISWA          |\n";
        cout << "=========================================\n";

        for (int i = 0; i < count; i++)
        {
            cout << "|Data " << i+1 << "                                 |\n";
            cout << "-----------------------------------------\n";
            cout << "| Nama Lengkap : " << mhs[i].nama << endl;
            cout << "| NIM          : " << mhs[i].nim << endl;
            cout << "| Jurusan      : " << mhs[i].jurusan << endl;
            cout << "| Tahun Masuk  : " << mhs[i].thn_msk << endl;
            cout << "| IPK          : " << mhs[i].ipk << endl;
            cout << "-----------------------------------------\n";
        }

        fclose(countMhs);
        
    }
    fclose(data);
    cin.ignore();
    system("cls");
}

void filterData(){
    int pil;

    do {
        cout << "=========================================\n";
        cout << "|         FILTER DATA MAHASISWA         |\n";
        cout << "=========================================\n";
        cout << "| 1. Cari Berdasarkan NIM               |\n";
        cout << "| 2. Cari Berdasarkan Jurusan           |\n";
        cout << "| 3. Kembali ke Menu Utama              |\n";
        cout << "=========================================\n";
        cout << "| Pilih | : "; cin >> pil; cin.ignore();
        system("cls");

        switch (pil)
        {
        case 1:
            cariNim();
            break;

        case 2:
            sequentialSearch(mhs, count);
            break;

        case 3:
            return;
            break;
        
        default:
            cout << "Pilihan tidak sesuai! silakkan pilih kembali.\n";
            break;
        }
    } while (pil != 3);

}

void cariNim(){
    int nim_cari;

    countMhs = fopen("JumlahData.txt", "r");
if (countMhs == NULL) 
    count = 0; 
// } else {
//     fscanf(countMhs, "Count : %d", &count);
//     fclose(countMhs);
// }

    data = fopen("MahasiswaData.dat", "rb");
    fread(mhs, sizeof(laporan), count, data);

    cout << "=========================================\n";
    cout << "|           CARI NIM MAHASISWA          |\n";
    cout << "=========================================\n";
    cout << "| Masukkan NIM yang dicari | : "; cin >> nim_cari;
    cin.ignore();

    quick_sort(mhs, 0, count - 1);
    binarySearch(mhs, count, nim_cari);

    fclose(countMhs);
    cin.ignore();
    system("cls");   
}

void quick_sort(laporan *ptr_lap, int awal, int akhir) {
    int low = awal, high = akhir;
    int pivot = mhs[(awal + akhir) / 2].nim;

    do {
        while (mhs[low].nim < pivot) low++;
        while (mhs[high].nim > pivot) high--;

        if (low <= high) {
            swap(mhs[low], mhs[high]);
            low++;
            high--;
        }
    } while (low <= high);

    if (awal < high)
        quick_sort(mhs, awal, high);
    if (low < akhir)
        quick_sort(mhs, low, akhir);
}

void binarySearch(laporan *ptr_lap, int banyak, int cari_nim) {
    bool found = false;
    int awal = 0, akhir = banyak - 1, tengah;

    while ((!found) && awal <= akhir) {
        tengah = (awal + akhir) / 2;
        if (cari_nim == mhs[tengah].nim) {
            found = true;
        } else {
            if (cari_nim < mhs[tengah].nim) akhir = tengah - 1;
            else awal = tengah + 1;
        }
    }

    if (found) {
        cout << "Status : Data tersedia\n";
        cout << "-----------------------------------------\n";
        cout << "| Nama Lengkap : " << mhs[tengah].nama << endl;
        cout << "| NIM          : " << mhs[tengah].nim << endl;
        cout << "| Jurusan      : " << mhs[tengah].jurusan << endl;
        cout << "| Tahun Masuk  : " << mhs[tengah].thn_msk << endl;
        cout << "| IPK          : " << mhs[tengah].ipk << endl;
        cout << "-----------------------------------------\n";
    } else {
        cout << "Status : Data Tidak Tersedia\n";
    }
}

void sequentialSearch(laporan *ptr_lap, int banyak){
    int i=0;
    char jur_cari[50];
    int hasil = 0;
    bool found = false;

    cout << "==========================================\n";
    cout << "|               CARI JURUSAN             |\n";
    cout << "==========================================\n"; 
    cout << " Data Jurusan : "; cin.getline(jur_cari, 50);
    
    for (int i = 0; i < banyak; i++) {
        if (strcmp(mhs[i].jurusan, jur_cari) == 0) {  // Gunakan strcmp() untuk membandingkan string
            found = true;
            cout << "Status : Data tersedia\n";
            cout << "-----------------------------------------\n";
            cout << "| Nama Lengkap : " << mhs[i].nama << endl;
            cout << "| NIM          : " << mhs[i].nim << endl;
            cout << "| Jurusan      : " << mhs[i].jurusan << endl;
            cout << "| Tahun Masuk  : " << mhs[i].thn_msk << endl;
            cout << "| IPK          : " << mhs[i].ipk << endl;
            cout << "-----------------------------------------\n";
        }
    }

    if (!found) {
        cout << "Status : Data tidak tersedia\n";
    }
}

void updateData(){
    int nim_ganti;
    float ipk_baru;
    bool found = false;

    countMhs = fopen("JumlahData.txt", "r");
    if (countMhs != NULL) {
        fscanf(countMhs, "Count : %d", &count);
        fclose(countMhs);
    }

    FILE *data = fopen("MahasiswaData.dat", "rb+");
    if (data == NULL) {
        cout << "Gagal membuka file!\n";
        return;
    }

    fread(mhs, sizeof(laporan), count, data);

    cout << "=========================================\n";
    cout << "|       PERBARUI DATA IPK MAHASISWA     |\n";
    cout << "=========================================\n";
    cout << "| Masukkan NIM Mahasiswa : "; cin >> nim_ganti;

    do
    {
        for (int i = 0; i < count; i++) {
            if (mhs[i].nim == nim_ganti) {
                cout << "| Nama Mahasiswa    : " << mhs[i].nama << endl;
                cout << "| IPK Saat Ini      : " << mhs[i].ipk << endl;
                cout << "| Masukkan IPK Baru : "; cin >> ipk_baru;
    
                if(ipk_baru < 0.0 || ipk_baru > 4.0){
                    cout << "IPK hanya boleh dalam rentang 0.0 - 4.0\n";
                    cin.ignore();
                    system("cls");
                } else
                mhs[i].ipk = ipk_baru;
                found = true;
                break;
            }
        }
    } while (ipk_baru >= 0.0 || ipk_baru <= 4.0);
    

    if (found) {
        rewind(data); // abis ganti data (nulis baru) buat balikin dia ke posisi awal u/ baca ulang
        fwrite(mhs, sizeof(laporan), count, data);
        cout << "\n| IPK berhasil diperbarui! |\n";
    } else {
        cout << "\n| Mahasiswa tidak ditemukan! |\n";
    }

    fclose(data);
}

void hapusData(){
    int nim_hapus;
    bool ditemukan = false;

    cout << "=========================================\n";
    cout << "|          HAPUS DATA MAHASISWA         |\n";
    cout << "=========================================\n";
    cout << "| Masukkan NIM Mahasiswa : "; cin >> nim_hapus;
    cin.ignore();

    data = fopen("MahasiswaData.dat", "rb");
    if(data == NULL){
        cout << "Gagal Membuka File\n\n";
        return;
    }

    countMhs = fopen("JumlahData.txt", "r");
    if(countMhs == NULL){
        cout << "Gagal Membuka File\n\n";
        return;
    }

    fscanf(countMhs, "Count : %d", &count);
    fclose(countMhs);

    laporan mhs[100];
    fread(mhs, sizeof(laporan), count, data);
    fclose(data);


    for (int i = 0; i < count; i++)
    {
        if(mhs[i].nim == nim_hapus){
            ditemukan = true;

            for(int j = i; j < count - 1; j++) {
                mhs[j] = mhs[j+1] ;        
            }

            count--;
            cout << "Data Mahasiswa dengan NIM " << nim_hapus << " berhasil di hapus!\n";
        } 

        if (!ditemukan) {
            cout << "Data mahasiswa dengan NIM " << nim_hapus << " tidak ditemukan!\n";
        }
    
    }

    SimpanDataKeFile(mhs, count);

    cin.ignore();
    system("cls");
}

void SimpanDataKeFile(laporan mhs[],int count){
    data = fopen("MahasiswaData.dat", "wb");

    if(data == NULL) {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }

        fwrite(&mhs, sizeof(laporan), 1, data);
    
    fclose(data);
    cout << "Data berhasil diperbarui di file\n";

}

