#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definição dos pinos
#define LED_VERDE 11
#define LED_VERMELHO 13
#define LED_AZUL 12
#define BOTAO 5

// Variáveis globais
volatile bool temporizador_ativo = false;
volatile int estado_atual = 0;

// Protótipos das funções
bool sequencia_led_callback(struct repeating_timer *rt);
void botao_callback(uint gpio, uint32_t eventos);

bool debounce()
{
    static uint32_t ultimo_tempo_botao = 0;
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (tempo_atual - ultimo_tempo_botao < 200)
    { // 200ms de debounce
        return false;
    }

    ultimo_tempo_botao = tempo_atual;
    return true;
}

bool sequencia_led_callback(struct repeating_timer *rt)
{
    switch (estado_atual)
    {
    case 0:
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERDE, 1);
        estado_atual++;
        break;

    case 1:
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AZUL, 0);
        gpio_put(LED_VERDE, 1);
        estado_atual++;
        break;

    case 2:
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AZUL, 0);
        gpio_put(LED_VERDE, 1);
        estado_atual++;
        break;

    case 3:
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_AZUL, 0);
        gpio_put(LED_VERDE, 0);
        temporizador_ativo = false;
        estado_atual = 0; // Reiniciar o estado
        return false;     // Encerra o temporizador
    }
    return true;
}

void botao_callback(uint gpio, uint32_t eventos)
{
    gpio_acknowledge_irq(gpio, eventos); // Garante que a interrupção foi reconhecida

    if (!debounce())
        return;

    if (!temporizador_ativo)
    {
        temporizador_ativo = true;
        estado_atual = 0; // Reinicia a sequência do início
        static struct repeating_timer temporizador;
        add_repeating_timer_ms(3000, sequencia_led_callback, NULL, &temporizador);
        sequencia_led_callback(NULL); // Inicia a sequência imediatamente
    }
}

int main()
{
    stdio_init_all();

    // Inicialização dos GPIOs
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_init(BOTAO);

    // Configuração da direção dos GPIOs
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(BOTAO, GPIO_IN);

    // Configuração do pull-up para o botão
    gpio_pull_up(BOTAO);

    // Configuração da interrupção do botão (detecta borda de descida)
    gpio_set_irq_enabled_with_callback(BOTAO,
                                       GPIO_IRQ_EDGE_FALL,
                                       true,
                                       &botao_callback);

    // Estado inicial: todos os LEDs apagados
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);

    // Loop principal (fica em espera ativa)
    while (1)
    {
        tight_loop_contents();
    }

    return 0;
}
