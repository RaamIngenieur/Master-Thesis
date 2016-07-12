// -----------------------------------------------------------------------------
// Copyright (c) 2010 Think Silicon Ltd
// Think Silicon Ltd Confidential Proprietary
// -----------------------------------------------------------------------------
//     All Rights reserved - Unpublished -rights reserved under
//         the Copyright laws of the European Union
//
//  This file includes the Confidential information of Think Silicon Ltd
//  The receiver of this Confidential Information shall not disclose
//  it to any third party and shall protect its confidentiality by
//  using the same degree of care, but not less than a reasonable
//  degree of care, as the receiver uses to protect receiver's own
//  Confidential Information. The entire notice must be reproduced on all
//  authorised copies and copies may only be made to the extent permitted
//  by a licensing agreement from Think Silicon Ltd.
//
//  The software is provided 'as is', without warranty of any kind, express or
//  implied, including but not limited to the warranties of merchantability,
//  fitness for a particular purpose and noninfringement. In no event shall
//  Think Silicon Ltd be liable for any claim, damages or other liability, whether
//  in an action of contract, tort or otherwise, arising from, out of or in
//  connection with the software or the use or other dealings in the software.
//
//
//                    Think Silicon Ltd
//                    http://www.think-silicon.com
//                    Patras Science Park
//                    Rion Achaias 26504
//                    Greece
// -----------------------------------------------------------------------------
// FILE NAME  : NemaUtils.h
// KEYWORDS   :
// PURPOSE    : Host-Nema Communication
// DEPARTMENT :
// AUTHOR     :
// GENERATION :
// RECEIVER   :
// NOTES      :

#ifndef __NEMA_UTILS_H__
#define __NEMA_UTILS_H__

#include <stdint.h>
//#include "../../NemaSpec/include/Nema_cmdlist.h"

#ifdef __cplusplus
extern "C" {
#endif

int         nema_init(void);
int         nema_shutdown(void);
int         nema_reg_read(int reg, uint32_t *var);
int         nema_reg_write(int reg, uint32_t value);

void        nema_info(void);
void       *nema_get_shm_ptr(void);
void       *nema_get_regs_ptr(void);
uint32_t    nema_get_shm_phys(void);
uint32_t    nema_virt_to_phys(uint32_t virt);

void        nema_wait_for_status(void);
void        nema_wait_for_interrupt(void);
void        nema_wait_for_interrupt_wtf(void);

void        nema_flush_caches(int wait);
void        nema_cmdl_flush_caches(void);
int         nema_get_file_size(const char *filename);
void       *nema_load_binary(const char *filename);
void       *nema_load_run_binary(char *filename, void *data_ptr, int wait);
void        nema_run_binary(void *bin_ptr, void *data_ptr, int wait);
void       *nema_cmdl_load_run_binary(char *filename, void *data_ptr);

/// Malloc, Init, Free etc
int         nema_memIsInited(void);
void        nema_meminit(void *address_start, size_t size);
void        nema_free(void *firstbyte);
void       *nema_realloc(void *src, size_t size);
void       *nema_malloc(size_t numbytes);
size_t      nema_malloc_usable_size(void *p);
size_t      nema_free_pool_size(void);

/// ThinkLCDML utils
int thinklcdml_reg_read(int reg, uint32_t *var);

#ifdef __cplusplus
}
#endif

#endif
