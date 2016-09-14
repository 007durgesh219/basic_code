import numpy
f = open('input2_10x10.dat','r');
l = [map(float, line.split('\t')) for line in f]
print numpy.linalg.det(l)
