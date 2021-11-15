
PREFIX=arm-none-eabi-
AS=$(PREFIX)as
CC=$(PREFIX)gcc

OBJDUMP=$(PREFIX)objdump

CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

obj = stm32/startup_stm32l432xx.o stm32/system_stm32l4xx.o \
			stm32/stm32l4xx_hal_msp.o \
			stm32/stm32l4xx_hal.o stm32/stm32l4xx_hal_cortex.o \
			stm32/stm32l4xx_hal_rcc.o stm32/stm32l4xx_hal_pwr_ex.o \
			stm32/stm32l4xx_hal_pwr.o \
			stm32/stm32l4xx_hal_dma.o \
			stm32/stm32l4xx_hal_uart.o stm32/stm32l4xx_hal_uart_ex.o \
			stm32/stm32l4xx_hal_gpio.o \
			stm32/stm32l4xx_it.o \
			main.o

ldscript = STM32L432KCUx_FLASH.ld

ASFLAGS=$(MCU)

CFLAGS=$(MCU)
CFLAGS+=-I. -Icmsis -Istm32
CFLAGS+=-DSTM32L432xx

LDFLAGS=$(MCU)
LDFLAGS+=--specs=nosys.specs

all : prog.elf

%.o : %.S
	$(CC) -c -g $(ASFLAGS) \
		-o $@ $<

%.o : %.c
	$(CC) -c -g $(CFLAGS) \
		-o $@ $<

prog.elf : $(obj)
	$(CC) $(LDFLAGS) \
		-T $(ldscript) \
		-o $@ $^

clean :
	rm -rf $(obj) prog.elf

objdump : prog.elf
	$(OBJDUMP) -d prog.elf

flash : prog.elf
	openocd -f board/st_nucleo_l4.cfg \
		-c "init" -c "program $< verify reset" \
		-c 'shutdown'