/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 *
 * Configuration settings for UDOO board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/arch/imx-regs.h>
#include <asm/imx-common/gpio.h>
#include <asm/sizes.h>

#define CONFIG_MX6
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define MACH_TYPE_UDOO		4800
#define CONFIG_MACH_TYPE	MACH_TYPE_UDOO

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(10 * SZ_1M)

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_MXC_GPIO

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART2_BASE

/* SATA Configs */

#if defined(CONFIG_MX6Q)
#define CONFIG_CMD_SATA
#endif
#ifdef CONFIG_CMD_SATA
#define CONFIG_DWC_AHSATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
#define CONFIG_LBA48
#define CONFIG_LIBATA
#endif

/* Network support */

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_CMD_NET
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE                    ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE             RGMII
#define CONFIG_ETHPRIME                 "FEC"
#define CONFIG_FEC_MXC_PHYADDR          6
#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL
#define CONFIG_PHY_MICREL_KSZ9031

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX		1
#define CONFIG_BAUDRATE			115200

/* HDMI or LVDS Display Configuration */
#define CONFIG_VIDEO_ENABLED
#ifdef CONFIG_VIDEO_ENABLED
#define CONFIG_VIDEO
#define CONFIG_VIDEO_IPUV3
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_IPUV3_CLK 260000000
#define CONFIG_CONSOLE_MUX
#define CONFIG_CMD_HDMIDETECT
#define CONFIG_CMD_PLOTMSG
#define CONFIG_IMX_HDMI
#define BOARD_INFO_STRING  "u-boot-imx-2013-10 on:"
#endif

/* Command definition */
#include <config_cmd_default.h>

#undef CONFIG_CMD_IMLS

#define CONFIG_CMD_BMODE
#define CONFIG_CMD_SETEXPR

#define CONFIG_BOOTDELAY		5

#define CONFIG_SYS_MEMTEST_START	0x10000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 500 * SZ_1M)
#define CONFIG_LOADADDR			0x12000000
#define CONFIG_SYS_TEXT_BASE		0x17800000

/* MMC Configuration */
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	0

#define CONFIG_MMC
#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_BOUNCE_BUFFER
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION

#define CONFIG_DEFAULT_FDT_FILE		"imx6q-udoo.dtb"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"boot=echo No boot source specified\0" \
	"src=sata\0" \
	"bootdelay=5\0" \
	"baudrate=115200\0" \
	"loadaddr=0x12000000\0" \
	"uimage=/boot/uImage\0" \
	"console=ttymxc1\0" \
	"splashpos=m,m\0" \
	"video=video=mxcfb0:dev=hdmi,1920x1080M@60,bpp=32\0" \
	"memory=fbmem=24M gpu_reserved=128M\0" \
	"hdmi_patch=\0" \
	"mmcboot=if mmc rescan; then echo Booting from mmc ...; run mmcloaduimage; run mmcargs; bootm; else mmc boot failed; fi\0" \
	"mmcdev=0\0" \
	"mmcpart=1\0" \
	"mmcroot=/dev/mmcblk0p1 rootwait rw\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} root=${mmcroot} ${hdmi_patch} ${memory} ${video}\0" \
	"mmcloaduimage=ext2load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${uimage}\0" \
	"sataboot=if sata init; then echo Booting from sata ...; run sataloaduimage; run sataargs; bootm; else sata boot failed; fi\0" \
	"satadev=0\0" \
	"satapart=1\0" \
	"sataroot=/dev/sda1 rootwait rw\0" \
	"sataargs=setenv bootargs console=${console},${baudrate} root=${sataroot} ${hdmi_patch} ${memory} ${video}\0" \
	"sataloaduimage=ext2load sata ${satadev}:${satapart} ${loadaddr} ${uimage}\0" \
	"ethprime=FEC\0" \
	"ipaddr=dhcp\0" \
	"serverip=192.192.1.1\0" \
	"nfsroot=/src/nfs4/\0" \
	"netargs=setenv bootargs console=${console},${baudrate} root=/dev/nfs ${hdmi_patch} ${memory} ${video} ip=${ipaddr} nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
	"netboot=echo Booting from net ...; run netargs; if test ${ipaddr} = dhcp; then setenv get_cmd dhcp; else setenv get_cmd tftp; fi; ${get_cmd} ${uimage}; bootm\0" \
	"script=boot.scr\0" \
	"loadbootscript=ext2load ${src} ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0 " \
	"bootscript=echo Running bootscript from ${src} ...; source\0"

#define CONFIG_BOOTCOMMAND \
	   "if run loadbootscript; then " \
	   "run bootscript; " \
	   "else " \
	   "run ${src}boot; run sataboot; run mmcboot; run netboot;" \
	   "fi; "
/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT	       "UDOO board => "
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_CBSIZE		256

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS	       16
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

#define CONFIG_CMDLINE_EDITING

/* Physical Memory Map */
#define ONEGIGA	       		       1
#define CONFIG_NR_DRAM_BANKS	 1
#define PHYS_SDRAM	 MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_SIZE			(8 * 1024)

#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_OFFSET		(6 * 128 * 1024)  // 0x000C0000
#define CONFIG_SYS_MMC_ENV_DEV		0

#define CONFIG_OF_LIBFDT
#define CONFIG_CMD_BOOTZ

#ifndef CONFIG_SYS_DCACHE_OFF
#define CONFIG_CMD_CACHE
#endif

#endif			       /* __CONFIG_H * */
