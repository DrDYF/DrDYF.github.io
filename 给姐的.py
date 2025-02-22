import numpy as n
import matplotlib.pyplot as p
import matplotlib.animation as a
t=n.linspace(0,2*n.pi,1000)
x=16*n.sin(t)**3
y=13*n.cos(t)-5*n.cos(2*t)-2*n.cos(3*t)-n.cos(4*t)
F,A=p.subplots()
A.set(xlim=(-20,20),ylim=(-20,15),aspect='equal')
A.axis('off')
XT,=A.fill(x,y,color='deepskyblue',alpha=1)
DYF,=A.fill(0.6*x,0.6*y,color='yellow',alpha=0.1)
We=A.fill(0.3*x+15,0.3*y-10,color='red',alpha=0.5)[0]
Bless,me="Sis Tian, Happy Birthday!","FanFan"
Colors=['red','darkorange','orange','gold','yellow','yellowgreen','green','mediumseagreen','cyan','skyblue','deepskyblue','dodgerblue','blue','mediumblue','darkblue','navy','indigo','violet','purple','plum','orchid','mediumorchid','darkviolet','fuchsia','magenta','pink','lightpink','lightcoral','salmon','sandybrown']
Happy=[A.text(-len(Bless)*0.6+i*1.2+0.75,1.5,c,fontsize=12,ha='center',va='center')for i,c in enumerate(Bless)]
ME=[A.text(-len(me)*0.6+i*1.3+16,-10,c,fontsize=12,ha='right',va='center')for i,c in enumerate(me)]
def Love(f):
    Si=n.sin(f/10)
    S=0.2+0.05*Si
    We.set_xy(n.column_stack((S*x+15,S*y-10)))
    XT.set_alpha(0.5+0.5*Si)
    DYF.set_alpha(0.1-0.1*Si)
    for i,T in enumerate(Happy):
        Yo=1.5-0.5*n.sin(f/5+i*0.3)
        T.set_position((-len(Bless)*0.6+i*1.2+Yo,Yo))
    for i,T in enumerate(ME):
        T.set_position((-len(me)*0.6+i*1.3+16+0.5*n.cos(f/5+i*0.3),-10+0.5*n.sin(f/5+i*0.3)))
    for i,T in enumerate(Happy+ME):
        T.set_color(Colors[(f+i)%len(Colors)])
    return [XT,DYF,We]+Happy+ME
Dream=a.FuncAnimation(F,Love,frames=519115,blit=True,interval=30)
p.show()