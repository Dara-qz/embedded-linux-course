#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Embedded Linux course");
MODULE_DESCRIPTION("Simple hello module for BeagleBone Black");
MODULE_VERSION("1.0");

static int __init hello_init(void)
{
    pr_info("hello_module: Hello from kernel space on BBB!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("hello_module: Goodbye from kernel space on BBB!\n");
}

module_init(hello_init);
module_exit(hello_exit);
