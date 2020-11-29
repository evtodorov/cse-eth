import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as an


dat = np.genfromtxt('store.dat');
x = dat[::2]
y = dat[1::2]

fig, ax = plt.subplots()

points, = ax.plot(x[0],y[0],'k.')
ax.set_xlim([-1,1])
ax.set_ylim([-1,1])
def animate(i):
    points.set_xdata(x[i])
    points.set_ydata(y[i])
    return points,

ani = an.FuncAnimation(fig,animate,np.arange(1,len(x)), interval = 100)

plt.show()
