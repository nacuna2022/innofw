#include <board/version.h>
#include <bug.h>
#include <config.h>
#include <config_version.h>

struct version_info version_info = {
        .signature = VERSION_INFO_SIGNATURE,
        .major = (u8)CONFIG_VERSION_MAJOR,
        .minor = (u8)CONFIG_VERSION_MINOR,
        .patch_level = (u8)CONFIG_VERSION_PATCH,
        .build_date = __DATE__,
};

static void version_ct_check(void)
{
        CT_ASSERT(offsetof(struct version_info, signature) == 0);
        CT_ASSERT(offsetof(struct version_info, major) == 16);
        CT_ASSERT(offsetof(struct version_info, minor) == 17);
        CT_ASSERT(offsetof(struct version_info, patch_level) == 18);
        CT_ASSERT(offsetof(struct version_info, pre_rel) == 19);
        CT_ASSERT(offsetof(struct version_info, build_date) == 51);
        return;
}

const char *get_version_string(void)
{
        return CONFIG_VERSION_STRING;
}

void get_version(int *major, int *minor, int *patch_level)
{
        if (major)
                *major = CONFIG_VERSION_MAJOR;
        if (minor)
                *minor = CONFIG_VERSION_MINOR;
        if (patch_level)
                *patch_level = CONFIG_VERSION_PATCH;
        return;
}

