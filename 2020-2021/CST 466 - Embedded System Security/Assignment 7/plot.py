import matplotlib.pyplot as plt

traces = [1,5,10,20,30,40,50,60,70,80,90,100]
correct_subkeys = [0,0,0,7,9,13,14,14,15,15,15,16]

plt.plot(traces, correct_subkeys)
plt.axis([0,100,0,16])
plt.ylabel("Correct subkeys")
plt.xlabel("Traces")
plt.show()