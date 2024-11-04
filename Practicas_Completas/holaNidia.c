#include <stdint.h>
#include <unistd.h>  // Para write()

void imprimir_hola_nidia(uint8_t veces) {
    const char *mensaje = "Hola Nidia\n";
    while (veces--) {

        //DE 1 a 11 longitud 
        write(1, mensaje, 11);  
    }
}

int main() {
    imprimir_hola_nidia(25);
    return 0;
}

