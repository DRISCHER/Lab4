// SPDX-License-Identifier: GPL-2-Clause
#include <hello1.h>

MODULE_AUTHOR("Andrii Stupak IO-13");
MODULE_DESCRIPTION("Lab 4 Zalikova 1325");
MODULE_LICENSE("GPL");

struct time_tracking {
    struct list_head node;
    ktime_t start_time;
    ktime_t end_time;
};

static struct list_head timing_list = LIST_HEAD_INIT(timing_list);

int print_hello(uint q) 
{
    struct time_tracking *element, *tmp_element; 
    uint i; 

    if (q <= 0) { 
        pr_err("Parameter 'q' must be a positive number\n");
        return -EINVAL;
    } else if (q < 5) { 
        pr_info("Value of 'q' is less than 5\n");
    } else if (q > 10) { 
        pr_err("Value of 'q' is more than 10\n");
        return -EINVAL;
    }

    for (i = 0; i < q; i++) { 
        element = kmalloc(sizeof(struct time_tracking), GFP_KERNEL);
        if (!element) { 
            goto error_handling;
        }
        element->start_time = ktime_get();
        pr_info("Hello, world sproba: %d\n", i + 1);
        element->end_time = ktime_get();
        list_add_tail(&element->node, &timing_list);
    }
    return 0;

error_handling: 
    pr_err("Failed to allocate memory\n");
    list_for_each_entry_safe(element, tmp_element, &timing_list, node) {
        list_del(&element->node);
        kfree(element);
    }
    return -ENOMEM;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_module_start(void) 
{
    pr_info("Starting hello1 module\n");
    return 0;
}

static void __exit hello1_module_end(void) 
{
    struct time_tracking *element, *tmp_element; 

    list_for_each_entry_safe(element, tmp_element, &timing_list, node) {
        pr_info("Time for execution: %lld ns\n", ktime_to_ns(element->end_time - element->start_time));
        list_del(&element->node);
        kfree(element);
    }
    BUG_ON(!list_empty(&timing_list));
    pr_info("hello1 module has been removed\n");
}

module_init(hello1_module_start);
module_exit(hello1_module_end);

