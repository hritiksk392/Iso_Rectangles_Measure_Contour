@mainpage CS F364 DAA Assigment-1
## Team Members
### Akshit 2018A7PS0187H
### Hritik Singh Kushwah  2018A7PS0323H
### Shubham Asopa 2018A7PS0101H
### Smiket Barodia 2018A7PS0231H

## Problem Statement
### Finding Measure and Contour of n iso-rectangles using Divide and Conquer Strategy.

## Input Format 
Input format : First line n : number of iso rectangles.

Next n lines contain x1 x2 y1 y2 which is the x interval= [x1,x2] and y interval = [y1,y2] for ith rectangle.

## Information about Files
'input.txt' contains the input

'meas.txt' contain value of measure

'out.txt' contains contour horizontal and vertical pieces as Line Segments( x1 ,x2 ,y) ([x1,x2] interval and coordinate y)

Note: Separated by ':' for horizontal and vertical edges

'geo.h' contains classes and function regarding the geometrical shapes

'helper.h' contains all helper functions for main algorithm to work such as set functions etc.

'iso_M.cpp' solves the measure problem

'iso_Contour.cpp' solves the contour problem

'Visualization.ipynb' contains python code for visualization of contour using matplotlib

## Compiling Files
As both the files iso_M.cpp and iso_Contour.cpp have header dependencies on helper.h and geo.h use the below command to compile.

For iso_M.cpp
~~~~~~~~~~~~~~~~~~~~~~~~~.sh
g++ -o iso_M iso_M.cpp helper.cpp geo.cpp
~~~~~~~~~~~~~~~~~~~~~~~~~

For iso_Contour.cpp
~~~~~~~~~~~~~~~~~~~~~~~~~.sh
g++ -o iso_Contour iso_Contour.cpp helper.cpp geo.cpp
~~~~~~~~~~~~~~~~~~~~~~~~~