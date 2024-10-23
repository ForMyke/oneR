#include <stdio.h>
#include <string.h>

// Definición de funciones
void bit_bit_and(unsigned char ip[4], unsigned char mascara_red[4], unsigned char resultado[4]);
void broad_pro(unsigned char clase, unsigned char ip[4], unsigned char resultado[4]);
void entrada(char* entrada, unsigned char ip[4]);
void calculul_tipo(unsigned char ip[4], unsigned char broadcast[4], unsigned char red[4], unsigned char clase);

int main(){
    unsigned char ip[4], mascara_red[4] = {255, 0, 0, 0}, aux_ip[4], broadcast[4];
    unsigned char clase;
    char entrada_ip[16];
    
    printf("\t\t\tCALCULADORA DE IP:\n");
    printf("Ingrese su IP (formato xxx.xxx.xxx.xxx): ");
    scanf("%s", entrada_ip);

    entrada(entrada_ip, ip);
    
    printf("Su IP es: %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);

    printf("Clase de IP: ");

    if ((ip[0] & 0x80) == 0x00) { 
        printf("Clase A\n");
        clase = 'A';
        mascara_red[0] = 255;
        mascara_red[1] = 0;
        mascara_red[2] = 0;
        mascara_red[3] = 0;
    } else if ((ip[0] & 0xC0) == 0x80) { 
        printf("Clase B\n");
        clase = 'B';
        mascara_red[0] = 255;
        mascara_red[1] = 255;
        mascara_red[2] = 0;
        mascara_red[3] = 0;
    } else if ((ip[0] & 0xE0) == 0xC0) { 
        printf("Clase C\n");
        clase = 'C';
        mascara_red[0] = 255;
        mascara_red[1] = 255;
        mascara_red[2] = 255;
        mascara_red[3] = 0;
    } else if ((ip[0] & 0xF0) == 0xE0) { 
        printf("Clase D (Multicast)\n");
        clase = 'D';
    return 0;
    } else if ((ip[0] & 0xF0) == 0xF0) { 
        printf("Clase E (Reservada)\n");
        clase = 'E';
        return 0;
    }

    // Calcular IP de red
    bit_bit_and(ip, mascara_red, aux_ip);
    printf("IP de red: %d.%d.%d.%d\n", aux_ip[0], aux_ip[1], aux_ip[2], aux_ip[3]);

    // Calcular IP de broadcast
    broad_pro(clase, ip, broadcast);
    printf("IP de broadcast: %d.%d.%d.%d\n", broadcast[0], broadcast[1], broadcast[2], broadcast[3]);

    // Determinar si la IP es de tipo Red, Host o Broadcast (solo para clases A, B y C)
    if (clase == 'A' || clase == 'B' || clase == 'C') {
        calculul_tipo(ip, broadcast, aux_ip, clase);
    }

    return 0;
}

// Funciones
void bit_bit_and(unsigned char ip[4], unsigned char mascara_red[4], unsigned char resultado[4]){
    for (unsigned int  i = 0; i < 4; i++){
        resultado[i] = ip[i] & mascara_red[i];
    }
}

void broad_pro(unsigned char clase, unsigned char ip[4], unsigned char resultado[4]){
    // Solo calcular broadcast si la clase es A, B o C
    if (clase == 'A' || clase == 'B' || clase == 'C') {
        unsigned char mascara_red[4];

        // Asignar la máscara de red correspondiente según la clase
        if (clase == 'A') {
            mascara_red[0] = 255; mascara_red[1] = 0; mascara_red[2] = 0; mascara_red[3] = 0;
        } else if (clase == 'B') {
            mascara_red[0] = 255; mascara_red[1] = 255; mascara_red[2] = 0; mascara_red[3] = 0;
        } else if (clase == 'C') {
            mascara_red[0] = 255; mascara_red[1] = 255; mascara_red[2] = 255; mascara_red[3] = 0;
        }

        // Calcular la dirección de broadcast usando OR con la máscara invertida
        for (unsigned int i = 0; i < 4; i++) {
            resultado[i] = ip[i] | (~mascara_red[i]);
        }
    } else {
        // No hacer nada si la clase es D o E
        printf("Clase D o E: No se calcula IP de broadcast.\n");
    }
}

void entrada(char* entrada, unsigned char ip[4]){
    sscanf(entrada, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
}

void calculul_tipo(unsigned char ip[4], unsigned char broadcast[4], unsigned char red[4], unsigned char clase){
    if (memcmp(ip, red, 4) == 0) {
        printf("La IP es de tipo Red.\n");
    } else if (memcmp(ip, broadcast, 4) == 0) {
        printf("La IP es de tipo Broadcast.\n");
    } else {
        printf("La IP es de tipo Host.\n");
    }
}