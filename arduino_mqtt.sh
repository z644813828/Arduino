#!/bin/bash

MAIN_PC_IP="192.168.2.2"

MONIT_IGNORE_REGEX="Monit|Service Name|Status ok|Running|Accessible|Online with all services"

monit=$(monit summary | grep -v -E "$MONIT_IGNORE_REGEX" | awk '{ print $1 }')
mosquitto_pub -h localhost -t "monit/text" -m "$monit"

! ping -c 1 $MAIN_PC_IP &> /dev/null
mosquitto_pub -h localhost -t "led/enabled" -m "$?"

