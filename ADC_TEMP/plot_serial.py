import serial
import matplotlib.pyplot as plt
from collections import deque

# Cấu hình serial
ser = serial.Serial('COM20', 115200, timeout=1)  # Cập nhật COM port của bạn
ser.flush()

# Dữ liệu buffer (cuối 100 giá trị)
temp_data = deque(maxlen=100)
curr_data = deque(maxlen=100)
time_data = deque(maxlen=100)

# Khởi tạo plot
plt.ion()
fig, ax = plt.subplots()
line1, = ax.plot([], [], label='Temperature (°C)')
line2, = ax.plot([], [], label='Charging Current (mA)')
ax.set_ylim(0, 6000)
ax.set_xlim(0, 100)
ax.legend()

i = 0
while True:
    if ser.in_waiting:
        line = ser.readline().decode('utf-8').strip()
        if line.startswith("TEMP=") and "CURRENT=" in line:
            try:
                parts = line.split(';')
                temp = float(parts[0].split('=')[1])
                curr = int(parts[1].split('=')[1])

                temp_data.append(temp)
                curr_data.append(curr)
                time_data.append(i)

                line1.set_xdata(time_data)
                line1.set_ydata(temp_data)
                line2.set_xdata(time_data)
                line2.set_ydata(curr_data)
                ax.relim()
                ax.autoscale_view()
                plt.pause(0.01)
                i += 1
            except Exception as e:
                print("Parse error:", e)