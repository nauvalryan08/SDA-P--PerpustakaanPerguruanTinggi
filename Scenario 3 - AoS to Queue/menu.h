#ifndef MENU_H
#define MENU_H

#include "buku.h"
#include "anggota.h"
#include "peminjaman.h"

// Fungsi-fungsi menu
void tampilkanMenuUtama();
void menuKelolaBuku(BukuArray* array);
void menuKelolaAnggota(AnggotaList* list);
void menuKelolaPeminjaman(BukuArray* bukuArray, AnggotaList* anggotaList);
void requirementAwal(BukuArray* bukuArray, AnggotaList* anggotaList);

#endif
