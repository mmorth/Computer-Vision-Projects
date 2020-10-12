x = 0:.1:2
aprx2 = 1 - x.^2/2
er = aprx2 - cos(x)
errorbar(x, aprx2, er)