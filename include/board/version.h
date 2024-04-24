#ifndef __INCLUDE_BOARD_VERSION_H__
#define __INCLUDE_BOARD_VERSION_H__
#include <board/boot.h>

#define PREREL_LENGTH      32
#define BUILD_DATE_LENGTH  16

#define VERSION_INFO_SIGNATURE  "\x7f-VERINFO-\xf7"
struct version_info {
        u8      signature[HEADER_SIGNATURE_LEN];
        u8      major;
        u8      minor;
        u8      patch_level;
        u8      pre_rel[PREREL_LENGTH];
        u8      build_date[BUILD_DATE_LENGTH];
};

const char *get_version_string(void);
void get_version(int *major, int *minor, int *patch_level);

#endif /* __INCLUDE_BOARD_VERSION_H__ */

