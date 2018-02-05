/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
* Copyright (c) 1999-2007 IVT Corporation
*
* All rights reserved.
* 
---------------------------------------------------------------------------*/
 
/////////////////////////////////////////////////////////////////////////////
// Module Name:
//     Btsdk_Macro.h
// Abstract:
//     This Module defines macros used by APIs and structures.
// Usage:
//     #include "Btsdk_Macro.h"
// 
// Author://     
//     
// Revision History:
//     2007-12-25		Created
// 
/////////////////////////////////////////////////////////////////////////////



#ifndef _BTSDK_MACRO_H
#define _BTSDK_MACRO_H


typedef char BTINT8;
typedef unsigned char BTUINT8;
typedef unsigned char BTBOOL;
typedef short BTINT16;
typedef unsigned short BTUINT16;
typedef long BTINT32;
typedef unsigned long BTUINT32;
typedef void * BTLPVOID;

typedef BTUINT32 BTDEVHDL;
typedef BTUINT32 BTSVCHDL;
typedef BTUINT32 BTCONNHDL;
typedef BTUINT32 BTSHCHDL;
typedef BTUINT32 BTSDKHANDLE;

#ifndef FUNC_EXPORT
#define FUNC_EXPORT 

#endif


#define BTSDK_TRUE		1
#define BTSDK_FALSE		0



/* Max size value used in service attribute structures */
#define BTSDK_SERVICENAME_MAXLENGTH				80
#define BTSDK_MAX_SUPPORT_FORMAT				6		/* OPP format number */
#define BTSDK_PATH_MAXLENGTH					256		/* Shall not be larger than FTP_MAX_PATH and OPP_MAX_PATH */
#define BTSDK_CARDNAME_MAXLENGTH				256		/* Shall not be larger than OPP_MAX_NAME */
#define BTSDK_PACKETTYPE_MAXNUM					10		/* PAN supported network packet type */

/* Max size value used in device attribute structures */
#define BTSDK_DEVNAME_LEN						64		/* Shall not be larger than MAX_NAME_LEN */
#define BTSDK_SHORTCUT_NAME_LEN					100
#define BTSDK_BDADDR_LEN						6
#define BTSDK_LINKKEY_LEN						16
#define BTSDK_PINCODE_LEN						16

/* Invalid handle value for all handle type */
#define BTSDK_INVALID_HANDLE					0x00000000

/* Error Code List */
#define BTSDK_OK												0x0000

/* SDP error */
#define BTSDK_ER_SDP_INDEX										0x00C0
#define BTSDK_ER_SERVER_IS_ACTIVE								(BTSDK_ER_SDP_INDEX + 0x0000)
#define BTSDK_ER_NO_SERVICE										(BTSDK_ER_SDP_INDEX + 0x0001)
#define BTSDK_ER_SERVICE_RECORD_NOT_EXIST						(BTSDK_ER_SDP_INDEX + 0x0002)

/* General Error */
#define BTSDK_ER_GENERAL_INDEX									0x0300
#define BTSDK_ER_HANDLE_NOT_EXIST								(BTSDK_ER_GENERAL_INDEX + 0x0001)
#define BTSDK_ER_OPERATION_FAILURE								(BTSDK_ER_GENERAL_INDEX + 0x0002)
#define BTSDK_ER_SDK_UNINIT										(BTSDK_ER_GENERAL_INDEX + 0x0003)
#define BTSDK_ER_INVALID_PARAMETER								(BTSDK_ER_GENERAL_INDEX + 0x0004)
#define BTSDK_ER_NULL_POINTER									(BTSDK_ER_GENERAL_INDEX + 0x0005)
#define BTSDK_ER_NO_MEMORY										(BTSDK_ER_GENERAL_INDEX + 0x0006)
#define BTSDK_ER_BUFFER_NOT_ENOUGH								(BTSDK_ER_GENERAL_INDEX + 0x0007)
#define BTSDK_ER_FUNCTION_NOTSUPPORT							(BTSDK_ER_GENERAL_INDEX + 0x0008)
#define BTSDK_ER_NO_FIXED_PIN_CODE								(BTSDK_ER_GENERAL_INDEX + 0x0009)
#define BTSDK_ER_CONNECTION_EXIST								(BTSDK_ER_GENERAL_INDEX + 0x000A)
#define BTSDK_ER_OPERATION_CONFLICT								(BTSDK_ER_GENERAL_INDEX + 0x000B)
#define BTSDK_ER_NO_MORE_CONNECTION_ALLOWED						(BTSDK_ER_GENERAL_INDEX + 0x000C)
#define BTSDK_ER_ITEM_EXIST										(BTSDK_ER_GENERAL_INDEX + 0x000D)
#define BTSDK_ER_ITEM_INUSE										(BTSDK_ER_GENERAL_INDEX + 0x000E)
#define BTSDK_ER_DEVICE_UNPAIRED								(BTSDK_ER_GENERAL_INDEX + 0x000F)

/* HCI Error */
#define BTSDK_ER_HCI_INDEX										0x0400
#define BTSDK_ER_UNKNOWN_HCI_COMMAND							(BTSDK_ER_HCI_INDEX + 0x0001)
#define BTSDK_ER_NO_CONNECTION									(BTSDK_ER_HCI_INDEX + 0x0002)
#define BTSDK_ER_HARDWARE_FAILURE								(BTSDK_ER_HCI_INDEX + 0x0003)
#define BTSDK_ER_PAGE_TIMEOUT									(BTSDK_ER_HCI_INDEX + 0x0004)
#define BTSDK_ER_AUTHENTICATION_FAILURE							(BTSDK_ER_HCI_INDEX + 0x0005)
#define BTSDK_ER_KEY_MISSING									(BTSDK_ER_HCI_INDEX + 0x0006)
#define BTSDK_ER_MEMORY_FULL									(BTSDK_ER_HCI_INDEX + 0x0007)
#define BTSDK_ER_CONNECTION_TIMEOUT								(BTSDK_ER_HCI_INDEX + 0x0008)
#define BTSDK_ER_MAX_NUMBER_OF_CONNECTIONS						(BTSDK_ER_HCI_INDEX + 0x0009)
#define BTSDK_ER_MAX_NUMBER_OF_SCO_CONNECTIONS					(BTSDK_ER_HCI_INDEX + 0x000A)
#define BTSDK_ER_ACL_CONNECTION_ALREADY_EXISTS					(BTSDK_ER_HCI_INDEX + 0x000B)
#define BTSDK_ER_COMMAND_DISALLOWED								(BTSDK_ER_HCI_INDEX + 0x000C)
#define BTSDK_ER_HOST_REJECTED_LIMITED_RESOURCES				(BTSDK_ER_HCI_INDEX + 0x000D)
#define BTSDK_ER_HOST_REJECTED_SECURITY_REASONS					(BTSDK_ER_HCI_INDEX + 0x000E)
#define BTSDK_ER_HOST_REJECTED_PERSONAL_DEVICE					(BTSDK_ER_HCI_INDEX + 0x000F)
#define BTSDK_ER_HOST_TIMEOUT									(BTSDK_ER_HCI_INDEX + 0x0010)
#define BTSDK_ER_UNSUPPORTED_FEATURE							(BTSDK_ER_HCI_INDEX + 0x0011)
#define BTSDK_ER_INVALID_HCI_COMMAND_PARAMETERS					(BTSDK_ER_HCI_INDEX + 0x0012)
#define BTSDK_ER_PEER_DISCONNECTION_USER_END					(BTSDK_ER_HCI_INDEX + 0x0013)
#define BTSDK_ER_PEER_DISCONNECTION_LOW_RESOURCES				(BTSDK_ER_HCI_INDEX + 0x0014)
#define BTSDK_ER_PEER_DISCONNECTION_TO_POWER_OFF				(BTSDK_ER_HCI_INDEX + 0x0015)
#define BTSDK_ER_LOCAL_DISCONNECTION							(BTSDK_ER_HCI_INDEX + 0x0016)
#define BTSDK_ER_REPEATED_ATTEMPTS								(BTSDK_ER_HCI_INDEX + 0x0017)
#define BTSDK_ER_PAIRING_NOT_ALLOWED							(BTSDK_ER_HCI_INDEX + 0x0018)
#define BTSDK_ER_UNKNOWN_LMP_PDU								(BTSDK_ER_HCI_INDEX + 0x0019)
#define BTSDK_ER_UNSUPPORTED_REMOTE_FEATURE						(BTSDK_ER_HCI_INDEX + 0x001A)
#define BTSDK_ER_SCO_OFFSET_REJECTED							(BTSDK_ER_HCI_INDEX + 0x001B)
#define BTSDK_ER_SCO_INTERVAL_REJECTED							(BTSDK_ER_HCI_INDEX + 0x001C)
#define BTSDK_ER_SCO_AIR_MODE_REJECTED							(BTSDK_ER_HCI_INDEX + 0x001D)
#define BTSDK_ER_INVALID_LMP_PARAMETERS							(BTSDK_ER_HCI_INDEX + 0x001E)
#define BTSDK_ER_UNSPECIFIED_ERROR								(BTSDK_ER_HCI_INDEX + 0x001F)
#define BTSDK_ER_UNSUPPORTED_LMP_PARAMETER_VALUE				(BTSDK_ER_HCI_INDEX + 0x0020)
#define BTSDK_ER_ROLE_CHANGE_NOT_ALLOWED						(BTSDK_ER_HCI_INDEX + 0x0021)
#define BTSDK_ER_LMP_RESPONSE_TIMEOUT							(BTSDK_ER_HCI_INDEX + 0x0022)
#define BTSDK_ER_LMP_ERROR_TRANSACTION_COLLISION				(BTSDK_ER_HCI_INDEX + 0x0023)
#define BTSDK_ER_LMP_PDU_NOT_ALLOWED							(BTSDK_ER_HCI_INDEX + 0x0024)
#define BTSDK_ER_ENCRYPTION_MODE_NOT_ACCEPTABLE					(BTSDK_ER_HCI_INDEX + 0x0025)
#define BTSDK_ER_UNIT_KEY_USED									(BTSDK_ER_HCI_INDEX + 0x0026)
#define BTSDK_ER_QOS_IS_NOT_SUPPORTED							(BTSDK_ER_HCI_INDEX + 0x0027)
#define BTSDK_ER_INSTANT_PASSED									(BTSDK_ER_HCI_INDEX + 0x0028)
#define BTSDK_ER_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED			(BTSDK_ER_HCI_INDEX + 0x0029)
#define BTSDK_ER_DIFFERENT_TRANSACTION_COLLISION				(BTSDK_ER_HCI_INDEX + 0x002A)
#define BTSDK_ER_QOS_UNACCEPTABLE_PARAMETER						(BTSDK_ER_HCI_INDEX + 0x002C)
#define BTSDK_ER_QOS_REJECTED									(BTSDK_ER_HCI_INDEX + 0x002D)
#define BTSDK_ER_CHANNEL_CLASS_NOT_SUPPORTED					(BTSDK_ER_HCI_INDEX + 0x002E)
#define BTSDK_ER_INSUFFICIENT_SECURITY							(BTSDK_ER_HCI_INDEX + 0x002F)
#define BTSDK_ER_PARAMETER_OUT_OF_RANGE							(BTSDK_ER_HCI_INDEX + 0x0030)
#define BTSDK_ER_ROLE_SWITCH_PENDING							(BTSDK_ER_HCI_INDEX + 0x0032)
#define BTSDK_ER_RESERVED_SLOT_VIOLATION						(BTSDK_ER_HCI_INDEX + 0x0034)
#define BTSDK_ER_ROLE_SWITCH_FAILED								(BTSDK_ER_HCI_INDEX + 0x0035)

/* OBEX error */
#define BTSDK_ER_OBEX_INDEX										0x0600
#define BTSDK_ER_CONTINUE										(BTSDK_ER_OBEX_INDEX + 0x0090)
#define BTSDK_ER_SUCCESS										(BTSDK_ER_OBEX_INDEX + 0x00A0)
#define BTSDK_ER_CREATED										(BTSDK_ER_OBEX_INDEX + 0x00A1)
#define BTSDK_ER_ACCEPTED										(BTSDK_ER_OBEX_INDEX + 0x00A2)
#define BTSDK_ER_NON_AUTH_INFO									(BTSDK_ER_OBEX_INDEX + 0x00A3)
#define BTSDK_ER_NO_CONTENT										(BTSDK_ER_OBEX_INDEX + 0x00A4)
#define BTSDK_ER_RESET_CONTENT									(BTSDK_ER_OBEX_INDEX + 0x00A5)
#define BTSDK_ER_PARTIAL_CONTENT								(BTSDK_ER_OBEX_INDEX + 0x00A6)
#define BTSDK_ER_MULT_CHOICES									(BTSDK_ER_OBEX_INDEX + 0x00B0)
#define BTSDK_ER_MOVE_PERM										(BTSDK_ER_OBEX_INDEX + 0x00B1)
#define BTSDK_ER_MOVE_TEMP										(BTSDK_ER_OBEX_INDEX + 0x00B2)
#define BTSDK_ER_SEE_OTHER										(BTSDK_ER_OBEX_INDEX + 0x00B3)
#define BTSDK_ER_NOT_MODIFIED									(BTSDK_ER_OBEX_INDEX + 0x00B4)
#define BTSDK_ER_USE_PROXY										(BTSDK_ER_OBEX_INDEX + 0x00B5)
#define BTSDK_ER_BAD_REQUEST									(BTSDK_ER_OBEX_INDEX + 0x00C0)
#define BTSDK_ER_UNAUTHORIZED									(BTSDK_ER_OBEX_INDEX + 0x00C1)
#define BTSDK_ER_PAY_REQ										(BTSDK_ER_OBEX_INDEX + 0x00C2)
#define BTSDK_ER_FORBIDDEN										(BTSDK_ER_OBEX_INDEX + 0x00C3)
#define BTSDK_ER_NOTFOUND										(BTSDK_ER_OBEX_INDEX + 0x00C4)
#define BTSDK_ER_METHOD_NOT_ALLOWED								(BTSDK_ER_OBEX_INDEX + 0x00C5)
#define BTSDK_ER_NOT_ACCEPTABLE									(BTSDK_ER_OBEX_INDEX + 0x00C6)
#define BTSDK_ER_PROXY_AUTH_REQ									(BTSDK_ER_OBEX_INDEX + 0x00C7)
#define BTSDK_ER_REQUEST_TIMEOUT								(BTSDK_ER_OBEX_INDEX + 0x00C8)
#define BTSDK_ER_CONFLICT										(BTSDK_ER_OBEX_INDEX + 0x00C9)
#define BTSDK_ER_GONE											(BTSDK_ER_OBEX_INDEX + 0x00CA)
#define BTSDK_ER_LEN_REQ										(BTSDK_ER_OBEX_INDEX + 0x00CB)
#define BTSDK_ER_PREC_FAIL										(BTSDK_ER_OBEX_INDEX + 0x00CC)
#define BTSDK_ER_REQ_ENTITY_TOO_LARGE							(BTSDK_ER_OBEX_INDEX + 0x00CD)
#define BTSDK_ER_URL_TOO_LARGE									(BTSDK_ER_OBEX_INDEX + 0x00CE)
#define BTSDK_ER_UNSUPPORTED_MEDIA_TYPE							(BTSDK_ER_OBEX_INDEX + 0x00CF)
#define BTSDK_ER_SVR_ERR										(BTSDK_ER_OBEX_INDEX + 0x00D0)
#define BTSDK_ER_NOTIMPLEMENTED									(BTSDK_ER_OBEX_INDEX + 0x00D1)
#define BTSDK_ER_BAD_GATEWAY									(BTSDK_ER_OBEX_INDEX + 0x00D2)
#define BTSDK_ER_SERVICE_UNAVAILABLE							(BTSDK_ER_OBEX_INDEX + 0x00D3)
#define BTSDK_ER_GATEWAY_TIMEOUT								(BTSDK_ER_OBEX_INDEX + 0x00D4)
#define BTSDK_ER_HTTP_NOTSUPPORT								(BTSDK_ER_OBEX_INDEX + 0x00D5)
#define BTSDK_ER_DATABASE_FULL									(BTSDK_ER_OBEX_INDEX + 0x00E0)
#define BTSDK_ER_DATABASE_LOCK									(BTSDK_ER_OBEX_INDEX + 0x00E1)

/* Class of Device */
/*major service classes*/
#define BTSDK_SRVCLS_LDM						0x002000     /* Limited Discoverable Mode */
#define BTSDK_SRVCLS_POSITION					0x010000
#define BTSDK_SRVCLS_NETWORK					0x020000
#define BTSDK_SRVCLS_RENDER						0x040000
#define BTSDK_SRVCLS_CAPTURE					0x080000
#define BTSDK_SRVCLS_OBJECT						0x100000
#define BTSDK_SRVCLS_AUDIO						0x200000
#define BTSDK_SRVCLS_TELEPHONE					0x400000
#define BTSDK_SRVCLS_INFOR						0x800000
#define BTSDK_SRVCLS_MASK(a)					(((BTUINT32)(a) >> 13) & 0x7FF)

/*major device classes*/			                                    
#define BTSDK_DEVCLS_MISC						0x000000
#define BTSDK_DEVCLS_COMPUTER					0x000100
#define BTSDK_DEVCLS_PHONE						0x000200
#define BTSDK_DEVCLS_LAP						0x000300
#define BTSDK_DEVCLS_AUDIO						0x000400
#define BTSDK_DEVCLS_PERIPHERAL					0x000500
#define BTSDK_DEVCLS_IMAGE             			0x000600
#define BTSDK_DEVCLS_WEARABLE          			0x000700
#define BTSDK_DEVCLS_UNCLASSIFIED				0x001F00
#define BTSDK_DEVCLS_MASK(a)					(((BTUINT32)(a) >> 8) & 0x1F)
#define BTSDK_MINDEVCLS_MASK(a)					(((BTUINT32)(a) >> 2) & 0x3F)

/*the minor device class field - computer major class */
#define BTSDK_COMPCLS_UNCLASSIFIED				(BTSDK_DEVCLS_COMPUTER | 0x000000) 
#define BTSDK_COMPCLS_DESKTOP					(BTSDK_DEVCLS_COMPUTER | 0x000004)
#define BTSDK_COMPCLS_SERVER            		(BTSDK_DEVCLS_COMPUTER | 0x000008)
#define BTSDK_COMPCLS_LAPTOP            		(BTSDK_DEVCLS_COMPUTER | 0x00000C)
#define BTSDK_COMPCLS_HANDHELD				  	(BTSDK_DEVCLS_COMPUTER | 0x000010)
#define BTSDK_COMPCLS_PALMSIZED					(BTSDK_DEVCLS_COMPUTER | 0x000014)
#define BTSDK_COMPCLS_WEARABLE					(BTSDK_DEVCLS_COMPUTER | 0x000018)

/*the minor device class field - phone major class*/
#define BTSDK_PHONECLS_UNCLASSIFIED   			(BTSDK_DEVCLS_PHONE | 0x000000) 
#define BTSDK_PHONECLS_CELLULAR         		(BTSDK_DEVCLS_PHONE | 0x000004)
#define BTSDK_PHONECLS_CORDLESS        			(BTSDK_DEVCLS_PHONE | 0x000008)
#define BTSDK_PHONECLS_SMARTPHONE    			(BTSDK_DEVCLS_PHONE | 0x00000C)
#define BTSDK_PHONECLS_WIREDMODEM    			(BTSDK_DEVCLS_PHONE | 0x000010)
#define BTSDK_PHONECLS_COMMONISDNACCESS			(BTSDK_DEVCLS_PHONE | 0x000014)
#define BTSDK_PHONECLS_SIMCARDREADER			(BTSDK_DEVCLS_PHONE | 0x000018)

/*the minor device class field - LAN/Network access point major class*/
#define BTSDK_LAP_FULLY             	    	(BTSDK_DEVCLS_LAP | 0x000000)
#define BTSDK_LAP_17              		       	(BTSDK_DEVCLS_LAP | 0x000020)
#define BTSDK_LAP_33              		       	(BTSDK_DEVCLS_LAP | 0x000040)
#define BTSDK_LAP_50                		   	(BTSDK_DEVCLS_LAP | 0x000060)
#define BTSDK_LAP_67              		       	(BTSDK_DEVCLS_LAP | 0x000080)
#define BTSDK_LAP_83              		       	(BTSDK_DEVCLS_LAP | 0x0000A0)
#define BTSDK_LAP_99               		      	(BTSDK_DEVCLS_LAP | 0x0000C0)
#define BTSDK_LAP_NOSRV       			       	(BTSDK_DEVCLS_LAP | 0x0000E0)

/*the minor device class field - Audio/Video major class*/
#define BTSDK_AV_UNCLASSIFIED        		   	(BTSDK_DEVCLS_AUDIO | 0x000000)
#define BTSDK_AV_HEADSET              		  	(BTSDK_DEVCLS_AUDIO | 0x000004)
#define BTSDK_AV_HANDSFREE           		  	(BTSDK_DEVCLS_AUDIO | 0x000008)
#define BTSDK_AV_HEADANDHAND           			(BTSDK_DEVCLS_AUDIO | 0x00000C)
#define BTSDK_AV_MICROPHONE            			(BTSDK_DEVCLS_AUDIO | 0x000010) 
#define BTSDK_AV_LOUDSPEAKER           			(BTSDK_DEVCLS_AUDIO | 0x000014)
#define BTSDK_AV_HEADPHONES            			(BTSDK_DEVCLS_AUDIO | 0x000018)
#define BTSDK_AV_PORTABLEAUDIO     				(BTSDK_DEVCLS_AUDIO | 0x00001C)
#define BTSDK_AV_CARAUDIO          		     	(BTSDK_DEVCLS_AUDIO | 0x000020)
#define BTSDK_AV_SETTOPBOX       		       	(BTSDK_DEVCLS_AUDIO | 0x000024)
#define BTSDK_AV_HIFIAUDIO          		   	(BTSDK_DEVCLS_AUDIO | 0x000028)
#define BTSDK_AV_VCR                     		(BTSDK_DEVCLS_AUDIO | 0x00002C)
#define BTSDK_AV_VIDEOCAMERA      		     	(BTSDK_DEVCLS_AUDIO | 0x000030)
#define BTSDK_AV_CAMCORDER           	  		(BTSDK_DEVCLS_AUDIO | 0x000034)
#define BTSDK_AV_VIDEOMONITOR	        	 	(BTSDK_DEVCLS_AUDIO | 0x000038)
#define BTSDK_AV_VIDEODISPANDLOUDSPK		 	(BTSDK_DEVCLS_AUDIO | 0x00003C) 
#define BTSDK_AV_VIDEOCONFERENCE     	  		(BTSDK_DEVCLS_AUDIO | 0x000040)
#define BTSDK_AV_GAMEORTOY             			(BTSDK_DEVCLS_AUDIO | 0x000048)

/*the minor device class field - peripheral major class*/
#define BTSDK_PERIPHERAL_UNCLASSIFIED			(BTSDK_DEVCLS_PERIPHERAL | 0x000000) 
#define BTSDK_PERIPHERAL_JOYSTICK				(BTSDK_DEVCLS_PERIPHERAL | 0x000004)
#define BTSDK_PERIPHERAL_GAMEPAD				(BTSDK_DEVCLS_PERIPHERAL | 0x000008)
#define BTSDK_PERIPHERAL_REMCONTROL				(BTSDK_DEVCLS_PERIPHERAL | 0x00000C)
#define BTSDK_PERIPHERAL_SENSE				 	(BTSDK_DEVCLS_PERIPHERAL | 0x000010)
#define BTSDK_PERIPHERAL_TABLET				 	(BTSDK_DEVCLS_PERIPHERAL | 0x000014)
#define BTSDK_PERIPHERAL_SIMCARDREADER			(BTSDK_DEVCLS_PERIPHERAL | 0x000018)
#define BTSDK_PERIPHERAL_KEYBOARD			 	(BTSDK_DEVCLS_PERIPHERAL | 0x000040)    
#define BTSDK_PERIPHERAL_POINT			    	(BTSDK_DEVCLS_PERIPHERAL | 0x000080)
#define BTSDK_PERIPHERAL_KEYORPOINT			 	(BTSDK_DEVCLS_PERIPHERAL | 0x0000C0)

/*the minor device class field - imaging major class*/
#define BTSDK_IMAGE_DISPLAY					   	(BTSDK_DEVCLS_IMAGE | 0x000010)
#define BTSDK_IMAGE_CAMERA					   	(BTSDK_DEVCLS_IMAGE | 0x000020)
#define BTSDK_IMAGE_SCANNER					   	(BTSDK_DEVCLS_IMAGE | 0x000040)
#define BTSDK_IMAGE_PRINTER					   	(BTSDK_DEVCLS_IMAGE | 0x000080)

/*the minor device class field - wearable major class*/
#define BTSDK_WERABLE_WATCH					   	(BTSDK_DEVCLS_WEARABLE | 0x000004)
#define BTSDK_WERABLE_PAGER					   	(BTSDK_DEVCLS_WEARABLE | 0x000008)
#define BTSDK_WERABLE_JACKET				   	(BTSDK_DEVCLS_WEARABLE | 0x00000C)
#define BTSDK_WERABLE_HELMET				   	(BTSDK_DEVCLS_WEARABLE | 0x000010)
#define BTSDK_WERABLE_GLASSES				   	(BTSDK_DEVCLS_WEARABLE | 0x000014)

/* Class of Service */
#define BTSDK_CLS_SERIAL_PORT					0x1101
#define BTSDK_CLS_LAN_ACCESS					0x1102
#define BTSDK_CLS_DIALUP_NET					0x1103
#define BTSDK_CLS_IRMC_SYNC						0x1104
#define BTSDK_CLS_OBEX_OBJ_PUSH					0x1105
#define BTSDK_CLS_OBEX_FILE_TRANS				0x1106
#define BTSDK_CLS_IRMC_SYNC_CMD					0x1107
#define BTSDK_CLS_HEADSET						0x1108
#define BTSDK_CLS_CORDLESS_TELE					0x1109
#define BTSDK_CLS_AUDIO_SOURCE					0x110A	
#define BTSDK_CLS_AUDIO_SINK					0x110B
#define BTSDK_CLS_AVRCP_TG						0x110C
#define BTSDK_CLS_ADV_AUDIO_DISTRIB				0x110D
#define BTSDK_CLS_AVRCP_CT						0x110E
#define BTSDK_CLS_VIDEO_CONFERENCE				0x110F
#define BTSDK_CLS_INTERCOM						0x1110
#define BTSDK_CLS_FAX							0x1111
#define BTSDK_CLS_HEADSET_AG					0x1112
#define BTSDK_CLS_WAP							0x1113
#define BTSDK_CLS_WAP_CLIENT					0x1114
#define BTSDK_CLS_PAN_PANU						0x1115
#define BTSDK_CLS_PAN_NAP						0x1116
#define BTSDK_CLS_PAN_GN						0x1117
#define BTSDK_CLS_DIRECT_PRINT					0x1118
#define BTSDK_CLS_REF_PRINT						0x1119
#define BTSDK_CLS_IMAGING						0x111A
#define BTSDK_CLS_IMAG_RESPONDER				0x111B
#define BTSDK_CLS_IMAG_AUTO_ARCH				0x111C
#define BTSDK_CLS_IMAG_REF_OBJ					0x111D
#define BTSDK_CLS_HANDSFREE						0x111E
#define BTSDK_CLS_HANDSFREE_AG					0x111F
#define BTSDK_CLS_DPS_REF_OBJ			        0x1120
#define BTSDK_CLS_REFLECTED_UI			        0x1121
#define BTSDK_CLS_BASIC_PRINT			        0x1122
#define BTSDK_CLS_PRINT_STATUS			        0x1123
#define BTSDK_CLS_HID							0x1124
#define BTSDK_CLS_HCRP							0x1125
#define BTSDK_CLS_HCR_PRINT						0x1126
#define BTSDK_CLS_HCR_SCAN						0x1127
#define BTSDK_CLS_SIM_ACCESS					0x112D
#define BTSDK_CLS_PBAP_PCE					    0x112E
#define BTSDK_CLS_PBAP_PSE					    0x112F
#define BTSDK_CLS_PHONEBOOK_ACCESS			    0x1130
#define BTSDK_CLS_PNP_INFO						0x1200

/* Type of Connection Event */
#define BTSDK_APP_EV_CONN_IND					0x01	
#define BTSDK_APP_EV_DISC_IND					0x02
#define BTSDK_APP_EV_CONN_CFM					0x07	
#define BTSDK_APP_EV_DISC_CFM					0x08

/* Definitions for Compatibility */
#define BTSDK_APP_EV_CONN						0x01	
#define BTSDK_APP_EV_DISC						0x02	

//Call back user priority
#define BTSDK_CLIENTCBK_PRIORITY_HIGH		  3
#define BTSDK_CLIENTCBK_PRIORITY_MEDIUM       2

//Whether user handle pin code and authorization callback
#define BTSDK_CLIENTCBK_HANDLED				  1
#define BTSDK_CLIENTCBK_NOTHANDLED			  0

/* Authorization Result */
#define BTSDK_AUTHORIZATION_GRANT				0x01
#define BTSDK_AUTHORIZATION_DENY				0x02

#define BTSDK_APP_EV_BASE						0x100
/* OPP specific event */
#define BTSDK_APP_EV_OPP_BASE				    0x200
#define BTSDK_APP_EV_OPP_PULL					(BTSDK_APP_EV_OPP_BASE+2)
#define BTSDK_APP_EV_OPP_PUSH					(BTSDK_APP_EV_OPP_BASE+3)
#define BTSDK_APP_EV_OPP_PUSH_CARD				(BTSDK_APP_EV_OPP_BASE+4)
#define BTSDK_APP_EV_OPP_EXCHG					(BTSDK_APP_EV_OPP_BASE+5)

/* FTP specific event */
#define BTSDK_APP_EV_FTP_BASE					0x300
#define BTSDK_APP_EV_FTP_PUT					(BTSDK_APP_EV_FTP_BASE+0)
#define BTSDK_APP_EV_FTP_GET				    (BTSDK_APP_EV_FTP_BASE+1)
#define BTSDK_APP_EV_FTP_DEL_FILE				(BTSDK_APP_EV_FTP_BASE+3)
#define BTSDK_APP_EV_FTP_DEL_FOLDER				(BTSDK_APP_EV_FTP_BASE+4)	

/* AVRCP specific event. */
#define BTSDK_APP_EV_AVRCP_BASE							0xB00
/* AVRCP TG specific event. */
#define BTSDK_APP_EV_AVTG_BASE							BTSDK_APP_EV_AVRCP_BASE
#define BTSDK_APP_EV_AVTG_ATTACHPLAYER_IND				(BTSDK_APP_EV_AVTG_BASE + 0x01)
#define BTSDK_APP_EV_AVRCP_DETACHPLAYER_IND 			(BTSDK_APP_EV_AVTG_BASE + 0x03)
#define BTSDK_APP_EV_AVRCP_IND_CONN 					BTSDK_APP_EV_AVTG_ATTACHPLAYER_IND
#define BTSDK_APP_EV_AVRCP_IND_DISCONN 					BTSDK_APP_EV_AVRCP_DETACHPLAYER_IND

/* BRSF feature mask ID for AG*/
#define BTSDK_AG_BRSF_3WAYCALL         			0x00000001 /* Three-way calling */
#define BTSDK_AG_BRSF_NREC             			0x00000002 /* EC and/or NR function */
#define BTSDK_AG_BRSF_BVRA             			0x00000004 /* Voice recognition function */
#define BTSDK_AG_BRSF_INBANDRING       			0x00000008 /* In-band ring tone capability */
#define BTSDK_AG_BRSF_BINP             			0x00000010 /* Attach a number to a voice tag */
#define BTSDK_AG_BRSF_REJECT_CALL          		0x00000020 /* Ability to reject a call */
#define BTSDK_AG_BRSF_ENHANCED_CALLSTATUS      	0x00000040 /* Enhanced call status */
#define BTSDK_AG_BRSF_ENHANCED_CALLCONTROL      0x00000080 /* Enhanced call control */
#define BTSDK_AG_BRSF_EXTENDED_ERRORRESULT     	0x00000100 /* Extended Error Result Codes */
#define BTSDK_AG_BRSF_ALL						0x000001FF /* Support all the upper features */ 

/* BRSF feature mask ID for HF */
#define BTSDK_HF_BRSF_NREC             			0x00000001 /* EC and/or NR function */
#define BTSDK_HF_BRSF_3WAYCALL         			0x00000002 /* Call waiting and 3-way calling */
#define BTSDK_HF_BRSF_CLIP             			0x00000004 /* CLI presentation capability */
#define BTSDK_HF_BRSF_BVRA             			0x00000008 /* Voice recognition activation */
#define BTSDK_HF_BRSF_RMTVOLCTRL       			0x00000010 /* Remote volume control */
#define BTSDK_HF_BRSF_ENHANCED_CALLSTATUS       0x00000020 /* Enhanced call status */
#define BTSDK_HF_BRSF_ENHANCED_CALLCONTROL     	0x00000040 /* Enhanced call control */
#define BTSDK_HF_BRSF_ALL						0x0000007F /* Support all the upper features */ 

/* HSP/HFP AG specific event. */
#define BTSDK_APP_EV_AGAP_BASE 							 0x900
enum BTSDK_HFP_APP_EventCodeEnum {
	/* HFP_SetState Callback to Application Event Code */
	/* SLC - Both AG and HF */
    BTSDK_HFP_EV_SLC_ESTABLISHED_IND = BTSDK_APP_EV_AGAP_BASE + 0x01,	/* HFP Service Level connection established. Parameter: Btsdk_HFP_ConnInfoStru */
	BTSDK_HFP_EV_SLC_RELEASED_IND,   	            /* SPP connection released. Parameter: Btsdk_HFP_ConnInfoStru */

	/* SCO - Both AG and HF  */
	BTSDK_HFP_EV_AUDIO_CONN_ESTABLISHED_IND,		/* SCO audio connection established */
	BTSDK_HFP_EV_AUDIO_CONN_RELEASED_IND,			/* SCO audio connection released */

	/* Status Changed Indication */
	BTSDK_HFP_EV_STANDBY_IND,      					/* STANDBY Menu, the incoming call or outgoing call or ongoing call is canceled  */
	BTSDK_HFP_EV_ONGOINGCALL_IND,					/* ONGOING-CALL Menu, a call (incoming call or outgoing call) is established (ongoing) */
	BTSDK_HFP_EV_RINGING_IND,						/* RINGING Menu, a call is incoming. Parameter: BTBOOL - in-band ring tone or not.   */
	BTSDK_HFP_EV_OUTGOINGCALL_IND,					/* OUTGOING-CALL Menu, an outgoing call is being established, 3Way in Guideline P91 */
	BTSDK_HFP_EV_CALLHELD_IND,						/* BTRH-HOLD Menu, +BTRH:0, AT+BTRH=0, incoming call is put on hold */
	BTSDK_HFP_EV_CALL_WAITING_IND,					/* Call Waiting Menu, +CCWA, When Call=Active, call waiting notification. Parameter: Btsdk_HFP_PhoneInfoStru */
	BTSDK_HFP_EV_TBUSY_IND,							/* GSM Network Remote Busy, TBusy Timer Activated */
	
	/* AG & HF APP General Event Indication */
	BTSDK_HFP_EV_GENERATE_INBAND_RINGTONE_IND,		/* AG Only, Generate the in-band ring tone */
	BTSDK_HFP_EV_TERMINATE_LOCAL_RINGTONE_IND,		/* Terminate local generated ring tone or the in-band ring tone */
	BTSDK_HFP_EV_VOICE_RECOGN_ACTIVATED_IND,		/* +BVRA:1, voice recognition activated indication or HF request to start voice recognition procedure */
	BTSDK_HFP_EV_VOICE_RECOGN_DEACTIVATED_IND,		/* +BVRA:0, voice recognition deactivated indication or requests AG to deactivate the voice recognition procedure */
	BTSDK_HFP_EV_NETWORK_AVAILABLE_IND,				/* +CIEV:<service><value>, cellular network is available */
	BTSDK_HFP_EV_NETWORK_UNAVAILABLE_IND,			/* +CIEV:<service><value>, cellular network is unavailable */
	BTSDK_HFP_EV_ROAMING_RESET_IND,					/* +CIEV:<roam><value>, roaming is not active */
	BTSDK_HFP_EV_ROAMING_ACTIVE_IND,					/* +CIEV:<roam><value>, a roaming is active */
	BTSDK_HFP_EV_SIGNAL_STRENGTH_IND,				/* +CIEV:<signal><value>, signal strength indication. Parameter: BTUINT8 - indicator value */	
	BTSDK_HFP_EV_BATTERY_CHARGE_IND,					/* +CIEV:<battchg><value>, battery charge indication. Parameter: BTUINT8 - indicator value  */
	BTSDK_HFP_EV_CHLDHELD_ACTIVATED_IND,			/* +CIEV:<callheld><1>, Call on CHLD Held to be or has been actived. */
	BTSDK_HFP_EV_CHLDHELD_RELEASED_IND,				/* +CIEV:<callheld><0>, Call on CHLD Held to be or has been released. */	
	BTSDK_HFP_EV_MICVOL_CHANGED_IND,					/* +VGM, AT+VGM, microphone volume changed indication */
	BTSDK_HFP_EV_SPKVOL_CHANGED_IND,					/* +VGS, AT+VGS, speaker volume changed indication */

	/* OK and Error Code - HF only */
	BTSDK_HFP_EV_ATCMD_RESULT,						/* HF Received OK, Error/+CME ERROR from AG or Wait for AG Response Timeout. Parameter: Btsdk_HFP_ATCmdResultStru */
	
	/* To HF APP, Call Related, AG Send information to HF */
	BTSDK_HFP_EV_CLIP_IND,							/* +CLIP, Phone Number Indication. Parameter: Btsdk_HFP_PhoneInfoStru */
	BTSDK_HFP_EV_CURRENT_CALLS_IND,					/* +CLCC, the current calls of AG. Parameter: Btsdk_HFP_CLCCInfoStru */
	BTSDK_HFP_EV_NETWORK_OPERATOR_IND,				/* +COPS, the current network operator name of AG. Parameter: Btsdk_HFP_COPSInfoStru */
	BTSDK_HFP_EV_SUBSCRIBER_NUMBER_IND,				/* +CNUM, the subscriber number of AG. Parameter: Btsdk_HFP_PhoneInfoStru */
	BTSDK_HFP_EV_VOICETAG_PHONE_NUM_IND,			/* +BINP, AG inputted phone number for voice-tag; requests AG to input a phone number for the voice-tag at the HF side. Parameter: Btsdk_HFP_PhoneInfoStru */
	
	/* AG APP, HF Request or Indicate AG */
	BTSDK_HFP_EV_CURRENT_CALLS_REQ,					/* AT+CLCC, query the list of current calls in AG. */
	BTSDK_HFP_EV_NETWORK_OPERATOR_FORMAT_REQ,		/* AT+COPS=3,0, indicate app the network operator name should be set to long alphanumeric */
	BTSDK_HFP_EV_NETWORK_OPERATOR_REQ,				/* AT+COPS?, requests AG to respond with +COPS response indicating the currently selected operator */
	BTSDK_HFP_EV_SUBSCRIBER_NUMBER_REQ,				/* AT+CNUM, query the AG subscriber number information. */
	BTSDK_HFP_EV_VOICETAG_PHONE_NUM_REQ,			/* AT+BINP, requests AG to input a phone number for the voice-tag at the HF */
	BTSDK_HFP_EV_CUR_INDICATOR_VAL_REQ,				/* AT+CIND?, get the current indicator during the service level connection initialization procedure */
	BTSDK_HFP_EV_HF_DIAL_REQ,						/* ATD, instructs AG to dial the specific phone number. Parameter: (HFP only) BTUINT8* - phone number */
	BTSDK_HFP_EV_HF_MEM_DIAL_REQ,					/* ATD>, instructs AG to dial the phone number indexed by the specific memory location of SIM card. Parameter: BTUINT8* - memory location */
	BTSDK_HFP_EV_HF_LASTNUM_REDIAL_REQ,				/* AT+BLDN, instructs AG to redial the last dialed phone number */
	BTSDK_HFP_EV_MANUFACTURER_REQ,					/* AT+CGMI, requests AG to respond with the Manufacturer ID */
	BTSDK_HFP_EV_MODEL_REQ,							/* AT+CGMM, requests AG to respond with the Model ID */
	BTSDK_HFP_EV_NREC_DISABLE_REQ,					/* AT+NREC=0, requests AG to disable NREC function */
	BTSDK_HFP_EV_DTMF_REQ,							/* AT+VTS, instructs AG to transmit the specific DTMF code. Parameter: BTUINT8 - DTMF code */
	BTSDK_HFP_EV_ANSWER_CALL_REQ,					/* inform AG app to answer the call. Parameter: BTUINT8 - One of BTSDK_HFP_TYPE_INCOMING_CALL, BTSDK_HFP_TYPE_HELDINCOMING_CALL. */	
	BTSDK_HFP_EV_CANCEL_CALL_REQ,					/* inform AG app to cancel the call. Parameter: BTUINT8 - One of BTSDK_HFP_TYPE_ALL_CALLS, BTSDK_HFP_TYPE_INCOMING_CALL, 
	                                                       BTSDK_HFP_TYPE_HELDINCOMING_CALL, BTSDK_HFP_TYPE_OUTGOING_CALL, BTSDK_HFP_TYPE_ONGOING_CALL. */	
	BTSDK_HFP_EV_HOLD_CALL_REQ,						/* inform AG app to hold the incoming call (AT+BTRH=0) */
	
	/* AG APP, 3-Way Calling */
	BTSDK_HFP_EV_REJECTWAITINGCALL_REQ,				/* AT+CHLD=0, Release all held calls or reject waiting call. */	
	BTSDK_HFP_EV_ACPTWAIT_RELEASEACTIVE_REQ,		/* AT+CHLD=1, Accept the held or waiting call and release all avtive calls. Parameter: BTUINT8 - value of <idx>*/
	BTSDK_HFP_EV_HOLDACTIVECALL_REQ,					/* AT+CHLD=2, Held Specified Active Call.  Parameter: BTUINT8 - value of <idx>*/
	BTSDK_HFP_EV_ADD_ONEHELDCALL_2ACTIVE_REQ,		/* AT+CHLD=3, Add One CHLD Held Call to Active Call. */
	BTSDK_HFP_EV_LEAVE3WAYCALLING_REQ,				/* AT+CHLD=4, Leave The 3-Way Calling. */
	
	/* Extended */
	BTSDK_HFP_EV_EXTEND_CMD_IND,						/* indicate app extend command received. Parameter: BTUINT8* - Full extended AT command or result code. */
	BTSDK_HFP_EV_PRE_SCO_CONNECTION_IND,			/* indicate app to create SCO connection. Parameter: Btsdk_AGAP_PreSCOConnIndStru. */
	BTSDK_HFP_EV_SPP_ESTABLISHED_IND,				/* SPP connection created. Parameter: Btsdk_HFP_ConnInfoStru. added 2008-7-3 */
	BTSDK_HFP_EV_HF_MANUFACTURERID_IND,				/* ManufacturerID indication. Parameter: BTUINT8* - Manufacturer ID of the AG device, a null-terminated ASCII string. */
	BTSDK_HFP_EV_HF_MODELID_IND,						/* ModelID indication.  Parameter: BTUINT8* - Model ID of the AG device, a null-terminated ASCII string. */
};

/* AG Action Reason */
#define BTSDK_HFP_CANCELED_ALLCALL					0x01	/* AG released all calls or GSM Service Unavailable */
#define BTSDK_HFP_CANCELED_CALLSETUP				0x02	/* AG or GSM Release the Incoming Call or Outgoing Call */
#define BTSDK_HFP_CANCELED_LASTCALL				    0x03	/* AG or GSM Release Last Call in Call=1 */

#define BTSDK_HFP_AG_PRIVATE_MODE					0x05	/* Answer the Outgoing/Incoming Call on AG */
#define BTSDK_HFP_AG_HANDSFREE_MODE					0x06	/* Answer the Outgoing/Incoming Call on HF */

/* Possible received events from GSM/CDMA cellular network */
#define BTSDK_AGAP_NETWORK_RMT_IS_BUSY						0x01
#define BTSDK_AGAP_NETWORK_ALERTING_RMT						0x02
#define BTSDK_AGAP_NETWORK_INCOMING_CALL					0x03
#define BTSDK_AGAP_NETWORK_RMT_ANSWER_CALL					0x04
#define BTSDK_AGAP_NETWORK_SVC_UNAVAILABLE				    0x05
#define BTSDK_AGAP_NETWORK_SVC_AVAILABLE					0x06
#define BTSDK_AGAP_NETWORK_SIGNAL_STRENGTH					0x07
#define BTSDK_AGAP_NETWORK_ROAMING_RESET					0x08
#define BTSDK_AGAP_NETWORK_ROAMING_ACTIVE					0x09

#define BTSDK_HFP_CMD_GROUP1           0x8000 		/* AT Command will response directly by OK */
#define BTSDK_HFP_CMD_CHLD_0  	   (BTSDK_HFP_CMD_GROUP1 | 0x0b)						/* AT+CHLD=0 Held Call Release */
#define BTSDK_HFP_CMD_CHLD_1 		   (BTSDK_HFP_CMD_GROUP1 | 0x0c)						/* AT+CHLD=1 Release Specified Active Call */
#define BTSDK_HFP_CMD_CHLD_2 		   (BTSDK_HFP_CMD_GROUP1 | 0x0d)						/* AT+CHLD=2 Call Held or Active/Held Position Swap */
#define BTSDK_HFP_CMD_CHLD_3 		   (BTSDK_HFP_CMD_GROUP1 | 0x0e)						/* AT+CHLD=3 Adds a held call to the conversation */
#define BTSDK_HFP_CMD_CHLD_4 		   (BTSDK_HFP_CMD_GROUP1 | 0x0f)						/* AT+CHLD=4 Connects the two calls and disconnects the subscriber from both calls */

/* HF Device state*/
#define BTSDK_HFAP_ST_IDLE          0x01		/*before service level connection is established*/
#define BTSDK_HFAP_ST_STANDBY       0x02		/*service level connection is established*/
#define BTSDK_HFAP_ST_RINGING       0x03		/*ringing*/
#define BTSDK_HFAP_ST_OUTGOINGCALL  0x04		/*outgoing call*/
#define BTSDK_HFAP_ST_ONGOINGCALL   0x05		/*ongoing call*/
#define BTSDK_HFAP_ST_BVRA          0x06     /*voice recognition is ongoing*/
#define BTSDK_HFAP_ST_VOVG          0x07
#define BTSDK_HFAP_ST_HELDINCOMINGCALL	0x08 /*the incoming call is held*/

//start bluetooth error extend
#define BTSDK_ER_FAIL_INITIALIZE_BTSDK		(BTSDK_ER_APPEXTEND_INDEX + 0x0006)
#define BTSDK_BLUETOOTH_STATUS_FLAG			0x0002 //status change about Bluetooth

//status change about Bluetooth
#define BTSDK_BTSTATUS_TURNON				0x0001
#define BTSDK_BTSTATUS_TURNOFF				0x0002
#define BTSDK_BTSTATUS_HWPLUGGED			0x0003
#define BTSDK_BTSTATUS_HWPULLED				0x0004


/*AV/C Panel Commands operation_id*/
#define BTSDK_AVRCP_OPID_AVC_PANEL_POWER 				0x40
#define BTSDK_AVRCP_OPID_AVC_PANEL_VOLUME_UP 			0x41
#define BTSDK_AVRCP_OPID_AVC_PANEL_VOLUME_DOWN 			0x42
#define BTSDK_AVRCP_OPID_AVC_PANEL_MUTE					0x43
#define BTSDK_AVRCP_OPID_AVC_PANEL_PLAY 				0x44
#define BTSDK_AVRCP_OPID_AVC_PANEL_STOP  				0x45
#define BTSDK_AVRCP_OPID_AVC_PANEL_PAUSE 				0x46
#define BTSDK_AVRCP_OPID_AVC_PANEL_RECORD 				0x47
#define BTSDK_AVRCP_OPID_AVC_PANEL_REWIND 				0x48
#define BTSDK_AVRCP_OPID_AVC_PANEL_FAST_FORWARD 		0x49
#define BTSDK_AVRCP_OPID_AVC_PANEL_EJECT 				0x4a
#define BTSDK_AVRCP_OPID_AVC_PANEL_FORWARD 				0x4b
#define BTSDK_AVRCP_OPID_AVC_PANEL_BACKWARD 			0x4c

/*button state(0: pressed 1: released)*/
/*used by Btsdk_AVRCP_Passthrough_Cmd_Func parameter state_flag*/
#define BTSDK_AVRCP_BUTTON_STATE_PRESSED         		0
#define BTSDK_AVRCP_BUTTON_STATE_RELEASED   			1

/* Possible roles for member 'role' in _BtSdkConnectionPropertyStru */
#define BTSDK_CONNROLE_INITIATOR				0x2
#define BTSDK_CONNROLE_ACCEPTOR					0x1

/* Possible op_type member of Btsdk_FTPBrowseFolder */
#define FTP_OP_REFRESH	0
#define FTP_OP_UPDIR	1
#define FTP_OP_NEXT		2

/* Type of Callback Indication */
#define BTSDK_INQUIRY_RESULT_IND  		0x04
#define BTSDK_INQUIRY_COMPLETE_IND 		0x05
#define BTSDK_CONNECTION_EVENT_IND  	0x09
#define BTSDK_PIN_CODE_IND              0x00
#define BTSDK_AUTHORIZATION_IND         0x06  
#define BTSDK_LINK_KEY_NOTIF_IND		0x02
#define BTSDK_AUTHENTICATION_FAIL_IND  	0x03

/* Discovery Mode for Btsdk_SetDiscoveryMode() and Btsdk_GetDiscoveryMode() */
#define BTSDK_GENERAL_DISCOVERABLE				0x01
#define BTSDK_LIMITED_DISCOVERABLE				0x02
#define BTSDK_DISCOVERABLE						BTSDK_GENERAL_DISCOVERABLE
#define BTSDK_CONNECTABLE						0x04
#define BTSDK_PAIRABLE							0x08
#define BTSDK_DISCOVERY_DEFAULT_MODE			(BTSDK_DISCOVERABLE | BTSDK_CONNECTABLE | BTSDK_PAIRABLE)

/*for win32 only*/
/* PAN Event */
#define BTSDK_PAN_EV_BASE			0x00000100
#define BTSDK_PAN_EV_IP_CHANGE		BTSDK_PAN_EV_BASE + 1


#define	DEVICE_CLASS_MASK		0x1FFC
#define IS_SAME_TYPE_DEVICE_CLASS(a, b)	(((a) & DEVICE_CLASS_MASK) == ((b) & DEVICE_CLASS_MASK))

/* Default role of local device when creating a new ACL connection. */
#define BTSDK_MASTER_ROLE						0x00
#define BTSDK_SLAVE_ROLE						0x01

/* Possible values for "flag" parameter of Btsdk_StartEnumRemoteDevice. */
#define BTSDK_ERD_FLAG_NOLIMIT		0x00000000
#define BTSDK_ERD_FLAG_PAIRED		0x00000001
#define BTSDK_ERD_FLAG_CONNECTED	0x00000002
#define BTSDK_ERD_FLAG_INQUIRED		0x00000004
#define BTSDK_ERD_FLAG_TRUSTED		0x00000020
#define BTSDK_ERD_FLAG_DEVCLASS		0x00010000

/* Possible values for "mask" member of BtSdkRemoteDevicePropertyStru structure. */
#define BTSDK_RDPM_HANDLE			0x0001
#define BTSDK_RDPM_ADDRESS			0x0002
#define BTSDK_RDPM_NAME				0x0004
#define BTSDK_RDPM_CLASS			0x0008
#define BTSDK_RDPM_LMPINFO			0x0010
#define BTSDK_RDPM_LINKKEY			0x0020

/* Possible ACL connection packet type */
#define BTSDK_ACL_PKT_2DH1			0x0002		/* Only supported by V2.0EDR */
#define BTSDK_ACL_PKT_3DH1			0x0004		/* Only supported by V2.0EDR */
#define BTSDK_ACL_PKT_DM1			0x0008
#define BTSDK_ACL_PKT_DH1			0x0010
#define BTSDK_ACL_PKT_2DH3			0x0100		/* Only supported by V2.0EDR */
#define BTSDK_ACL_PKT_3DH3			0x0200		/* Only supported by V2.0EDR */
#define BTSDK_ACL_PKT_DM3			0x0400
#define BTSDK_ACL_PKT_DH3			0x0800
#define BTSDK_ACL_PKT_2DH5			0x1000		/* Only supported by V2.0EDR */
#define BTSDK_ACL_PKT_3DH5			0x2000		/* Only supported by V2.0EDR */
#define BTSDK_ACL_PKT_DM5			0x4000
#define BTSDK_ACL_PKT_DH5			0x8000

/* Possible flags for member 'mask' in _BtSdkSDPSearchPatternStru */
#define BTSDK_SSPM_UUID16					0x0001
#define BTSDK_SSPM_UUID32					0x0002
#define BTSDK_SSPM_UUID128					0x0004

/* Possible flags for member 'mask' in _BtSdkRemoteServiceAttrStru */
#define BTSDK_RSAM_SERVICENAME					0x0001
#define BTSDK_RSAM_EXTATTRIBUTES				0x0002

#define BTSDK_MAX_SEARCH_PATTERNS				12

/* Possible parameters for Btsdk_VDIInstallDev */
#define HARDWAREID_MDMDUN		TEXT("{F12D3CF8-B11D-457e-8641-BE2AF2D6D204}\\MDMBTGEN336")
#define HARDWAREID_MDMFAX		TEXT("{F12D3CF8-B11D-457e-8641-BE2AF2D6D204}\\MDMBTFAX")

/* Parameters for Btsdk_PlugOutVComm and Btsdk_PlugInVComm */
#define COMM_SET_USAGETYPE	0x00000001
#define COMM_SET_RECORD		0x00000010

/* Macros for HFP/HSP AG */
/* Parameters for Btsdk_AGAP_Init */
#define BTSDK_AGAP_FEA_3WAY_CALLING			0x00000001      
#define BTSDK_AGAP_FEA_NREC					0x00000002              
#define BTSDK_AGAP_FEA_VOICE_RECOG			0x00000004       
#define BTSDK_AGAP_FEA_INBAND_RING			0x00000008       
#define BTSDK_AGAP_FEA_VOICETAG_PHONE_NUM	0x00000010
#define BTSDK_AGAP_FEA_REJ_CALL				0x00000020 
#define BTSDK_AGAP_SCO_PKT_HV1				0x20
#define BTSDK_AGAP_SCO_PKT_HV2				0x40
#define BTSDK_AGAP_SCO_PKT_HV3				0x80

/* Available status for Btsdk_AGAP_GetStatus. */
#define BTSDK_AGAP_STATUS_GENERATE_INBAND_RINGTONE   0x01  /* whether AG is capable of generating in-band ring tone */
#define BTSDK_AGAP_STATUS_AUDIO_CONN_ONGOING         0x02  /* whether audio connection with remote device is ongoing */

/* Possible AG state of Btsdk_AGAP_GetAGState*/
#define BTSDK_AGAP_ST_IDLE          0x01		/*before service level connection is established*/
#define BTSDK_AGAP_ST_STANDBY       0x02		/*service level connection is established*/
#define BTSDK_AGAP_ST_RINGING       0x03		/*ringing*/
#define BTSDK_AGAP_ST_OUTGOINGCALL  0x04		/*outgoing call*/
#define BTSDK_AGAP_ST_ONGOINGCALL   0x05		/*ongoing call*/
#define BTSDK_AGAP_ST_BVRA          0x06     /*voice recognition is ongoing*/
#define BTSDK_AGAP_ST_VOVG          0x07
#define BTSDK_AGAP_ST_HELDINCOMINGCALL	0x08 /*the incoming call is held*/
#define BTSDK_AGAP_ST_THREEWAYCALLING	0x09 /*three way calling*/

/* Current state mask code for function Btsdk_AGAP_SetCurIndicatorVal. */
#define BTSDK_AGAP_INDICATOR_SVC_UNAVAILABLE     0x00    
#define BTSDK_AGAP_INDICATOR_SVC_AVAILABLE       0x01      
#define BTSDK_AGAP_INDICATOR_ACTIVE              0x02             
#define BTSDK_AGAP_INDICATOR_INCOMING            0x04           
#define BTSDK_AGAP_INDICATOR_DIALING             0x08            
#define BTSDK_AGAP_INDICATOR_ALERTING            0x10 

/* Possible "features" parameter of Btsdk_HFAP_Init */ 
#define BTSDK_HFAP_FEA_NREC                         0x00000001
#define BTSDK_HFAP_FEA_3WAY_CALLING                 0x00000002
#define BTSDK_HFAP_FEA_CALLING_LINE_NUM             0x00000004
#define BTSDK_HFAP_FEA_VOICE_RECOG                  0x00000008
#define BTSDK_HFAP_FEA_RMT_VOL_CTRL                 0x00000010

/* Possible "sco_pkt_type" parameter of Btsdk_HFAP_Init */ 
#define BTSDK_HFAP_SCO_PKT_HV1				0x20
#define BTSDK_HFAP_SCO_PKT_HV2				0x40
#define BTSDK_HFAP_SCO_PKT_HV3				0x80

/* Available status from function Btsdk_HFAP_GetStatus. */
#define BTSDK_HFAP_STATUS_LOCAL_GENERATE_RINGTONE   0x01  /* whether HF device need to generate its own in-band ring tone */
#define BTSDK_HFAP_STATUS_AUDIO_CONN_ONGOING        0x02  /* whether audio connection with remote device is ongoing */

/* HF state */
#define BTSDK_HFAP_ST_IDLE                          0x01 /*conn not established, for HSP & HFP*/
#define BTSDK_HFAP_ST_STANDBY                       0x02 /*conn established, for HSP & HFP*/
#define BTSDK_HFAP_ST_RINGING                       0x03 /*ringing, for HSP & HFP*/
#define BTSDK_HFAP_ST_OUTGOINGCALL                  0x04 /*outgoing call, only for HFP*/
#define BTSDK_HFAP_ST_ONGOINGCALL                   0x05 /*ongoing call, only for HFP and HSP*/

/* Three way calling mode */
#define BTSDK_HFAP_3WAY_MOD0                        '0' /*Set busy tone for a waiting call; Release the held call*/
#define BTSDK_HFAP_3WAY_MOD1                        '1' /*Release activate call & accept held/waiting call*/
#define BTSDK_HFAP_3WAY_MOD2                        '2' /*Swap between active call and held call; Place active call on held; Place held call on active*/
#define BTSDK_HFAP_3WAY_MOD3                        '3' /*Add a held call to the conversation*/
#define BTSDK_HFAP_3WAY_MOD4                        '4' /*Connects the two calls and disconnects the subscriber from both calls (Explicit Call Transfer)*/

/* AG Type of the call, possible values of HFP_EV_ANSWER_CALL_REQ and HFP_EV_CANCEL_CALL_REQ event parameter */
#define BTSDK_HFP_TYPE_ALL_CALLS					0x01 /* (Release) all the existing calls */
#define BTSDK_HFP_TYPE_INCOMING_CALL				0x02 /* (Reject or accept) the incoming call */ 
#define BTSDK_HFP_TYPE_HELDINCOMING_CALL			0x03 /* (Reject or accept) the Held incoming call */
#define BTSDK_HFP_TYPE_OUTGOING_CALL				0x04 /* (Release) the outgoing call */
#define BTSDK_HFP_TYPE_ONGOING_CALL					0x05 /* (Release) the ongoing call */


/*-----------------------------------------------------------------------------
/* 					 CME Error Code and Standard Error Code for APP			 */
/*---------------------------------------------------------------------------*/
/* This CME ERROR Code is only for APP Reference. More Code reference to GSM Spec. */
#define BTSDK_HFP_CMEERR_AGFAILURE						0  /* +CME ERROR:0 - AG failure */
#define BTSDK_HFP_CMEERR_NOCONN2PHONE					1  /* +CME ERROR:1 - no connection to phone */
#define BTSDK_HFP_CMEERR_OPERATION_NOTALLOWED			3  /* +CME ERROR:3 - operation not allowed */
#define BTSDK_HFP_CMEERR_OPERATION_NOTSUPPORTED			4  /* +CME ERROR:4 - operation not supported */
#define BTSDK_HFP_CMEERR_PHSIMPIN_REQUIRED				5  /* +CME ERROR:5 - PH-SIM PIN required */
#define BTSDK_HFP_CMEERR_SIMNOT_INSERTED				10 /* +CME ERROR:10 - SIM not inserted */
#define BTSDK_HFP_CMEERR_SIMPIN_REQUIRED				11 /* +CME ERROR:11 - SIM PIN required */
#define BTSDK_HFP_CMEERR_SIMPUK_REQUIRED				12 /* +CME ERROR:12 - SIM PUK required */
#define BTSDK_HFP_CMEERR_SIM_FAILURE					13 /* +CME ERROR:13 - SIM failure */
#define BTSDK_HFP_CMEERR_SIM_BUSY						14 /* +CME ERROR:14 - SIM busy */
#define BTSDK_HFP_CMEERR_INCORRECT_PASSWORD				16 /* +CME ERROR:16 - incorrect password */
#define BTSDK_HFP_CMEERR_SIMPIN2_REQUIRED				17 /* +CME ERROR:17 - SIM PIN2 required */
#define BTSDK_HFP_CMEERR_SIMPUK2_REQUIRED				18 /* +CME ERROR:18 - SIM PUK2 required */
#define BTSDK_HFP_CMEERR_MEMORY_FULL					20 /* +CME ERROR:20 - memory full */
#define BTSDK_HFP_CMEERR_INVALID_INDEX					21 /* +CME ERROR:21 - invalid index */
#define BTSDK_HFP_CMEERR_MEMORY_FAILURE					23 /* +CME ERROR:23 - memory failure */
#define BTSDK_HFP_CMEERR_TEXTSTRING_TOOLONG				24 /* +CME ERROR:24 - text string too long */
#define BTSDK_HFP_CMEERR_INVALID_CHAR_INTEXTSTRING 	    25 /* +CME ERROR:25 - invalid characters in text string */
#define BTSDK_HFP_CMEERR_DIAL_STRING_TOOLONG			26 /* +CME ERROR:26 - dial string too long */
#define BTSDK_HFP_CMEERR_INVALID_CHAR_INDIALSTRING		27 /* +CME ERROR:27 - invalid characters in dial string */
#define BTSDK_HFP_CMEERR_NETWORK_NOSERVICE				30 /* +CME ERROR:30 - no network service */
#define BTSDK_HFP_CMEERR_NETWORK_TIMEOUT				31 /* +CME ERROR:31 - network timeout */
#define BTSDK_HFP_CMEERR_EMERGENCYCALL_ONLY				32 /* +CME ERROR:32 - Network not allowed, emergency calls only */

/* APP specific error code. */
#define BTSDK_HFP_APPERR_TIMEOUT						200 /* Wait for response timeout */

/* Standard error result code. */
#define BTSDK_HFP_STDERR_ERROR							201 /* result code: ERROR */
#define BTSDK_HFP_STDRR_NOCARRIER						202 /* result code: NO CARRIER */
#define BTSDK_HFP_STDERR_BUSY							203 /* result code: BUSY */
#define BTSDK_HFP_STDERR_NOANSWER						204 /* result code: NO ANSWER */
#define BTSDK_HFP_STDERR_DELAYED						205 /* result code: DELAYED */
#define BTSDK_HFP_STDERR_BLACKLISTED					206 /* result code: BLACKLISTED */
#define BTSDK_HFP_OK								    255 /* result code: OK */

/*A2DP*/
#define BTSDK_A2DP_AUDIOCARD_NAME_LEN      				0x80

#endif