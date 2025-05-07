#ifndef PEMINJAMAN_H
#define PEMINJAMAN_H

#include "anggota.h"
#include "buku.h"

// ADT untuk menyimpan data peminjaman per buku
typedef struct {
    char idAnggota[20];
    struct PeminjamanNode* next;
} PeminjamanNode;

// Priority Queue untuk peminjaman
typedef struct {
    char judulBuku[100];
    PeminjamanNode* headDosen;    // Prioritas tertinggi
    PeminjamanNode* headMahasiswa;
    PeminjamanNode* headMasyarakat; // Prioritas terendah
    int totalPeminjam;
} PeminjamanBuku;

// LinkedList untuk semua peminjaman
typedef struct PeminjamanListNode {
    PeminjamanBuku data;
    struct PeminjamanListNode* next;
} PeminjamanListNode;

typedef struct {
    PeminjamanListNode* head;
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
