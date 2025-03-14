#ifndef _OLE2_H
#define _OLE2_H

#ifdef __ORANGEC__ 
#pragma GCC system_header
#endif

/* Windows Linking and Embedding API definitions */

#include <pshpack8.h>
#include <winerror.h>
#include <objbase.h>
#include <oleauto.h>

#define E_DRAW  VIEW_E_DRAW

#define DATA_E_FORMATETC  DV_E_FORMATETC

#define OLEIVERB_PRIMARY  (0L)
#define OLEIVERB_SHOW  (-1L)
#define OLEIVERB_OPEN  (-2L)
#define OLEIVERB_HIDE  (-3L)
#define OLEIVERB_UIACTIVATE  (-4L)
#define OLEIVERB_INPLACEACTIVATE  (-5L)
#define OLEIVERB_DISCARDUNDOSTATE  (-6L)

#define EMBDHLP_INPROC_HANDLER  0x0000L
#define EMBDHLP_INPROC_SERVER  0x0001L
#define EMBDHLP_CREATENOW  0x00000000L
#define EMBDHLP_DELAYCREATE  0x00010000L

#define OLECREATE_LEAVERUNNING  0x00000001

#include <oleidl.h>

WINOLEAPI CreateDataAdviseHolder(LPDATAADVISEHOLDER*);
WINOLEAPI_(DWORD) OleBuildVersion(VOID);
WINOLEAPI ReadClassStg(LPSTORAGE,CLSID*);
WINOLEAPI WriteClassStg(LPSTORAGE,REFCLSID);
WINOLEAPI ReadClassStm(LPSTREAM,CLSID*);
WINOLEAPI WriteClassStm(LPSTREAM,REFCLSID);
WINOLEAPI WriteFmtUserTypeStg (LPSTORAGE,CLIPFORMAT,LPOLESTR);
WINOLEAPI ReadFmtUserTypeStg (LPSTORAGE,CLIPFORMAT*,LPOLESTR*);
WINOLEAPI OleInitialize(LPVOID);
WINOLEAPI_(void) OleUninitialize(void);
WINOLEAPI OleQueryLinkFromData(LPDATAOBJECT);
WINOLEAPI OleQueryCreateFromData(LPDATAOBJECT);
WINOLEAPI OleCreate(REFCLSID,REFIID,DWORD,LPFORMATETC,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateEx(REFCLSID,REFIID,DWORD,DWORD,ULONG,DWORD*,LPFORMATETC,IAdviseSink*,DWORD*,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateFromData(LPDATAOBJECT,REFIID,DWORD,LPFORMATETC,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateFromDataEx(LPDATAOBJECT,REFIID,DWORD,DWORD,ULONG,DWORD*,LPFORMATETC,IAdviseSink*,DWORD*,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateLinkFromData(LPDATAOBJECT,REFIID,DWORD,LPFORMATETC,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateLinkFromDataEx(LPDATAOBJECT,REFIID,DWORD,DWORD,ULONG,DWORD*,LPFORMATETC,IAdviseSink*,DWORD*,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateStaticFromData(LPDATAOBJECT,REFIID,DWORD,LPFORMATETC,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateLink(LPMONIKER,REFIID,DWORD,LPFORMATETC,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateLinkEx(LPMONIKER,REFIID,DWORD,DWORD,ULONG,DWORD*,LPFORMATETC,IAdviseSink*,DWORD*,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateLinkToFile(LPCOLESTR,REFIID,DWORD,LPFORMATETC,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateLinkToFileEx(LPCOLESTR,REFIID,DWORD,DWORD,ULONG,DWORD*,LPFORMATETC,IAdviseSink*,DWORD*,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateFromFile(REFCLSID,LPCOLESTR,REFIID,DWORD,LPFORMATETC,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleCreateFromFileEx(REFCLSID,LPCOLESTR,REFIID,DWORD,DWORD,ULONG,DWORD*,LPFORMATETC,IAdviseSink*,DWORD*,LPOLECLIENTSITE,LPSTORAGE,LPVOID*);
WINOLEAPI OleLoad(LPSTORAGE,REFIID,LPOLECLIENTSITE,LPVOID*);
WINOLEAPI OleSave(LPPERSISTSTORAGE,LPSTORAGE,BOOL);
WINOLEAPI OleLoadFromStream(LPSTREAM,REFIID,LPVOID*);
WINOLEAPI OleSaveToStream(LPPERSISTSTREAM,LPSTREAM);
WINOLEAPI OleSetContainedObject(LPUNKNOWN,BOOL);
WINOLEAPI OleNoteObjectVisible(LPUNKNOWN,BOOL);
WINOLEAPI RegisterDragDrop(HWND,LPDROPTARGET);
WINOLEAPI RevokeDragDrop(HWND);
WINOLEAPI DoDragDrop(LPDATAOBJECT,LPDROPSOURCE,DWORD,LPDWORD);
WINOLEAPI OleSetClipboard(LPDATAOBJECT);
WINOLEAPI OleGetClipboard(LPDATAOBJECT*);
WINOLEAPI OleFlushClipboard(void);
WINOLEAPI OleIsCurrentClipboard(LPDATAOBJECT);
WINOLEAPI_(HOLEMENU) OleCreateMenuDescriptor(HMENU,LPOLEMENUGROUPWIDTHS);
WINOLEAPI OleSetMenuDescriptor(HOLEMENU,HWND,HWND,LPOLEINPLACEFRAME,LPOLEINPLACEACTIVEOBJECT);
WINOLEAPI OleDestroyMenuDescriptor(HOLEMENU);
WINOLEAPI OleTranslateAccelerator(LPOLEINPLACEFRAME,LPOLEINPLACEFRAMEINFO,LPMSG);
WINOLEAPI_(HANDLE) OleDuplicateData(HANDLE,CLIPFORMAT,UINT);
WINOLEAPI OleDraw(LPUNKNOWN,DWORD,HDC,LPCRECT);
WINOLEAPI OleRun(LPUNKNOWN);
WINOLEAPI_(BOOL) OleIsRunning(LPOLEOBJECT);
WINOLEAPI OleLockRunning(LPUNKNOWN,BOOL,BOOL);
WINOLEAPI_(void) ReleaseStgMedium(LPSTGMEDIUM);
WINOLEAPI CreateOleAdviseHolder(LPOLEADVISEHOLDER*);
WINOLEAPI OleCreateDefaultHandler(REFCLSID,LPUNKNOWN,REFIID,LPVOID*);
WINOLEAPI OleCreateEmbeddingHelper(REFCLSID,LPUNKNOWN,DWORD,LPCLASSFACTORY,REFIID,LPVOID*);
WINOLEAPI_(BOOL) IsAccelerator(HACCEL,int,LPMSG,WORD*);
WINOLEAPI_(HGLOBAL) OleGetIconOfFile(LPOLESTR,BOOL);
WINOLEAPI_(HGLOBAL) OleGetIconOfClass(REFCLSID,LPOLESTR,BOOL);
WINOLEAPI_(HGLOBAL) OleMetafilePictFromIconAndLabel(HICON,LPOLESTR,LPOLESTR,UINT);
WINOLEAPI OleRegGetUserType(REFCLSID,DWORD,LPOLESTR*);
WINOLEAPI OleRegGetMiscStatus(REFCLSID,DWORD,DWORD*);
WINOLEAPI OleRegEnumFormatEtc(REFCLSID,DWORD,LPENUMFORMATETC*);
WINOLEAPI OleRegEnumVerbs(REFCLSID,LPENUMOLEVERB*);

/* OLE 1.0 declarations */

typedef struct _OLESTREAM *LPOLESTREAM;

typedef struct _OLESTREAMVTBL {
    DWORD (CALLBACK* Get)(LPOLESTREAM,void*,DWORD);
    DWORD (CALLBACK* Put)(LPOLESTREAM,const void*,DWORD);
} OLESTREAMVTBL, *LPOLESTREAMVTBL;

typedef struct _OLESTREAM {
    LPOLESTREAMVTBL lpstbl;
} OLESTREAM;

WINOLEAPI OleConvertOLESTREAMToIStorage(LPOLESTREAM,LPSTORAGE,const DVTARGETDEVICE*);
WINOLEAPI OleConvertIStorageToOLESTREAM(LPSTORAGE,LPOLESTREAM);
WINOLEAPI GetHGlobalFromILockBytes(LPLOCKBYTES,HGLOBAL*);
WINOLEAPI CreateILockBytesOnHGlobal(HGLOBAL,BOOL,LPLOCKBYTES*);
WINOLEAPI GetHGlobalFromStream(LPSTREAM,HGLOBAL*);
WINOLEAPI CreateStreamOnHGlobal(HGLOBAL,BOOL,LPSTREAM*);
WINOLEAPI OleDoAutoConvert(LPSTORAGE,LPCLSID);
WINOLEAPI OleGetAutoConvert(REFCLSID,LPCLSID);
WINOLEAPI OleSetAutoConvert(REFCLSID,REFCLSID);
WINOLEAPI GetConvertStg(LPSTORAGE);
WINOLEAPI SetConvertStg(LPSTORAGE,BOOL);
WINOLEAPI OleConvertIStorageToOLESTREAMEx(LPSTORAGE,CLIPFORMAT,LONG,LONG,DWORD,LPSTGMEDIUM,LPOLESTREAM);
WINOLEAPI OleConvertOLESTREAMToIStorageEx(LPOLESTREAM,LPSTORAGE,CLIPFORMAT*,LONG*,LONG*,DWORD*,LPSTGMEDIUM);

#include <poppack.h>

#endif /* _OLE2_H */

