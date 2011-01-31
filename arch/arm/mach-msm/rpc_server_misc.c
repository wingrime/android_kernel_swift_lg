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

#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <asm/gpio.h>
#include <mach/msm_i2ckbd.h>
#include <linux/delay.h>
#include <linux/at_kpd_eve.h> 
#include <mach/msm_rpcrouter.h> 

static int handle_misc_rpc_call(struct msm_rpc_server *server,
			   struct rpc_request_hdr *req, unsigned len)
{
return  RPC_ACCEPTSTAT_SUCCESS;
}
#define MISC_APPS_APISPROG		0x30000006
#define MISC_APPS_APISVERS		0
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
