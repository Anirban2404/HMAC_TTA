#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include "linux/string.h"
#include "linux/ktime.h"

// ******************************************************************************
// ** Anirban Bhattacharjee 
// ******************************************************************************

ktime_t ktime_get(void);
#include "SHA3_sponge.h"



static int __init init_main(void)
{
	// HMAC Variables
	unsigned char text[5] = "hello";
	int text_len = 0;
	unsigned char *key ="5FCD395FCD395FCD395FCD395FCD395FCD395FCD395FCD312AF3JAK86AA3ABS0";
	unsigned char digest[64];

	int i=0;
	// Timer Variables
	ktime_t start, end;
	s64 actual_time;

	printk(KERN_INFO "[CRYPTO] -> Successfully loaded crypto module.\n");
	start = ktime_get();
	hmac_sha256(key, strlen(key), text, strlen(text), digest);
	sponge_hmac_512(digest, key, strlen(key), text, strlen(text) );
	end = ktime_get();
	for(i=0; i<64; i++)
	{
		printk("%02x", (digest[i] & 0xff));
	}
	printk("\n");
	actual_time = ktime_to_ns(ktime_sub(end, start));
	printk("<%d>", strlen(key));
	return 0;
}

static void __exit cleanup_main(void)
{

	printk(KERN_INFO "[CRYPTO] < - Successfully unloaded crypto module.\n");

}

module_init(init_main);
module_exit(cleanup_main);


