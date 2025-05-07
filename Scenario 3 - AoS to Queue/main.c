#include <stdio.h>
#include <stdlib.h>
#include "buku.h"
#include "anggota.h"
#include "peminjaman.h"
#include "menu.h"

int main() {
    BukuArray bukuArray;
    AnggotaList anggotaList;
    
    // Inisialisasi semua struktur data
    initBukuArray(&bukuArray);
    initAnggotaList(&anggotaList);
    
    int pilihan;
    do {
    	system("cls");
        tampilkanMenuUtama();
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                menuKelolaBuku(&bukuArray);
                break;
            case 2:
                menuKelolaAnggota(&anggotaList);
                break;
            case 3:
                menuKelolaPeminjaman(&bukuArray, &anggotaList);
                break;
            case 4:
                requirementAwal(&bukuArray, &anggotaList);
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
    
    // Bebaskan memori yang digunakan
    freeBukuArray(&bukuArray);
    freeAnggotaList(&anggotaList);
    
    return 0;
}
