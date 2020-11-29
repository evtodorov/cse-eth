import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as an


dat = np.genfromtxt('store.dat');
x = dat[::2]
y = dat[1::2]

dat2 = np.genfromtxt('store2.dat');
x2 = dat2[::2]
y2 = dat2[1::2]

dat3 = np.genfromtxt('store_mpi_rank_0.dat');
x3 = dat3[::2]
y3 = dat3[1::2]


fig, ax = plt.subplots()

points, = ax.plot(x[0],y[0],'k.')
points2, = ax.plot(x2[0],y2[0],'r.')
points3, = ax.plot(x3[0],y3[0],'b.')
ax.set_xlim([-1,1])
ax.set_ylim([-1,1])
def animate(i):
    points.set_xdata(x[i])
    points.set_ydata(y[i])
    points2.set_xdata(x2[i])
    points2.set_ydata(y2[i])
    points3.set_xdata(x3[i])
    points3.set_ydata(y3[i])
    return points,

ani = an.FuncAnimation(fig,animate,np.arange(1,len(x)), interval = 100)

plt.show()
