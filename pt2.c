#include "os.h"

#define LEVELS_AMOUNT 5
#define KEY_MASK 0x1FF
#define KEY_SIZE 9
#define CHILDREN 512

/*
 * Whether or not a PTE holds a valid value.
 * Checks the valid bit
 */
int is_valid(uint64_t pte) {
	return pte & 0x1;
}

/*
 * Given a VPN and a part number (zero based),
 * return the part of the VPN used in the matching trie level.
 */
int get_index(uint64_t vpn, int part) {
	int offset;
	offset = 45 - part * KEY_SIZE;

	vpn = vpn >> offset;
	vpn = vpn & KEY_MASK;

	return vpn;
}

/*
 * Given an old ppn and a new one,
 * return the value that `update` needs to put in the PTE.
 */
uint64_t format_pte_entry(uint64_t old_ppn, uint64_t new_ppn) {
	if (new_ppn == NO_MAPPING)
		return old_ppn & 0xFFFFFFFFFFFFFFFE;
	else
		return (new_ppn << 12) + 1;
}

/*
 * Given a PTE, return the value it contains (either a PPN or NO_MAPPING).
 */
uint64_t get_value_pte_entry(uint64_t pte) {
	if (is_valid(pte))
		return pte >> 12;

	return NO_MAPPING;
}

/*
 * Given a PTE, returns the virtual address of the node this PTE points to.
 * A pre-condition is that PTE contains a valid PPN which points to an actual (allocated) node.
 */
uint64_t *get_node_from_pte(uint64_t pte) {
	return (uint64_t*) phys_to_virt(pte & 0xFFFFFFFFFFFFF000); // Reset lowest 12 bits (no offset)
}


uint64_t page_table_query(uint64_t pt, uint64_t vpn) {
	uint64_t *node = phys_to_virt(pt << 12);
	int index;

	for (int i = 0; i < LEVELS_AMOUNT; i++){
		index = get_index(vpn, i);

		if (!is_valid(node[index]))
			return NO_MAPPING;

		node =  get_node_from_pte(node[index]);
	}

	index = get_index(vpn, LEVELS_AMOUNT);
	return get_value_pte_entry(node[index]);
}

void page_table_update(uint64_t pt,  uint64_t vpn, uint64_t ppn) {
	uint64_t *node = phys_to_virt(pt << 12);
	int index;

	for (int i = 0; i < LEVELS_AMOUNT; i++){
		index = get_index(vpn, i);

	       	if (node[index] == 0)
			node[index] = (alloc_page_frame() << 12) + 0x1;

		node = get_node_from_pte(node[index]);
	}

	index = get_index(vpn, LEVELS_AMOUNT);
	node[index] = format_pte_entry(node[index], ppn);
}
