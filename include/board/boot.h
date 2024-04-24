#ifndef __INCLUDE_BOARD_BOOT_H__
#define __INCLUDE_BOARD_BOOT_H__
#include <compiler.h>
#include <types.h>

#define HEADER_SIGNATURE_LEN    16

#define HEADERS_SECTION         ".rominfo"
#define INFO_SECTION            ".headers"

/* only for the rom header  */
#define ROM_HEADER_ALIGNMENT    256

/* every other kind of header should be on 16 */
#define HEADER_ALIGNMENT        16

#define __rom_header    __align(ROM_HEADER_ALIGNMENT) __section(HEADERS_SECTION)
#define __header        __align(HEADER_ALIGNMENT) __section(INFO_SECTION)

#define ROM_HEADER_SIGNATURE    "\x7f-ROM_IMG-\xf7"
struct rom_header {
        u8     signature[HEADER_SIGNATURE_LEN];
        addr_t boot_info_ptr;
        addr_t version_info_ptr;
        addr_t product_info_ptr;
        addr_t dfu_info_ptr;
        addr_t parameters_info_ptr;
        addr_t reserved;
};

#define BOOT_INFO_SIGNATURE     "\x7f-BOOTINFO-\xf7"
struct boot_info {
        u8     signature[HEADER_SIGNATURE_LEN];
        addr_t load_addr;
        addr_t initial_sp_addr;
        addr_t entry_point_addr;
        u32    rom_size;
};

extern const struct boot_info boot_info;

#endif /* __INCLUDE_BOARD_BOOT_H__ */

