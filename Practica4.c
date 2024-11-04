#include <stdio.h>
#include <stdint.h>

#define MAX_TRAMA_SIZE 200

void AnalizaARP(unsigned char T[][MAX_TRAMA_SIZE], unsigned char NumTrama, int trama_size);
void imprimir_mac_destino(const unsigned char trama[], int trama_size);
void imprimir_mac_origen(const unsigned char trama[], int trama_size);

int main() {
    unsigned char tramas[5][MAX_TRAMA_SIZE] = {
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x08, 0x06, 0x00, 0x04,
         0x08, 0x00, 0x05, 0x04, 0x00, 0x01, 0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0xcc, 0x39, 0xfe},

        {0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x06, 0x00, 0x01,
         0x08, 0x00, 0x06, 0x04, 0x00, 0x02, 0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x39, 0xfe,
         0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x08, 0x06, 0x00, 0x10,
         0x08, 0x00, 0x06, 0x04, 0x00, 0x03, 0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb},

        {0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x06, 0x00, 0x10,
         0x08, 0x00, 0x05, 0x04, 0x00, 0x04, 0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x3a, 0xe1,
         0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb}
    };

    unsigned int opcion;
    printf("Ingrese que opcion desea ejecutar:\n");
    printf("1. Usar una trama ARP predeterminada\n");
    printf("2. Ingresar una trama manualmente\n");
    printf("OPCION: ");
    scanf("%u", &opcion);

    if (opcion == 1) {
        unsigned int indiceTrama;
        printf("Seleccione una opcion (0 a 3): ");
        scanf("%u", &indiceTrama);

        if (indiceTrama < 5) {
            int trama_size = sizeof(tramas[indiceTrama]) / sizeof(tramas[indiceTrama][0]);
            imprimir_mac_destino(tramas[indiceTrama], trama_size);
            imprimir_mac_origen(tramas[indiceTrama], trama_size);
            AnalizaARP(tramas, indiceTrama, trama_size);
        } else {
            printf("ERROR: Indice de trama no válido\n");
        }
    } else if (opcion == 2) {
       unsigned char tramaManual[1][MAX_TRAMA_SIZE] = {0};
        unsigned int i = 0;

        printf("Ingresa la trama en hexadecimal (un valor a la vez, selecciona '2' para finalizar):\n");

        while (i < MAX_TRAMA_SIZE) {
            int valor;
            printf("Hexadecimal %d: ", i + 1);
            scanf("%x", &valor);
            if (valor == 2) {
                break; 
            }
            tramaManual[0][i++] = (unsigned char)valor;
        }
        imprimir_mac_destino(tramaManual[0], i);
        imprimir_mac_origen(tramaManual[0], i);
        AnalizaARP(tramaManual, 0, i);
    } else {
        printf("ERROR: OPCION NO VALIDA\n");
    }

    return 0;
}

void imprimir_mac_destino(const unsigned char trama[], int trama_size) {
     printf("____CABECERA ETHERNET____");
    if (trama_size < 6) {
        printf("Trama demasiado corta para contener una direccion MAC destino.\n");
        return;
    }
    printf("\nLa MAC destino es: ");
    for (unsigned int i = 0; i < 6; i++) {
        printf("%02x", trama[i]);
        if (i < 5) {
            printf(":");
        }
    }
    printf("\n");
}

void imprimir_mac_origen(const unsigned char trama[], int trama_size) {
    if (trama_size < 12) {
        printf("Trama demasiado corta para contener una direccion MAC origen.\n");
        return;
    }
    printf("La MAC origen es: ");
    for (unsigned int i = 6; i < 12; i++) {
        printf("%02x", trama[i]);
        if (i < 11) {
            printf(":");
        }
    }
    printf("\n");
}

void AnalizaARP(unsigned char T[][MAX_TRAMA_SIZE], unsigned char NumTrama, int trama_size) {
        printf("____Cabecera ARP____");

    if (trama_size < 42) {
        printf("Trama demasiado corta para analisis completo.\n");
        return;
    }

    printf("\nHW add type: ");
    if (((T[NumTrama][14]) << 8 | T[NumTrama][15]) == 1) {
        printf(" Ethernet\n");
    } else if (((T[NumTrama][14]) << 8 | T[NumTrama][15]) == 2) {
        printf(" IEE 802 LAN\n");
    } else if (((T[NumTrama][14]) << 8 | T[NumTrama][15]) == 15) {
        printf(" Frame Relay\n");
    } else if (((T[NumTrama][14]) << 8 | T[NumTrama][15]) == 16) {
        printf(" ATM\n");
    } else {
        printf(" No reconocido\n");
    }

    printf("Prot add type: ");
    if (((T[NumTrama][16]) << 8 | T[NumTrama][17]) == 2048) {
        printf(" IPv4\n");
    } else {
        printf(" No reconocido %.2x %.2x\n", T[NumTrama][16], T[NumTrama][17]);
    }

    printf("SIZE direccion de HW: %d bytes\n", T[NumTrama][18]);
    printf("SIZE direccion de Protocolo: %d bytes\n", T[NumTrama][19]);

    if (((T[NumTrama][20]) << 8 | T[NumTrama][21]) == 1) {
        printf("OPCION: SOLICITUD\n");
    } else if (((T[NumTrama][20]) << 8 | T[NumTrama][21]) == 2) {
        printf("OPCION: RESPUESTA\n");
    } else {
        printf("OPCION NO RECONOCIDA\n");
    }

    // MAC Origen e IP Origen
    printf("\nMAC origen: %.2x.%.2x.%.2x.%.2x.%.2x.%.2x", 
           T[NumTrama][22], T[NumTrama][23], T[NumTrama][24], T[NumTrama][25], T[NumTrama][26], T[NumTrama][27]);
    printf("\nIP origen: %d.%d.%d.%d", 
           T[NumTrama][28], T[NumTrama][29], T[NumTrama][30], T[NumTrama][31]);

    // MAC Destino e IP Destino
    printf("\nMAC destino: %.2x.%.2x.%.2x.%.2x.%.2x.%.2x", 
           T[NumTrama][32], T[NumTrama][33], T[NumTrama][34], T[NumTrama][35], T[NumTrama][36], T[NumTrama][37]);
    printf("\nIP destino: %d.%d.%d.%d\n", 
           T[NumTrama][38], T[NumTrama][39], T[NumTrama][40], T[NumTrama][41]);
}
