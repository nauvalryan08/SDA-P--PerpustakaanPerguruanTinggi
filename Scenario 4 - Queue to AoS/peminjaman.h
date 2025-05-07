#ifndef PEMINJAMAN_H
#define PEMINJAMAN_H

#include "buku.h"
#include "anggota.h"

typedef struct PeminjamNode {
    char idAnggota[20];
    Prioritas prioritas;
    Buku* buku; // Pointer ke buku yang dipinjam
    struct PeminjamNode* next;
} PeminjamNode;

typedef struct {
    PeminjamNode* headDosen;
    PeminjamNode* tailDosen;
    PeminjamNode* headMahasiswa;
    PeminjamNode* tailMahasiswa;
    PeminjamNode* headMasyarakat;
    PeminjamNode* tailMasyarakat;
    int totalPeminjam;
} PeminjamanQueue;

// Fungsi-fungsi ADT Peminjaman
void initPeminjamanQueue(PeminjamanQueue* queue);
void tambahPeminjam(PeminjamanQueue* queue, BukuArray* bukuArray, AnggotaList* anggotaList, const char* judulBuku, const char* idAnggota);
void prosesPeminjaman(PeminjamanQueue* queue, BukuArray* bukuArray, AnggotaList* anggotaList);
void prosesPengembalian(PeminjamanQueue* queue, BukuArray* bukuArray, const char* judulBuku, const char* idAnggota);
void batalkanPeminjaman(PeminjamanQueue* queue, const char* judulBuku, const char* idAnggota);
void tampilkanAntrianPeminjaman(PeminjamanQueue* queue);
void freePeminjamanQueue(PeminjamanQueue* queue);

#endif
