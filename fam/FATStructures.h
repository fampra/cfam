/*
 * Copyright (c) 2024, Allexander <allexander.linux@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Types.h> // TODO : Create File.

namespace Kernel {

    struct [[gnu::packed]] DOS3BIOSParameterBlock {
        u8 boot_jump[3];
        char oem_identifier[8];
        u16 bytes_per_sector; // Offset 0x0B -- beginning of DOS 3.31 BPB.
        u8 sectors_per_cluster;
        u16 reserved_sector_count;
        u8 fat_count;
        u16 root_directory_entry_count;
        u16 sector_count_16bit;
        u8 media_descriptor_type;
        u16 sectors_per_fat_16bit;
        u16 sectors_per_track;
        u16 head_count;
        u32 hidden_sector_count;
        u32 sector_count_32bit; // 0x020 -- end of DOS 3.31 BPB.
    };
    // 11 is the boot jump/OEM identifier prefix prior to the official BPB.
    static_assert(AssertSize<DOS3BIOSParameterBlock, 11 + 25>());

    struct [[gnu::packed]] DOS4BIOSParameterBlock {
        // Begins at sector offset 0x024.
        u8 drive_number; // 0x024
        u8 flags;
        u8 signature;
        u32 volume_id;
        char volume_label_string[11];
        char file_system_type[8];
    };
    static_assert(AssertSize<DOS4BIOSParameterBlock, 26>());

    struct [[gnu::packed]] DOS7BIOSParameterBlock {
        // Begins at sector offset 0x024.
        u32 sectors_per_fat_32bit; // 0x024
        u16 flags;
        u16 fat_version; // Expected value 0x2b2a.
        u32 root_directory_cluster;
        u16 fs_info_sector;
        u16 backup_boot_sector;
        u8 unused3[12];
        u8 drive_number;
        u8 unused4;
        u8 signature;
        u32 volume_id;
        char volume_label_string[11];
        char file_system_type[8];
    };
    static_assert(AssertSize<DOS7BIOSParameterBlock, 54>());

    struct [[gnu::packed]] FAT32FSInfo {
        u32 lead_signature;
        u8 unused1[480];
        u32 struct_signature;
        u32 last_known_free_cluster_count;
        u32 next_free_cluster_hint;
        u8 unused2[12];
        u32 trailing_signature;
    };
    static_assert(AssertSize<FAT32FSInfo, 512>());

}
