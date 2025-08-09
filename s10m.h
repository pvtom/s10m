#ifndef __S10M_H_
#define __S10M_H_

#define CONFIG_FILE     ".config"

#define MODBUS_REG      40000
#define MODBUS_1_NR     125
#define MODBUS_1_OFFSET 0
#define MODBUS_2_NR     34
#define MODBUS_2_OFFSET 1000
#define REGISTER_41000  MODBUS_1_NR

#define BUFFER_SIZE     32
#define TOPIC_SIZE      128

#define F_UINT16        0
#define F_UINT16_01     1
#define F_UINT16_001    2
#define F_INT16         3
#define F_INT16_01      4
#define F_INT16_001     5
#define F_UINT32        6
#define F_INT32         7

static void publish(char *topic, char *payload);
static void publish_number_if(int16_t *reg, int16_t *old, int format, int r, char *topic);
static void publish_string_if_changed(int16_t *reg, char *lst_value, int r, int length, char *topic);
static void publish_boolean(int16_t *reg, int r, int bit, int b, char *topic);

typedef struct _pool_t {
    int reg;
    int format;
    char topic[TOPIC_SIZE];
} pool_t;

pool_t pool[] = {
    { 83, F_UINT16, "battery/soc" },
    { 70, F_INT32, "battery/power" },
    { 74, F_INT32, "grid/power" },
    { 106, F_INT16, "grid/power/L1" },
    { 107, F_INT16, "grid/power/L2" },
    { 108, F_INT16, "grid/power/L3" },
    { 72, F_UINT32, "home/power" },
    { 76, F_UINT32, "addon/power" },
    { 68, F_UINT32, "solar/power" },
    { 99, F_UINT16_001, "current/string_1" },
    { 100, F_UINT16_001, "current/string_2" },
    { 102, F_UINT16, "power/string_1" },
    { 103, F_UINT16, "power/string_2" },
    { 96, F_UINT16, "voltage/string_1" },
    { 97, F_UINT16, "voltage/string_2" },
    { 137, F_UINT16, "sg_ready/status" },
    { 186, F_UINT16, "grid/limit_power" },
    { 188, F_UINT16, "power/ready" },
    { REGISTER_41000 + 0, F_INT16, "pvi/apparent_power/L1" },
    { REGISTER_41000 + 2, F_INT16, "pvi/apparent_power/L2" },
    { REGISTER_41000 + 4, F_INT16, "pvi/apparent_power/L3" },
    { REGISTER_41000 + 6, F_INT16, "pvi/active_power/L1" },
    { REGISTER_41000 + 8, F_INT16, "pvi/active_power/L2" },
    { REGISTER_41000 + 10, F_INT16, "pvi/active_power/L3" },
    { REGISTER_41000 + 12, F_INT16, "pvi/reactive_power/L1" },
    { REGISTER_41000 + 14, F_INT16, "pvi/reactive_power/L2" },
    { REGISTER_41000 + 16, F_INT16, "pvi/reactive_power/L3" },
    { REGISTER_41000 + 18, F_INT16_01, "pvi/voltage/L1" },
    { REGISTER_41000 + 19, F_INT16_01, "pvi/voltage/L2" },
    { REGISTER_41000 + 20, F_INT16_01, "pvi/voltage/L3" },
    { REGISTER_41000 + 21, F_INT16_001, "pvi/current/L1" },
    { REGISTER_41000 + 22, F_INT16_001, "pvi/current/L2" },
    { REGISTER_41000 + 23, F_INT16_001, "pvi/current/L3" },
    { REGISTER_41000 + 24, F_INT16_001, "grid/frequency" },
    { REGISTER_41000 + 25, F_UINT16, "pvi/power/string_1" },
    { REGISTER_41000 + 26, F_UINT16, "pvi/power/string_2" },
    { REGISTER_41000 + 28, F_INT16_01, "pvi/voltage/string_1" },
    { REGISTER_41000 + 29, F_INT16_01, "pvi/voltage/string_2" },
    { REGISTER_41000 + 31, F_INT16_001, "pvi/current/string_1" },
    { REGISTER_41000 + 32, F_INT16_001, "pvi/current/string_2" }
};

#endif
