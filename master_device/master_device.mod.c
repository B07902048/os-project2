#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xe3df580a, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xadceca59, __VMLINUX_SYMBOL_STR(debugfs_remove) },
	{ 0xf93e8fd6, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0x55fa24af, __VMLINUX_SYMBOL_STR(klisten) },
	{ 0x311a85d, __VMLINUX_SYMBOL_STR(kbind) },
	{ 0xe2dda5bb, __VMLINUX_SYMBOL_STR(ksocket) },
	{ 0x8658f3e5, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xb052fb93, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x362ef408, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x10cde6fd, __VMLINUX_SYMBOL_STR(inet_ntoa) },
	{ 0x4e8a7293, __VMLINUX_SYMBOL_STR(ksend) },
	{ 0x3911fe33, __VMLINUX_SYMBOL_STR(kclose) },
	{ 0x5715be90, __VMLINUX_SYMBOL_STR(kaccept) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x465d63d3, __VMLINUX_SYMBOL_STR(pv_mmu_ops) },
	{ 0xa06eefa8, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xdca1fd18, __VMLINUX_SYMBOL_STR(remap_pfn_range) },
	{ 0x7cd8d75e, __VMLINUX_SYMBOL_STR(page_offset_base) },
	{ 0x4c9d28b0, __VMLINUX_SYMBOL_STR(phys_base) },
	{ 0xa202a8e5, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ksocket";


MODULE_INFO(srcversion, "D66C8543E1F9A9A877F6506");
