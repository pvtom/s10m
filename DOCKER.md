## Docker

A Docker image is available at https://hub.docker.com/r/pvtom/s10m

### Start the docker container

```
docker run --rm -e MODBUS_HOST=your_e3dc_device -e MQTT_HOST=your_mqtt_broker pvtom/s10m:latest
```

Or create a `.config` file as described in the [Readme](README.md) and start with
```
docker run --rm -v /path/to/your/.config:/app/.config pvtom/s10m:latest
```

Thanks to [felix1507](https://github.com/felix1507/s10m-docker) for developing the Dockerfile!
