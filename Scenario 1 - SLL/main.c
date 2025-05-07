#include <stdio.h>
#include <stdlib.h>
#include "buku.h"
#include "anggota.h"
#include "peminjaman.h"
#include "menu.h"

int main() {
    BukuList bukuList;
    AnggotaList anggotaList;
    PeminjamanList peminjamanList;
    
    // Inisialisasi semua list
    initBukuList(&bukuList);
    initAnggotaList(&anggotaList);
    initPeminjamanList(&peminjamanList);
    
    int pilihan;
    do {
    	system("cls");
        tampilkanMenuUtama();
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                menuKelolaBuku(&bukuList);
                break;
            case 2:
                menuKelolaAnggota(&anggotaList);
                break;
            case 3:
                menuKelolaPeminjaman(&peminjamanList, &bukuList, &anggotaList);
                break;
            case 4: 
                requirementAwal(&peminjamanList, &bukuList, &anggotaList);
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
    
    // Bebaskan memori yang digunakan
    freeBukuList(&bukuList);
    freeAnggotaList(&anggotaList);
    freePeminjamanList(&peminjamanList);
    
    return 0;
}
