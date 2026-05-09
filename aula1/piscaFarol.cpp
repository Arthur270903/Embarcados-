#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>

#define LED_PORT "GPIO_1" // Tente mudar para "GPIOB" se continuar não piscando

// Pinos reais do LED RGB embutido na FRDM-KL25Z
#define LED_RED_PIN   18  // PTB18
#define LED_GREEN_PIN 19  // PTB19

// Tempos do semáforo
#define TIME_RED_MS    5000
#define TIME_GREEN_MS  4000
#define TIME_YELLOW_MS 1000

typedef enum {
    STATE_RED,
    STATE_GREEN,
    STATE_YELLOW
} traffic_light_state_t;

void main(void)
{
    const struct device *port = device_get_binding(LED_PORT);

    // Configurando os pinos
    gpio_pin_configure(port, LED_RED_PIN, GPIO_OUTPUT);
    gpio_pin_configure(port, LED_GREEN_PIN, GPIO_OUTPUT);

    traffic_light_state_t current_state = STATE_RED;

    while (1) {
        // 1. APAGA TUDO (Lógica invertida: 1 = apagado)
        gpio_pin_set(port, LED_RED_PIN, 1);
        gpio_pin_set(port, LED_GREEN_PIN, 1);

        // 2. AVALIA O ESTADO E ACENDE A COR CERTA (0 = aceso)
        switch (current_state) {
            case STATE_RED:
                gpio_pin_set(port, LED_RED_PIN, 0); 
                k_msleep(TIME_RED_MS);
                current_state = STATE_GREEN;
                break;

            case STATE_GREEN:
                gpio_pin_set(port, LED_GREEN_PIN, 0); 
                k_msleep(TIME_GREEN_MS);
                current_state = STATE_YELLOW;
                break;

            case STATE_YELLOW:
                // Amarelo = Vermelho + Verde ligados juntos!
                gpio_pin_set(port, LED_RED_PIN, 0); 
                gpio_pin_set(port, LED_GREEN_PIN, 0); 
                k_msleep(TIME_YELLOW_MS);
                current_state = STATE_RED;
                break;
        }
    }
}