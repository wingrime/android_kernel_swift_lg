/* Created by princlee@lge.com  
 * arch/arm/mach-msm/rpc_server_misc.c
 *
 * Copyright (C) 2008 LGE, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <mach/msm_rpcrouter.h>
#include <../../../drivers/staging/android/timed_output.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>
#include <linux/eve_at.h>
#include <linux/at_kpd_eve.h>
#include <linux/input.h>
/* Misc server definitions. */

#include <asm/uaccess.h>

#define MISC_APPS_APISPROG		0x30000006
#define MISC_APPS_APISVERS		0




#define ONCRPC_MISC_APPS_APIS_NULL_PROC 0
#define ONCRPC_LCD_MESSAGE_PROC 1
#define ONCRPC_LCD_DEBUG_MESSAGE_PROC 2


#define ONCRPC_LGE_ATCMD_FACTORY_PROC 3
#define ONCRPC_LGE_ATCMD_MSG_PROC 4
#define ONCRPC_LGE_ATCMD_MSG_RSTSTR_PROC 5
#define ONCRPC_LGE_ATCMD_FACTORY_LARGE_PROC 6
#define ONCRPC_LGE_GET_FLEX_MCC_PROC 7 
#define ONCRPC_LGE_GET_FLEX_MNC_PROC 8 
#define ONCRPC_LGE_GET_FLEX_OPERATOR_CODE_PROC 9 
#define ONCRPC_LGE_GET_FLEX_COUNTRY_CODE_PROC 10

#define DSATAPIPROG		0x30000074
#define DSATAPIVERS		0

#define ONCRPC_DSATAPI_NULL_PROC 0
#define ONCRPC_DSAT_CHANGE_BAUD_PROC 1
#define ONCRPC_DSAT_GET_BAUD_PROC 2
#define ONCRPC_DSAT_GET_SREG_VAL_PROC 3
#define ONCRPC_DSAT_AT_CMD_TEST 4


//struct rpc_misc_apps_bases_args {
  //	uint32_t at_cmd;
  //	uint32_t at_act;
  //	uint32_t at_param;
  //};

//struct rpc_misc_apps_LARGE_bases_args {
//	uint32_t at_cmd;
//	uint32_t at_act;
//	uint32_t sendNum;
//	uint32_t endofBuffer;
//	uint32_t buffersize;
//	AT_SEND_BUFFER_t buffer[MAX_SEND_SIZE_BUFFER];
//	/
//};

static struct atcmd_dev *atpdev;

//extern void update_battery_status_to_android(void);//temp
// Commands

// at_cmd value start
// !!! must same with dsatfactory.h in ARM9 (AMSS) side  !!!
//////////////////////////////////////////////////////////////////
#define ATCMD_AT	1
//Information Check
#define ATCMD_FRST	2
#define ATCMD_SWV	3
#define ATCMD_INFO	4
#define ATCMD_IMEI	5
#define ATCMD_IMPL	6
#define ATCMD_SLEN	7
#define ATCMD_SCHK	8
#define ATCMD_SULC	9
#define ATCMD_IDDE	10
#define ATCMD_HLRV	11
#define ATCMD_ISSIM	12
#define ATCMD_FUSG	13
#define ATCMD_DRMCERT	14
#define ATCMD_DRMTYPE	15
#define ATCMD_DRMERASE	16
#define ATCMD_INITDB	17
#define ATCMD_SVN	18
#define ATCMD_HWVER	19
// Calibration & Auto Test
#define ATCMD_CAMP	20
#define ATCMD_BNDI	21
#define ATCMD_CALM	22
#define ATCMD_NETORD	23
#define ATCMD_NETMODE	24
#define ATCMD_CALCK	25
#define ATCMD_CALDT	26
#define ATCMD_TESTCK	27
#define ATCMD_RADCK	28
#define ATCMD_RESTART	29
#define ATCMD_SFTUNE	30
// Call & Special Function Test
#define ATCMD_ACS	31
#define ATCMD_ECALL	32
#define ATCMD_FKPD	33
#define ATCMD_GKPD	34
#define ATCMD_MID	35
#define ATCMD_VLC	36
#define ATCMD_BATI	37
#define ATCMD_BATL	38
#define ATCMD_ANTB	39
#define ATCMD_SPM	40
#define ATCMD_FMT	41
#define ATCMD_FMR	42
#define ATCMD_MPT	43
#define ATCMD_MPC	44
#define ATCMD_AVR	45
#define ATCMD_EMT	46
#define ATCMD_INISIM	47
#define ATCMD_IRDA	48
#define ATCMD_PSENT	49
#define ATCMD_BATC	50
// Bluetooth Test	
#define ATCMD_BDCK	51
#define ATCMD_BTAD	52
#define ATCMD_BTTM	53 // hotaek 20070608 for BTTM
// DMB Test
#define ATCMD_DVBH	54
#define ATCMD_TDMB	55
#define ATCMD_CAS	56
// Misc
#define ATCMD_SYNC	57
#define ATCMD_BOFF	58//hotaek 2007/1/8 BOFF 
#define ATCMD_FC	59
#define ATCMD_FO	60
#define ATCMD_CONFIG	61
#define ATCMD_NDER	62
#define ATCMD_SPCK	63
#define ATCMD_SPUC	64
#define ATCMD_BCPL	65
#define ATCMD_SIMOFF	66
#define ATCMD_CGATT	67
#define ATCMD_RNO	68
#define ATCMD_LCD	69
#define ATCMD_CAM	70
#define ATCMD_MOT	71
// Wireless LAN
#define ATCMD_WLAN	72
#define ATCMD_WLANT	73
#define ATCMD_WLANR	74
// PMIC
#define ATCMD_PMRST	75
// Wireless LAN extention
#define ATCMD_WLANRF	76
#define ATCMD_WLANCAL	77
#define ATCMD_WLANWL	78

#define ATCMD_ATD	  79
#define ATCMD_MTC	  80

#define ATCMD_DRMINDEX		81
#define ATCMD_FLIGHT		82
#define ATCMD_LANG			83
// yorong drm command
#define ATCMD_DRMIMEI		84
#define ATCMD_POWERDOWN		85 

#define ATCMD_QEM		86

#define ATCMD_FRSTSTATUS			87
#define ATCMD_NOT_ATMCD_EARSENSE			88

//////////////////////////////////////////////////////////////////
// at_cmd value end



// at_act value  start
// !!! must same with dsatfactory.h in ARM9 (AMSS) side  !!!
//action/query/range/assign
//////////////////////////////////////////////////////////////////
#define ATCMD_ACTION	0
#define ATCMD_QUERY		1
#define ATCMD_RANGE		2
#define ATCMD_ASSIGN	3
//////////////////////////////////////////////////////////////////
// at_act value  end

#define OTHER_FB_TIMEOUT 3000
#define ORG_FB_TIMEOUT 21000

struct timer_list lg_fb_control;
static int fb_control_timer_init=0;
//extern int msm_fb_refesh_enabled;
static void lg_fb_control_timer(unsigned long arg)
{
	printk(KERN_INFO "%s is expire\n",__func__);
	//	msm_fb_refesh_enabled=1;
}



// dsatHandleAT_ARM11 return Value
//////////////////////////////////////////////////////////////////
#define HANDLE_OK  0
#define HANLDE_FAIL 1
#define HANDLE_ERROR 2
#define HANDLE_OK_MIDDLE 4
//////////////////////////////////////////////////////////////////
/* constants relating to events sent into the input core */

#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <asm/gpio.h>
#include <mach/msm_i2ckbd.h>
#include <linux/delay.h>
//#include <asm/arch/lprintk.h>
#include <linux/at_kpd_eve.h> 
#include <mach/msm_rpcrouter.h> 

static char s_bufFlexINI[500];
static char s_bufItem[500];
static char s_bufValue2[400];
static char s_bufValue3[100];

#if defined(CONFIG_MACH_MSM7X27_SWIFT)
static unsigned char at_fkpd_keycode[42]  = { //Encoder from AT cmd ASCII to Android key map code for GKPD
KEY_VOLUMEUP,	KEY_VOLUMEDOWN,	KEY_HOME,	KEY_SEARCH,	KEY_CAMERA,	242 /* FOCUS */,	KEY_6,	KEY_7,	KEY_8,	KEY_9,	/*#*/228,	227/***/, KEY_SEND, KEY_MENU,
85,			68,			72,			65,			67,			70,			54,			55,			56,			57,			35,			42,			83,				77,
41,			33,			64,			126,			36,			37,			60,			38,			62,			40,			63,			124,			115,				101
};
#else
static unsigned char at_fkpd_keycode[42]  = { //Encoder from AT cmd ASCII to Android key map code for GKPD
KEY_0,	KEY_1,	KEY_2,	KEY_3,	KEY_4,	KEY_5,	KEY_6,	KEY_7,	KEY_8,	KEY_9,	/*#*/228,	227/***/, KEY_SEND, KEY_END,
48,			49,			50,			51,			52,			53,			54,			55,			56,			57,			35,			42,			83,				69,
41,			33,			64,			126,			36,			37,			60,			38,			62,			40,			63,			124,			115,				101
};
#endif

enum kbd_inevents {
	QKBD_IN_KEYPRESS        = 1,
	QKBD_IN_KEYRELEASE      = 0,
	QKBD_IN_MXKYEVTS        = 256
};


// static int fkpd_press_delay, fkpd_release_delay, fkpd_work_index =0,
static int gkpd_state, gkpd_last_index, gkpd_value[21],fkpd_temp_index=0,  fkpd_type=0;
static int fkpd_buffer[41] = { 200, 200, 200, 200, 200,   200, 200, 200, 200, 200,   200, 200, 200, 200, 200,   200, 200, 200, 200, 200, 
	                  200, 200, 200, 200, 200,   200, 200, 200, 200, 200,   200, 200, 200, 200, 200,   200, 200, 200, 200, 200, 200};
	                  
int at_gkpd_cfg(unsigned int type, int value) //0,0 : READ STATE, 0,1 : READ LEFT VALUE, 1,0 : WRITE DISABLE VALUE, 1,1 : WRITE ENABLE VALUE
{

	return 0;
}
void write_gkpd_value(int value)
{
	
}

int fkpd_xlkcode (int value)
{

	return 0;	
}
void manual_fkpd_input (struct input_dev *dev, int value)
{		
	             				
}

void auto_fkpd_input (struct input_dev *dev, int value, int time1, int time2)
{
				
}

//extern struct input_dev *at_input_dev;


static void at_fkpd_fetchkeys (struct work_struct *work)
{		

}

DECLARE_WORK(fkpd_work, at_fkpd_fetchkeys); //antispoon test


int at_fkpd_cfg ( unsigned int type, int value)
{	
	     
	return 0; 
}	


// change little Endian to Big endian (there is not change function in Kernel)
char cpu_to_be8_AT(char value)
{
#define BITS_NUM_PER_BYTE  8
char c_value = 0;
#if 0

int loop = 0;
int TOT_SIZE = sizeof(char)*BITS_NUM_PER_BYTE;

for (loop = 0; loop < TOT_SIZE/2; loop++)
{
c_value |= (value & (1 << loop)) << (TOT_SIZE - loop -1);

}
// there is no ODD lengh 
for (loop = TOT_SIZE/2; loop < TOT_SIZE; loop++)
{
c_value |= (value & (1 << loop)) >> (TOT_SIZE/2 - loop +1 );

}
#else
c_value = value;
#endif
return c_value;
}

#define CAM_AVR_INITIAL     0
#define CAM_AVR_ON          1
#define CAM_AVR_SHOT        2
#define CAM_AVR_SAVE        3
#define CAM_AVR_CALL        4
#define CAM_AVR_ERASE       5
#define AVR_FLASH_ON        6
#define AVR_FLASH_OFF       7
#define CAM_STROBE_ON       8
#define CAM_STROBE_OFF      9
#define CAM_ZOOM_ON         11
#define CAM_ZOOM_OFF        12

//void lge_atcmd_report_key(unsigned int, unsigned int);

#ifdef CONFIG_BACKLIGHT_EVE
void lge_atcmd_boff(void);
#endif

int external_memory_test(void)
{

	return 0;
}

static int set_kernel_factory_reset_status(uint32_t status)
{

	return 0;
}

static int get_kernel_factory_reset_status()
{

	return 0;
}

extern unsigned char headset_inserted;


// at_param shall be ONLY  INTERGER, do not  (float / pointer / string...)
static int  dsatHandleAT_ARM11(uint32_t at_cmd, uint32_t at_act, uint32_t at_param,struct msm_rpc_server *server)
{
	int result = HANDLE_OK;
	return result;
}

int lg_get_flex_from_xml(char *strIndex, char* flexValue)
{


	return 0;

}

static int eta_execute(char *string)
{
	int ret=0;

	return ret;
}
static int  dsatHandleAT_ARM11_LARGE(struct rpc_misc_apps_LARGE_bases_args *args,struct msm_rpc_server *server)
{

  return 0;


}


static int handle_misc_rpc_call(struct msm_rpc_server *server,
			   struct rpc_request_hdr *req, unsigned len)
{
return  RPC_ACCEPTSTAT_SUCCESS;

}



static struct msm_rpc_server rpc_server = {

	.prog = MISC_APPS_APISPROG,
	.vers = MISC_APPS_APISVERS,
	.rpc_call = handle_misc_rpc_call,



};

static int __init rpc_misc_server_init(void)
{
	return msm_rpc_create_server(&rpc_server);
}


module_init(rpc_misc_server_init);

