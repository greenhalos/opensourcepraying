#!/bin/sh

# https://stackoverflow.com/questions/16501663/macs-say-command-to-mp3


say -f pray.txt -o pray.aiff
lame -m m pray.aiff pray.mp3
