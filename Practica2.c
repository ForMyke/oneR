#include <stdio.h>
#include <stdint.h>

//Definicion de las funciones
void leer_cabecera(uint8_t ethernet_header[14]);
void imprimir_cabecera(const uint8_t ethernet_header[14]);
void imprimir_mac_destino(const uint8_t ethernet_header[14]);
void imprimir_mac_origen(const uint8_t ethernet_header[14]);
void determinar_protocolo(const uint8_t ethernet_header[14]);

int main() {

    uint8_t ethernet_header[14];  

    printf("Ingresa la cabecera Ethernet (14 valores hexadecimales separados por espacios): \n");

    leer_cabecera(ethernet_header);
    imprimir_cabecera(ethernet_header);
    imprimir_mac_destino(ethernet_header);
    imprimir_mac_origen(ethernet_header);
    determinar_protocolo(ethernet_header);
    return 0;
}

// Función para leer los 14 bytes de la cabecera Ethernet ingresados de golpe
void leer_cabecera(uint8_t ethernet_header[14]) {
    printf("Ingresa la cabecera: ");
    for (int i = 0; i < 14; i++) {
        scanf("%hhx", &ethernet_header[i]);
    }
}

// Funcion para imprimir la cabecera Ethernet completa
void imprimir_cabecera(const uint8_t ethernet_header[14]) {
    printf("\nLa cabecera Ethernet es: ");
    for (uint8_t index = 0; index < 14; index++) {
        printf("%02x ", ethernet_header[index]);  
    }
    printf("\n");
}

// Funcion para imprimir la dirección MAC de destino (primeros 6 bytes)
void imprimir_mac_destino(const uint8_t ethernet_header[14]) {
    printf("\nLa MAC destino es: ");
    for (uint8_t index = 0; index < 6; index++) {
        printf("%02x ", ethernet_header[index]);  
    }
    printf("\n");
}

// Función para imprimir la dirección MAC de origen (bytes 6 a 11)
void imprimir_mac_origen(const uint8_t ethernet_header[14]) {
    printf("La MAC origen es: ");
    for (uint8_t index = 6; index < 12; index++) {
        printf("%02x ", ethernet_header[index]);  
    }
    printf("\n");
}

// Función para determinar el tipo de protocolo basado en los bytes 12 y 13
void determinar_protocolo(const uint8_t ethernet_header[14]) {
    uint16_t protocol_type;

    protocol_type = (ethernet_header[12] << 8) | ethernet_header[13];  

    if (protocol_type <= 1500) {
        printf("\nEs un protocolo LLC (Logical Link Control)\n");
    } else if (protocol_type == 2048) {
        printf("\nEs un protocolo IP (Internet Protocol)\n");
    } else if (protocol_type == 2054) {
        printf("\nEs un protocolo ARP (Address Resolution Protocol)\n");
    } else {
        printf("\nProtocolo desconocido\n");
    }
}