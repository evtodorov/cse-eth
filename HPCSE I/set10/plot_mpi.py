import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as an

number_of_processes = 4 if len(sys.argv) < 2 else int(sys.argv[1])

dats = []

for i in xrange(number_of_processes):
    dat = np.genfromtxt('store_mpi_rank_'+str(i)+'.dat')
    dats.append(dat)

dat = np.concatenate(dats,1)
x = dat[::2]
y = dat[1::2]

dat2 = np.genfromtxt('store_serial.dat')
x2 = dat2[::2]
y2 = dat2[1::2]
fig, ax = plt.subplots()

points, = ax.plot(x[0],y[0],'k.')
points2, = ax.plot(x2[0],y2[0],'g.')
ax.set_xlim([-1,1])
ax.set_ylim([-1,1])
def animate(i):
    points.set_xdata(x[i])
    points.set_ydata(y[i])
    points2.set_xdata(x2[i])
    points2.set_ydata(y2[i])
    return points,

ani = an.FuncAnimation(fig,animate,np.arange(0,len(x)), interval = 100)

plt.show()

