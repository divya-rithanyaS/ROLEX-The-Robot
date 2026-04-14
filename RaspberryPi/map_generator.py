import csv
import matplotlib.pyplot as plt

x, y = 0, 0
direction = 0  # 0=N,1=E,2=S,3=W

xs, ys = [], []
hazards, motions, cliffs = [], [], []

with open("rolex_log.csv") as f:

    reader = csv.DictReader(f)

    for row in reader:

        gas = float(row["gas"])
        distance = float(row["distance"])
        motion = int(row["motion_front"]) or int(row["motion_back"])
        cliff = int(row["cliff"])

        step = 1

        if direction == 0: y += step
        elif direction == 1: x += step
        elif direction == 2: y -= step
        elif direction == 3: x -= step

        xs.append(x)
        ys.append(y)

        if gas > 400:
            hazards.append((x,y))

        if motion:
            motions.append((x,y))

        if cliff:
            cliffs.append((x,y))

        if distance < 20 and distance != 0:
            direction = (direction + 1) % 4

# -------- PLOT --------

plt.figure(figsize=(8,8))
plt.plot(xs, ys, 'b-', linewidth=2, label="Path")

if hazards:
    hx, hy = zip(*hazards)
    plt.scatter(hx, hy, c='red', label="Hazard")

if motions:
    mx, my = zip(*motions)
    plt.scatter(mx, my, c='green', label="Motion")

if cliffs:
    cx, cy = zip(*cliffs)
    plt.scatter(cx, cy, c='black', label="Cliff")

plt.title("ROLEX Blueprint Map")
plt.legend()
plt.grid()

plt.savefig("rolex_map.png")
plt.show()
