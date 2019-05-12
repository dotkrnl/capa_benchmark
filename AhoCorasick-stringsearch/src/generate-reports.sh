#!/bin/bash -

for ARRAY_LOG in 12 13 14 15 16 17 18 19 20 21
do
    xocc -c --platform xilinx_vcu1525_xdma_201830_1 kernel-transformed.cpp -o kernel-transformed.xo --kernel AhoCorasick_search --target hw -O3 -DARRAY_LOG=${ARRAY_LOG}
    xocc -l kernel-transformed.xo --platform xilinx_vcu1525_xdma_201830_1 -O3 -DARRAY_LOG=${ARRAY_LOG}
    mv _x _x${ARRAY_LOG}
    break
done
