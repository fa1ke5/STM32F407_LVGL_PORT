##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.7.1] date: [Sun Feb 07 19:08:12 MSK 2021] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = HACK_RF_NEW


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Src/main.c \
Drivers/LCD/ILI9341/ILI9341_GFX.c \
Drivers/LCD/ILI9341/ILI9341_STM32_Driver.c \
Drivers/TS/Src/XPT2046_lv.c \
Drivers/TS/Src/touchpad.c \
lv_examples/src/lv_demo_widgets/lv_demo_widgets.c \
lv_examples/src/lv_ex_widgets/lv_ex_btn/lv_ex_btn_1.c \
lv_examples/src/lv_demo_benchmark/lv_demo_benchmark.c \
lv_examples/assets/lv_font_montserrat_28_compr_az.c \
lv_examples/assets/lv_font_montserrat_16_compr_az.c \
lv_examples/assets/lv_font_montserrat_12_compr_az.c \
lv_examples/assets/img_cogwheel_alpha16.c \
lv_examples/assets/img_cogwheel_argb.c \
lv_examples/assets/img_cogwheel_rgb.c \
lv_examples/assets/img_cogwheel_indexed16.c \
lv_examples/assets/img_cogwheel_chroma_keyed.c \
lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.c \
lvgl/src/lv_misc/lv_fs.c \
lvgl/src/lv_themes/lv_theme_material.c \
lvgl/src/lv_core/lv_indev.c \
lvgl/src/lv_hal/lv_hal_indev.c \
lvgl/src/lv_misc/lv_printf.c \
lvgl/src/lv_widgets/lv_arc.c \
lvgl/src/lv_widgets/lv_bar.c \
lvgl/src/lv_widgets/lv_btn.c \
lvgl/src/lv_widgets/lv_btnmatrix.c \
lvgl/src/lv_widgets/lv_calendar.c \
lvgl/src/lv_widgets/lv_canvas.c \
lvgl/src/lv_widgets/lv_chart.c \
lvgl/src/lv_widgets/lv_checkbox.c \
lvgl/src/lv_widgets/lv_cont.c \
lvgl/src/lv_widgets/lv_cpicker.c \
lvgl/src/lv_widgets/lv_dropdown.c \
lvgl/src/lv_widgets/lv_gauge.c \
lvgl/src/lv_widgets/lv_img.c \
lvgl/src/lv_widgets/lv_imgbtn.c \
lvgl/src/lv_widgets/lv_keyboard.c \
lvgl/src/lv_widgets/lv_label.c \
lvgl/src/lv_widgets/lv_led.c \
lvgl/src/lv_widgets/lv_line.c \
lvgl/src/lv_widgets/lv_linemeter.c \
lvgl/src/lv_widgets/lv_list.c \
lvgl/src/lv_widgets/lv_msgbox.c \
lvgl/src/lv_widgets/lv_objmask.c \
lvgl/src/lv_widgets/lv_objx_templ.c \
lvgl/src/lv_widgets/lv_page.c \
lvgl/src/lv_widgets/lv_roller.c \
lvgl/src/lv_widgets/lv_slider.c \
lvgl/src/lv_widgets/lv_spinbox.c \
lvgl/src/lv_widgets/lv_spinner.c \
lvgl/src/lv_widgets/lv_switch.c \
lvgl/src/lv_widgets/lv_table.c \
lvgl/src/lv_widgets/lv_tabview.c \
lvgl/src/lv_widgets/lv_textarea.c \
lvgl/src/lv_widgets/lv_tileview.c \
lvgl/src/lv_widgets/lv_win.c \
lvgl/src/lv_core/lv_group.c \
lvgl/src/lv_core/lv_obj.c \
lvgl/src/lv_core/lv_refr.c \
lvgl/src/lv_core/lv_style.c \
lvgl/src/lv_core/lv_disp.c \
lvgl/src/lv_hal/lv_hal_tick.c \
lvgl/src/lv_hal/lv_hal_disp.c \
lvgl/src/lv_misc/lv_gc.c \
lvgl/src/lv_misc/lv_debug.c \
lvgl/src/lv_misc/lv_task.c \
lvgl/src/lv_misc/lv_mem.c \
lvgl/src/lv_misc/lv_ll.c \
lvgl/src/lv_misc/lv_txt.c \
lvgl/src/lv_misc/lv_math.c \
lvgl/src/lv_misc/lv_area.c \
lvgl/src/lv_misc/lv_color.c \
lvgl/src/lv_misc/lv_anim.c \
lvgl/src/lv_misc/lv_utils.c \
lvgl/src/lv_themes/lv_theme.c \
lvgl/src/lv_draw/lv_draw_rect.c \
lvgl/src/lv_draw/lv_draw_blend.c \
lvgl/src/lv_draw/lv_draw_mask.c \
lvgl/src/lv_draw/lv_draw_arc.c \
lvgl/src/lv_draw/lv_draw_img.c \
lvgl/src/lv_draw/lv_draw_label.c \
lvgl/src/lv_draw/lv_draw_line.c \
lvgl/src/lv_draw/lv_draw_triangle.c \
lvgl/src/lv_draw/lv_img_buf.c \
lvgl/src/lv_draw/lv_img_cache.c \
lvgl/src/lv_draw/lv_img_decoder.c \
lvgl/src/lv_font/lv_font.c \
lvgl/src/lv_font/lv_font_fmt_txt.c \
lvgl/src/lv_font/lv_font_montserrat_8.c \
lvgl/src/lv_font/lv_font_montserrat_10.c \
lvgl/src/lv_font/lv_font_montserrat_12.c \
lvgl/src/lv_font/lv_font_montserrat_14.c \
lvgl/src/lv_font/lv_font_montserrat_20.c \
lvgl/src/lv_font/lv_font_montserrat_24.c \
lvgl/src/lv_font/lv_font_montserrat_16.c \
lvgl/src/lv_font/lv_font_montserrat_30.c \
Src/usb_device.c \
Src/usbd_conf.c \
Src/usbd_desc.c \
Src/usbd_storage_if.c \
Src/stm32f4xx_it.c \
Src/stm32f4xx_hal_msp.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Src/system_stm32f4xx.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c \
Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc.c \
Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_bot.c \
Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_data.c \
Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_scsi.c

# ASM sources
ASM_SOURCES =  \
startup_stm32f407xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F407xx


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-IInc \
-Ilvgl \
-IDrivers/TS/Inc \
-IDrivers/LCD/ILI9341 \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IMiddlewares/ST/STM32_USB_Device_Library/Core/Inc \
-IMiddlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F407VETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
