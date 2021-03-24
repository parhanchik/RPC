

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for C:\Users\1\Desktop\учеба\RPCInterface.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, app_config, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __RPCInterface_h__
#define __RPCInterface_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __RpcInt_INTERFACE_DEFINED__
#define __RpcInt_INTERFACE_DEFINED__

/* interface RpcInt */
/* [implicit_handle][version][uuid] */ 

int logon( 
    /* [size_is][in] */ unsigned char *log,
    /* [size_is][in] */ unsigned char *pas,
    /* [in] */ unsigned long sizelog,
    /* [in] */ unsigned long sizepas);

void FileDelete( 
    /* [string][in] */ const unsigned char *path);

unsigned long FileDownload( 
    /* [string][in] */ const unsigned char *path,
    /* [size_is][out][in] */ unsigned char *Out);

void FileUpload( 
    /* [string][in] */ const unsigned char *path,
    /* [size_is][out][in] */ unsigned char *Out,
    /* [in] */ unsigned long sizeOut);


extern handle_t BHandle;


extern RPC_IF_HANDLE RpcInt_v1_0_c_ifspec;
extern RPC_IF_HANDLE RpcInt_v1_0_s_ifspec;
#endif /* __RpcInt_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


