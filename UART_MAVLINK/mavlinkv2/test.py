from pymavlink import mavutil

# Kết nối với cổng COM của STM32 (hoặc cổng ảo USB-TTL)
master = mavutil.mavlink_connection('COM20', baud=115200)

# Đợi heartbeat
master.wait_heartbeat()

# Gửi COMMAND_LONG để ARM
master.mav.command_long_send(
    target_system=1,
    target_component=1,
    command=400,   # MAV_CMD_COMPONENT_ARM_DISARM
    confirmation=0,
    param1=0, param2=2, param3=0,
    param4=0, param5=0, param6=0, param7=0
)

print("Đã gửi lệnh ARM đến system 1")