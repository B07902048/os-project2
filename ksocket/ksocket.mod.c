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
	{ 0x7f60820e, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd1804d15, __VMLINUX_SYMBOL_STR(sock_setsockopt) },
	{ 0x7aff68d4, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0x7d5624b3, __VMLINUX_SYMBOL_STR(sock_recvmsg) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xa06eefa8, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x5687e6d5, __VMLINUX_SYMBOL_STR(sock_sendmsg) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x2ea2c95c, __VMLINUX_SYMBOL_STR(__x86_indirect_thunk_rax) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0x6ba2674b, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x230a8e0b, __VMLINUX_SYMBOL_STR(sock_create) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "91768B575EDE64B72FECBEF");
