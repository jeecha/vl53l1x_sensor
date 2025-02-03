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
    # Higher data rates reduce the time required for read/write operations, which
    # should prevent the "component took a long time for an operation" warning in the logs.
    frequency: 400kHz 

sensor:
  - platform: vl53l1x_sensor
    id: distance_sensor
    name: Test sensor
    enable_pin: GPIO10 # connected to XSHUT
    distance_mode: MEDIUM # LOW (up to 1.3m, better ambient immunity), MEDIUM (up to 3m), HIGH (up to 4 m, maximum distance)
    # Time required by the sensor to perform one range measurement.
    # If fast response time is critical (e.g., obstacle avoidance in robots), use 20ms-33ms.
    # For general-purpose use, 50ms-100ms provides a good balance. For high accuracy at long distances, use 200ms-500ms.
    timing_budget: 200ms
    # Signal threashold recomendations:
    # - Use a low threshold (500-1000 kcps) if detecting dark or distant objects.
    # - Use a medium threshold (1000-2000 kcps) for most applications.
    # - Use a high threshold (2000+ kcps) for precise distance measurement with strong signals.
    signal_threshold: 512
    update_interval: 1s
    address: 0x32
    accuracy_decimals: 2
```
