/* Definir Endereço dos Registradores */
#define SIM_SCGC5      (*(volatile unsigned int*)0x40048038)
#define PORTB_PCR19    (*(volatile unsigned int*)0x4004A04C) // Configuração do Pino 19 (Porta B)
#define GPIOB_PDDR     (*(volatile unsigned int*)0x400FF054) // Direção dos Pinos da Porta B
#define GPIOB_PSOR     (*(volatile unsigned int*)0x400FF044) // Set (Coloca o pino em 1 / Apaga o LED)
#define GPIOB_PCOR     (*(volatile unsigned int*)0x400FF048) // Clear (Coloca o pino em 0 / Acende o LED)

void delayMs(int n); 
/* Função: Espera n milisegundos CORRIGIDA */
void delayMs(int n) {
    volatile int i; // <--- Adicionado 'volatile'
    volatile int j; // <--- Adicionado 'volatile'
    for (i = 0; i < n; i++) {
        for (j = 0; j < 7000; j++) {
            // O compilador agora é obrigado a executar este bloco linha por linha
        }
    }
}
int main(void) {
    
    
    SIM_SCGC5 |= (1 << 10); 
    PORTB_PCR19 &= ~0x700;  
    PORTB_PCR19 |= 0x100;   

    GPIOB_PDDR |= (1 << 19); 

  
    for (; ; ) { // 
        
   
        GPIOB_PCOR = (1 << 19); // [cite: 8]

        /* (5) Função de espera (1000 milisegundos = 1 segundo) */
        delayMs(1000); // [cite: 9]

        /* (6) Desabilitar saída (Desliga o LED verde) */
        // Colocamos o pino em 1 (Set) para cortar a corrente e apagar o LED
        GPIOB_PSOR = (31<< 19); // [cite: 10]

    
        delayMs(1000); // [cite: 11]
    }

    return 0;
}

