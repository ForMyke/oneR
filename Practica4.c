#include <stdio.h>
void AnalizaARP(unsigned char T[][200], unsigned char NumTrama);


int main() {
    unsigned char tramas[5][200] = {
        // Trama ARP de ejemplo 1
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x01, 0x08, 0x00, 6, 4, 0, 1, 0x52, 0x54, 0x00, 0x12, 0x34, 0x56, 192, 168, 1, 1, 0x52, 0x54, 0x00, 0x12, 0x34, 0x57, 192, 168, 1, 2},
    };

    int opcion;
    printf("Ingrese que opcion desea ejecutar:\n");
    printf("1. Usar trama ARP predeterminada\n");
    printf("2. Ingresar trama manualmente\n");
    printf("OPCION: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        AnalizaARP(tramas, 0);
    } else if (opcion == 2) {
        unsigned char tramaManual[200] = {0};
        printf("Ingresa la trama en hexadecimal (8 bits por valor, separados por espacios):\n");
        int valor, i = 0;
        while (1) {
            scanf("%x", &valor);
            if (valor == -1) break;
            tramaManual[i++] = (unsigned char)valor;
        }
        AnalizaARP(&tramaManual, 0);
    } else {
        printf("ERROR: OPCION NO VALIDA\n");
    }

    return 0;
}

void AnalizaARP(unsigned char T[][200], unsigned char NumTrama) {
    printf("\nHW add type: ");
    if (((T[NumTrama][14]) << 8 | T[NumTrama][15]) == 1) {
        printf(" Ethernet,");
    } else if (((T[NumTrama][14]) << 8 | T[NumTrama][15]) == 2) {
        printf(" IEE 802 LAN,");
    } else if (((T[NumTrama][14]) << 8 | T[NumTrama][15]) == 15) {
        printf(" Frame Relay,");
    } else if (((T[NumTrama][14]) << 8 | T[NumTrama][15]) == 16) {
        printf(" ATM,");
    } else {
        printf(" No reconocido ");
    }

    // Tipo de dirección de protocolo
    printf("Prot add type: ");
    if (((T[NumTrama][16]) << 8 | T[NumTrama][17]) == 2048) {
        printf(" IPv4,");
    } else {
        printf(" No reconocido %.2x %.2x, ", T[NumTrama][16], T[NumTrama][17]);
    }

    // Tamaños HW y Protocolo
    printf("SIZE direccion de HW: %d bytes,", T[NumTrama][18]);
    printf("SIZE direccion de Protocolo: %d bytes,", T[NumTrama][19]);

    // Opción
    if (((T[NumTrama][20]) << 8 | T[NumTrama][21]) == 1) {
        printf("OPCION: SOLICITUD.");
    } else if (((T[NumTrama][20]) << 8 | T[NumTrama][21]) == 2) {
        printf("OPCION: RESPUESTA.");
    } else {
        printf("OPCION NO RECONOCIDA");
    }

    // MAC Origen e IP Origen
    printf("\nMAC ORIGEN: %.2x.%.2x.%.2x.%.2x.%.2x.%.2x", T[NumTrama][22], T[NumTrama][23], T[NumTrama][24], T[NumTrama][25], T[NumTrama][26], T[NumTrama][27]);
    printf("\nIP ORIGEN: %d.%d.%d.%d", T[NumTrama][28], T[NumTrama][29], T[NumTrama][30], T[NumTrama][31]);

    // MAC Destino e IP Destino
    printf("\nMAC DESTINO: %.2x.%.2x.%.2x.%.2x.%.2x.%.2x", T[NumTrama][32], T[NumTrama][33], T[NumTrama][34], T[NumTrama][35], T[NumTrama][36], T[NumTrama][37]);
    printf("\nIP DESTINO: %d.%d.%d.%d\n", T[NumTrama][38], T[NumTrama][39], T[NumTrama][40], T[NumTrama][41]);
}
