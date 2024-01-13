# ¿Cómo inicia una computadora?

## ¿Qué es lo que sucede apenas iniciamos una computadora?

1. La BIOS (Basic input output system) desde la ROM (Read only memory, esta contiene información como la BIOS o el firmware)
2. La BIOS se ejecuta
 - Inicializa todo el hardware
 - corre algunos test (POST - power-on self test)
3. La BIOS busca algún sistema operativo existente
4. La BIOS carga e inicializa el sistema operativo
5. El sistema operativo se ejecuta

## ¿Cómo encuentra la BIOS un SO?

No voy a adentrarme en UEFI que es el sistema de booteo que usan la mayoría de los sitemas modernos. En este caso voy a hablar del legacy boot

- La BIOS carga el primer sector booteable de cada dispositivo dentro de la memoria (esto es en la dirección 0x7C00)
- La BIOS chequea si hay datos existes o "firmas" en la dirección 0xAA55
- Si esto es así, se ejecuta el código

### Registros válidos en x86_64

![Imagen](https://en.wikipedia.org/wiki/X86#/media/File:Table_of_x86_Registers_svg.svg)
