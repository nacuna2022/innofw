#include <config.h>
#include <board/boot.h>
#include <bug.h>

/* product info and dfu is define per board, so each board should define
 * them themselves in one of their board c files.
 */

extern const addr_t load_addr[];
extern const addr_t __vtor[];
extern const addr_t __SP_main[];
extern const addr_t __entry_point[];
extern const u32    __rom_size[]; 

const struct boot_info boot_info __header = {
        .signature = BOOT_INFO_SIGNATURE,
        .load_addr = (const addr_t)__vtor,
        .initial_sp_addr = (const addr_t)__SP_main,
        .entry_point_addr = (const addr_t)__entry_point,
        .rom_size = 0,
};

const struct rom_header rom_header __rom_header = {
        .signature = ROM_HEADER_SIGNATURE,
        .boot_info_ptr = (addr_t)&boot_info,
        .version_info_ptr = 0,
#ifndef CONFIG_HAVE_PRODUCT_INFO
        .product_info_ptr = 0,
#endif
#ifndef CONFIG_HAVE_DFU_INFO
        .dfu_info_ptr = 0,
#endif
#ifndef CONFIG_HAVE_PARAMETERS_INFO
        .parameters_info_ptr = 0,
#endif
};

/* this function is not really called anywhere and hopefully will be discarded.
 * this is just here to provide a place where the compiler is able to 
 * syntax check and catch compile time errors.
 */
static void rom_ct_check(void)
{
        CT_ASSERT(offsetof(struct rom_header, signature) == 0);
        CT_ASSERT(offsetof(struct rom_header, boot_info_ptr) == 16);
        CT_ASSERT(offsetof(struct rom_header, version_info_ptr) == 20);
        CT_ASSERT(offsetof(struct rom_header, product_info_ptr) == 24);
        CT_ASSERT(offsetof(struct rom_header, dfu_info_ptr) == 28);
        CT_ASSERT(offsetof(struct rom_header, parameters_info_ptr) == 32);
        CT_ASSERT(offsetof(struct rom_header, reserved) == 36);

        CT_ASSERT(offsetof(struct boot_info, signature) == 0);
        CT_ASSERT(offsetof(struct boot_info, load_addr) == 16);
        CT_ASSERT(offsetof(struct boot_info, initial_sp_addr) == 20);
        CT_ASSERT(offsetof(struct boot_info, entry_point_addr) == 24);
        CT_ASSERT(offsetof(struct boot_info, rom_size) == 28);
        
        return;
}

