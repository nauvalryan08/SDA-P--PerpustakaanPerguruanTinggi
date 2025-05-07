#ifndef PEMINJAMAN_H
#define PEMINJAMAN_H

#include "anggota.h"
#include "buku.h"

// ADT untuk menyimpan data peminjaman per buku
typedef struct PeminjamanNode {
    char idAnggota[20];
    struct PeminjamanNode* next;
    struct PeminjamanNode* prev; // Tambahan untuk DLL
} PeminjamanNode;

// Priority Queue untuk peminjaman
typedef struct {
    char judulBuku[100];
    PeminjamanNode* headDosen;    // Prioritas tertinggi
    PeminjamanNode* tailDosen;    // Tambahan untuk DLL
    PeminjamanNode* headMahasiswa;
    PeminjamanNode* tailMahasiswa; // Tambahan untuk DLL
    PeminjamanNode* headMasyarakat; // Prioritas terendah
    PeminjamanNode* tailMasyarakat; // Tambahan untuk DLL
    int totalPeminjam;
} PeminjamanBuku;

// Node untuk Doubly Linked List semua peminjaman
typedef struct PeminjamanListNode {
    PeminjamanBuku data;
    struct PeminjamanListNode* next;
    struct PeminjamanListNode* prev; // Tambahan untuk DLL
} PeminjamanListNode;

typedef struct {
    PeminjamanListNode* head;
    PeminjamanListNode* tail; // Tambahan untuk DLL
    int size;
} PeminjamanList;

// Fungsi-fungsi ADT Peminjaman
void initPeminjamanList(PeminjamanList* list);
void tambahPeminjam(PeminjamanList* list, const char* judulBuku, const char* idAnggota, Prioritas prioritas);
void prosesPeminjaman(PeminjamanList* peminjamanList, BukuList* bukuList, AnggotaList* anggotaList);
void prosesPengembalian(PeminjamanList* peminjamanList, BukuList* bukuList, AnggotaList* anggotaList);
void batalkanPeminjaman(PeminjamanList* list, const char* judulBuku, const char* idAnggota);
void tampilkanAntrianPeminjaman(PeminjamanList* list, const char* judulBuku);
void freePeminjamanList(PeminjamanList* list);

#endif
