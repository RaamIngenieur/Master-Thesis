#ifndef __TSI_CMDLIST_H__
#define __TSI_CMDLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

int initialize_mmu(void);
int tsi_cmdl_init(void *v_addr, void *p_addr, size_t size, uint32_t *cmdaddr_reg, uint32_t *cmdsize_reg, uint32_t *devstatus_reg, void (*wait_dev)(void));
void tsi_cmdl_flush_list(int i);
void tsi_cmdl_emit_commands(int block);
void tsi_cmdl_add_cmd(uint32_t reg, uint32_t data);

#ifdef __cplusplus
}				/* end of extern "C" */
#endif

#endif // __TSI_CMDLIST_H__
