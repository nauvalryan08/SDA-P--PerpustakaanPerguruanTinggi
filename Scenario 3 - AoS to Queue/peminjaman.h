#ifndef PEMINJAMAN_H
#define PEMINJAMAN_H

#include "buku.h"
#include "anggota.h"

// Fungsi-fungsi ADT Peminjaman untuk array version
void tambahPeminjam(BukuArray* bukuArray, AnggotaList* anggotaList, const char* judulBuku, const char* idAnggota);
void prosesPeminjaman(BukuArray* bukuArray, AnggotaList* anggotaList, const char* judulBuku);
void prosesPengembalian(BukuArray* bukuArray, const char* judulBuku, const char* idAnggota);
void batalkanPeminjaman(BukuArray* bukuArray, const char* judulBuku, const char* idAnggota);
void tampilkanAntrianPeminjaman(BukuArray* bukuArray, const char* judulBuku);

#endif
