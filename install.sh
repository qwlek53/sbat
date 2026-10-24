#!/bin/bash

if [ $(id -u) != "0" ]; then
    echo "Please execute with sudo: sudo ./install.sh"
    exit
fi
  
echo "Installing..."
cp sbat /usr/bin/sbat
chmod +x /usr/bin/sbat
