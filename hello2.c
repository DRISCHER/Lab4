// SPDX-License-Identifier: GPL-2-Clause
#include <hello1.h>

MODULE_AUTHOR("Andrii Stupak IO-13");
MODULE_DESCRIPTION("Lab 4 Zalikova 1325");
MODULE_LICENSE("GPL");

static uint q = 1; 

module_param(q, uint, 0); 
MODULE_PARM_DESC(q, "Parameter to control the number of greetings\n"); 
static int __init start_hello2_module(void) 
{
    pr_info("hello2: Module start\n"); 
    print_hello(q); 
    return 0;
}

static void __exit end_hello2_module(void) 
{
    pr_info("hello2: Module end\n"); 
}

module_init(start_hello2_module); 
module_exit(end_hello2_module); 

