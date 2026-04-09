The software concept is to help manage an airline’s fleet for average fuel consumption.

While a plane is
flying, the onboard systems (the client) communicate in real-time with the ground-based software (the
server).

Each plane in the fleet will have a unique ID and provide several parameters of data, including
time and gallons of fuel remaining. Your system is to monitor, collect and maintain a record of the flight(s)
and calculate the average fuel consumption, in real-time, over the length of the flight and all future flights
for that airplane.


### Client
Port, IP, and Telemetry directory can be specified via command line arguments
```sh
.\Client.exe --port=5555 --ip=127.0.0.1 --dir=../../Client/data/
```
