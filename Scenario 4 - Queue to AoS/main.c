#include <stdio.h>
#include <stdlib.h>
#include "buku.h"
#include "anggota.h"
#include "peminjaman.h"
#include "menu.h"

int main() {
    BukuArray bukuArray;
    AnggotaList anggotaList;
    PeminjamanQueue peminjamanQueue;
    
    initBukuArray(&bukuArray);
    initAnggotaList(&anggotaList);
    initPeminjamanQueue(&peminjamanQueue);
    
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
                menuKelolaPeminjaman(&peminjamanQueue, &bukuArray, &anggotaList);
                break;
            case 4:
                requirementAwal(&peminjamanQueue, &bukuArray, &anggotaList);
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
    
    freeBukuArray(&bukuArray);
    freeAnggotaList(&anggotaList);
    freePeminjamanQueue(&peminjamanQueue);
    
    return 0;
}
