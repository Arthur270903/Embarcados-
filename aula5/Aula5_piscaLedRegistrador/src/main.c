/* Definir Endereço dos Registradores */
#define SIM_SCGC5      (*(volatile unsigned int*)0x40048038)
#define PORTB_PCR19    (*(volatile unsigned int*)0x4004A04C)
#define GPIOB_PDDR     (*(volatile unsigned int*)0x400FF054) 
#define GPIOB_PSOR     (*(volatile unsigned int*)0x400FF044) 
#define GPIOB_PCOR     (*(volatile unsigned int*)0x400FF048) 
void delayMs(int n); 
void delayMs(int n) {
    volatile int i; 
    volatile int j; 
    for (i = 0; i < n; i++) {
        for (j = 0; j < 7000; j++) {
            
        }
    }
}
int main(void) {
    
    
    SIM_SCGC5 |= (1 << 10); 
    PORTB_PCR19 &= ~0x700;  
    PORTB_PCR19 |= 0x100;   

    GPIOB_PDDR |= (1 << 19); 

  
    for (; ; ) { 
        
   
        GPIOB_PCOR = (1 << 19); 

        
        delayMs(1000); 

      
        GPIOB_PSOR = (1<< 19); 

    
        delayMs(1000);
    }

    return 0;
}

