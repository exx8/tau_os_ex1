#include "os.h"

#define NLEVELS 5
#define leaves 512

//counting from zero!!!!

void delete_page(uint64_t pt, uint64_t vpn) {
    //@todo
}

uint64_t pad_address(uint64_t pt) {
    return pt << 12;
}

void move_page(uint64_t pt, uint64_t vpn, uint64_t ppn) {
    //todo
}

uint64_t *get_virt_address(uint64_t pt) {
    uint64_t padded_phys = pad_address(pt);
    uint64_t *virt_address = (uint64_t *) (phys_to_virt(padded_phys));
    return virt_address;
}

void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn) {
    uint64_t *virt_address = get_virt_address(pt);

    if (ppn == NO_MAPPING)
        delete_page(pt, vpn);
    else
        move_page(pt, vpn, ppn);
}

uint64_t get_level(uint64_t ppn, short level) {
    int keep_only = 511;
    const int level_size = 9;
    keep_only <<= level * level_size;
    return ppn && keep_only;

}

uint64_t page_table_query(uint64_t pt, uint64_t vpn) {
    uint64_t *virt_address = get_virt_address(pt);
    for (short i = 0; i < NLEVELS; i++) {

    }

}