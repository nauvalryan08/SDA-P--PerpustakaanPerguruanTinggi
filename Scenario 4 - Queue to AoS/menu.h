#ifndef MENU_H
#define MENU_H

#include "buku.h"
#include "anggota.h"
#include "peminjaman.h"

void tampilkanMenuUtama();
void menuKelolaBuku(BukuArray* array);
void menuKelolaAnggota(AnggotaList* list);
void menuKelolaPeminjaman(PeminjamanQueue* queue, BukuArray* bukuArray, AnggotaList* anggotaList);
void requirementAwal(PeminjamanQueue* queue, BukuArray* bukuArray, AnggotaList* anggotaList);

#endif
