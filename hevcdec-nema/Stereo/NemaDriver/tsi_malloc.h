// -----------------------------------------------------------------------------
// Copyright (c) 2012 Think Silicon Ltd
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
// FILE NAME  :
// KEYWORDS   :
// PURPOSE    :
// DEPARTMENT :
// AUTHOR     : PA
// GENERATION :
// RECEIVER   :
// NOTES      :

#ifndef __TSI_MALLOC_H__
#define __TSI_MALLOC_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

int ASSERT_IS_IN_POOL(void *p);

int tsi_memIsInited(void);
void tsi_meminit(void *address_start, size_t size);
void tsi_free(void *firstbyte);
void *tsi_realloc(void *src, size_t size);
void *tsi_malloc(size_t numbytes);

size_t tsi_malloc_usable_size(void *p);
size_t tsi_free_pool_size(void);

#ifdef __cplusplus
}
#endif

#endif

