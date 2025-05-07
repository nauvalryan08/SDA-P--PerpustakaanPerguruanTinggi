#ifndef MENU_H
#define MENU_H

#include "buku.h"
#include "anggota.h"
#include "peminjaman.h"

// Fungsi-fungsi menu
void tampilkanMenuUtama();
void menuKelolaBuku(BukuList* list);
void menuKelolaAnggota(AnggotaList* list);
void menuKelolaPeminjaman(PeminjamanList* peminjamanList, BukuList* bukuList, AnggotaList* anggotaList);
void requirementAwal(PeminjamanList* peminjamanList, BukuList* bukuList, AnggotaList* anggotaList);

#endif
