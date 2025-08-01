#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/bitcoin.png
ICON_DST=../../src/qt/res/icons/bitcoin.ico
convert ${ICON_SRC} -resize 16x16 bitcoin-16.png
convert ${ICON_SRC} -resize 24x24 bitcoin-24.png
convert ${ICON_SRC} -resize 32x32 bitcoin-32.png
convert ${ICON_SRC} -resize 48x48 bitcoin-48.png
convert ${ICON_SRC} -resize 256x256 bitcoin-256.png
convert bitcoin-16.png bitcoin-24.png bitcoin-32.png bitcoin-48.png bitcoin-256.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/bitcoin_testnet.png
ICON_DST=../../src/qt/res/icons/bitcoin_testnet.ico
convert ${ICON_SRC} -resize 16x16 bitcoin-16.png
convert ${ICON_SRC} -resize 24x24 bitcoin-24.png
convert ${ICON_SRC} -resize 32x32 bitcoin-32.png
convert ${ICON_SRC} -resize 48x48 bitcoin-48.png
convert ${ICON_SRC} -resize 256x256 bitcoin-256.png
convert bitcoin-16.png bitcoin-24.png bitcoin-32.png bitcoin-48.png bitcoin-256.png ${ICON_DST}
#regtest
ICON_SRC=../../src/qt/res/icons/bitcoin_regtest.png
ICON_DST=../../src/qt/res/icons/bitcoin_regtest.ico
convert ${ICON_SRC} -resize 16x16 bitcoin-16.png
convert ${ICON_SRC} -resize 24x24 bitcoin-24.png
convert ${ICON_SRC} -resize 32x32 bitcoin-32.png
convert ${ICON_SRC} -resize 48x48 bitcoin-48.png
convert ${ICON_SRC} -resize 256x256 bitcoin-256.png
convert bitcoin-16.png bitcoin-24.png bitcoin-32.png bitcoin-48.png bitcoin-256.png ${ICON_DST}
rm bitcoin-16.png bitcoin-24.png bitcoin-32.png bitcoin-48.png bitcoin-256.png
