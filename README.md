# Semáforo com Raspberry Pi Pico W



## Autor - Inácio Oliveira Borges

### Link para demonstração do funcionamento: https://youtu.be/9LXWO1LJqFg?si=4hNqFvtJdvNVLUYc


Este projeto implementa um semáforo simples utilizando o Raspberry Pi Pico W, controlando três LEDs (verde, vermelho e azul) através de um botão.

## Descrição

O código demonstra o uso de interrupções, temporizadores e controle de GPIOs para criar um semáforo com a seguinte sequência:

1. Vermelho aceso por 3 segundos.
2. Vermelho e verde acesos por 1 segundo.
3. Verde aceso por 2 segundos.
4. Todos os LEDs apagados.

A sequência é iniciada ao pressionar um botão conectado ao Raspberry Pi Pico W.

## Hardware Necessário

- Raspberry Pi Pico W
- 3 LEDs (verde, vermelho, azul)
- 1 botão
- Resistores (para os LEDs e o botão)
- Jumpers para conexão

## Conexões

- LED Verde: GPIO 11
- LED Vermelho: GPIO 13
- LED Azul: GPIO 12
- Botão: GPIO 5

## Dependências

- SDK do Raspberry Pi Pico: [https://github.com/raspberrypi/pico-sdk](https://github.com/raspberrypi/pico-sdk)

## Como usar

1. Clone este repositório.
2. Certifique-se de ter o SDK do Raspberry Pi Pico instalado e configurado.
3. Conecte os componentes de hardware de acordo com o esquema.
4. Compile o código usando o SDK do Raspberry Pi Pico.
5. Envie o código para o Raspberry Pi Pico W.

## Funcionamento

1. Ao pressionar o botão, a sequência do semáforo é iniciada.
2. Os LEDs acendem e apagam de acordo com a sequência predefinida.
3. Após o término da sequência, todos os LEDs se apagam.
4. A sequência pode ser reiniciada pressionando o botão novamente.

## Código

O código foi escrito em C e utiliza as bibliotecas do SDK do Raspberry Pi Pico para controle de GPIOs, interrupções e temporizadores.

## Melhorias

- O código inclui tratamento de debounce para evitar leituras falsas do botão.
- A sequência do semáforo é definida em um array de estruturas, facilitando a modificação da sequência.
- O código utiliza um único temporizador para controlar todas as etapas da sequência, otimizando o uso de recursos.