/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* Copyright (c) 1999-2007 IVT Corporation
*
* All rights reserved.
* 
---------------------------------------------------------------------------*/
 
/////////////////////////////////////////////////////////////////////////////
// Module Name:
//     Btsdk_Stru.h
// Abstract:
//     This module defines BlueSoleil SDK structures.
// Usage:
//     #include "Btsdk_Stru.h"
// 
// Author://     
//     
// Revision History:
//     2007-12-25		Created
// 
/////////////////////////////////////////////////////////////////////////////



#ifndef _BTSDK_STRU_H
#define _BTSDK_STRU_H


/*************** Structure Definition ******************/ 

typedef struct  _BtSdkCallbackStru
{
	BTUINT16 type;					/*type of callback*/
	void *func;						/*callback function*/
}BtSdkCallbackStru, *PBtSdkCallbackStru;

typedef struct _BtSdkLocalLMPInfoStru
{
	BTUINT8 lmp_feature[8];				/* LMP features */
	BTUINT16 manuf_name;				/* the name of the manufacturer */
	BTUINT16 lmp_subversion;			/* the sub version of the LMP firmware */
	BTUINT8 lmp_version;				/* the main version of the LMP firmware */
	BTUINT8 hci_version;				/* HCI version */
	BTUINT16 hci_revision;				/* HCI revision */
	BTUINT8 country_code;				/* country code */
} BtSdkLocalLMPInfoStru, *PBtSdkLocalLMPInfoStru;

typedef struct _BtSdkVendorCmdStru
{
	BTUINT16 ocf;			/* OCF Range (10 bits): 0x0000-0x03FF */
	BTUINT8	 param_len;		/* length of param in bytes */
	BTUINT8	 param[1];		/* Parameters to be packed in the vendor command. Little endian is adopted. */
} BtSdkVendorCmdStru, *PBtSdkVendorCmdStru;

typedef struct _BtSdkEventParamStru
{
	BTUINT8 ev_code;		/* Event code. */
	BTUINT8 param_len;		/* length of param in bytes */
	BTUINT8 param[1];		/* Event parameters. */
} BtSdkEventParamStru, *PBtSdkEventParamStru;

typedef struct  _BtSdkRemoteLMPInfoStru
{
	BTUINT8 lmp_feature[8];				/* LMP features */
	BTUINT16 manuf_name; 				/* the name of the manufacturer */
	BTUINT16 lmp_subversion;			/* the sub version of the LMP firmware */
	BTUINT8 lmp_version; 				/* the main version of the LMP firmware */
} BtSdkRemoteLMPInfoStru, *PBtSdkRemoteLMPInfoStru;

typedef struct _BtSdkRemoteDevicePropertyStru
{
	BTUINT32 mask;								/*Specifies members available.*/
	BTDEVHDL dev_hdl;							/*Handle assigned to the device record*/
	BTUINT8 bd_addr[BTSDK_BDADDR_LEN];			/*BT address of the device record*/
	BTUINT8 name[BTSDK_DEVNAME_LEN];			/*Name of the device record, must be in UTF-8*/
	BTUINT32 dev_class;							/*Device class*/
	BtSdkRemoteLMPInfoStru lmp_info;			/* LMP info */
	BTUINT8	link_key[BTSDK_LINKKEY_LEN];		/* link key for this device. */
} BtSdkRemoteDevicePropertyStru;  
typedef BtSdkRemoteDevicePropertyStru* PBtSdkRemoteDevicePropertyStru;

/* Parameters of Hold_Mode command */
typedef struct _BtSdkHoldModeStru {
	BTUINT16 conn_hdl;					/* reserved, set it to 0. */
	BTUINT16 max;						/* Hold mode max interval. */
	BTUINT16 min;						/* Hold mode min interval. */
} BtSdkHoldModeStru;
typedef BtSdkHoldModeStru* PBtSdkHoldModeStru;

/* Parameters of Sniff_Mode command */
typedef struct _BtSdkSniffModeStru {
	BTUINT16 conn_hdl;					/* reserved, set it to 0. */
	BTUINT16 max;						/* Sniff mode max interval. */
	BTUINT16 min;						/* Sniff mode min interval. */
	BTUINT16 attempt;					/* Sniff mode attempt value. */
	BTUINT16 timeout;					/* Sniff mode timeout value. */
} BtSdkSniffModeStru;
typedef BtSdkSniffModeStru* PBtSdkSniffModeStru;

/* Parameters of Park_Mode (V1.1) or Park_State (V1.2) command */
typedef struct _BtSdkParkModeStru {
	BTUINT16 conn_hdl;					/* reserved, set it to 0. */
	BTUINT16 max;						/* Beacon max interval. */
	BTUINT16 min;						/* Beacon min interval. */
} BtSdkParkModeStru;
typedef BtSdkParkModeStru* PBtSdkParkModeStru;

/* Basic SDP Element */
typedef struct _BtSdkUUIDStru
{
    BTUINT32 Data1;
    BTUINT16 Data2;
    BTUINT16 Data3;
    BTUINT8  Data4[8];
} BtSdkUUIDStru, *PBtSdkUUIDStru;

typedef struct _BtSdkSDPSearchPatternStru
{
	BTUINT32 mask;					/*Specifies the valid bytes in the uuid*/
	BtSdkUUIDStru uuid;				/*UUID value*/
} BtSdkSDPSearchPatternStru, *PBtSdkSDPSearchPatternStru;

/* Remote service record attributes */
typedef struct _BtSdkRemoteServiceAttrStru
{
	BTUINT16 mask;									/*Decide which parameter to be retrieved*/
	union
	{
		BTUINT16 svc_class;							/* For Compatibility */
		BTUINT16 service_class;
	};												/*Type of this service record*/
	BTDEVHDL dev_hdl;								/*Handle to the remote device which provides this service.*/
	BTUINT8 svc_name[BTSDK_SERVICENAME_MAXLENGTH];	/*Service name in UTF-8*/
	BTLPVOID ext_attributes;						/*Free by the APP*/
	BTUINT16 status;
} BtSdkRemoteServiceAttrStru, *PBtSdkRemoteServiceAttrStru;

typedef struct _BtSdkRmtSPPSvcExtAttrStru 
{
	BTUINT32 size;						/*Size of BtSdkRmtSPPSvcExtAttrStru*/
	BTUINT8  server_channel;			/*Server channel value of this SPP service record*/
} BtSdkRmtSPPSvcExtAttrStru, *PBtSdkRmtSPPSvcExtAttrStru;

typedef struct _BtSdkConnectionPropertyStru
{
	BTUINT32 role : 2;
	BTUINT32 result : 30;
	BTDEVHDL device_handle;
	BTSVCHDL service_handle;
	BTUINT16 service_class;
	BTUINT32 duration;
	BTUINT32 received_bytes;
	BTUINT32 sent_bytes;
} BtSdkConnectionPropertyStru, *PBtSdkConnectionPropertyStru;

typedef struct _BtSdkFileTransferReqStru
{
	BTDEVHDL dev_hdl;		/* Handle to the remote device tries to upload/delete the file. */
	BTUINT16 operation;		/* Specify the operation on the file. 
							It can be one of the following values:
								BTSDK_APP_EV_FTP_PUT: The remote device request to upload the file.
								BTSDK_APP_EV_FTP_DEL_FILE: The remote device request to delete the file.
								BTSDK_APP_EV_FTP_DEL_FOLDER: The remote device request to delete the folder. In this case,
															 file_name specify the name of the folder to be deleted.
							*/
	BTUINT16 flag;			/* Flag specifies the current status of uploading/deleting. 
							It can be one of the following values:
								BTSDK_ER_CONTINUE: The remote device request to upload/delete the file. 
								BTSDK_ER_SUCCESS: The remote device uploads/deletes the file successfully. 
								Other value: Error code specifies the reason of uploading/deleting failure. 
							*/
	BTUINT8	 file_name[BTSDK_PATH_MAXLENGTH];	/* the name of the file uploaded/deleted or to be uploaded/deleted */
} BtSdkFileTransferReqStru, *PBtSdkFileTransferReqStru;

typedef struct _BtSdkAppExtSPPAttrStru
{
	BTUINT32			size;									/* Size of this structure */
	BTUINT32			sdp_record_handle;						/* 32bit interger specifies the SDP service record handle */
	BtSdkUUIDStru 		service_class_128;						/* 128bit UUID specifies the service class of this service record */
	BTUINT8				svc_name[BTSDK_SERVICENAME_MAXLENGTH];	/* Service name, in UTF-8 */
	BTUINT8				rf_svr_chnl;							/* RFCOMM server channel assigned to this service record */
	BTUINT8				com_index;								/* Index of the local COM port assigned to this service record */
} BtSdkAppExtSPPAttrStru, *PBtSdkAppExtSPPAttrStru;

/* lParam for SPP */
typedef struct _BtSdkSPPConnParamStru
{
	BTUINT32 size;
	BTUINT16 mask;	//Reserved set 0
	BTUINT8 com_index;
} BtSdkSPPConnParamStru, *PBtSdkSPPConnParamStru;

/* lParam for OPP */
typedef struct _BtSdkOPPConnParamStru
{
	BTUINT32 size;									/*Size of this structure, use for verification and versioning.*/
	BTUINT8 inbox_path[BTSDK_PATH_MAXLENGTH];		/*must in UTF-8*/
	BTUINT8 outbox_path[BTSDK_PATH_MAXLENGTH];		/*must in UTF-8*/
	BTUINT8 own_card[BTSDK_CARDNAME_MAXLENGTH]; 	/*must in UTF-8*/
} BtSdkOPPConnParamStru, *PBtSdkOPPConnParamStru;

/* lParam for DUN */
typedef struct _BtSdkDUNConnParamStru
{ 
	BTUINT32 size;
	BTUINT16 mask;	//Reserved set 0
	BTUINT8 com_index;
} BtSdkDUNConnParamStru, *PBtSdkDUNConnParamStru;

/* lParam for FAX */
typedef struct _BtSdkFAXConnParamStru 
{
	BTUINT32 size;
	BTUINT16 mask;	//Reserved set 0
	BTUINT8 com_index;
} BtSdkFAXConnParamStru, *PBtSdkFAXConnParamStru;

/* Used By +COPS */
typedef struct Btsdk_HFP_COPSInfo {
	BTUINT8 	mode;				/* current mode and provides no information with regard to the name of the operator */
	BTUINT8 	format;				/* the format of the operator parameter string */
	BTUINT8		operator_len;
	BTINT8 	operator_name[1];	/* the string in alphanumeric format representing the name of the network operator */	
} Btsdk_HFP_COPSInfoStru, *PBtsdk_HFP_COPSInfoStru;

/* Used By +BINP, +CNUM, +CLIP, +CCWA */
typedef struct Btsdk_HFP_PhoneInfo {
	BTUINT8 	type;				/* the format of the phone number provided */
	BTUINT8 	service;			/* Indicates which service this phone number relates to. Shall be either 4 (voice) or 5 (fax). */
	BTUINT8 	num_len;			/* the length of the phone number provided */	
	BTINT8 		number[32];			/* subscriber number, the length shall be PHONENUM_MAX_DIGITS */	
	BTUINT8 	name_len;			/* length of subaddr */
	BTINT8 		alpha_str[1];		/* string type subaddress of format specified by <cli_validity> */	
} Btsdk_HFP_PhoneInfoStru, *PBtsdk_HFP_PhoneInfoStru;

/* Used By +CLCC */
typedef struct Btsdk_HFP_CLCCInfo {
	BTUINT8 	idx;				/* The numbering (start with 1) of the call given by the sequence of setting up or receiving the calls */
	BTUINT8 	dir;				/* Direction, 0=outgoing, 1=incoming */
	BTUINT8 	status;				/* 0=active, 1=held, 2=dialling(outgoing), 3=alerting(outgoing), 4=incoming(incoming), 5=waiting(incoming) */
	BTUINT8 	mode;				/* 0=voice, 1=data, 2=fax */
	BTUINT8 	mpty;				/* 0=not multiparty, 1=multiparty */
	BTUINT8		type;				/* the format of the phone number provided */
	BTUINT8		num_len;			/* the length of the phone number provided */	
	BTINT8		number[1];			/* phone number */	
} Btsdk_HFP_CLCCInfoStru, *PBtsdk_HFP_CLCCInfoStru;

/* current state mask code for function HFP_AG_SetCurIndicatorVal */
typedef struct Btsdk_HFP_CINDInfo {
	BTUINT8		service;			/* 0=unavailable, 1=available */
	BTUINT8		call;				/* 0=no active call, 1=have active call */
	BTUINT8		callsetup;			/* 0=no callsetup, 1=incoming, 2=outgoing, 3=outalert */
	BTUINT8 	callheld;			/* 0=no callheld, 1=active-hold, 2=onhold */
	BTUINT8 	signal;				/* 0~5 */
	BTUINT8		roam;				/* 0=no roam, 1= roam */
	BTUINT8		battchg;			/* 0~5 */
} Btsdk_HFP_CINDInfoStru, *PBtsdk_HFP_CINDInfoStru;

/* Parameter of the BTSDK_HFP_EV_SLC_ESTABLISHED_IND and BTSDK_HFP_EV_SLC_RELEASED_IND events */
typedef struct Btsdk_HFP_ConnInfo {
    BTUINT16 role; /* 16bit UUID specifies the local role of the connection:
                          BTSDK_CLS_HANDSFREE - Local device acts as a HF. 
                          BTSDK_CLS_HANDSFREE_AG - Local device acts as a Hands-free AG. 
                          BTSDK_CLS_HEADSET - Local device acts as a HS. 
                          BTSDK_CLS_HEADSET_AG - Local device acts as a Headset AG. */
	BTDEVHDL dev_hdl;  /* Handle to the remote device. */
} Btsdk_HFP_ConnInfoStru, *PBtsdk_HFP_ConnInfoStru;

/* Used by BTSDK_HFP_EV_ATCMD_RESULT */
typedef struct Btsdk_HFP_ATCmdResult {
	BTUINT16	cmd_code;			/* Which AT command code got an error */
	BTUINT8	    result_code;		/* What result occurs, BTSDK_HFP_APPERR_TIMEOUT, CME Error Code or standard error result code */
} Btsdk_HFP_ATCmdResultStru, *PBtsdk_HFP_ATCmdResultStru;

/* lParam of Btsdk_StartClient, Btsdk_StartClientEx and Btsdk_ConnectShortCutEx; and,
   ext_attributes of BtSdkLocalServerAttrStru. */
typedef struct _BtSdkHFPUIParam {
	BTUINT32 size;      /* Must set to sizeof(BtSdkHFPConnParamStru) */
	BTUINT16 mask;	    /* Reserved, set to 0 */
	BTUINT16 features;  /* Local supported features.
	                       1) For HSP, it shall be 0.
	                       2) For HFP-HF, it can be the bit OR operation of following values:
	                          BTSDK_HF_BRSF_NREC, BTSDK_HF_BRSF_3WAYCALL, BTSDK_HF_BRSF_CLIP,
	                          BTSDK_HF_BRSF_BVRA, BTSDK_HF_BRSF_RMTVOLCTRL, BTSDK_HF_BRSF_ENHANCED_CALLSTATUS,
	                          BTSDK_HF_BRSF_ENHANCED_CALLCONTROL.
	                       3) For HFP-AG, it can be the bit OR operation of following values:
	                          BTSDK_AG_BRSF_3WAYCALL, BTSDK_AG_BRSF_NREC, BTSDK_AG_BRSF_BVRA,
	                          BTSDK_AG_BRSF_INBANDRING, BTSDK_AG_BRSF_BINP, BTSDK_AG_BRSF_REJECT_CALL,
	                          BTSDK_AG_BRSF_ENHANCED_CALLSTATUS, BTSDK_AG_BRSF_ENHANCED_CALLCONTROL,
	                          BTSDK_AG_BRSF_EXTENDED_ERRORRESULT.
	                     */
} BtSdkHFPUIParamStru, *PBtSdkHFPUIParamStru,
  BtSdkHFPConnParamStru, *PBtSdkHFPConnParamStru,
  BtSdkLocalHFPServerAttrStru, *PBtSdkHFPLocalHFPServerAttrStru;

typedef struct _BtSdk_SDAP_PNPINFO
{
	BTUINT16 size;				
	BTUINT16 mask;				
	BTUINT32 svc_hdl;			
	BTUINT16 spec_id;			
	BTUINT16 vendor_id;			
	BTUINT16 product_id;		
	BTUINT16 version_value;		
	BTUINT16 vendor_id_src;		
}BtSdk_SDAP_PNPINFO, *PBtSdk_SDAP_PNPINFO;

typedef struct _BtSdkRmtDISvcExtAttrStru
{
	BTUINT32 size;				
	BTUINT16 mask;				
	BTUINT16 spec_id;			
	BTUINT16 vendor_id;			
	BTUINT16 product_id;		
	BTUINT16 version;			
	BTBOOL  primary_record;		
	BTUINT16 vendor_id_source;	
	BTUINT16 list_size;			
	BTUINT8  str_url_list[1];
} BtSdkRmtDISvcExtAttrStru, *PBtSdkRmtDISvcExtAttrStru;

#endif