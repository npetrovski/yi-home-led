## Led Control for Xiaomi's YI Home cameras

Simple LED (light-emitting diode) control interface on `cpld_periph` kernel module for YI Home camera 

Supported cams:
* 720p 47US

## Build

```sh
$ cd yi-home-led
$ make
```

### Usage
```sh
Usage: led <options>

Options:
        -b[fast|slow|pulse|on|off]  Blue led mode
        -y[fast|slow|on|off]        Yellow led mode
        -l[on|off]                  Light on/off

Example: led -bon -lon
```
