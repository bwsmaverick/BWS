#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/Bws.ico

convert ../../src/qt/res/icons/Bws-16.png ../../src/qt/res/icons/Bws-32.png ../../src/qt/res/icons/Bws-48.png ${ICON_DST}
