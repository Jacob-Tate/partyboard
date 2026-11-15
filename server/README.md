# Party Board relay server

Relays controller input between Party Board players for online play. It never runs game code:
each frame it collects every human player's controller state, then sends the bundle to everyone
in the room (lockstep). It also compares periodic checksums from each player and ends the game if
anyone drifts out of sync.

- Protocol: [`include/netplay/protocol.h`](../include/netplay/protocol.h), shared with the game
- Transport: [ENet](http://enet.bespin.org/) over UDP, default port **7845**
- Rooms: 4-letter codes, up to 4 players, all on the same Party Board build

## Run with Docker

From the repository root:

```sh
docker build -f server/Dockerfile -t partyboard-server .
docker run -d --name partyboard-server --restart unless-stopped -p 7845:7845/udp partyboard-server
docker logs -f partyboard-server
```

Open **UDP** port 7845 on the host's firewall (and forward it on the router if the host is at home).
To use another port: `-p 9000:9000/udp -e PB_SERVER_PORT=9000`.

Check a running deployment with the bundled test client (two fake players, ~1 second):

```sh
docker exec partyboard-server partyboard-server-test 127.0.0.1 7845
```

## Build without Docker

```sh
cmake -S server -B build/server -DCMAKE_BUILD_TYPE=Release
cmake --build build/server
build/server/partyboard-server --port 7845
```

ENet is downloaded automatically during configure.
