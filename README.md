# capa_benchmark

Author: Qian Zhang
Time: 04/17/2019

This repo lists the selected benchmarks for CAPA. Basically they are either edited from Rosseta/SDAccel or written by hand.

For integer bitwidth optimization:
	bubble: bubble sort
	3drendering: this is an integer operation-intensive design. It renders 2D images from 3D models(3D triangle mesh). Each 3D triangl is packed into a 32-bit integer.
	facedetection: another integer operation-intensive application. It detects human faces in a given image. The application takes an 320x240 greyscale image as input, and eventually the positions and sizes of the human faces are returned.

For refactoring the recursive functions:
	binarysearch: recursive binary search with randomly generated inputs.
	determinant: calculate the determinant of a given matrix in a recursive manner.

For floating-point bitwidth optimization: (these two still have bugs)
	kmeans
	opticalflow

Referenced benchmarks for FPGA High-level Synthesis:
Rosseta: https://github.com/cornell-zhang/rosetta
CHStone: http://www.ertl.jp/chstone/#Publication
SDAccel: https://github.com/Xilinx/SDAccel_Examples/tree/master/acceleration/smithwaterman/src

CHStone and SDAccel are popular used FPGA high level synthesis benchmarks, Rosseta is the latest and realistic hls benchmark suit. However CHStone programs are written in a limited set of C programming language. The following data types and constructs, which are not supported by most of HLS tools, are not used: floating-point data, composite data types, dynamic memory allocation, and recursive functions. Thus we only consider the test programs in SDAccel and Rosseta here.
