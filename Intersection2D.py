# -*- coding: utf-8 -*-
"""
Created on Mon Sep 14 11:11:40 2020

@author: thanh
"""

import FPSynDivLib as FPSDiv
import FPSynLib as FPS
import copy
import math
from sympy import *
import itertools
import random

x, y, z, t, m,n,eps = symbols('x y z t m n eps')
x1,x2,x3,x4,y1,y2,y3,y4 =symbols('x1 x2 x3 x4 y1 y2 y3 y4 ')
num=(x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4)
den=(x1-x2)*(y3-y4)-(y1-y2)*(x3-x4)

##Running---------------------------###



p=FPSDiv.FPSynthesisDiv(num,den,"Intersection2D")
#p=FPS.FPSynthesis(num,"Intersection2D")
