# s10m - E3/DC S10 Modbus to MQTT Connector
[![GitHub sourcecode](https://img.shields.io/badge/Source-GitHub-green)](https://github.com/pvtom/s10m/)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/pvtom/s10m)](https://github.com/pvtom/s10m/releases/latest)
[![GitHub last commit](https://img.shields.io/github/last-commit/pvtom/s10m)](https://github.com/pvtom/s10m/commits)
[![GitHub issues](https://img.shields.io/github/issues/pvtom/s10m)](https://github.com/pvtom/s10m/issues)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/pvtom/s10m)](https://github.com/pvtom/s10m/pulls)
[![GitHub](https://img.shields.io/github/license/pvtom/s10m)](https://github.com/pvtom/s10m/blob/main/LICENSE)

This software module connects a home power station from E3/DC to an MQTT broker. It uses the Modbus interface of the S10 device.

Developed and tested with a Raspberry Pi and a Linux PC (x86_64).

The tool s10m queries the data from the home power station and sends it to the MQTT broker. The following topics are supported:

- s10/addon/power
- s10/autarky
- s10/battery/charging/lock
- s10/battery/discharging/lock
- s10/battery/power
- s10/battery/soc
- s10/battery/state
- s10/battery/weather_regulation
- s10/consumption
- s10/current/string_1
- s10/current/string_2
- s10/emergency/mode
- s10/emergency/ready
- s10/firmware
- s10/grid/frequency
- s10/grid/limit
- s10/grid/limit_power
- s10/grid/power
- s10/grid/power/L1
- s10/grid/power/L2
- s10/grid/power/L3
- s10/grid/state
- s10/home/power
- s10/idle_period/charging/active
- s10/idle_period/discharging/active
- s10/manufacturer
- s10/model
- s10/power/ready
- s10/power/string_1
- s10/power/string_2
- s10/pvi/active_power/L1
- s10/pvi/active_power/L2
- s10/pvi/active_power/L3
- s10/pvi/apparent_power/L1
- s10/pvi/apparent_power/L2
- s10/pvi/apparent_power/L3
- s10/pvi/current/L1
- s10/pvi/current/L2
- s10/pvi/current/L3
- s10/pvi/current/string_1
- s10/pvi/current/string_2
- s10/pvi/power/string_1
- s10/pvi/power/string_2
- s10/pvi/reactive_power/L1
- s10/pvi/reactive_power/L2
- s10/pvi/reactive_power/L3
- s10/pvi/voltage/L1
- s10/pvi/voltage/L2
- s10/pvi/voltage/L3
- s10/pvi/voltage/string_1
- s10/pvi/voltage/string_2
- s10/serial_number
- s10/sg_ready/status
- s10/solar/power
- s10/voltage/string_1
- s10/voltage/string_2

If one or more E3/DC wallboxes are available:

- s10/wallbox/[0-7]/available
- s10/wallbox/[0-7]/sun_mode
- s10/wallbox/[0-7]/ready
- s10/wallbox/[0-7]/charging
- s10/wallbox/[0-7]/1phase
- s10/wallbox/total/power
- s10/wallbox/solar/power

Write register:

```
mosquitto_pub -h localhost -t s10/set/register/40088 -m "0"
```
This function depends on the E3/DC software version and has not been sufficiently tested.
Please take the register definitions in the E3DC Modbus documentation.

The prefix of the topics can be configured by the attribute ROOT_TOPIC. By default all topics start with "s10". This can be changed to any other string that MQTT accepts as a topic.

## Docker

Instead of installing the package you can use the [Docker image](DOCKER.md).

## Local installation
### Prerequisites

- S10 configuration: Switch on the Modbus interface (mode E3/DC, not Sunspec)
- An existing MQTT broker in your environment, e.g. a Mosquitto (https://mosquitto.org)
- s10m needs the library libmosquitto. To install it on a Raspberry Pi enter:

```
sudo apt-get install -y build-essential git automake autoconf libtool libmosquitto-dev
```
- s10m connects the S10 via the Modbus protocol, so you have to install a Modbus library:
```
git clone https://github.com/stephane/libmodbus.git
cd libmodbus/
./autogen.sh
./configure
sudo make install
```

### Cloning the Repository

```
sudo apt-get install git # if necessary
git clone https://github.com/pvtom/s10m.git
```

### Compilation

```
cd s10m
make
```

### Installation

```
sudo mkdir -p /opt/s10m
sudo chown pi:pi /opt/s10m/
```
Adjust user and group (pi:pi) if you use another user.

```
cp -a s10m /opt/s10m
```

### Configuration

Configuration can also be set via environment variables. This simplifies the start of a Docker container, as no .config file is required. The environment variables correspond to the names in config.template.

If you use both, the environment variables overwrite the parameters set with .config!

Copy the config template file into the directory `/opt/s10m`
```
cp config.template /opt/s10m/.config
```

Please change to the directory `/opt/s10m` and edit `.config` to adjust to your configuration:

```
cd /opt/s10m
nano .config
```

### Test

Start the program:

```
./s10m
```

Check the configuration if the connections are not established.

If you use the Mosquitto tools you can subscribe the topics with

```
mosquitto_sub -h localhost -p 1883 -t 's10/#' -v
```

Stop s10m with Crtl-C and start it in the background.

### Daemon Mode

Start the program in daemon mode:

```
./s10m -d
```

If you like to start s10m during the system start, use `/etc/rc.local`. Add the following line before `exit 0`.

```
(cd /opt/s10m ; /usr/bin/sudo -H -u pi /opt/s10m/s10m -d)
```
Adjust the user (pi) if you use another user.

The daemon can be terminated with
```
pkill s10m
```
Be careful that the program runs only once.

### Systemd

Alternatively, s10m can be managed by systemd. To do this, copy the file `s10m.service` to the systemd directory:
```
sudo cp -a s10m.service /etc/systemd/system/
```
Configure the service `sudo nano s10m.service` (adjust user 'User=pi'), if needed.

Register the service and start it with:
```
sudo systemctl start s10m
sudo systemctl enable s10m
```

## Used external libraries

- Eclipse Mosquitto (https://github.com/eclipse/mosquitto)
- Modbus library (https://github.com/stephane/libmodbus)
