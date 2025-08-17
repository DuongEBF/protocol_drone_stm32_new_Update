#ifndef CANARD_BUILD_CONFIG_H
#define CANARD_BUILD_CONFIG_H

// Dùng static buffer thay malloc
#define CANARD_MALLOC(x) my_custom_alloc(x)
#define CANARD_FREE(x)   my_custom_free(x)

// Giới hạn số frame gửi
#define CANARD_TX_QUEUE_CAPACITY 10

// Kích thước buffer tối đa
#define CANARD_MTU 64  // Cho CAN FD nếu dùng UAVCAN v1

#endif // CANARD_BUILD_CONFIG_H
