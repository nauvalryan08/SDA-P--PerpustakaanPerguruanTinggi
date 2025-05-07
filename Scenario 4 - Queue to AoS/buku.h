#ifndef BUKU_H
#define BUKU_H

#include "anggota.h"

#define MAX_BUKU 100

typedef struct {
    char judul[100];
    int stok;
    int dipinjam;
} Buku;

typedef struct {
    Buku data[MAX_BUKU];
    int size;
} BukuArray;

// Fungsi-fungsi ADT Buku
void initBukuArray(BukuArray* array);
int tambahBuku(BukuArray* array, const char* judul, int stok);
Buku* cariBuku(BukuArray* array, const char* judul);
void tampilkanSemuaBuku(BukuArray* array);
int hapusBuku(BukuArray* array, const char* judul);
void freeBukuArray(BukuArray* array);

#endif
