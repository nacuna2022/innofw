#!/usr/bin/python
import subprocess

def update_config_header(v):

    verlist = v.split(".")
    major = verlist[0][1:]
    minor = verlist[1]
    
    tmplist = verlist[2].split("-")
    patch = tmplist[0]
    try:
        pre_rel = tmplist[1]
    except:
        pre_rel = ""

    with open("include/config_version.h", "w") as version_hdr:
        version_hdr.write("#ifndef __INCLUDE_CONFIG_VERSION_H__\n")
        version_hdr.write("#define __INCLUDE_CONFIG_VERSION_H___\n")
        version_hdr.write("\n")
        version_hdr.write("/* This is is auto-generated! Do not edit! */\n")
        version_hdr.write("\n")
        version_hdr.write(f'#define CONFIG_VERSION_STRING\t"{v}"\n')
        version_hdr.write(f"#define CONFIG_VERSION_MAJOR\t{major}\n")
        version_hdr.write(f"#define CONFIG_VERSION_MINOR\t{minor}\n")
        version_hdr.write(f"#define CONFIG_VERSION_PATCH\t{patch}\n")
        if (pre_rel != ""):
            version_hdr.write(f'#define CONFIG_VERSION_PRE_REL\t"{pre_rel}"\n')
        version_hdr.write("\n")
        version_hdr.write("#endif /* __INCLUDE_CONFIG_VERSION_H__ */\n\n")



def test_and_replace_version(version_string, version_git):
    # compare them with the assumption that if they are not the same
    # then the version taken from the git repo is the more updated
    if (version_string != version_git):
        with open(".version", "w") as dot_version:
            dot_version.write(version_git)
            update_config_header(version_git)



def process_version_string(version_git):
    try:
        dot_version = open(".version", "r")
        version_string = dot_version.readline().rstrip()
        dot_version.close()
    except:
        version_string = ""

    test_and_replace_version(version_string, version_git)



if __name__ == "__main__":
    ret = subprocess.run(["git", "describe", "--abbrev=0","--match", "v*.*.*"], capture_output=True)
    if ret.returncode != 0:
        process_version_string("v0.0.0")
    else:
        version_git = ret.stdout.decode().rstrip()
        process_version_string(version_git)

