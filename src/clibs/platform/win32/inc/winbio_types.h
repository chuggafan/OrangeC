#ifndef _WINBIO_TYPES_H
#define _WINBIO_TYPES_H

#if (NTDDI_VERSION >= NTDDI_WIN7)

typedef ULONG WINBIO_UNIT_ID, *PWINBIO_UNIT_ID;
typedef ULONG WINBIO_SESSION_HANDLE, *PWINBIO_SESSION_HANDLE;
typedef WINBIO_SESSION_HANDLE WINBIO_FRAMEWORK_HANDLE, *PWINBIO_FRAMEWORK_HANDLE;

typedef GUID WINBIO_UUID, *PWINBIO_UUID;

#define WINBIO_MAX_STRING_LEN  256
typedef WCHAR WINBIO_STRING[WINBIO_MAX_STRING_LEN];
typedef WINBIO_STRING *PWINBIO_STRING;

typedef struct _WINBIO_VERSION {
    DWORD MajorVersion;
    DWORD MinorVersion;
} WINBIO_VERSION, *PWINBIO_VERSION;

typedef ULONG WINBIO_IDENTITY_TYPE, *PWINBIO_IDENTITY_TYPE;

#define WINBIO_ID_TYPE_NULL  ((WINBIO_IDENTITY_TYPE)0)
#define WINBIO_ID_TYPE_WILDCARD ((WINBIO_IDENTITY_TYPE)1)
#define WINBIO_ID_TYPE_GUID  ((WINBIO_IDENTITY_TYPE)2)
#define WINBIO_ID_TYPE_SID  ((WINBIO_IDENTITY_TYPE)3)

typedef struct _WINBIO_IDENTITY {
    WINBIO_IDENTITY_TYPE Type;
    union {
        ULONG Null;
        ULONG Wildcard;
        GUID TemplateGuid;
        struct {
            ULONG Size;
            UCHAR Data[SECURITY_MAX_SID_SIZE];
        } AccountSid;
    } Value;
} WINBIO_IDENTITY;

typedef WINBIO_IDENTITY *PWINBIO_IDENTITY;

#define WINBIO_IDENTITY_WILDCARD  ((ULONG)0x25066282)

typedef ULONG32 WINBIO_BIOMETRIC_TYPE, *PWINBIO_BIOMETRIC_TYPE;

#define WINBIO_STANDARD_TYPE_MASK  ((WINBIO_BIOMETRIC_TYPE)0x00FFFFFF)

#define WINBIO_NO_TYPE_AVAILABLE  ((WINBIO_BIOMETRIC_TYPE)0x00000000)

#define WINBIO_TYPE_MULTIPLE  ((WINBIO_BIOMETRIC_TYPE)0x00000001)
#define WINBIO_TYPE_FACIAL_FEATURES  ((WINBIO_BIOMETRIC_TYPE)0x00000002)
#define WINBIO_TYPE_VOICE  ((WINBIO_BIOMETRIC_TYPE)0x00000004)
#define WINBIO_TYPE_FINGERPRINT  ((WINBIO_BIOMETRIC_TYPE)0x00000008)
#define WINBIO_TYPE_IRIS  ((WINBIO_BIOMETRIC_TYPE)0x00000010)
#define WINBIO_TYPE_RETINA  ((WINBIO_BIOMETRIC_TYPE)0x00000020)
#define WINBIO_TYPE_HAND_GEOMETRY  ((WINBIO_BIOMETRIC_TYPE)0x00000040)
#define WINBIO_TYPE_SIGNATURE_DYNAMICS  ((WINBIO_BIOMETRIC_TYPE)0x00000080)
#define WINBIO_TYPE_KEYSTROKE_DYNAMICS  ((WINBIO_BIOMETRIC_TYPE)0x00000100)
#define WINBIO_TYPE_LIP_MOVEMENT  ((WINBIO_BIOMETRIC_TYPE)0x00000200)
#define WINBIO_TYPE_THERMAL_FACE_IMAGE  ((WINBIO_BIOMETRIC_TYPE)0x00000400)
#define WINBIO_TYPE_THERMAL_HAND_IMAGE  ((WINBIO_BIOMETRIC_TYPE)0x00000800)
#define WINBIO_TYPE_GAIT  ((WINBIO_BIOMETRIC_TYPE)0x00001000)
#define WINBIO_TYPE_SCENT  ((WINBIO_BIOMETRIC_TYPE)0x00002000)
#define WINBIO_TYPE_DNA  ((WINBIO_BIOMETRIC_TYPE)0x00004000)
#define WINBIO_TYPE_EAR_SHAPE  ((WINBIO_BIOMETRIC_TYPE)0x00008000)
#define WINBIO_TYPE_FINGER_GEOMETRY  ((WINBIO_BIOMETRIC_TYPE)0x00010000)
#define WINBIO_TYPE_PALM_PRINT  ((WINBIO_BIOMETRIC_TYPE)0x00020000)
#define WINBIO_TYPE_VEIN_PATTERN  ((WINBIO_BIOMETRIC_TYPE)0x00040000)
#define WINBIO_TYPE_FOOT_PRINT  ((WINBIO_BIOMETRIC_TYPE)0x00080000)
#define WINBIO_TYPE_OTHER  ((WINBIO_BIOMETRIC_TYPE)0x40000000)
#define WINBIO_TYPE_PASSWORD  ((WINBIO_BIOMETRIC_TYPE)0x80000000)

#define WINBIO_TYPE_ANY  ((WINBIO_BIOMETRIC_TYPE)(WINBIO_STANDARD_TYPE_MASK |  \
  WINBIO_TYPE_OTHER |  \
  WINBIO_TYPE_PASSWORD))

typedef ULONG WINBIO_BIOMETRIC_SENSOR_SUBTYPE, *PWINBIO_BIOMETRIC_SENSOR_SUBTYPE;

#define WINBIO_SENSOR_SUBTYPE_UNKNOWN  ((WINBIO_BIOMETRIC_SENSOR_SUBTYPE)0x00000000)

#define WINBIO_FP_SENSOR_SUBTYPE_SWIPE  ((WINBIO_BIOMETRIC_SENSOR_SUBTYPE)0x00000001)
#define WINBIO_FP_SENSOR_SUBTYPE_TOUCH  ((WINBIO_BIOMETRIC_SENSOR_SUBTYPE)0x00000002)

typedef ULONG WINBIO_CAPABILITIES, *PWINBIO_CAPABILITIES;

#define WINBIO_CAPABILITY_SENSOR  ((WINBIO_CAPABILITIES)0x00000001)
#define WINBIO_CAPABILITY_MATCHING  ((WINBIO_CAPABILITIES)0x00000002)
#define WINBIO_CAPABILITY_DATABASE  ((WINBIO_CAPABILITIES)0x00000004)
#define WINBIO_CAPABILITY_PROCESSING  ((WINBIO_CAPABILITIES)0x00000008)
#define WINBIO_CAPABILITY_ENCRYPTION  ((WINBIO_CAPABILITIES)0x00000010)
#define WINBIO_CAPABILITY_NAVIGATION  ((WINBIO_CAPABILITIES)0x00000020)
#define WINBIO_CAPABILITY_INDICATOR  ((WINBIO_CAPABILITIES)0x00000040)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
#define WINBIO_CAPABILITY_VIRTUAL_SENSOR  ((WINBIO_CAPABILITIES)0x00000080)
#endif /* NTDDI_VERSION >= NTDDI_WINTHRESHOLD */

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
#define WINBIO_CAPABILITY_SECURE_SENSOR  ((WINBIO_CAPABILITIES)0x00000100)
#endif /* NTDDI_VERSION >= NTDDI_WIN10_RS1 */

typedef ULONG WINBIO_SENSOR_STATUS, *PWINBIO_SENSOR_STATUS;

#define WINBIO_SENSOR_STATUS_UNKNOWN  ((WINBIO_SENSOR_STATUS)0)
#define WINBIO_SENSOR_ACCEPT  ((WINBIO_SENSOR_STATUS)1)
#define WINBIO_SENSOR_REJECT  ((WINBIO_SENSOR_STATUS)2)
#define WINBIO_SENSOR_READY  ((WINBIO_SENSOR_STATUS)3)
#define WINBIO_SENSOR_BUSY  ((WINBIO_SENSOR_STATUS)4)
#define WINBIO_SENSOR_NOT_CALIBRATED  ((WINBIO_SENSOR_STATUS)5)
#define WINBIO_SENSOR_FAILURE  ((WINBIO_SENSOR_STATUS)6)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
#define WINBIO_SENSOR_AVAILABLE  ((WINBIO_SENSOR_STATUS)7)
#define WINBIO_SENSOR_UNAVAILABLE  ((WINBIO_SENSOR_STATUS)8)
#endif /* NTDDI_VERSION >= NTDDI_WINTHRESHOLD */

typedef DWORD WINBIO_INDICATOR_STATUS, *PWINBIO_INDICATOR_STATUS;

#define WINBIO_INDICATOR_ON  ((WINBIO_INDICATOR_STATUS)1)
#define WINBIO_INDICATOR_OFF  ((WINBIO_INDICATOR_STATUS)2)

typedef ULONG WINBIO_SENSOR_MODE, *PWINBIO_SENSOR_MODE;

#define WINBIO_SENSOR_UNKNOWN_MODE  ((WINBIO_SENSOR_MODE)0)
#define WINBIO_SENSOR_BASIC_MODE  ((WINBIO_SENSOR_MODE)1)
#define WINBIO_SENSOR_ADVANCED_MODE  ((WINBIO_SENSOR_MODE)2)
#define WINBIO_SENSOR_NAVIGATION_MODE  ((WINBIO_SENSOR_MODE)3)
#define WINBIO_SENSOR_SLEEP_MODE  ((WINBIO_SENSOR_MODE)4)

typedef UCHAR WINBIO_BIOMETRIC_SUBTYPE, *PWINBIO_BIOMETRIC_SUBTYPE;

#define WINBIO_SUBTYPE_NO_INFORMATION  ((WINBIO_BIOMETRIC_SUBTYPE)0x00)
#define WINBIO_SUBTYPE_ANY  ((WINBIO_BIOMETRIC_SUBTYPE)0xFF)

typedef ULONG WINBIO_REJECT_DETAIL, *PWINBIO_REJECT_DETAIL;


#ifndef WINBIO_REJECT_DETAILS_DEFINED
#define WINBIO_REJECT_DETAILS_DEFINED

#define WINBIO_FP_TOO_HIGH  ((WINBIO_REJECT_DETAIL)1)
#define WINBIO_FP_TOO_LOW  ((WINBIO_REJECT_DETAIL)2)
#define WINBIO_FP_TOO_LEFT  ((WINBIO_REJECT_DETAIL)3)
#define WINBIO_FP_TOO_RIGHT  ((WINBIO_REJECT_DETAIL)4)
#define WINBIO_FP_TOO_FAST  ((WINBIO_REJECT_DETAIL)5)
#define WINBIO_FP_TOO_SLOW  ((WINBIO_REJECT_DETAIL)6)
#define WINBIO_FP_POOR_QUALITY  ((WINBIO_REJECT_DETAIL)7)
#define WINBIO_FP_TOO_SKEWED  ((WINBIO_REJECT_DETAIL)8)
#define WINBIO_FP_TOO_SHORT  ((WINBIO_REJECT_DETAIL)9)
#define WINBIO_FP_MERGE_FAILURE  ((WINBIO_REJECT_DETAIL)10)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

#define WINBIO_REJECT_DETAIL_ANTI_SPOOF_MASK  ((WINBIO_REJECT_DETAIL)0xFF000000)

#define WINBIO_ANTI_SPOOF_TURN_SIDE_TO_SIDE  ((WINBIO_REJECT_DETAIL)0x01000000)

#define WINBIO_REJECT_DETAIL_POSITION_MASK  ((WINBIO_REJECT_DETAIL)0x00FF0000)

#define WINBIO_REJECT_DETAIL_REASON_MASK  ((WINBIO_REJECT_DETAIL)0x0000FFFF)

#define WINBIO_IRIS_POOR_QUALITY  ((WINBIO_REJECT_DETAIL)1)
#define WINBIO_IRIS_TOO_BRIGHT  ((WINBIO_REJECT_DETAIL)2)
#define WINBIO_IRIS_TOO_DARK  ((WINBIO_REJECT_DETAIL)3)
#define WINBIO_IRIS_SPOOF_DETECTED  ((WINBIO_REJECT_DETAIL)4)
#define WINBIO_IRIS_TOO_SKEWED  ((WINBIO_REJECT_DETAIL)5)
#define WINBIO_IRIS_TOO_CLOSED  ((WINBIO_REJECT_DETAIL)6)
#define WINBIO_IRIS_GLARE  ((WINBIO_REJECT_DETAIL)7)
#define WINBIO_IRIS_DIRTY_LENS  ((WINBIO_REJECT_DETAIL)8)
#define WINBIO_IRIS_POOR_FOCUS  ((WINBIO_REJECT_DETAIL)9)

#define WINBIO_IRIS_WRONG_ORIENTATION  ((WINBIO_REJECT_DETAIL)10)

#define WINBIO_IRIS_TOO_HIGH  ((WINBIO_REJECT_DETAIL)0x00010000)
#define WINBIO_IRIS_TOO_LOW  ((WINBIO_REJECT_DETAIL)0x00020000)
#define WINBIO_IRIS_TOO_LEFT  ((WINBIO_REJECT_DETAIL)0x00040000)
#define WINBIO_IRIS_TOO_RIGHT  ((WINBIO_REJECT_DETAIL)0x00080000)
#define WINBIO_IRIS_TOO_NEAR  ((WINBIO_REJECT_DETAIL)0x00100000)
#define WINBIO_IRIS_TOO_FAR  ((WINBIO_REJECT_DETAIL)0x00200000)

#define WINBIO_FACE_POOR_QUALITY  ((WINBIO_REJECT_DETAIL)1)
#define WINBIO_FACE_TOO_BRIGHT  ((WINBIO_REJECT_DETAIL)2)
#define WINBIO_FACE_TOO_DARK  ((WINBIO_REJECT_DETAIL)3)
#define WINBIO_FACE_SPOOF_DETECTED  ((WINBIO_REJECT_DETAIL)4)
#define WINBIO_FACE_AMBIGUOUS_TARGET  ((WINBIO_REJECT_DETAIL)5)
#define WINBIO_FACE_EYES_OCCLUDED  ((WINBIO_REJECT_DETAIL)6)

#define WINBIO_FACE_WRONG_ORIENTATION  ((WINBIO_REJECT_DETAIL)7)

#define WINBIO_FACE_TOO_HIGH  ((WINBIO_REJECT_DETAIL)0x00010000)
#define WINBIO_FACE_TOO_LOW  ((WINBIO_REJECT_DETAIL)0x00020000)
#define WINBIO_FACE_TOO_LEFT  ((WINBIO_REJECT_DETAIL)0x00040000)
#define WINBIO_FACE_TOO_RIGHT  ((WINBIO_REJECT_DETAIL)0x00080000)
#define WINBIO_FACE_TOO_NEAR  ((WINBIO_REJECT_DETAIL)0x00100000)
#define WINBIO_FACE_TOO_FAR  ((WINBIO_REJECT_DETAIL)0x00200000)

#define WINBIO_VOICE_POOR_QUALITY  ((WINBIO_REJECT_DETAIL)1)
#define WINBIO_VOICE_TOO_SLOW  ((WINBIO_REJECT_DETAIL)2)
#define WINBIO_VOICE_TOO_FAST  ((WINBIO_REJECT_DETAIL)3)
#define WINBIO_VOICE_NO_KEYWORD  ((WINBIO_REJECT_DETAIL)4)
#define WINBIO_VOICE_PROCESSING_ERROR  ((WINBIO_REJECT_DETAIL)5)

#endif /* NTDDI_VERSION >= NTDDI_WINTHRESHOLD */

#endif /* WINBIO_REJECT_DETAILS_DEFINED */


#define WINBIO_BIR_ALIGN_SIZE  (8)
#define WINBIO_BIR_ALGIN_SIZE  WINBIO_BIR_ALIGN_SIZE

typedef struct _WINBIO_BIR_DATA {
    ULONG Size;
    ULONG Offset;
} WINBIO_BIR_DATA;

typedef WINBIO_BIR_DATA *PWINBIO_BIR_DATA;

typedef struct _WINBIO_BIR {
    WINBIO_BIR_DATA HeaderBlock;
    WINBIO_BIR_DATA StandardDataBlock;
    WINBIO_BIR_DATA VendorDataBlock;
    WINBIO_BIR_DATA SignatureBlock;
} WINBIO_BIR;

typedef WINBIO_BIR *PWINBIO_BIR;

#define WINBIO_BIR_FIELD_SUBHEAD_COUNT  ((USHORT)0x0001)
#define WINBIO_BIR_FIELD_PRODUCT_ID  ((USHORT)0x0002)
#define WINBIO_BIR_FIELD_PATRON_ID  ((USHORT)0x0004)
#define WINBIO_BIR_FIELD_INDEX  ((USHORT)0x0008)

#define WINBIO_BIR_FIELD_CREATION_DATE  ((USHORT)0x0010)
#define WINBIO_BIR_FIELD_VALIDITY_PERIOD  ((USHORT)0x0020)
#define WINBIO_BIR_FIELD_BIOMETRIC_TYPE  ((USHORT)0x0040)
#define WINBIO_BIR_FIELD_BIOMETRIC_SUBTYPE  ((USHORT)0x0080)

#define WINBIO_BIR_FIELD_CBEFF_HEADER_VERSION  ((USHORT)0x0100)
#define WINBIO_BIR_FIELD_PATRON_HEADER_VERSION  ((USHORT)0x0200)
#define WINBIO_BIR_FIELD_BIOMETRIC_PURPOSE  ((USHORT)0x0400)
#define WINBIO_BIR_FIELD_BIOMETRIC_CONDITION  ((USHORT)0x0800)

#define WINBIO_BIR_FIELD_QUALITY  ((USHORT)0x1000)
#define WINBIO_BIR_FIELD_CREATOR  ((USHORT)0x2000)
#define WINBIO_BIR_FIELD_CHALLENGE  ((USHORT)0x4000)
#define WINBIO_BIR_FIELD_PAYLOAD  ((USHORT)0x8000)

#define WINBIO_BIR_FIELD_NEVER_VALID  (WINBIO_BIR_FIELD_SUBHEAD_COUNT |  \
  WINBIO_BIR_FIELD_PATRON_ID |  \
  WINBIO_BIR_FIELD_INDEX |  \
  WINBIO_BIR_FIELD_CHALLENGE |  \
  WINBIO_BIR_FIELD_PAYLOAD )

typedef UCHAR WINBIO_BIR_VERSION, *PWINBIO_BIR_VERSION;

#define WINBIO_CBEFF_HEADER_VERSION  ((WINBIO_BIR_VERSION)0x11)
#define WINBIO_PATRON_HEADER_VERSION  ((WINBIO_BIR_VERSION)0x11)

typedef UCHAR WINBIO_BIR_DATA_FLAGS, *PWINBIO_BIR_DATA_FLAGS;

#define WINBIO_DATA_FLAG_PRIVACY  ((UCHAR)0x02)
#define WINBIO_DATA_FLAG_INTEGRITY  ((UCHAR)0x01)
#define WINBIO_DATA_FLAG_SIGNED  ((UCHAR)0x04)

#define WINBIO_DATA_FLAG_RAW  ((UCHAR)0x20)
#define WINBIO_DATA_FLAG_INTERMEDIATE  ((UCHAR)0x40)
#define WINBIO_DATA_FLAG_PROCESSED  ((UCHAR)0x80)

#define WINBIO_DATA_FLAG_OPTION_MASK_PRESENT  ((UCHAR)0x08)

typedef UCHAR WINBIO_BIR_PURPOSE, *PWINBIO_BIR_PURPOSE;

#define WINBIO_NO_PURPOSE_AVAILABLE  ((WINBIO_BIR_PURPOSE)0x00)
#define WINBIO_PURPOSE_VERIFY  ((WINBIO_BIR_PURPOSE)0x01)
#define WINBIO_PURPOSE_IDENTIFY  ((WINBIO_BIR_PURPOSE)0x02)
#define WINBIO_PURPOSE_ENROLL  ((WINBIO_BIR_PURPOSE)0x04)
#define WINBIO_PURPOSE_ENROLL_FOR_VERIFICATION  ((WINBIO_BIR_PURPOSE)0x08)
#define WINBIO_PURPOSE_ENROLL_FOR_IDENTIFICATION  ((WINBIO_BIR_PURPOSE)0x10)
#define WINBIO_PURPOSE_AUDIT  ((WINBIO_BIR_PURPOSE)0x80)

typedef CHAR WINBIO_BIR_QUALITY, *PWINBIO_BIR_QUALITY;

#define WINBIO_DATA_QUALITY_NOT_SET  ((WINBIO_BIR_QUALITY)-1)
#define WINBIO_DATA_QUALITY_NOT_SUPPORTED  ((WINBIO_BIR_QUALITY)-2)

typedef struct _WINBIO_REGISTERED_FORMAT {
    USHORT Owner;
    USHORT Type;
} WINBIO_REGISTERED_FORMAT, *PWINBIO_REGISTERED_FORMAT;

#define WINBIO_NO_FORMAT_OWNER_AVAILABLE  ((USHORT)0)
#define WINBIO_NO_FORMAT_TYPE_AVAILABLE  ((USHORT)0)

typedef struct _WINBIO_BIR_HEADER {
    USHORT ValidFields;
    WINBIO_BIR_VERSION HeaderVersion;
    WINBIO_BIR_VERSION PatronHeaderVersion;
    WINBIO_BIR_DATA_FLAGS DataFlags;
    WINBIO_BIOMETRIC_TYPE Type;
    WINBIO_BIOMETRIC_SUBTYPE Subtype;
    WINBIO_BIR_PURPOSE Purpose;
    WINBIO_BIR_QUALITY DataQuality;
    LARGE_INTEGER CreationDate;
    struct {
        LARGE_INTEGER BeginDate;
        LARGE_INTEGER EndDate;
    } ValidityPeriod;
    WINBIO_REGISTERED_FORMAT BiometricDataFormat;
    WINBIO_REGISTERED_FORMAT ProductId;
} WINBIO_BIR_HEADER;

typedef WINBIO_BIR_HEADER *PWINBIO_BIR_HEADER;

#define WINBIO_ANSI_381_FORMAT_OWNER  ((USHORT)0x001B)
#define WINBIO_ANSI_381_FORMAT_TYPE  ((USHORT)0x0401)

typedef struct _WINBIO_BDB_ANSI_381_HEADER {
    ULONG64 RecordLength;
    ULONG FormatIdentifier;
    ULONG VersionNumber;
    WINBIO_REGISTERED_FORMAT ProductId;
    USHORT CaptureDeviceId;
    USHORT ImageAcquisitionLevel;
    USHORT HorizontalScanResolution;
    USHORT VerticalScanResolution;
    USHORT HorizontalImageResolution;
    USHORT VerticalImageResolution;
    UCHAR ElementCount;
    UCHAR ScaleUnits;
    UCHAR PixelDepth;
    UCHAR ImageCompressionAlg;
    USHORT Reserved;
} WINBIO_BDB_ANSI_381_HEADER;

typedef WINBIO_BDB_ANSI_381_HEADER *PWINBIO_BDB_ANSI_381_HEADER;

#define WINBIO_ANSI_381_IMG_ACQ_LEVEL_10  ((USHORT)10)
#define WINBIO_ANSI_381_IMG_ACQ_LEVEL_20  ((USHORT)20)
#define WINBIO_ANSI_381_IMG_ACQ_LEVEL_30  ((USHORT)30)
#define WINBIO_ANSI_381_IMG_ACQ_LEVEL_31  ((USHORT)31)
#define WINBIO_ANSI_381_IMG_ACQ_LEVEL_40  ((USHORT)40)
#define WINBIO_ANSI_381_IMG_ACQ_LEVEL_41  ((USHORT)41)

#define WINBIO_ANSI_381_PIXELS_PER_INCH  ((UCHAR)0x01)
#define WINBIO_ANSI_381_PIXELS_PER_CM  ((UCHAR)0x02)

#define WINBIO_ANSI_381_IMG_UNCOMPRESSED  ((UCHAR)0)
#define WINBIO_ANSI_381_IMG_BIT_PACKED  ((UCHAR)1)
#define WINBIO_ANSI_381_IMG_COMPRESSED_WSQ  ((UCHAR)2)
#define WINBIO_ANSI_381_IMG_COMPRESSED_JPEG  ((UCHAR)3)
#define WINBIO_ANSI_381_IMG_COMPRESSED_JPEG2000  ((UCHAR)4)
#define WINBIO_ANSI_381_IMG_COMPRESSED_PNG  ((UCHAR)5)

typedef struct _WINBIO_BDB_ANSI_381_RECORD {
    ULONG BlockLength;
    USHORT HorizontalLineLength;
    USHORT VerticalLineLength;
    WINBIO_BIOMETRIC_SUBTYPE Position;
    UCHAR CountOfViews;
    UCHAR ViewNumber;
    UCHAR ImageQuality;
    UCHAR ImpressionType;
    UCHAR Reserved;
} WINBIO_BDB_ANSI_381_RECORD;

typedef WINBIO_BDB_ANSI_381_RECORD *PWINBIO_BDB_ANSI_381_RECORD;

#define WINBIO_ANSI_381_POS_UNKNOWN  ((WINBIO_BIOMETRIC_SUBTYPE)0)
#define WINBIO_ANSI_381_POS_RH_THUMB  ((WINBIO_BIOMETRIC_SUBTYPE)1)
#define WINBIO_ANSI_381_POS_RH_INDEX_FINGER  ((WINBIO_BIOMETRIC_SUBTYPE)2)
#define WINBIO_ANSI_381_POS_RH_MIDDLE_FINGER  ((WINBIO_BIOMETRIC_SUBTYPE)3)
#define WINBIO_ANSI_381_POS_RH_RING_FINGER  ((WINBIO_BIOMETRIC_SUBTYPE)4)
#define WINBIO_ANSI_381_POS_RH_LITTLE_FINGER  ((WINBIO_BIOMETRIC_SUBTYPE)5)
#define WINBIO_ANSI_381_POS_LH_THUMB  ((WINBIO_BIOMETRIC_SUBTYPE)6)
#define WINBIO_ANSI_381_POS_LH_INDEX_FINGER  ((WINBIO_BIOMETRIC_SUBTYPE)7)
#define WINBIO_ANSI_381_POS_LH_MIDDLE_FINGER  ((WINBIO_BIOMETRIC_SUBTYPE)8)
#define WINBIO_ANSI_381_POS_LH_RING_FINGER  ((WINBIO_BIOMETRIC_SUBTYPE)9)
#define WINBIO_ANSI_381_POS_LH_LITTLE_FINGER  ((WINBIO_BIOMETRIC_SUBTYPE)10)

#define WINBIO_ANSI_381_POS_RH_FOUR_FINGERS  ((WINBIO_BIOMETRIC_SUBTYPE)13)
#define WINBIO_ANSI_381_POS_LH_FOUR_FINGERS  ((WINBIO_BIOMETRIC_SUBTYPE)14)
#define WINBIO_ANSI_381_POS_TWO_THUMBS  ((WINBIO_BIOMETRIC_SUBTYPE)15)

#define WINBIO_ANSI_381_POS_UNKNOWN_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)20)
#define WINBIO_ANSI_381_POS_RH_FULL_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)21)
#define WINBIO_ANSI_381_POS_RH_WRITERS_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)22)
#define WINBIO_ANSI_381_POS_LH_FULL_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)23)
#define WINBIO_ANSI_381_POS_LH_WRITERS_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)24)
#define WINBIO_ANSI_381_POS_RH_LOWER_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)25)
#define WINBIO_ANSI_381_POS_RH_UPPER_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)26)
#define WINBIO_ANSI_381_POS_LH_LOWER_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)27)
#define WINBIO_ANSI_381_POS_LH_UPPER_PALM  ((WINBIO_BIOMETRIC_SUBTYPE)28)
#define WINBIO_ANSI_381_POS_RH_OTHER  ((WINBIO_BIOMETRIC_SUBTYPE)29)
#define WINBIO_ANSI_381_POS_LH_OTHER  ((WINBIO_BIOMETRIC_SUBTYPE)30)
#define WINBIO_ANSI_381_POS_RH_INTERDIGITAL  ((WINBIO_BIOMETRIC_SUBTYPE)31)
#define WINBIO_ANSI_381_POS_RH_THENAR  ((WINBIO_BIOMETRIC_SUBTYPE)32)
#define WINBIO_ANSI_381_POS_RH_HYPOTHENAR  ((WINBIO_BIOMETRIC_SUBTYPE)33)
#define WINBIO_ANSI_381_POS_LH_INTERDIGITAL  ((WINBIO_BIOMETRIC_SUBTYPE)34)
#define WINBIO_ANSI_381_POS_LH_THENAR  ((WINBIO_BIOMETRIC_SUBTYPE)35)
#define WINBIO_ANSI_381_POS_LH_HYPOTHENAR  ((WINBIO_BIOMETRIC_SUBTYPE)36)

#define WINBIO_ANSI_381_IMP_TYPE_LIVE_SCAN_PLAIN  ((UCHAR)0)
#define WINBIO_ANSI_381_IMP_TYPE_LIVE_SCAN_ROLLED  ((UCHAR)1)
#define WINBIO_ANSI_381_IMP_TYPE_NONLIVE_SCAN_PLAIN  ((UCHAR)2)
#define WINBIO_ANSI_381_IMP_TYPE_NONLIVE_SCAN_ROLLED  ((UCHAR)3)
#define WINBIO_ANSI_381_IMP_TYPE_LATENT  ((UCHAR)7)
#define WINBIO_ANSI_381_IMP_TYPE_SWIPE  ((UCHAR)8)
#define WINBIO_ANSI_381_IMP_TYPE_LIVE_SCAN_CONTACTLESS  ((UCHAR)9)

#if (NTDDI_VERSION >= NTDDI_WIN9)

#define WINBIO_FINGER_UNSPECIFIED_POS_01  ((WINBIO_BIOMETRIC_SUBTYPE)0xF5)
#define WINBIO_FINGER_UNSPECIFIED_POS_02  ((WINBIO_BIOMETRIC_SUBTYPE)0xF6)
#define WINBIO_FINGER_UNSPECIFIED_POS_03  ((WINBIO_BIOMETRIC_SUBTYPE)0xF7)
#define WINBIO_FINGER_UNSPECIFIED_POS_04  ((WINBIO_BIOMETRIC_SUBTYPE)0xF8)
#define WINBIO_FINGER_UNSPECIFIED_POS_05  ((WINBIO_BIOMETRIC_SUBTYPE)0xF9)
#define WINBIO_FINGER_UNSPECIFIED_POS_06  ((WINBIO_BIOMETRIC_SUBTYPE)0xFA)
#define WINBIO_FINGER_UNSPECIFIED_POS_07  ((WINBIO_BIOMETRIC_SUBTYPE)0xFB)
#define WINBIO_FINGER_UNSPECIFIED_POS_08  ((WINBIO_BIOMETRIC_SUBTYPE)0xFC)
#define WINBIO_FINGER_UNSPECIFIED_POS_09  ((WINBIO_BIOMETRIC_SUBTYPE)0xFD)
#define WINBIO_FINGER_UNSPECIFIED_POS_10  ((WINBIO_BIOMETRIC_SUBTYPE)0xFE)

#endif /* NTDDI_VERSION >= NTDDI_WIN9 */

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

#define WINBIO_ANSI_385_FACE_TYPE_UNKNOWN  ((WINBIO_BIOMETRIC_SUBTYPE)0)
#define WINBIO_ANSI_385_FACE_FRONTAL_FULL  ((WINBIO_BIOMETRIC_SUBTYPE)1)
#define WINBIO_ANSI_385_FACE_FRONTAL_TOKEN  ((WINBIO_BIOMETRIC_SUBTYPE)2)

#define WINBIO_IRIS_TYPE_UNKNOWN  ((WINBIO_BIOMETRIC_SUBTYPE)0)
#define WINBIO_IRIS_LEFT_EYE  ((WINBIO_BIOMETRIC_SUBTYPE)0xF5)
#define WINBIO_IRIS_RIGHT_EYE  ((WINBIO_BIOMETRIC_SUBTYPE)0xF6)
#define WINBIO_IRIS_UNSPECIFIED_POS_01  ((WINBIO_BIOMETRIC_SUBTYPE)0xF7)
#define WINBIO_IRIS_UNSPECIFIED_POS_02  ((WINBIO_BIOMETRIC_SUBTYPE)0xF8)
#define WINBIO_IRIS_BOTH_EYES  ((WINBIO_BIOMETRIC_SUBTYPE)0xF9)
#define WINBIO_IRIS_EITHER_EYE  ((WINBIO_BIOMETRIC_SUBTYPE)0xFA)

#define WINBIO_VOICE_TYPE_UNKNOWN  ((WINBIO_BIOMETRIC_SUBTYPE)0)

#define WINBIO_VOICE_MIN_UTTERANCE  ((WINBIO_BIOMETRIC_SUBTYPE)1)
#define WINBIO_VOICE_MAX_UTTERANCE  ((WINBIO_BIOMETRIC_SUBTYPE)32)

#endif /* NTDDI_VERSION >= NTDDI_WINTHRESHOLD */

typedef ULONG WINBIO_POOL_TYPE, *PWINBIO_POOL_TYPE;

#define WINBIO_POOL_UNKNOWN  ((WINBIO_POOL_TYPE)0)
#define WINBIO_POOL_SYSTEM  ((WINBIO_POOL_TYPE)1)
#define WINBIO_POOL_PRIVATE  ((WINBIO_POOL_TYPE)2)
#define WINBIO_POOL_UNASSIGNED  ((WINBIO_POOL_TYPE)3)

#define BIO_UNIT_RAW  ((USHORT)0x0001)
#define BIO_UNIT_MAINTENANCE  ((USHORT)0x0002)
#define BIO_UNIT_OPEN_SESSION  ((USHORT)0x0004)
#define BIO_UNIT_EXTENDED_ACCESS  ((USHORT)0x0008)
#define BIO_UNIT_ENROLL  ((USHORT)0x0010)

#if (NTDDI_VERSION >= NTDDI_WIN9)

#define BIO_UNIT_DELETE_TEMPLATE  ((USHORT)0x0020)
#define BIO_UNIT_CONTROL_UNIT  ((USHORT)0x0040)

#endif /* NTDDI_VERSION >= NTDDI_WIN9 */

typedef ULONG WINBIO_SESSION_FLAGS, *PWINBIO_SESSION_FLAGS;

#define WINBIO_FLAG_DEFAULT  ((WINBIO_SESSION_FLAGS)0x00000000)
#define WINBIO_FLAG_BASIC  ((WINBIO_SESSION_FLAGS)((WINBIO_SENSOR_BASIC_MODE & 0xFFFF)<<16))
#define WINBIO_FLAG_ADVANCED  ((WINBIO_SESSION_FLAGS)((WINBIO_SENSOR_ADVANCED_MODE & 0xFFFF)<<16))
#define WINBIO_FLAG_RAW  ((WINBIO_SESSION_FLAGS)BIO_UNIT_RAW)
#define WINBIO_FLAG_MAINTENANCE  ((WINBIO_SESSION_FLAGS)BIO_UNIT_MAINTENANCE)

#define WINBIO_DB_DEFAULT  ((GUID *)1)
#define WINBIO_DB_BOOTSTRAP  ((GUID *)2)
#define WINBIO_DB_ONCHIP  ((GUID *)3)

typedef ULONG WINBIO_COMPONENT, *PWINBIO_COMPONENT;

#define WINBIO_COMPONENT_SENSOR  ((WINBIO_COMPONENT)1)
#define WINBIO_COMPONENT_ENGINE  ((WINBIO_COMPONENT)2)
#define WINBIO_COMPONENT_STORAGE  ((WINBIO_COMPONENT)3)

typedef ULONG WINBIO_EVENT_TYPE, *PWINBIO_EVENT_TYPE;

#define WINBIO_EVENT_ERROR  ((WINBIO_EVENT_TYPE)0xFFFFFFFF)

#define WINBIO_EVENT_FP_UNCLAIMED  ((WINBIO_EVENT_TYPE)0x00000001)
#define WINBIO_EVENT_FP_UNCLAIMED_IDENTIFY  ((WINBIO_EVENT_TYPE)0x00000002)

typedef struct _WINBIO_EVENT {
    WINBIO_EVENT_TYPE Type;
    union {
        struct {
            WINBIO_UNIT_ID UnitId;
            WINBIO_REJECT_DETAIL RejectDetail;
        } Unclaimed;
        struct {
            WINBIO_UNIT_ID UnitId;
            WINBIO_IDENTITY Identity;
            WINBIO_BIOMETRIC_SUBTYPE SubFactor;
            WINBIO_REJECT_DETAIL RejectDetail;
        } UnclaimedIdentify;
        struct {
            HRESULT ErrorCode;
        } Error;
    } Parameters;
} WINBIO_EVENT, *PWINBIO_EVENT;

#if (NTDDI_VERSION >= NTDDI_WIN9)
typedef ULONG64 WINBIO_PROTECTION_TICKET, *PWINBIO_PROTECTION_TICKET;
#endif /* NTDDI_VERSION >= NTDDI_WIN9 */

#define WINBIO_OPAQUE_ENGINE_DATA_ITEM_COUNT  ((ULONG)72)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

typedef ULONG WINBIO_PRESENCE_CHANGE, *PWINBIO_PRESENCE_CHANGE;

#define WINBIO_PRESENCE_CHANGE_TYPE_UNKNOWN  ((WINBIO_PRESENCE_CHANGE)0)
#define WINBIO_PRESENCE_CHANGE_TYPE_UPDATE_ALL  ((WINBIO_PRESENCE_CHANGE)1)
#define WINBIO_PRESENCE_CHANGE_TYPE_ARRIVE  ((WINBIO_PRESENCE_CHANGE)2)
#define WINBIO_PRESENCE_CHANGE_TYPE_RECOGNIZE  ((WINBIO_PRESENCE_CHANGE)3)
#define WINBIO_PRESENCE_CHANGE_TYPE_DEPART  ((WINBIO_PRESENCE_CHANGE)4)
#define WINBIO_PRESENCE_CHANGE_TYPE_TRACK  ((WINBIO_PRESENCE_CHANGE)5)

typedef union _WINBIO_PRESENCE_PROPERTIES {
    struct {
        RECT BoundingBox;
        LONG Distance;
        struct {
            WINBIO_UUID AdapterId;
            ULONG Data[WINBIO_OPAQUE_ENGINE_DATA_ITEM_COUNT];
        } OpaqueEngineData;
    } FacialFeatures;
    struct {
        RECT EyeBoundingBox_1;
        RECT EyeBoundingBox_2;
        POINT PupilCenter_1;
        POINT PupilCenter_2;
        LONG Distance;
    } Iris;
} WINBIO_PRESENCE_PROPERTIES, *PWINBIO_PRESENCE_PROPERTIES;

typedef struct _WINBIO_PRESENCE {
    WINBIO_BIOMETRIC_TYPE Factor;
    WINBIO_BIOMETRIC_SUBTYPE SubFactor;
    HRESULT Status;
    WINBIO_REJECT_DETAIL RejectDetail;
    WINBIO_IDENTITY Identity;
    ULONGLONG TrackingId;
    WINBIO_PROTECTION_TICKET Ticket;
    WINBIO_PRESENCE_PROPERTIES Properties;
    struct {
        ULONG Size;
        UCHAR Data[32];
    } Authorization;
} WINBIO_PRESENCE, *PWINBIO_PRESENCE;

#endif /* NTDDI_VERSION >= NTDDI_WINTHRESHOLD */

typedef struct _WINBIO_BSP_SCHEMA {
    WINBIO_BIOMETRIC_TYPE BiometricFactor;
    WINBIO_UUID BspId;
    WINBIO_STRING Description;
    WINBIO_STRING Vendor;
    WINBIO_VERSION Version;
} WINBIO_BSP_SCHEMA, *PWINBIO_BSP_SCHEMA;

typedef struct _WINBIO_UNIT_SCHEMA {
    WINBIO_UNIT_ID UnitId;
    WINBIO_POOL_TYPE PoolType;
    WINBIO_BIOMETRIC_TYPE BiometricFactor;
    WINBIO_BIOMETRIC_SENSOR_SUBTYPE SensorSubType;
    WINBIO_CAPABILITIES Capabilities;
    WINBIO_STRING DeviceInstanceId;
    WINBIO_STRING Description;
    WINBIO_STRING Manufacturer;
    WINBIO_STRING Model;
    WINBIO_STRING SerialNumber;
    WINBIO_VERSION FirmwareVersion;
} WINBIO_UNIT_SCHEMA, *PWINBIO_UNIT_SCHEMA;

#define WINBIO_DATABASE_TYPE_MASK  ((ULONG)0x0000FFFF)
#define WINBIO_DATABASE_TYPE_FILE  ((ULONG)0x00000001)
#define WINBIO_DATABASE_TYPE_DBMS  ((ULONG)0x00000002)
#define WINBIO_DATABASE_TYPE_ONCHIP  ((ULONG)0x00000003)
#define WINBIO_DATABASE_TYPE_SMARTCARD  ((ULONG)0x00000004)

#define WINBIO_DATABASE_FLAG_MASK  ((ULONG)0xFFFF0000)
#define WINBIO_DATABASE_FLAG_REMOVABLE  ((ULONG)0x00010000)
#define WINBIO_DATABASE_FLAG_REMOTE  ((ULONG)0x00020000)

typedef struct _WINBIO_STORAGE_SCHEMA {
    WINBIO_BIOMETRIC_TYPE BiometricFactor;
    WINBIO_UUID DatabaseId;
    WINBIO_UUID DataFormat;
    ULONG Attributes;
    WINBIO_STRING FilePath;
    WINBIO_STRING ConnectionString;
} WINBIO_STORAGE_SCHEMA, *PWINBIO_STORAGE_SCHEMA;

typedef ULONG WINBIO_FRAMEWORK_CHANGE_TYPE, *PWINBIO_FRAMEWORK_CHANGE_TYPE;

#define WINBIO_FRAMEWORK_CHANGE_UNIT  ((WINBIO_FRAMEWORK_CHANGE_TYPE)0x00000001)

#define WINBIO_MAX_SAMPLE_BUFFER_SIZE ((ULONG)0x7FFFFFFF)

typedef ULONG WINBIO_OPERATION_TYPE, *PWINBIO_OPERATION_TYPE;

#define WINBIO_OPERATION_NONE  ((WINBIO_OPERATION_TYPE)0)
#define WINBIO_OPERATION_OPEN  ((WINBIO_OPERATION_TYPE)1)
#define WINBIO_OPERATION_CLOSE  ((WINBIO_OPERATION_TYPE)2)
#define WINBIO_OPERATION_VERIFY  ((WINBIO_OPERATION_TYPE)3)
#define WINBIO_OPERATION_IDENTIFY  ((WINBIO_OPERATION_TYPE)4)
#define WINBIO_OPERATION_LOCATE_SENSOR  ((WINBIO_OPERATION_TYPE)5)
#define WINBIO_OPERATION_ENROLL_BEGIN  ((WINBIO_OPERATION_TYPE)6)
#define WINBIO_OPERATION_ENROLL_CAPTURE  ((WINBIO_OPERATION_TYPE)7)
#define WINBIO_OPERATION_ENROLL_COMMIT  ((WINBIO_OPERATION_TYPE)8)
#define WINBIO_OPERATION_ENROLL_DISCARD  ((WINBIO_OPERATION_TYPE)9)
#define WINBIO_OPERATION_ENUM_ENROLLMENTS  ((WINBIO_OPERATION_TYPE)10)
#define WINBIO_OPERATION_DELETE_TEMPLATE  ((WINBIO_OPERATION_TYPE)11)
#define WINBIO_OPERATION_CAPTURE_SAMPLE  ((WINBIO_OPERATION_TYPE)12)
#define WINBIO_OPERATION_GET_PROPERTY  ((WINBIO_OPERATION_TYPE)13)
#define WINBIO_OPERATION_SET_PROPERTY  ((WINBIO_OPERATION_TYPE)14)
#define WINBIO_OPERATION_GET_EVENT  ((WINBIO_OPERATION_TYPE)15)
#define WINBIO_OPERATION_LOCK_UNIT  ((WINBIO_OPERATION_TYPE)16)
#define WINBIO_OPERATION_UNLOCK_UNIT  ((WINBIO_OPERATION_TYPE)17)
#define WINBIO_OPERATION_CONTROL_UNIT  ((WINBIO_OPERATION_TYPE)18)
#define WINBIO_OPERATION_CONTROL_UNIT_PRIVILEGED  ((WINBIO_OPERATION_TYPE)19)

#define WINBIO_OPERATION_OPEN_FRAMEWORK  ((WINBIO_OPERATION_TYPE)20)
#define WINBIO_OPERATION_CLOSE_FRAMEWORK  ((WINBIO_OPERATION_TYPE)21)
#define WINBIO_OPERATION_ENUM_SERVICE_PROVIDERS  ((WINBIO_OPERATION_TYPE)22)
#define WINBIO_OPERATION_ENUM_BIOMETRIC_UNITS  ((WINBIO_OPERATION_TYPE)23)
#define WINBIO_OPERATION_ENUM_DATABASES  ((WINBIO_OPERATION_TYPE)24)
#define WINBIO_OPERATION_UNIT_ARRIVAL  ((WINBIO_OPERATION_TYPE)25)
#define WINBIO_OPERATION_UNIT_REMOVAL  ((WINBIO_OPERATION_TYPE)26)

typedef ULONG32 WINBIO_PROPERTY_TYPE, *PWINBIO_PROPERTY_TYPE;

#define WINBIO_PROPERTY_TYPE_SESSION  ((WINBIO_PROPERTY_TYPE)1)
#define WINBIO_PROPERTY_TYPE_UNIT  ((WINBIO_PROPERTY_TYPE)2)
#define WINBIO_PROPERTY_TYPE_TEMPLATE  ((WINBIO_PROPERTY_TYPE)3)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

#define WINBIO_PROPERTY_TYPE_ACCOUNT  ((WINBIO_PROPERTY_TYPE)4)

#define WINBIO_MAX_SET_PROPERTY_BUFFER_SIZE ((ULONG)0x1000)

#endif /* NTDDI_VERSION >= NTDDI_WINTHRESHOLD */

typedef ULONG32 WINBIO_PROPERTY_ID, *PWINBIO_PROPERTY_ID;

#define WINBIO_PROPERTY_SAMPLE_HINT  ((WINBIO_PROPERTY_ID)1)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

#define WINBIO_PROPERTY_EXTENDED_SENSOR_INFO  ((WINBIO_PROPERTY_ID)2)

typedef ULONG WINBIO_ORIENTATION, *PWINBIO_ORIENTATION;

#define WINBIO_ORIENTATION_UNSPECIFIED  ((WINBIO_ORIENTATION)0)
#define WINBIO_ORIENTATION_LANDSCAPE  ((WINBIO_ORIENTATION)1)
#define WINBIO_ORIENTATION_PORTRAIT  ((WINBIO_ORIENTATION)2)
#define WINBIO_ORIENTATION_ANY  ((WINBIO_ORIENTATION)3)

typedef struct _WINBIO_EXTENDED_SENSOR_INFO {
    WINBIO_CAPABILITIES GenericSensorCapabilities;
    WINBIO_BIOMETRIC_TYPE Factor;
    union {
        ULONG32 Null;
        struct {
            RECT FrameSize;
            POINT FrameOffset;
            WINBIO_ORIENTATION MandatoryOrientation;
            struct {
                WCHAR ColorSensorId[260];
                WCHAR InfraredSensorId[260];
                UINT32 InfraredSensorRotationAngle;
            } HardwareInfo;
        } FacialFeatures;
        struct {
            ULONG32 Reserved;
        } Fingerprint;
        struct {
            RECT FrameSize;
            POINT FrameOffset;
            WINBIO_ORIENTATION MandatoryOrientation;
        } Iris;
        struct {
            ULONG32 Reserved;
        } Voice;
    } Specific;
} WINBIO_EXTENDED_SENSOR_INFO, *PWINBIO_EXTENDED_SENSOR_INFO;

#endif /* NTDDI_VERSION >= NTDDI_WINTHRESHOLD */

#define WINBIO_PROPERTY_EXTENDED_ENGINE_INFO  ((WINBIO_PROPERTY_ID)3)

#define WINBIO_ENG_CAP_ITERATIVE_IMPROVEMENT  ((WINBIO_CAPABILITIES)0x00000001)
#define WINBIO_ENG_CAP_SPOOF_DETECTION  ((WINBIO_CAPABILITIES)0x00000002)

typedef struct _WINBIO_EXTENDED_ENGINE_INFO {
    WINBIO_CAPABILITIES GenericEngineCapabilities;
    WINBIO_BIOMETRIC_TYPE Factor;
    union {
        ULONG32 Null;
        struct {
            WINBIO_CAPABILITIES Capabilities;
            struct {
                ULONG32 Null;
            } EnrollmentRequirements;
        } FacialFeatures;
        struct {
            WINBIO_CAPABILITIES Capabilities;
            struct {
                ULONG GeneralSamples;
                ULONG Center;
                ULONG TopEdge;
                ULONG BottomEdge;
                ULONG LeftEdge;
                ULONG RightEdge;
            } EnrollmentRequirements;
        } Fingerprint;
        struct {
            WINBIO_CAPABILITIES Capabilities;
            struct {
                ULONG32 Null;
            } EnrollmentRequirements;
        } Iris;
        struct {
            WINBIO_CAPABILITIES Capabilities;
            struct {
                ULONG32 Null;
            } EnrollmentRequirements;
        } Voice;
    } Specific;
} WINBIO_EXTENDED_ENGINE_INFO, *PWINBIO_EXTENDED_ENGINE_INFO;

#define WINBIO_PROPERTY_EXTENDED_STORAGE_INFO  ((WINBIO_PROPERTY_ID)4)

typedef struct _WINBIO_EXTENDED_STORAGE_INFO {
    WINBIO_CAPABILITIES GenericStorageCapabilities;
    WINBIO_BIOMETRIC_TYPE Factor;
    union {
        ULONG32 Null;
        struct {
            WINBIO_CAPABILITIES Capabilities;
        } FacialFeatures;
        struct {
            WINBIO_CAPABILITIES Capabilities;
        } Fingerprint;
        struct {
            WINBIO_CAPABILITIES Capabilities;
        } Iris;
        struct {
            WINBIO_CAPABILITIES Capabilities;
        } Voice;
    } Specific;
} WINBIO_EXTENDED_STORAGE_INFO, *PWINBIO_EXTENDED_STORAGE_INFO;

#define WINBIO_PROPERTY_EXTENDED_ENROLLMENT_STATUS  ((WINBIO_PROPERTY_ID)5)

typedef struct _WINBIO_EXTENDED_ENROLLMENT_STATUS {
    HRESULT TemplateStatus;
    WINBIO_REJECT_DETAIL RejectDetail;
    ULONG PercentComplete;
    WINBIO_BIOMETRIC_TYPE Factor;
    WINBIO_BIOMETRIC_SUBTYPE SubFactor;
    union {
        ULONG32 Null;
        struct {
            RECT BoundingBox;
            LONG Distance;
            struct {
                WINBIO_UUID AdapterId;
                ULONG Data[WINBIO_OPAQUE_ENGINE_DATA_ITEM_COUNT];
            } OpaqueEngineData;
        } FacialFeatures;
        struct {
            ULONG GeneralSamples;
            ULONG Center;
            ULONG TopEdge;
            ULONG BottomEdge;
            ULONG LeftEdge;
            ULONG RightEdge;
        } Fingerprint;
        struct {
            RECT EyeBoundingBox_1;
            RECT EyeBoundingBox_2;
            POINT PupilCenter_1;
            POINT PupilCenter_2;
            LONG Distance;
        } Iris;
        struct {
            ULONG32 Reserved;
        } Voice;
    } Specific;
} WINBIO_EXTENDED_ENROLLMENT_STATUS, *PWINBIO_EXTENDED_ENROLLMENT_STATUS;

#define WINBIO_PROPERTY_EXTENDED_UNIT_STATUS  ((WINBIO_PROPERTY_ID)6)

typedef struct _WINBIO_EXTENDED_UNIT_STATUS {
    WINBIO_SENSOR_STATUS Availability;
} WINBIO_EXTENDED_UNIT_STATUS, *PWINBIO_EXTENDED_UNIT_STATUS;

#define WINBIO_PROPERTY_ANTI_SPOOF_POLICY  ((WINBIO_PROPERTY_ID)1)

typedef enum _WINBIO_ANTI_SPOOF_POLICY_ACTION {
    WINBIO_ANTI_SPOOF_DISABLE = 0x00000000,
    WINBIO_ANTI_SPOOF_ENABLE = 0x00000001,
    WINBIO_ANTI_SPOOF_REMOVE = 0x00000002,
} WINBIO_ANTI_SPOOF_POLICY_ACTION, *PWINBIO_ANTI_SPOOF_POLICY_ACTION;

typedef enum _WINBIO_POLICY_SOURCE {
    WINBIO_POLICY_UNKNOWN = 0x00000000,
    WINBIO_POLICY_DEFAULT = 0x00000001,
    WINBIO_POLICY_LOCAL = 0x00000002,
    WINBIO_POLICY_ADMIN = 0x00000003,
} WINBIO_POLICY_SOURCE, *PWINBIO_POLICY_SOURCE;

typedef struct _WINBIO_ANTI_SPOOF_POLICY {
    WINBIO_ANTI_SPOOF_POLICY_ACTION Action;
    WINBIO_POLICY_SOURCE Source;
} WINBIO_ANTI_SPOOF_POLICY, *PWINBIO_ANTI_SPOOF_POLICY;

#if (NTDDI_VERSION >= NTDDI_WIN9)

#define WINBIO_OPERATION_IDENTIFY_AND_RELEASE_TICKET  ((WINBIO_OPERATION_TYPE)27)
#define WINBIO_OPERATION_VERIFY_AND_RELEASE_TICKET  ((WINBIO_OPERATION_TYPE)28)

#endif /* NTDDI_VERSION >= NTDDI_WIN9 */

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

#define WINBIO_OPERATION_MONITOR_PRESENCE  ((WINBIO_OPERATION_TYPE)29)
#define WINBIO_OPERATION_ENROLL_SELECT  ((WINBIO_OPERATION_TYPE)30)

#endif /* NTDDI_VERSION >= NTDDI_WINTHRESHOLD */

typedef enum _WINBIO_CREDENTIAL_TYPE {
    WINBIO_CREDENTIAL_PASSWORD = 0x00000001,
    WINBIO_CREDENTIAL_ALL = 0xffffffff,
} WINBIO_CREDENTIAL_TYPE;

typedef enum _WINBIO_CREDENTIAL_FORMAT {
    WINBIO_PASSWORD_GENERIC = 0x00000001,
    WINBIO_PASSWORD_PACKED = 0x00000002,
    WINBIO_PASSWORD_PROTECTED = 0x00000003,
} WINBIO_CREDENTIAL_FORMAT;

typedef enum _WINBIO_CREDENTIAL_STATE {
    WINBIO_CREDENTIAL_NOT_SET = 0x00000001,
    WINBIO_CREDENTIAL_SET = 0x00000002,
} WINBIO_CREDENTIAL_STATE, *PWINBIO_CREDENTIAL_STATE;

typedef ULONG32 WINBIO_SETTING_SOURCE_TYPE, *PWINBIO_SETTING_SOURCE_TYPE;

#define WINBIO_SETTING_SOURCE_INVALID  ((WINBIO_SETTING_SOURCE_TYPE)0)
#define WINBIO_SETTING_SOURCE_DEFAULT  ((WINBIO_SETTING_SOURCE_TYPE)1)
#define WINBIO_SETTING_SOURCE_POLICY  ((WINBIO_SETTING_SOURCE_TYPE)2)
#define WINBIO_SETTING_SOURCE_LOCAL  ((WINBIO_SETTING_SOURCE_TYPE)3)

typedef struct _WINBIO_EXTENDED_ENROLLMENT_PARAMETERS {
    SIZE_T Size;
    WINBIO_BIOMETRIC_SUBTYPE SubFactor;
} WINBIO_EXTENDED_ENROLLMENT_PARAMETERS, *PWINBIO_EXTENDED_ENROLLMENT_PARAMETERS;

typedef struct _WINBIO_ACCOUNT_POLICY {
    WINBIO_IDENTITY Identity;
    WINBIO_ANTI_SPOOF_POLICY_ACTION AntiSpoofBehavior;
} WINBIO_ACCOUNT_POLICY, *PWINBIO_ACCOUNT_POLICY;

#endif /* NTDDI_VERSION >= NTDDI_WIN7 */

#endif /* _WINBIO_TYPES_H */

