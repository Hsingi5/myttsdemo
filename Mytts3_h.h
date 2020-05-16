

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Mytts3.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __Mytts3_h_h__
#define __Mytts3_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMytts3_FWD_DEFINED__
#define __IMytts3_FWD_DEFINED__
typedef interface IMytts3 IMytts3;

#endif 	/* __IMytts3_FWD_DEFINED__ */


#ifndef __Mytts3_FWD_DEFINED__
#define __Mytts3_FWD_DEFINED__

#ifdef __cplusplus
typedef class Mytts3 Mytts3;
#else
typedef struct Mytts3 Mytts3;
#endif /* __cplusplus */

#endif 	/* __Mytts3_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Mytts3_LIBRARY_DEFINED__
#define __Mytts3_LIBRARY_DEFINED__

/* library Mytts3 */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Mytts3;

#ifndef __IMytts3_DISPINTERFACE_DEFINED__
#define __IMytts3_DISPINTERFACE_DEFINED__

/* dispinterface IMytts3 */
/* [uuid] */ 


EXTERN_C const IID DIID_IMytts3;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0c24bd81-9cdd-4400-9ec1-387069640989")
    IMytts3 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMytts3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMytts3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMytts3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMytts3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMytts3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMytts3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMytts3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMytts3 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMytts3Vtbl;

    interface IMytts3
    {
        CONST_VTBL struct IMytts3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMytts3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMytts3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMytts3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMytts3_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMytts3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMytts3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMytts3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMytts3_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Mytts3;

#ifdef __cplusplus

class DECLSPEC_UUID("ebc507bb-b1c0-40f2-a3fa-1ef070239179")
Mytts3;
#endif
#endif /* __Mytts3_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


