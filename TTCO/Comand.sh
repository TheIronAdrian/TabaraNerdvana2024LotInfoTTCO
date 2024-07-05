#!/bin/bash

echo ======
echo ~
echo ======
PATH_TO_TWOGTP="/home/mihai/pentobi/twogtp/twogtp"
PATH_TO_TTCO="/home/mihai/TabaraNerdvana2024LOTINFO/TabaraNerdvana2024LotInfoTTCO/TTCO/winner"
PATH_TO_PENTOBI="/home/mihai/pentobi/pentobi_gtp/pentobi-gtp"
PATH_TO_BYRG="/home/mihai/byrg/byrg --seed 0"
ls -la $PATH_TO_TWOGTP

rm -rf output.dat output.blksgf

# Two player
$PATH_TO_TWOGTP \
  --black "$PATH_TO_BYRG" \
  --white "$PATH_TO_TTCO" \
  -g duo

# Four player
#$PATH_TO_TWOGTP \
#  --blue $PATH_TO_US \
#  --yellow $PATH_TO_PENTOBI \
#  --red $PATH_TO_PENTOBI \
#  --green $PATH_TO_PENTOBI \
#  -g classic
