.. zephyr:code-sample:: bluetooth_hci_usb
   :name: HCI USB
   :relevant-api: hci_raw bluetooth _usb_device_core_api usbd_api

   Turn a Zephyr board into a USB Bluetooth dongle (compatible with all operating systems).

Overview
********

Make a USB Bluetooth dongle out of Zephyr. This project is configured for the
HoLyiot 21017-52840+PA module which includes:

* nRF52840 SoC
* 2401C Front-End Module (PA/LNA) for extended range
* RGB LED for status indication

The green LED (LED2_G) turns on when the software is running.

Hardware Configuration
**********************

FEM (2401C PA/LNA) Pin Mapping:

* **TXEN**: P0.24
* **RXEN**: P0.22

LED Pin Mapping:

* **LED2_G (Green)**: P1.09

Requirements
************

* Bluetooth stack running on the host (e.g. BlueZ)
* HoLyiot 21017-52840+PA module (nRF52840 Dongle form factor)
* nRF Connect SDK

Building
********

Build the project::

    cd /path/to/hci_usb
    west build -b nrf52840dongle/nrf52840 -- -DBOARD_ROOT=/path/to/hci_usb

Flashing
********

Put the dongle in bootloader mode (press reset while holding the user button),
then flash using nrfutil::

    nrfutil pkg generate --hw-version 52 --sd-req=0x00 \
        --application build/hci_usb/zephyr/zephyr.hex \
        --application-version 1 pkg.zip
    nrfutil dfu usb-serial -pkg pkg.zip -p /dev/ttyACM0

Usage
*****

Once flashed, the dongle will appear as a USB Bluetooth adapter. The green LED
will illuminate to indicate the software is running.

On Linux with BlueZ::

    # Check if the device is detected
    hciconfig

    # Bring up the interface
    sudo hciconfig hci0 up

    # Scan for devices
    sudo hcitool lescan
