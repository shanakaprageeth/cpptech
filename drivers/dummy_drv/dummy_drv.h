#if !defined(DUMMY_DRV_H)
#define DUMMY_DRV_H

#define LICENSE_V "GPL"
#define DRV_NAME "DUMMY_DRV"
#define DRV_MODULE_VERSION "1.0"
#define DRV_MODULE_AUTHOR "Shanaka"
#define DRV_MODULE_DESCRIPTION "Test driver with kernel messages"

#define DEVICE_NAME "dummy_device"
#define DEVICE_CLASS "char_device"

/* Userland device properties*/
static dev_t device_no;
static struct class *device_class;
static struct cdev device_cdev;

/* Buffer for device char*/
static char buffer[255];
static size_t buffer_pointer = 0;

/**
 * @brief Return kernel data back to user buffer
 * @param input file pointer
 * @param char buffer pointer to access user data
 * @param size size to read
 * @param longlong offset
 */
static ssize_t return_data_to_user(struct file *File, char *user_buffer, size_t count, loff_t *offset);

/**
 * @brief Process user buffer data in kernel
 * @param input file pointer
 * @param char buffer pointer to access user data
 * @param size size to read
 * @param longlong offset
 */
static ssize_t process_user_data(struct file *File, const char *user_buffer, size_t count, loff_t *offset);

/**
 * @brief This function notify when the device driver file is open from userland
 * @param struct inode pointer to device_file instance
 * @param struct file pointer to a file instance
 * @return int 0-success
 */
static int user_device_open(struct inode *device_file, struct file *instance);

/**
 * @brief This function notify when the device driver file is closed from userland
 * @param struct inode pointer to device_file instance
 * @param struct file pointer to a file instance
 * @return int 0-success
 */
static int user_device_release(struct inode *device_file, struct file *instance);

/**
 * @brief structure to save the file operations functions
 * @param owner owner of the operation
 * @param open open operation function
 * @param release release operation function
*/
static struct file_operations file_ops = {
	.owner = THIS_MODULE,
	.open = user_device_open,
	.release = user_device_release,
    .read = return_data_to_user,
    .write = process_user_data
};

/**
 * @brief this function initialize the module
 * @return int 0-success 1-failure
*/
static int __init ModuleInit(void);


/**
 * @brief this function remove the module
 * @return int 0-success 1-failure
*/
static void __exit ModuleExit(void);


#endif