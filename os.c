
#define _GNU_SOURCE

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <sys/mman.h>

#include "os.h"

/* 2^20 pages ought to be enough for anybody */
#define NPAGES    (1024*1024)
#define NLEVELS 6
static void *pages[NPAGES];

uint64_t alloc_page_frame(void) {
    static uint64_t nalloc;
    uint64_t ppn;
    void *va;

    if (nalloc == NPAGES)
        errx(1, "out of physical memory");

    /* OS memory management isn't really this simple */
    ppn = nalloc;
    nalloc++;

    va = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (va == MAP_FAILED)
        err(1, "mmap failed");

    pages[ppn] = va;
    return ppn;
}

void *phys_to_virt(uint64_t phys_addr) {
    uint64_t ppn = phys_addr >> 12;
    uint64_t off = phys_addr & 0xfff;
    void *va = NULL;

    if (ppn < NPAGES)
        va = pages[ppn] + off;

    return va;
}

void delete_page(uint64_t pt, uint64_t vpn) {
    uint64_t ppn2Destroy = page_table_query(pt, vpn);
    pages[ppn2Destroy] = NULL;

}

void move_page(uint64_t pt, uint64_t vpn, uint64_t new_ppn) {
    uint64_t ppn2move = page_table_query(pt, vpn);
    pages[new_ppn] = pages[ppn2move];
    pages[ppn2move] = NULL;
}

/*VPN== VIRTUAL PAGE NUMBER
 * PPN==PHYSICAL PAGE NUMBER
 * PT==POINTER
 */

void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn) {
    switch (ppn) {
        case NO_MAPPING: //AKA delete page

            delete_page(pt, vpn);
            break;
        default:
            move_page(pt, vpn, ppn);
            break;

    }
}

uint64_t page_table_query(uint64_t pt, uint64_t vpn) {
    //@todo
}

void asserti(int expr)
{
    //assert(expr);
}
int main2(int argc, char **argv) {
    uint64_t pt = alloc_page_frame();

    asserti(page_table_query(pt, 0xcafe) == NO_MAPPING);
    page_table_update(pt, 0xcafe, 0xf00d);
    asserti(page_table_query(pt, 0xcafe) == 0xf00d);
    page_table_update(pt, 0xcafe, NO_MAPPING);
    asserti(page_table_query(pt, 0xcafe) == NO_MAPPING);

    return 0;
}
int main(int argc, char **argv) {
    uint64_t pt = alloc_page_frame();
    for(int i=0;i<100;i++)
    pt = alloc_page_frame();

    asserti(page_table_query(pt, 3) == NO_MAPPING);
    page_table_update(pt, 3, 7);
    asserti(page_table_query(pt, 3) == 7);
    page_table_update(pt, 3, NO_MAPPING);
    asserti(page_table_query(pt, 3) == NO_MAPPING);
    uint64_t * t=pages[7];
    return 0;
}