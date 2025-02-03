You can use this component by adding this line to your ESPHome project yaml:
```yaml
external_components:
  - source: github://soldierkam/vl53l1x_sensor
    refresh: 1s
```

Sensor configuration:
```yaml
i2c:
  - id: bus_a
    sda: GPIO8
    scl: GPIO9
    frequency: 400kHz # higher data rates helps to decrease time spend on read/write operations (should eliminate "component took a long time for an operation" warning)

sensor:
  - platform: vl53l1x_sensor
    id: distance_sensor
    name: Test sensor
    enable_pin: GPIO10 # connected to XSHUT
    distance_mode: MEDIUM # LOW (up to 1.3m, better ambient immunity), MEDIUM (up to 3m), HIGH (up to 4 m, maximum distance) 
    timing_budget: 200ms # time required by the sensor to perform one range measurement
    signal_threshold: 512
    update_interval: 1s
    address: 0x32
    accuracy_decimals: 2
```
