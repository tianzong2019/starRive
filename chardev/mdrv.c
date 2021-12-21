#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

static int gval = 0;
static int glmajor = 0;

#define DEVNAME   "chardev"

struct globaldemo {
	struct cdev gcdev;
	struct class *gclass;
	dev_t devno;
} gldemo;

static int dmisc_open(struct inode *inode, struct file *filp)
{
    printk ("%s %d\n", __func__, __LINE__);
    return 0;
}
static int dmisc_release(struct inode *inode, struct file *filp)
{
    printk ("%s %d\n", __func__, __LINE__);
    return 0;
}
static ssize_t dmisc_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    int ret = 0;
    printk ("%s %d\n", __func__, __LINE__);
	ret = copy_to_user(buf, &gval, sizeof(gval));
    return ret;
}
static ssize_t dmisc_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	int ret = 0;
	ret = copy_from_user(&gval, buf, count);
    printk ("%s %d, gval %d\n", __func__, __LINE__, gval);
	gval += 10;

    return ret;
}
static long dmisc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk ("%s %d\n", __func__, __LINE__);
    return 0;
}
static struct file_operations dmisc_fops =
{
    .owner           = THIS_MODULE,
    .open            = dmisc_open,
    .read            = dmisc_read,
    .write           = dmisc_write,
    .compat_ioctl    = dmisc_ioctl,
    .release         = dmisc_release
};
static int hello_init(void)
{
	int ret = 0;
	printk ("%s %d\n", __func__, __LINE__);

	gldemo.devno = MKDEV(glmajor, 0);
	if (glmajor)
		ret = register_chrdev_region(gldemo.devno, 1, DEVNAME);
	else {
		ret = alloc_chrdev_region(&gldemo.devno, 0, 1, DEVNAME);
		glmajor = MAJOR(gldemo.devno);
	}
	if (ret < 0) {
		printk ("%s %d, register_chrdev error\n", __func__, __LINE__);
		return ret;
	}
	cdev_init(&gldemo.gcdev, &dmisc_fops);
	gldemo.gcdev.owner = THIS_MODULE;
	ret = cdev_add(&gldemo.gcdev, gldemo.devno, 1);

	gldemo.gclass = class_create(THIS_MODULE, DEVNAME);
	device_create(gldemo.gclass, NULL, gldemo.devno, NULL, DEVNAME);

	return 0;
}

static void hello_exit(void)
{
	printk ("%s %d\n", __func__, __LINE__);
	device_destroy(gldemo.gclass, gldemo.devno);
	class_destroy(gldemo.gclass);
	cdev_del(&gldemo.gcdev);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
