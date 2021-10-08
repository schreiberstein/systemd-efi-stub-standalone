/* SPDX-License-Identifier: LGPL-2.1-or-later */
#pragma once

#include <efi.h>

#include "macro-fundamental.h"

#ifndef EFI_RNG_PROTOCOL_GUID

#define EFI_RNG_PROTOCOL_GUID                                           \
          { 0x3152bca5, 0xeade, 0x433d, {0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44} }

typedef EFI_GUID EFI_RNG_ALGORITHM;

#define EFI_RNG_ALGORITHM_SP800_90_HASH_256_GUID       \
     {0xa7af67cb, 0x603b, 0x4d42, {0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96} }

#define EFI_RNG_ALGORITHM_SP800_90_HMAC_256_GUID       \
     {0xc5149b43, 0xae85, 0x4f53, {0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7} }

#define EFI_RNG_ALGORITHM_SP800_90_CTR_256_GUID        \
     {0x44f0de6e, 0x4d8c, 0x4045, {0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e} }

#define EFI_RNG_ALGORITHM_X9_31_3DES_GUID              \
     {0x63c4785a, 0xca34, 0x4012, {0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46} }

#define EFI_RNG_ALGORITHM_X9_31_AES_GUID               \
     {0xacd03321, 0x777e, 0x4d3d, {0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9} }

#define EFI_RNG_ALGORITHM_RAW                          \
     {0xe43176d7, 0xb6e8, 0x4827, {0xb7, 0x84, 0x7f, 0xfd, 0xc4, 0xb6, 0x85, 0x61} }

INTERFACE_DECL(_EFI_RNG_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_INFO) (
  IN      struct _EFI_RNG_PROTOCOL   *This,
  IN OUT  UINTN                      *RNGAlgorithmListSize,
  OUT     EFI_RNG_ALGORITHM          *RNGAlgorithmList
);

typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_RNG) (
  IN      struct _EFI_RNG_PROTOCOL   *This,
  IN      EFI_RNG_ALGORITHM          *RNGAlgorithm,           OPTIONAL
  IN      UINTN                      RNGValueLength,
  OUT     UINT8                      *RNGValue
);

typedef struct _EFI_RNG_PROTOCOL {
          EFI_RNG_GET_INFO           GetInfo;
          EFI_RNG_GET_RNG            GetRNG;
} EFI_RNG_PROTOCOL;

#endif

#ifndef EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID \
    { 0xdd9e7534, 0x7762, 0x4698, {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa} }

#define EFI_SHIFT_STATE_VALID           0x80000000
#define EFI_RIGHT_CONTROL_PRESSED       0x00000004
#define EFI_LEFT_CONTROL_PRESSED        0x00000008
#define EFI_RIGHT_ALT_PRESSED           0x00000010
#define EFI_LEFT_ALT_PRESSED            0x00000020

struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_INPUT_RESET_EX)(
        struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        BOOLEAN ExtendedVerification
);

typedef UINT8 EFI_KEY_TOGGLE_STATE;

typedef struct {
        UINT32 KeyShiftState;
        EFI_KEY_TOGGLE_STATE KeyToggleState;
} EFI_KEY_STATE;

typedef struct {
        EFI_INPUT_KEY Key;
        EFI_KEY_STATE KeyState;
} EFI_KEY_DATA;

typedef EFI_STATUS (EFIAPI *EFI_INPUT_READ_KEY_EX)(
        struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        EFI_KEY_DATA *KeyData
);

typedef EFI_STATUS (EFIAPI *EFI_SET_STATE)(
        struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        EFI_KEY_TOGGLE_STATE *KeyToggleState
);

typedef EFI_STATUS (EFIAPI *EFI_KEY_NOTIFY_FUNCTION)(
        EFI_KEY_DATA *KeyData
);

typedef EFI_STATUS (EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY)(
        struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        EFI_KEY_DATA KeyData,
        EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
        VOID **NotifyHandle
);

typedef EFI_STATUS (EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY)(
        struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
        VOID *NotificationHandle
);

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
        EFI_INPUT_RESET_EX Reset;
        EFI_INPUT_READ_KEY_EX ReadKeyStrokeEx;
        EFI_EVENT WaitForKeyEx;
        EFI_SET_STATE SetState;
        EFI_REGISTER_KEYSTROKE_NOTIFY RegisterKeyNotify;
        EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

#endif

#ifndef EFI_IMAGE_MACHINE_RISCV64
        #define EFI_IMAGE_MACHINE_RISCV64 0x5064
#endif

#ifndef EFI_DTB_TABLE_GUID
#define EFI_DTB_TABLE_GUID \
        { 0xb1b621d5, 0xf19c, 0x41a5, {0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0} }
#define EfiDtbTableGuid ((EFI_GUID)EFI_DTB_TABLE_GUID)
#endif

#ifndef EFI_DT_FIXUP_PROTOCOL_GUID
#define EFI_DT_FIXUP_PROTOCOL_GUID \
        { 0xe617d64c, 0xfe08, 0x46da, {0xf4, 0xdc, 0xbb, 0xd5, 0x87, 0x0c, 0x73, 0x00} }
#define EfiDtFixupProtocol ((EFI_GUID)EFI_DT_FIXUP_PROTOCOL_GUID)

#define EFI_DT_FIXUP_PROTOCOL_REVISION 0x00010000

/* Add nodes and update properties */
#define EFI_DT_APPLY_FIXUPS    0x00000001
/*
 * Reserve memory according to the /reserved-memory node
 * and the memory reservation block
 */
#define EFI_DT_RESERVE_MEMORY  0x00000002

typedef struct _EFI_DT_FIXUP_PROTOCOL EFI_DT_FIXUP_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_DT_FIXUP) (
        IN EFI_DT_FIXUP_PROTOCOL *This,
        IN VOID                  *Fdt,
        IN OUT UINTN             *BufferSize,
        IN UINT32                Flags);

struct _EFI_DT_FIXUP_PROTOCOL {
        UINT64         Revision;
        EFI_DT_FIXUP   Fixup;
};

#define EFI_TCG_GUID \
        &(const EFI_GUID) { 0xf541796d, 0xa62e, 0x4954, { 0xa7, 0x75, 0x95, 0x84, 0xf6, 0x1b, 0x9c, 0xdd } }

typedef struct _TCG_VERSION {
        UINT8 Major;
        UINT8 Minor;
        UINT8 RevMajor;
        UINT8 RevMinor;
} TCG_VERSION;

typedef struct tdEFI_TCG2_VERSION {
        UINT8 Major;
        UINT8 Minor;
} EFI_TCG2_VERSION;

typedef struct _TCG_BOOT_SERVICE_CAPABILITY {
        UINT8 Size;
        struct _TCG_VERSION StructureVersion;
        struct _TCG_VERSION ProtocolSpecVersion;
        UINT8 HashAlgorithmBitmap;
        BOOLEAN TPMPresentFlag;
        BOOLEAN TPMDeactivatedFlag;
} TCG_BOOT_SERVICE_CAPABILITY;

typedef struct tdTREE_BOOT_SERVICE_CAPABILITY {
        UINT8 Size;
        EFI_TCG2_VERSION StructureVersion;
        EFI_TCG2_VERSION ProtocolVersion;
        UINT32 HashAlgorithmBitmap;
        UINT32 SupportedEventLogs;
        BOOLEAN TrEEPresentFlag;
        UINT16 MaxCommandSize;
        UINT16 MaxResponseSize;
        UINT32 ManufacturerID;
} TREE_BOOT_SERVICE_CAPABILITY;

typedef UINT32 TCG_ALGORITHM_ID;
#define TCG_ALG_SHA 0x00000004  // The SHA1 algorithm

#define SHA1_DIGEST_SIZE 20

typedef struct _TCG_DIGEST {
        UINT8 Digest[SHA1_DIGEST_SIZE];
} TCG_DIGEST;

#define EV_IPL 13

typedef struct _TCG_PCR_EVENT {
        UINT32 PCRIndex;
        UINT32 EventType;
        struct _TCG_DIGEST digest;
        UINT32 EventSize;
        UINT8 Event[1];
} TCG_PCR_EVENT;

INTERFACE_DECL(_EFI_TCG);

typedef EFI_STATUS(EFIAPI * EFI_TCG_STATUS_CHECK) (IN struct _EFI_TCG * This,
                                                   OUT struct _TCG_BOOT_SERVICE_CAPABILITY * ProtocolCapability,
                                                   OUT UINT32 * TCGFeatureFlags,
                                                   OUT EFI_PHYSICAL_ADDRESS * EventLogLocation,
                                                   OUT EFI_PHYSICAL_ADDRESS * EventLogLastEntry);

typedef EFI_STATUS(EFIAPI * EFI_TCG_HASH_ALL) (IN struct _EFI_TCG * This,
                                               IN UINT8 * HashData,
                                               IN UINT64 HashDataLen,
                                               IN TCG_ALGORITHM_ID AlgorithmId,
                                               IN OUT UINT64 * HashedDataLen, IN OUT UINT8 ** HashedDataResult);

typedef EFI_STATUS(EFIAPI * EFI_TCG_LOG_EVENT) (IN struct _EFI_TCG * This,
                                                IN struct _TCG_PCR_EVENT * TCGLogData,
                                                IN OUT UINT32 * EventNumber, IN UINT32 Flags);

typedef EFI_STATUS(EFIAPI * EFI_TCG_PASS_THROUGH_TO_TPM) (IN struct _EFI_TCG * This,
                                                          IN UINT32 TpmInputParameterBlockSize,
                                                          IN UINT8 * TpmInputParameterBlock,
                                                          IN UINT32 TpmOutputParameterBlockSize,
                                                          IN UINT8 * TpmOutputParameterBlock);

typedef EFI_STATUS(EFIAPI * EFI_TCG_HASH_LOG_EXTEND_EVENT) (IN struct _EFI_TCG * This,
                                                            IN EFI_PHYSICAL_ADDRESS HashData,
                                                            IN UINT64 HashDataLen,
                                                            IN TCG_ALGORITHM_ID AlgorithmId,
                                                            IN struct _TCG_PCR_EVENT * TCGLogData,
                                                            IN OUT UINT32 * EventNumber,
                                                            OUT EFI_PHYSICAL_ADDRESS * EventLogLastEntry);

typedef struct _EFI_TCG {
        EFI_TCG_STATUS_CHECK StatusCheck;
        EFI_TCG_HASH_ALL HashAll;
        EFI_TCG_LOG_EVENT LogEvent;
        EFI_TCG_PASS_THROUGH_TO_TPM PassThroughToTPM;
        EFI_TCG_HASH_LOG_EXTEND_EVENT HashLogExtendEvent;
} EFI_TCG;

#define EFI_TCG2_GUID \
        &(const EFI_GUID) { 0x607f766c, 0x7455, 0x42be, { 0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f } }

typedef struct tdEFI_TCG2_PROTOCOL EFI_TCG2_PROTOCOL;

typedef UINT32 EFI_TCG2_EVENT_LOG_BITMAP;
typedef UINT32 EFI_TCG2_EVENT_LOG_FORMAT;
typedef UINT32 EFI_TCG2_EVENT_ALGORITHM_BITMAP;

typedef struct tdEFI_TCG2_BOOT_SERVICE_CAPABILITY {
        UINT8 Size;
        EFI_TCG2_VERSION StructureVersion;
        EFI_TCG2_VERSION ProtocolVersion;
        EFI_TCG2_EVENT_ALGORITHM_BITMAP HashAlgorithmBitmap;
        EFI_TCG2_EVENT_LOG_BITMAP SupportedEventLogs;
        BOOLEAN TPMPresentFlag;
        UINT16 MaxCommandSize;
        UINT16 MaxResponseSize;
        UINT32 ManufacturerID;
        UINT32 NumberOfPCRBanks;
        EFI_TCG2_EVENT_ALGORITHM_BITMAP ActivePcrBanks;
} EFI_TCG2_BOOT_SERVICE_CAPABILITY;

#define EFI_TCG2_EVENT_HEADER_VERSION  1

typedef struct {
        UINT32 HeaderSize;
        UINT16 HeaderVersion;
        UINT32 PCRIndex;
        UINT32 EventType;
} _packed_ EFI_TCG2_EVENT_HEADER;

typedef struct tdEFI_TCG2_EVENT {
        UINT32 Size;
        EFI_TCG2_EVENT_HEADER Header;
        UINT8 Event[1];
} _packed_ EFI_TCG2_EVENT;

typedef EFI_STATUS(EFIAPI * EFI_TCG2_GET_CAPABILITY) (IN EFI_TCG2_PROTOCOL * This,
                                                      IN OUT EFI_TCG2_BOOT_SERVICE_CAPABILITY * ProtocolCapability);

typedef EFI_STATUS(EFIAPI * EFI_TCG2_GET_EVENT_LOG) (IN EFI_TCG2_PROTOCOL * This,
                                                     IN EFI_TCG2_EVENT_LOG_FORMAT EventLogFormat,
                                                     OUT EFI_PHYSICAL_ADDRESS * EventLogLocation,
                                                     OUT EFI_PHYSICAL_ADDRESS * EventLogLastEntry,
                                                     OUT BOOLEAN * EventLogTruncated);

typedef EFI_STATUS(EFIAPI * EFI_TCG2_HASH_LOG_EXTEND_EVENT) (IN EFI_TCG2_PROTOCOL * This,
                                                             IN UINT64 Flags,
                                                             IN EFI_PHYSICAL_ADDRESS DataToHash,
                                                             IN UINT64 DataToHashLen, IN EFI_TCG2_EVENT * EfiTcgEvent);

typedef EFI_STATUS(EFIAPI * EFI_TCG2_SUBMIT_COMMAND) (IN EFI_TCG2_PROTOCOL * This,
                                                      IN UINT32 InputParameterBlockSize,
                                                      IN UINT8 * InputParameterBlock,
                                                      IN UINT32 OutputParameterBlockSize, IN UINT8 * OutputParameterBlock);

typedef EFI_STATUS(EFIAPI * EFI_TCG2_GET_ACTIVE_PCR_BANKS) (IN EFI_TCG2_PROTOCOL * This, OUT UINT32 * ActivePcrBanks);

typedef EFI_STATUS(EFIAPI * EFI_TCG2_SET_ACTIVE_PCR_BANKS) (IN EFI_TCG2_PROTOCOL * This, IN UINT32 ActivePcrBanks);

typedef EFI_STATUS(EFIAPI * EFI_TCG2_GET_RESULT_OF_SET_ACTIVE_PCR_BANKS) (IN EFI_TCG2_PROTOCOL * This,
                                                                          OUT UINT32 * OperationPresent, OUT UINT32 * Response);

typedef struct tdEFI_TCG2_PROTOCOL {
        EFI_TCG2_GET_CAPABILITY GetCapability;
        EFI_TCG2_GET_EVENT_LOG GetEventLog;
        EFI_TCG2_HASH_LOG_EXTEND_EVENT HashLogExtendEvent;
        EFI_TCG2_SUBMIT_COMMAND SubmitCommand;
        EFI_TCG2_GET_ACTIVE_PCR_BANKS GetActivePcrBanks;
        EFI_TCG2_SET_ACTIVE_PCR_BANKS SetActivePcrBanks;
        EFI_TCG2_GET_RESULT_OF_SET_ACTIVE_PCR_BANKS GetResultOfSetActivePcrBanks;
} EFI_TCG2;

#endif
