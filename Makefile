APPLICATION = test_lis2dw12
BOARD ?= lora3a-h10
RIOTBASE ?= $(CURDIR)/../RIOT
LORA3ABASE ?= $(CURDIR)/../lora3a-boards
EXTERNAL_BOARD_DIRS=$(LORA3ABASE)/boards
EXTERNAL_MODULE_DIRS=$(LORA3ABASE)/modules
EXTERNAL_PKG_DIRS=$(LORA3ABASE)/pkg
QUIET ?= 1
DEVELHELP ?= 1
PORT ?= /dev/ttyUSB0

USEMODULE += printf_float
USEMODULE += periph_gpio_irq
USEMODULE += ztimer_msec

CFLAGS += -DENABLE_ACME2=MODE_I2C -DLIS2DW12_I2C_DEVICE=ACME2_I2C_DEV

include $(RIOTBASE)/Makefile.include
