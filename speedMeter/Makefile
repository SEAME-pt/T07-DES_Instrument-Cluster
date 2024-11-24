DIR_Config   = ./includes/Config
DIR_OLED     = ./includes/OLED
DIR_sources = ./sources
DIR_BIN      = ./build

OBJ_C = $(wildcard ${DIR_OLED}/*.c ${DIR_Config}/*.c ${DIR_GUI}/*.c ${DIR_sources}/*.c ${DIR_FONTS}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

# TARGET = ../../../oled/oled
TARGET = oled

# USELIB = USE_BCM2835_LIB
# USELIB = USE_WIRINGPI_LIB
USELIB = USE_DEV_LIB
DEBUG = -D $(USELIB)
ifeq ($(USELIB), USE_BCM2835_LIB)
    LIB = -lbcm2835 -lm
else ifeq ($(USELIB), USE_WIRINGPI_LIB)
    LIB = -lwiringPi -lm
else ifeq ($(USELIB), USE_DEV_LIB)
    LIB = -llgpio -lm
endif


CC = gcc
MSG = -g -O0 -Wall
CFLAGS += $(MSG) $(DEBUG)

all : ${TARGET}

${TARGET}:${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB) -lgpiod -lpthread

${DIR_BIN}/%.o:$(DIR_sources)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ -I $(DIR_Config) -I $(DIR_OLED)

${DIR_BIN}/%.o:$(DIR_OLED)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ -I $(DIR_Config)

${DIR_BIN}/%.o:$(DIR_Config)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)

clean :
	rm -rf $(DIR_BIN)/*.*
	rm $(TARGET)

re : clean all

run :
	../../../oled/oled2
