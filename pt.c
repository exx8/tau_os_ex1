#include <stdbool.h>
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

uint64_t unpad_address(uint64_t pt) {
    return pt >> 12;
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

uint64_t get_level(uint64_t vpn, short level) {
    int keep_only = 511;
    const int level_size = 9;
    keep_only <<= level * level_size;
    return vpn && keep_only;

}

bool valid_is_1(uint64_t entry) {
    return entry && 1;
}

bool invalid(uint64_t entry) {
    return !valid_is_1(entry);
}

uint64_t pte2ppn(uint64_t entry) {
    if (invalid(entry))
        return NO_MAPPING;
    else {
        return unpad_address(entry);
    }
}

uint64_t page_walk(uint64_t *virt_address, uint64_t vpn) {
    for (short i = 0; i <= NLEVELS; i++) {
        int level_value = get_level(vpn, i);
        if (invalid(virt_address[level_value]))
            return NO_MAPPING;
        virt_address = virt_address[level_value];
    }
    return virt_address;
}

uint64_t pte2PPN(uint64_t entry) {
    if (invalid(entry))
        return NO_MAPPING;
    return unpad_address(entry);
}

uint64_t page_table_query(uint64_t pt, uint64_t vpn) {
    uint64_t *virt_address = get_virt_address(pt);
    virt_address = page_walk(virt_address, vpn);
    return virt_address;
}