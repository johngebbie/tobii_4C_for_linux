#!/bin/bash

sudo cp -R tobii_usb_service/etc/* /etc/
sudo cp -R tobii_usb_service/usr/* /usr/
sudo cp -R tobii_engine/etc/* /etc/
sudo cp -R tobii_engine/usr/* /usr/
sudo systemctl daemon-reload
sudo systemctl start tobiiusb.service
sudo systemctl start tobii_engine.service

sudo mkdir /usr/lib/tobii
sudo cp -pR lib/lib/x64/*.so /usr/lib/tobii/
sudo cp ./tobii.conf /etc/ld.so.conf.d/
sudo mkdir /usr/include/tobii
sudo cp -R lib/include/tobii/* /usr/include/tobii
