/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/drivers/gpio.h>

/* Green LED - indicates software is running */
#define LED_STATUS_NODE DT_ALIAS(led_status)

#if DT_NODE_EXISTS(LED_STATUS_NODE)
static const struct gpio_dt_spec led_status = GPIO_DT_SPEC_GET(LED_STATUS_NODE, gpios);
#endif

#if defined(CONFIG_USB_DEVICE_STACK_NEXT)
#include <sample_usbd.h>

static int enable_usb_device_next(void)
{
	struct usbd_context *sample_usbd = sample_usbd_init_device(NULL);

	if (sample_usbd == NULL) {
		printk("Failed to initialize USB device");
		return -ENODEV;
	}

	return usbd_enable(sample_usbd);
}
#endif /* CONFIG_USB_DEVICE_STACK_NEXT */

static void led_status_init(void)
{
#if DT_NODE_EXISTS(LED_STATUS_NODE)
	if (!gpio_is_ready_dt(&led_status)) {
		printk("LED GPIO not ready\n");
		return;
	}

	if (gpio_pin_configure_dt(&led_status, GPIO_OUTPUT_ACTIVE) < 0) {
		printk("Failed to configure LED GPIO\n");
		return;
	}

	/* Turn on green LED to indicate software is running */
	gpio_pin_set_dt(&led_status, 1);
	printk("Status LED enabled\n");
#endif
}

int main(void)
{
	int ret;

	/* Enable green LED to indicate software is up and running */
	led_status_init();

#if defined(CONFIG_USB_DEVICE_STACK_NEXT)
	ret = enable_usb_device_next();
#else
	ret = usb_enable(NULL);
#endif

	if (ret != 0) {
		printk("Failed to enable USB");
		return 0;
	}

	printk("Bluetooth over USB sample\n");
	return 0;
}
