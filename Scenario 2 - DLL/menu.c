#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "buku.h"
#include "anggota.h"
#include "peminjaman.h"

// Menampilkan menu utama
void tampilkanMenuUtama() {
    printf("\n=== SISTEM MANAJEMEN PERPUSTAKAAN ===\n");
    printf("1. Kelola Buku\n");
    printf("2. Kelola Anggota\n");
    printf("3. Kelola Peminjaman\n");
    printf("4. Requirement Awal\n");
    printf("0. Keluar\n");
    printf("Pilihan: ");
}

// Menu untuk mengelola buku
void menuKelolaBuku(BukuList* list) {
    int pilihan;
    char judul[100];
    int stok;
    
    do {
    	system("cls");
        printf("\n=== KELOLA BUKU ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Hapus Buku\n");
        printf("3. Tampilkan Semua Buku\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                printf("Masukkan judul buku: ");
                scanf(" %[^\n]", judul);
                printf("Masukkan stok: ");
                scanf("%d", &stok);
                tambahBuku(list, judul, stok);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            case 2:
                printf("Masukkan judul buku yang akan dihapus: ");
                scanf(" %[^\n]", judul);
                hapusBuku(list, judul);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            case 3:
                tampilkanSemuaBuku(list);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
}

// Menu untuk mengelola anggota
void menuKelolaAnggota(AnggotaList* list) {
    int pilihan;
    char nama[100];
    char id[20];
    int prioritas;
    
    do {
    	system("cls");
        printf("\n=== KELOLA ANGGOTA ===\n");
        printf("1. Tambah Anggota\n");
        printf("2. Hapus Anggota\n");
        printf("3. Tampilkan Semua Anggota\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                printf("Masukkan nama anggota: ");
                scanf(" %[^\n]", nama);
                printf("Masukkan ID anggota: ");
                scanf(" %s", id);
                printf("Pilih prioritas (0=Masyarakat, 1=Mahasiswa, 2=Dosen): ");
                scanf("%d", &prioritas);
                if (prioritas < 0 || prioritas > 2) {
                    printf("Prioritas tidak valid.\n");
                    break;
                }
                tambahAnggota(list, nama, id, (Prioritas)prioritas);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            case 2:
                printf("Masukkan ID anggota yang akan dihapus: ");
                scanf(" %s", id);
                hapusAnggota(list, id);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            case 3:
                tampilkanSemuaAnggota(list);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
}

// Menu untuk mengelola peminjaman
void menuKelolaPeminjaman(PeminjamanList* peminjamanList, BukuList* bukuList, AnggotaList* anggotaList) {
    int pilihan;
    char judul[100];
    char id[20];
    
    do {
    	system("cls");
        printf("\n=== KELOLA PEMINJAMAN ===\n");
        printf("1. Tambah Peminjaman\n");
        printf("2. Proses Peminjaman\n");
        printf("3. Proses Pengembalian\n");
        printf("4. Batalkan Peminjaman\n");
        printf("5. Tampilkan Antrian Peminjaman\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1: {
                printf("Masukkan judul buku: ");
                scanf(" %[^\n]", judul);
                printf("Masukkan ID anggota: ");
                scanf(" %s", id);
                
                // Cari buku dan anggota
                Buku* buku = cariBuku(bukuList, judul);
                Anggota* anggota = cariAnggota(anggotaList, id);
                
                if (buku == NULL) {
                    printf("Buku tidak ditemukan.\n");
                    break;
                }
                if (anggota == NULL) {
                    printf("Anggota tidak ditemukan.\n");
                    break;
                }
                
                tambahPeminjam(peminjamanList, judul, id, anggota->prioritas);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            }
            case 2:
                prosesPeminjaman(peminjamanList, bukuList, anggotaList);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            case 3:
                prosesPengembalian(peminjamanList, bukuList, anggotaList);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            case 4: {
                printf("Masukkan judul buku: ");
                scanf(" %[^\n]", judul);
                printf("Masukkan ID anggota: ");
                scanf(" %s", id);
                batalkanPeminjaman(peminjamanList, judul, id);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            }
            case 5: {
                printf("Masukkan judul buku: ");
                scanf(" %[^\n]", judul);
                tampilkanAntrianPeminjaman(peminjamanList, judul);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
                getchar(); getchar();
                break;
            }
            case 0:
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
}

// Fungsi untuk menjalankan requirement awal/skenario pengujian 
void requirementAwal(PeminjamanList* peminjamanList, BukuList* bukuList, AnggotaList* anggotaList) {
	system("cls");
    printf("\n=== MENJALANKAN REQUIREMENT AWAL/SKENARIO PENGUJIAN ===\n");
    
    // a) Insert 2 buku dengan stok masing-masing 1
    printf("\n1. Menambahkan 2 buku (Buku1 dan Buku2) dengan stok masing-masing 1...\n");
    tambahBuku(bukuList, "Buku1", 1);
    tambahBuku(bukuList, "Buku2", 1);
    tampilkanSemuaBuku(bukuList);
    
    // b) Insert Anggota1 sebagai mahasiswa
    printf("\n2. Menambahkan Anggota1 sebagai mahasiswa...\n");
    tambahAnggota(anggotaList, "Anggota1", "A001", MAHASISWA);
    
    // c) Insert Dosen1 sebagai dosen
    printf("\n3. Menambahkan Dosen1 sebagai dosen...\n");
    tambahAnggota(anggotaList, "Dosen1", "D001", DOSEN);
    
    // d) Insert Umum1 sebagai masyarakat umum
    printf("\n4. Menambahkan Umum1 sebagai masyarakat umum...\n");
    tambahAnggota(anggotaList, "Umum1", "U001", MASYARAKAT);
    tampilkanSemuaAnggota(anggotaList);
    
    // e) Anggota1 meminjam Buku1
    printf("\n5. Anggota1 (mahasiswa) meminjam Buku1...\n");
    tambahPeminjam(peminjamanList, "Buku1", "A001", MAHASISWA);
    
    // f) Dosen1 meminjam Buku1
    printf("\n6. Dosen1 meminjam Buku1...\n");
    tambahPeminjam(peminjamanList, "Buku1", "D001", DOSEN);
    
    // g) Umum1 meminjam Buku1
    printf("\n7. Umum1 meminjam Buku1...\n");
    tambahPeminjam(peminjamanList, "Buku1", "U001", MASYARAKAT);
    
    // h) Umum1 meminjam Buku2
    printf("\n8. Umum1 meminjam Buku2...\n");
    tambahPeminjam(peminjamanList, "Buku2", "U001", MASYARAKAT);
    
    // Tampilkan antrian peminjaman
    printf("\n9. Menampilkan antrian peminjaman Buku1...\n");
    tampilkanAntrianPeminjaman(peminjamanList, "Buku1");
    printf("\n10. Menampilkan antrian peminjaman Buku2...\n");
    tampilkanAntrianPeminjaman(peminjamanList, "Buku2");
    
    // i) Proses peminjaman Buku1 (harusnya Dosen1 yang dapat)
    printf("\n11. Memproses peminjaman Buku1...\n");
    prosesPeminjaman(peminjamanList, bukuList, anggotaList);
    tampilkanSemuaBuku(bukuList);
    tampilkanAntrianPeminjaman(peminjamanList, "Buku1");
    
    // j) Dosen1 mengembalikan Buku1 (harusnya Anggota1 yang dapat berikutnya)
    printf("\n12. Dosen1 mengembalikan Buku1...\n");
    prosesPengembalian(peminjamanList, bukuList, anggotaList);
    tampilkanSemuaBuku(bukuList);
    tampilkanAntrianPeminjaman(peminjamanList, "Buku1");
    
    // k) Umum1 membatalkan peminjaman Buku2
    printf("\n13. Umum1 membatalkan peminjaman Buku2...\n");
    batalkanPeminjaman(peminjamanList, "Buku2", "U001");
    tampilkanAntrianPeminjaman(peminjamanList, "Buku2");
    
    printf("\n=== SKENARIO PENGUJIAN SELESAI ===\n");
    
    printf("\n\nPress ENTER untuk melanjutkan..\n");
    getchar(); getchar();
}

// ... (fungsi-fungsi menu lainnya sama dengan SLL version)
