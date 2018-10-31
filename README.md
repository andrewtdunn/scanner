Homework 2 Object Finder

Andrew Dunn ad2718	

Prof Shree Nayar 
Computer Vision 
CS 4371
Fall 2011


resubmission
10-19-2011

p1 threshold 142
p3 no additional properties added to database
p4 roundness and eMin used as criteria for recognition. 
	roundness threshold - a difference of 0.02
	eMin threshold - difference of 50000000 (this could be helpful for scaling, 
			as images could have similar roundness, but scaled differently, 
			therefore representing different objects).


note- I found the source of my error with the sequential labelling algorithm
and equivalence set. I was processing labels directly on the image struct through 
setPixel() rather than in an external data vector. setPixel() only takes ints 
up to 255, and then it starts again 1. So, equivalences happened between the wrong 
numbers (such as 255 and 1 rather than 255 and 256), leading to one large equivalent set. 

 When I switched to an external storage grid for processing it worked fine. 
