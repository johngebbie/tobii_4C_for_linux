#!/bin/sh

sudo systemctl disable tobii_engine.service
sudo systemctl disable tobiiusb.service
sudo rm /etc/systemd/system/tobii_engine.service
sudo rm /etc/systemd/system/tobiiusb.servicie
sudo rm -R /usr/local/lib/tobiiusb
sudo rm /usr/local/sbin/tobiiusbserviced

sudo rm -R /usr/lib/tobii
sudo rm -R /usr/include/tobii
sudo rm /etc/ld.so.conf.d/tobii.conf
