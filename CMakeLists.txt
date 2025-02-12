# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Detectando sistema operacional
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

# Configurações da ferramenta
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

# Inclusão do arquivo necessário para o SDK
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Define a placa a ser usada
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Importa o SDK do Pico
include(pico_sdk_import.cmake)

# Nome do projeto
project(Pwm C CXX ASM)

# Inicializa o SDK do Pico
pico_sdk_init()

# Adiciona o executável
add_executable(Pwm Pwm.c)

# Define nome e versão do programa
pico_set_program_name(Pwm "Pwm")
pico_set_program_version(Pwm "0.1")

# Habilita saída de depuração (ajuste conforme necessário)
pico_enable_stdio_uart(Pwm 0)
pico_enable_stdio_usb(Pwm 0)

# Inclui diretórios necessários
target_include_directories(Pwm PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Adiciona as bibliotecas corretas
target_link_libraries(Pwm
    pico_stdlib  
    hardware_pwm
    hardware_clocks
)

# Gera arquivos adicionais (UF2, HEX, etc.)
pico_add_extra_outputs(Pwm)

