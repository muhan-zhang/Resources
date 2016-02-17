#!/usr/bin/env python

import math
import re
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.font_manager as font_manager

mpl.rcParams['pdf.fonttype'] = 42 # Set font to TrueType (editable in Illustrator)

plt.rcParams['font.family'] = 'Helvetica'
#plt.rcParams['font.family'] = 'Museo Sans'
#plt.rc('font', serif='Museo Sans')
plt.rcParams['font.size'] = 7
plt.rcParams['figure.figsize'] = 3.375, 2.25
#plt.rcParams['figure.figsize'] = 6.75, 4.5


fig, ax = plt.subplots()
ax.spines['right'].set_visible(False)
#ax.spines['top'].set_visible(False)
ax.spines['top'].set_position('zero')

#ax = plt.gca()
#ax.get_yaxis().set_tick_params(direction='out')
#ax.get_xaxis().set_tick_params(direction='out')

AA = u"\u00C5"
plt.xlabel(r"r(H-H)/" + AA)
plt.ylabel("Energy/mHartree")

plt.tick_params(
    direction='out',
    axis='x',          # changes apply to the x-axis
    which='both',      # both major and minor ticks are affected
    bottom='on',       # ticks along the bottom edge are on
    top='off')         # ticks along the top edge are off

plt.tick_params(
    direction='out',
    axis='y',          # changes apply to the x-axis
    which='both',      # both major and minor ticks are affected
    left='on',         # ticks along the left edge are on
    right='off')       # ticks along the left edge are off

rgb_colors = [(  0, 78,139), # Dark blue
              (  0,130,183), # Blue
              ( 97,202,228), # Light blue
              (255,205, 65), # Dark yellow
              (225, 27, 46), # Reddish
              (  0,  0,  0), # Black
             ]

colors = []
for c in rgb_colors:
    colors.append(tuple([float(p) / 255.0 for p in c]))

x = []
y = []
for i in xrange(200):
    myx = float(i)/100.0
    x.append(myx)
    y.append(math.sin(myx * math.cos(myx)))

plt.plot(x,y,linewidth=1,color=colors[5],label='HF Energy')
#plt.legend(prop={'size':11})
plt.text(1.,.32,'Exact')
#plt.text(3.,-0.805,'DFT')
#plt.text(3.,-0.685,'Hartree-Fock')

#x1,x2,y1,y2 = plt.axis()
#plt.axis((0.75,3.0,-109.3,-108.9))
plt.tight_layout()  # Automagically figure out margins

plt.savefig('plot.pdf')

