#include <stdlib.h>

typedef struct MMGR_Entry MMGR_Entry;
typedef struct MMGR MMGR;

MMGR *mmgr_init();
void *mmgr_malloc(MMGR *tbl, size_t size);
void mmgr_free(MMGR *tbl, void *handle);
void mmgr_cleanup(MMGR *tbl);
void mmgr_mutex_acquire(MMGR *tbl);
void mmgr_mutex_release(MMGR *tbl);

// Global MMGR instance
MMGR *g_MEM;
