#include "tte_config.h"
#include "tte_target.h"
#include "tte_hw_timer.h"
#include "tte_api.h"
#include "linux/string.h"

#include "SHA1_Crypto.h"
#include "SHA2_Crypto.h"
#include "SHA3_sponge.h"

// ******************************************************************************
// ** Created by Anirban Bhattacharjee and Goncalo Martins **
// ******************************************************************************

#define TMSG_SIZE		6	//bytes
#define TFRAME_SIZE		(TMSG_SIZE + HMAC_TAG_20BYTES)

static void task1(void *arg)
{
	// Auxiliar Variables
	static int taskInit = 0;
	static unsigned char counter = 0;
	int i,j;
	int retVal;

	// TTTech Variables
	tte_buffer_t buf;
	tte_frame_t frame;

	// HMAC Variables
	unsigned char *text = "Hello!";
	int text_len = strlen(text);
	unsigned char *key = "5FCD395FCD395FCD395FCD395FCD395FCD395FCD395FCD312AF3JAK86AA3ABS0";
	int key_len = strlen(key);
	unsigned char digest[64];

	//Compute HMAC
	text[0] = counter;
	hmac_sha1(text, text_len, key, key_len, digest);
	hmac_sha256(key, keylen, text, text_len ,digest);
	sponge_hmac_512(digest, key, strlen(key), text, strlen(text) );
	counter++;

	//** send msg with 300 ID to LKC
	// obtain a buffer hTMSG_SIZEandle
	tte_get_ct_output_buf(0, 300, &buf);
	// prepare the frame header (big endian)
	frame.eth_hdr.type = cpu_to_be16(0x88d7); //cpu_to_be16(0xD178);
	frame.length = TFRAME_SIZE;
	// open the message buffer (lock a single free message slot)
	retVal = tte_open_output_buf(&buf, &frame);

	// check if there is space to store message
	if(retVal >= ETT_SUCCESS){

		// Send Msg
		for(i=0; i<TMSG_SIZE; i++){
			frame.data[i] = text[i];
		}

		// Send Tag
		j=0;
		for(i=TMSG_SIZE; i < (HMAC_TAG_20BYTES + TMSG_SIZE); i++){
			frame.data[i] = digest[j];
			j++;
		}
	}

	// close the buffer (unlocks the message, allows transmission)
	tte_close_output_buf(&buf);

	//	print_log("Task Schedule Time\n");
	return 0;
}

static void task2(void *arg)
{
	//  	static int taskInit = 0;
	//  	int i, j;

	//For now do nothing ...
}


/* -*- coding: iso-8859-1 -*- */
/*** Copyright (C) TTTech Computertechnik AG 2010-2012. All rights reserved. ***/
/*** Module DR_ECU1.dc.c, written at 04-Feb-2012 14:51:58 ***/
/*** generated by TTE-Build 2.2.18 ***/
/*** using plugin TTE_Schema 2.2.3 ***/
/*** using plugin TTE_Prot_Layer_100M 2.2.32 ***/
/*** using plugin TTE_PMC_ESys_1G 2.2.6 ***/
/*** using plugin TTE_PCI_ESys_1G 2.2.6 ***/
/*** using plugin TTE_Network_Config 2.2.34 ***/
/*** using plugin TTE_Mon_Switch_4port_1G 2.2.5 ***/
/*** using plugin TTE_Dev_Switch_8port_100M_V2 2.2.12 ***/
/*** using plugin TTE_Dev_Switch_4port_1G 2.2.13 ***/
/*** using plugin TTE_Dev_Switch_12port_1G 2.2.7 ***/
/*** invoked by user TTEConfig at ISIS-TTECONFIG ***/

#include "tte_config.h"
#include "tte_target.h"
#include "tte_hw_timer.h"

static void app_init (void);
static void bg_task (void);
static void app_err_handler (int32_t tte_error_nr);

tte_message_conf_t rx_message_conf_buffer [] =
{
	{ 100 /* msg_id = VL_TT_100 */
	, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} /* dst_mac */
	, 0x88d7 /* eth_type */
		, 1514 /* size */
		, TTE_QUEUE_BUF /* buf_type */
		, 63 /* buf_len */
	} /* [0] */
	, { 210 /* msg_id = VL_TT_210 */
		, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} /* dst_mac */
	, 0x88d7 /* eth_type */
		, 1514 /* size */
		, TTE_QUEUE_BUF /* buf_type */
		, 63 /* buf_len */
	} /* [1] */
	, { 310 /* msg_id = VL_TT_310 */
		, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} /* dst_mac */
	, 0x88d7 /* eth_type */
		, 1514 /* size */
		, TTE_QUEUE_BUF /* buf_type */
		, 63 /* buf_len */
	} /* [2] */
	, { 4043 /* msg_id = VL_PCF_Switch_sm_IN_4043_0 */
		, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} /* dst_mac */
	, 0x891d /* eth_type */
		, 60 /* size */
		, TTE_DOUBLE_BUF /* buf_type */
		, 2 /* buf_len */
	} /* [3] */
}; /* end rx_message_conf_buffer */

tte_message_conf_t tx_message_conf_buffer [] =
{
	{ 110 /* msg_id = VL_TT_110 */
	, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} /* dst_mac */
	, 0x88d7 /* eth_type */
		, 1514 /* size (byte) */
		, TTE_QUEUE_BUF /* buf_type */
		, 63 /* buf_len */
	} /* [0] */
	, { 200 /* msg_id = VL_TT_200 */
		, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} /* dst_mac */
	, 0x88d7 /* eth_type */
		, 1514 /* size (byte) */
		, TTE_QUEUE_BUF /* buf_type */
		, 63 /* buf_len */
	} /* [1] */
	, { 300 /* msg_id = VL_TT_300 */
		, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} /* dst_mac */
	, 0x88d7 /* eth_type */
		, 1514 /* size (byte) */
		, TTE_QUEUE_BUF /* buf_type */
		, 63 /* buf_len */
	} /* [2] */
}; /* end tx_message_conf_buffer */

tte_task_conf_t task_conf_table [] =
{
	{.fn = task1, .arg = 0},
	{.fn = task2, .arg = 0}
};

tte_schedule_entry_t schedule_entry_buffer [] =
{
	{ (TTE_HZ * 0.00000) /* time */
	, TTE_SCHED_SYNC
	, { (tte_message_conf_t *) & (rx_message_conf_buffer [  3]) } /* tt_msg */
	, 0 /* deadline */
	} /* [0] */
	, { (TTE_HZ * 0.00020) /* time */
		, TTE_SCHED_BG_TX
		, { (tte_message_conf_t *) 19 } /* bg_max */
	, 0 /* deadline */
	} /* [1] */
	, { (TTE_HZ * 0.00040) /* time */
		, TTE_SCHED_BG_TX
		, { (tte_message_conf_t *) 66 } /* bg_max */
	, 0 /* deadline */
	} /* [2] */
	, { (TTE_HZ * 0.00181) /* time */
		, TTE_SCHED_RX
		, { (tte_message_conf_t *) 0 } /* expected VLID(s)=100 */
	, 0 /* deadline */
	} /* [3] */
	// task1 - sensing - triggered at 2.1 ms
	,{ (TTE_HZ * 0.00210),
		TTE_SCHED_TASK,
	{(tte_task_conf_t *) &task_conf_table[0]},
	0
	}
	, { (TTE_HZ * 0.00300) /* time */
		, TTE_SCHED_TT_TX
		, { (tte_message_conf_t *) & (tx_message_conf_buffer [  1]) } /* tt_msg */
	, 0 /* deadline */
	} /* [4] */
	, { (TTE_HZ * 0.00400) /* time */
		, TTE_SCHED_TT_TX
		, { (tte_message_conf_t *) & (tx_message_conf_buffer [  2]) } /* tt_msg */
	, 0 /* deadline */
	} /* [5] */
	, { (TTE_HZ * 0.00513) /* time */
		, TTE_SCHED_BG_TX
		, { (tte_message_conf_t *) 19 } /* bg_max */
	, 0 /* deadline */
	} /* [6] */
	, { (TTE_HZ * 0.00581) /* time */
		, TTE_SCHED_RX
		, { (tte_message_conf_t *) 0 } /* expected VLID(s)=210 */
	, 0 /* deadline */
	} /* [7] */
	, { (TTE_HZ * 0.00681) /* time */
		, TTE_SCHED_RX
		, { (tte_message_conf_t *) 0 } /* expected VLID(s)=310 */
	, 0 /* deadline */
	} /* [8] */
	// task2 - actuation - triggered at 7.51ms
	,{(TTE_HZ * 0.00751),
		TTE_SCHED_TASK,
	{(tte_task_conf_t *) &task_conf_table[1]},
	0
	}
	, { (TTE_HZ * 0.00800) /* time */
		, TTE_SCHED_TT_TX
		, { (tte_message_conf_t *) & (tx_message_conf_buffer [  0]) } /* tt_msg */
	, 0 /* deadline */
	} /* [9] */
}; /* end schedule_entry_buffer */

uint32_t integration_cycle_lookup_buffer [1] =
{
	0 /* [  0] */
}; /* end integration88d7_cycle_l1520ookup */

tte_swes_conf_t tte_conf_buffer =
{ 0x3040506 /* cluster_id */
, 0 /* sync_master */
, 0 /* crankshaft */
, (TTE_HZ * 0.01000) /* period */
, 10 /* cs_blackout_cnt */
, sizeof (rx_message_conf_buffer) / sizeof (rx_message_conf_buffer [0]) /* rx_table_len */
, sizeof (tx_message_conf_buffer) / sizeof (tx_message_conf_buffer [0]) /* tx_table_len */
, sizeof (schedule_entry_buffer) / sizeof (schedule_entry_buffer [0]) /* schedule_table_len */
, sizeof (task_conf_table) / sizeof (task_conf_table [0]) /* task_table_len */
, & (rx_message_conf_buffer [  0]) /* rx_table */
, & (tx_message_conf_buffer [  0]) /* tx_table */
, & (schedule_entry_buffer [  0]) /* schedule_table */
, & (task_conf_table [  0]) /* task_table */
, & (rx_message_conf_buffer [  3]) /* pcf_conf */
, app_init /* init_cb */
, bg_task /* bg_hook_cb */
, app_err_handler /* app_error_cb */
, {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}} /* mac */
, 191 /* tt_rx_ethbufs */
	, 189 /* tt_tx_ethbufs */
	, 65 /* bg_rx_ethbufs */
	, 67 /* bg_tx_ethbufs */
	, 1520 /* tx_maxbufsize */
	, NULL /* app_dcl_cb */
	, NULL /* app_get_node_id */
	, 1 /* promisc */
	, (TTE_HZ * 0.00010) /* max_sched_delay */
	, & (integration_cycle_lookup_buffer [0]) /* ic_lookup_tbl */
	, sizeof (integration_cycle_lookup_buffer) / sizeof (integration_cycle_lookup_buffer [0]) /* ic_lookup_tbl_len */
};

tte_swes_conf_t *tte_conf = &tte_conf_buffer;

tte_conf_t conf_buffer =
{ (uint32_t *) &tte_conf_buffer /* data */
, 0 /* length (unused for protocol layer) */
};

static void app_init (void)
{
	print_log ("HMAC TX Module Started.\n");
}

static void bg_task (void)
{
	return;
}

static void app_err_handler (int32_t tte_error_nr)
{
	print_log ("Executing app error handler ....\n");
}
