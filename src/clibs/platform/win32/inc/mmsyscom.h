#ifndef _MMSYSCOM_H
#define _MMSYSCOM_H

#ifdef __ORANGEC__ 
#pragma GCC system_header
#endif

#include <pshpack1.h>

#define WINMMAPI  DECLSPEC_IMPORT

#define MAXPNAMELEN  32
#define MAXERRORLENGTH  256
#define MAX_JOYSTICKOEMVXDNAME  260

#ifndef MM_MIDI_MAPPER
#define MM_MIDI_MAPPER      1
#define MM_WAVE_MAPPER      2
#define MM_SNDBLST_MIDIOUT  3
#define MM_SNDBLST_MIDIIN   4
#define MM_SNDBLST_SYNTH    5
#define MM_SNDBLST_WAVEOUT  6
#define MM_SNDBLST_WAVEIN   7
#define MM_ADLIB            9
#define MM_MPU401_MIDIOUT   10
#define MM_MPU401_MIDIIN    11
#define MM_PC_JOYSTICK      12
#endif /* MM_MIDI_MAPPER */

typedef UINT MMVERSION;
typedef UINT MMRESULT;

#define _MMRESULT_

typedef UINT *LPUINT;

typedef struct mmtime_tag {
    UINT wType;
    union {
        DWORD ms;
        DWORD sample;
        DWORD cb;
        DWORD ticks;

        struct {
            BYTE hour;
            BYTE min;
            BYTE sec;
            BYTE frame;
            BYTE fps;
            BYTE dummy;
            BYTE pad[2];
        } smpte;
        struct {
            DWORD songptrpos;
        } midi;
    } u;
} MMTIME, *PMMTIME, *NPMMTIME, *LPMMTIME;

#define TIME_MS       0x0001
#define TIME_SAMPLES  0x0002
#define TIME_BYTES    0x0004
#define TIME_SMPTE    0x0008
#define TIME_MIDI     0x0010
#define TIME_TICKS    0x0020

#define MAKEFOURCC(ch0,ch1,ch2,ch3) \
    ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
    ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24))

#define MM_JOY1MOVE         0x3A0
#define MM_JOY2MOVE         0x3A1
#define MM_JOY1ZMOVE        0x3A2
#define MM_JOY2ZMOVE        0x3A3
#define MM_JOY1BUTTONDOWN   0x3B5
#define MM_JOY2BUTTONDOWN   0x3B6
#define MM_JOY1BUTTONUP     0x3B7
#define MM_JOY2BUTTONUP     0x3B8

#define MM_MCINOTIFY        0x3B9

#define MM_WOM_OPEN         0x3BB
#define MM_WOM_CLOSE        0x3BC
#define MM_WOM_DONE         0x3BD

#define MM_WIM_OPEN         0x3BE
#define MM_WIM_CLOSE        0x3BF
#define MM_WIM_DATA         0x3C0

#define MM_MIM_OPEN         0x3C1
#define MM_MIM_CLOSE        0x3C2
#define MM_MIM_DATA         0x3C3
#define MM_MIM_LONGDATA     0x3C4
#define MM_MIM_ERROR        0x3C5
#define MM_MIM_LONGERROR    0x3C6

#define MM_MOM_OPEN         0x3C7
#define MM_MOM_CLOSE        0x3C8
#define MM_MOM_DONE         0x3C9

#ifndef MM_DRVM_OPEN
#define MM_DRVM_OPEN        0x3D0
#define MM_DRVM_CLOSE       0x3D1
#define MM_DRVM_DATA        0x3D2
#define MM_DRVM_ERROR       0x3D3
#endif /* !MM_DRVM_OPEN */

#define MM_STREAM_OPEN      0x3D4
#define MM_STREAM_CLOSE     0x3D5
#define MM_STREAM_DONE      0x3D6
#define MM_STREAM_ERROR     0x3D7

#define MM_MOM_POSITIONCB   0x3CA

#ifndef MM_MCISIGNAL
#define MM_MCISIGNAL        0x3CB
#endif /* !MM_MCISIGNAL */

#define MM_MIM_MOREDATA     0x3CC

#define MM_MIXM_LINE_CHANG  0x3D0
#define MM_MIXM_CONTROL_CHANGE  0x3D1

#define MMSYSERR_BASE       0
#define WAVERR_BASE         32
#define MIDIERR_BASE        64
#define TIMERR_BASE         96
#define JOYERR_BASE         160
#define MCIERR_BASE         256
#define MIXERR_BASE         1024

#define MCI_STRING_OFFSET   512
#define MCI_VD_OFFSET       1024
#define MCI_CD_OFFSET       1088
#define MCI_WAVE_OFFSET     1152
#define MCI_SEQ_OFFSET      1216

#define MMSYSERR_NOERROR       0
#define MMSYSERR_ERROR         (MMSYSERR_BASE + 1)
#define MMSYSERR_BADDEVICEID   (MMSYSERR_BASE + 2)
#define MMSYSERR_NOTENABLED    (MMSYSERR_BASE + 3)
#define MMSYSERR_ALLOCATED     (MMSYSERR_BASE + 4)
#define MMSYSERR_INVALHANDLE   (MMSYSERR_BASE + 5)
#define MMSYSERR_NODRIVER      (MMSYSERR_BASE + 6)
#define MMSYSERR_NOMEM         (MMSYSERR_BASE + 7)
#define MMSYSERR_NOTSUPPORTED  (MMSYSERR_BASE + 8)
#define MMSYSERR_BADERRNUM     (MMSYSERR_BASE + 9)
#define MMSYSERR_INVALFLAG     (MMSYSERR_BASE + 10)
#define MMSYSERR_INVALPARAM    (MMSYSERR_BASE + 11)
#define MMSYSERR_HANDLEBUSY    (MMSYSERR_BASE + 12)
#define MMSYSERR_INVALIDALIAS  (MMSYSERR_BASE + 13)
#define MMSYSERR_BADDB         (MMSYSERR_BASE + 14)
#define MMSYSERR_KEYNOTFOUND   (MMSYSERR_BASE + 15)
#define MMSYSERR_READERROR     (MMSYSERR_BASE + 16)
#define MMSYSERR_WRITEERROR    (MMSYSERR_BASE + 17)
#define MMSYSERR_DELETEERROR   (MMSYSERR_BASE + 18)
#define MMSYSERR_VALNOTFOUND   (MMSYSERR_BASE + 19)
#define MMSYSERR_NODRIVERCB    (MMSYSERR_BASE + 20)
#define MMSYSERR_MOREDATA      (MMSYSERR_BASE + 21)
#define MMSYSERR_LASTERROR     (MMSYSERR_BASE + 21)

DECLARE_HANDLE(HDRVR);

#define CALLBACK_TYPEMASK   0x00070000l
#define CALLBACK_NULL       0x00000000l
#define CALLBACK_WINDOW     0x00010000l
#define CALLBACK_TASK       0x00020000l
#define CALLBACK_FUNCTION   0x00030000l
#define CALLBACK_THREAD     (CALLBACK_TASK)
#define CALLBACK_EVENT      0x00050000l

typedef void (CALLBACK DRVCALLBACK)(HDRVR, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);

typedef DRVCALLBACK *LPDRVCALLBACK;
typedef DRVCALLBACK *PDRVCALLBACK;

#include <poppack.h>

#endif /* _MMSYSCOM_H */
