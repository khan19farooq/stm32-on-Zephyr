# Custom board CMake configuration for STM32F407

# Setting up OpenOCD for STM32F4
board_runner_args(openocd "--file" "board/stm32f4discovery.cfg")

# Include the Zephyr STM32 common CMake configurations
include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
