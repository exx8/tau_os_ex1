#include <stdbool.h>
#include "os.h"

#define NLEVELS 5
#define leaves 512

//counting from zero!!!!


/**
 * side note: no padding for NO_MAPPING as it is not a real address
 */
uint64_t pad_address(uint64_t pt) {
    if (pt == NO_MAPPING)
        return NO_MAPPING;
    return pt << 12;
}

uint64_t unpad_address(uint64_t pt) {
    if (pt == NO_MAPPING)
        return NO_MAPPING;
    return pt >> 12;
}


uint64_t *get_virt_address(uint64_t pt) {
    uint64_t padded_phys = pad_address(pt);
    uint64_t *virt_address = (uint64_t *) (phys_to_virt(padded_phys));
    return virt_address;
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


uint64_t page_walk(uint64_t *virt_address, uint64_t vpn) {
    for (short i = 0; i <= NLEVELS; i++) {
        int level_value = get_level(vpn, i);
        if (invalid(virt_address[level_value]))
            return NO_MAPPING;
        virt_address = virt_address[level_value];
    }
    return virt_address;
}


uint64_t get_pte(uint64_t pt, uint64_t vpn) {
    uint64_t *virt_address = get_virt_address(pt);
    virt_address = page_walk(virt_address, vpn);
    return virt_address;
}

uint64_t page_table_query(uint64_t pt, uint64_t vpn) {
    uint64_t pte = get_pte(pt, vpn);
    pte = unpad_address(pte);
    return pte;
}


void set_new_frame(uint64_t *virt_address, int level_value) {
    uint64_t new_frame = alloc_page_frame();
    new_frame = pad_address(new_frame);
    new_frame |= 1;
    virt_address[level_value] = new_frame;
}
void put_new_pte(uint64_t ppn,uint64_t level_value,uint64_t* virt_address)
{
    uint64_t new_value;
    if(ppn==NO_MAPPING)
        ppn&18446744073709551614; //18446744073709551614==1111111111111111111111111111111111111111111111111111111111111110_2
        else {
        new_value = pad_address(ppn);
        new_value++;
    }
        virt_address[level_value]=new_value;
}
void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn) {
    uint64_t *virt_address = get_virt_address(pt);
    for (short i = 0; i < NLEVELS; i++) {
        int level_value = get_level(vpn, i);
        if (virt_address[level_value] == 0) {
            set_new_frame(virt_address, level_value);
        }
        virt_address = virt_address[level_value];
    }



}