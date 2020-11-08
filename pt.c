#include <stdbool.h>
#include "os.h"

#define NLEVELS 5

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
    const int effective_size = 45;
    const int keep_only = 511;
    const int level_size = 9;
    uint64_t shift_vpn=vpn >> effective_size - level * level_size;
    return shift_vpn & keep_only;

}
uint64_t remove_valid_bit(uint64_t address)
{
    return (address>>1)<<1;
}
bool valid_is_1(uint64_t entry) {
    return entry&1;
}

bool invalid(uint64_t entry) {
    return !valid_is_1(entry);
}


uint64_t page_walk(uint64_t *virt_address, uint64_t vpn) {
    for (short i = 0; i < NLEVELS; i++) {
        int level_value = get_level(vpn, i);
        if (invalid(virt_address[level_value]))
            return NO_MAPPING;
        virt_address = phys_to_virt(remove_valid_bit(virt_address[level_value]));
    }
    short final_level_value = get_level(vpn, NLEVELS);
    return virt_address[final_level_value];
}


uint64_t get_pte(uint64_t pt, uint64_t vpn) {
    uint64_t *virt_address = get_virt_address(pt);
    uint64_t page_walk_result;
    page_walk_result = page_walk(virt_address, vpn);
    return page_walk_result;
}

uint64_t page_table_query(uint64_t pt, uint64_t vpn) {
    uint64_t pte = get_pte(pt, vpn);
    pte = unpad_address(pte);
    return pte;
}


void set_new_frame(uint64_t *virt_address, int level_value) {
    uint64_t new_frame = alloc_page_frame();
    new_frame = pad_address(new_frame);
    virt_address[level_value] = new_frame|1;
}


void put_new_pte(uint64_t ppn, uint64_t level_value, uint64_t *virt_address) {
    uint64_t new_value = ppn;
    if (ppn == NO_MAPPING) {
    } else {
        new_value = pad_address(ppn);
        new_value |= 1;
    }
    virt_address[level_value] = new_value;
}
uint64_t get_next_virt(uint64_t pte)
{
    return phys_to_virt(remove_valid_bit(pte));
}
uint64_t *page_update_walk(uint64_t vpn, uint64_t *virt_address, short i) {
    if (i == NLEVELS)
        return virt_address;
    int level_value = get_level(vpn, i);
    if ((virt_address[level_value] &1 )==0) {
        set_new_frame(virt_address, level_value);
    }
    virt_address = get_next_virt(virt_address[level_value]); //this seems to be ok
    return page_update_walk(vpn, virt_address, i + 1);
}

void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn) {
    uint64_t *virt_address = get_virt_address(pt);
    virt_address = page_update_walk(vpn, virt_address, 0);
    put_new_pte(ppn, get_level(vpn, NLEVELS), virt_address);


}