# Party Board relay server

Relays controller input between Party Board players for online play. It never runs game code:
each frame it collects every human player's controller state, then sends the bundle to everyone
in the room (lockstep). It also compares periodic checksums from each player and ends the game if
anyone drifts out of sync.

- Protocol: [`include/netplay/protocol.h`](../include/netplay/protocol.h), shared with the game
- Transport: [ENet](http://enet.bespin.org/) over UDP, default port **7845**
- Rooms: 4-letter codes, up to 4 players, all on the same Party Board build

## Run with Docker

Every push to the `netplay` branch that passes the integration test publishes
`ghcr.io/jacob-tate/partyboard-server` (tags: `latest` and the short commit hash).

```sh
docker run -d --name partyboard-server --restart unless-stopped -p 7845:7845/udp \
    ghcr.io/jacob-tate/partyboard-server:latest
docker logs -f partyboard-server
```

Update to the newest build:

```sh
docker pull ghcr.io/jacob-tate/partyboard-server:latest
docker rm -f partyboard-server
docker run -d --name partyboard-server --restart unless-stopped -p 7845:7845/udp \
    ghcr.io/jacob-tate/partyboard-server:latest
```

To build the image yourself instead, from the repository root:
`docker build -f server/Dockerfile -t partyboard-server .`

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
