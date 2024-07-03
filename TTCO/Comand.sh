#!/bin/bash

echo ======
echo ~
echo ======
PATH_TO_TWOGTP="/home/mihai/pentobi/twogtp/twogtp"
PATH_TO_PENTOBI="/home/mihai/TabaraNerdvana2024LOTINFO/TabaraNerdvana2024LotInfoTTCO/TTCO/loser"
PATH_TO_US="/home/mihai/pentobi/pentobi_gtp/pentobi-gtp"
ls -la $PATH_TO_TWOGTP

rm -rf output.dat output.blksgf

# Two player
$PATH_TO_TWOGTP \
  --black $PATH_TO_US \
  --white $PATH_TO_PENTOBI \
  -g duo

# Four player
#$PATH_TO_TWOGTP \
#  --blue $PATH_TO_US \
#  --yellow $PATH_TO_PENTOBI \
#  --red $PATH_TO_PENTOBI \
#  --green $PATH_TO_PENTOBI \
#  -g classic
