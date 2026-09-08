#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Lab 02 hello module for BeagleBone Black");
MODULE_VERSION("1.0");

static char *name = "Student";
module_param(name, charp, 0444);
MODULE_PARM_DESC(name, "Name printed when the module loads");

static int __init hello_init(void)
{
    if (!name || name[0] == '\0')
        return -EINVAL;

    pr_info("hello_module: Hello, %s, from kernel space on BBB!\n", name);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("hello_module: Goodbye from kernel space on BBB!\n");
}

module_init(hello_init);
module_exit(hello_exit);
