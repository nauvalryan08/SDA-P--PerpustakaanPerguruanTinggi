#ifndef BUKU_H
#define BUKU_H

#include "anggota.h" // Diperlukan untuk Prioritas

#define MAX_BUKU 100 // Maksimal buku yang dapat disimpan

// ADT untuk menyimpan informasi buku
typedef struct {
    char judul[100];
    int stok;
    int dipinjam; // jumlah yang sedang dipinjam
} Buku;

// Node untuk Queue Linked List peminjam
typedef struct PeminjamNode {
    char idAnggota[20];
    Prioritas prioritas;
    struct PeminjamNode* next;
} PeminjamNode;

// Queue untuk antrian peminjam per buku
typedef struct {
    PeminjamNode* head;
    PeminjamNode* tail;
    int size;
} PeminjamQueue;

// Array of Struct untuk buku dengan queue peminjam
typedef struct {
    Buku data[MAX_BUKU];
    PeminjamQueue peminjam[MAX_BUKU]; // Queue peminjam untuk setiap buku
    int size; // Jumlah buku yang terisi
} BukuArray;

// Fungsi-fungsi ADT Buku
void initBukuArray(BukuArray* array);
int tambahBuku(BukuArray* array, const char* judul, int stok);
Buku* cariBuku(BukuArray* array, const char* judul);
void tampilkanSemuaBuku(BukuArray* array);
int hapusBuku(BukuArray* array, const char* judul);
void freeBukuArray(BukuArray* array);

#endif
