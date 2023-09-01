## Gerador de sinal com arduíno

# Materiais
    - Um arduino Uno, microcontrolador Atmel328p a 16mHz
    - 1 chave táctil montada como pull-up
    - 1 ponteciômetro 10k

# Os sinais gerados são de PWM

    Pino 2 -> LED Frequência PDIM
    Pino 4 -> LED Frequência ADIM
    Pino 5 -> LED DutyCycle ADIM
    Pino 7 -> LED DutyCycle REF

    PINO 6 -> Saída PDIM
    PINO 9 -> Saída ADIM
    PINO 3 -> Saída REF

    PINO 8 -> CHAVE
    PINO A0 -> POTENCIÔMETRO

    É IMPORTANTE MANTER ESTE PADRÃO DE PINAGEM

# Como funciona
São 3 pwm's diferentes gerados, com 4 configurações disponíveis:
    Alterar Frequência PDIM  50-250Hz
    Alterar Frequência ADIM  50-250Hz
    Alterar DutyCycle ADIM   0-100%
    Alterar DutyCycle REF    0-100%

O led indica qual funcionalidade está sendo utilizada.
A chave altera a funcionalidade.
O potenciômentro atua fazendo as configurações

PDIM -> Um pwm com frequência variável e DC fixo de 50%
ADIM -> Um pwm com frequência e DC variáveis
REF  -> Um pwm com frequência fixa de 60Hz e DC variável