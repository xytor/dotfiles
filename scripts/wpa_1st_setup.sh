#!/bin/sh
echo "Write your interface"
read interface
touch /etc/wpa_supplicant/wpa_supplicant-$interface.conf
echo "ctrl_interface=/run/wpa_supplicant" >> /etc/wpa_supplicant/wpa_supplicant-$interface.conf
echo "update_config=1" >> /etc/wpa_supplicant/wpa_supplicant-$interface.conf
echo "Write your ssid"
read ssid
echo "Write password"
read -s passwd
wpa_passphrase $essid $passwd >> /etc/wpa_supplicant/wpa_supplicant-$interface.conf
wpa_supplicant -B -i $interface -c /etc/wpa_supplicant/wpa_supplicant-$interface.conf
echo "All done!"
