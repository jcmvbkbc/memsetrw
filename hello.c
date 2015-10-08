#include <linux/module.h>
#include <linux/init.h>

#include <asm/pgtable_types.h>
#include <asm/tlbflush.h>

void mem_setrw(void **table) {
	unsigned int l;
	pte_t *pte;
	pte = lookup_address((long unsigned int)table, &l);
	pte->pte |= _PAGE_RW;
	__flush_tlb_one((unsigned long)table);
}

void mem_setro(void **table) {
	unsigned int l;
	pte_t *pte;
	pte = lookup_address((long unsigned int)table, &l);
	pte->pte &= ~_PAGE_RW;
	__flush_tlb_one((unsigned long)table);
}

static int __init hello_init(void)
{
	printk(KERN_DEBUG "Hello, world!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	return;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
