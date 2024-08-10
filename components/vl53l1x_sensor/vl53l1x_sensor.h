#pragma once
#include <list>
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace vl53l1x {

enum DistanceMode { Short=1, Medium=2, Long=3 };

class VL53L1XSensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
    public:
    VL53L1XSensor();

    void setup() override;

    void update() override;
    void dump_config() override;

    void loop() override;

    void set_timeout_us(uint32_t timeout_us) { this->timeout_us_ = timeout_us; }
    void set_enable_pin(GPIOPin *enable) { this->enable_pin_ = enable; }
    void set_distance_mode(DistanceMode dm) { this->distance_mode_ = dm; };
    void set_timing_budget(uint32_t us) { this->timing_budget_us_ = us; };
    void set_signal_threshold(uint16_t signal) { this->signal_threshold_ = signal; };

    private:
    void setI2CAddress(uint8_t addr);
    void startRanging();
    void stopRanging();
    bool checkForDataReady();
    uint8_t getInterruptPolarity();
    void clearInterrupt();
    uint16_t sensorId();
    uint16_t readWord(uint16_t reg_idx);
    uint32_t calc_macro_period(uint8_t vcsel_period);
    uint16_t encode_timeout(uint32_t timeout_mclks);
    uint32_t timeout_microseconds_to_mclks(uint32_t timeout_us, uint32_t macro_period_us);
    void writeWord(uint16_t reg_idx, uint16_t data);

    int8_t getRangeStatus();
    int16_t distance();
    void set_distance_mode();
    void set_measurement_timing_budget();
    void set_signal_threshold();

    static std::list<VL53L1XSensor *> vl53_sensors;
    GPIOPin *enable_pin_{nullptr};
    GPIOPin *irq_pin_{nullptr};
    static bool enable_pin_setup_complete;
    uint16_t timeout_start_us_;
    uint16_t timeout_us_{};
    DistanceMode distance_mode_{Long};
    uint16_t timing_budget_us_{};
    uint16_t signal_threshold_{};
    uint8_t rangeStatus{};
};

} //namespace vl53l1x
} //namespace esphome
