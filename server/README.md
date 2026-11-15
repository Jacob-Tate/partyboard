# Party Board relay server

Relays controller input between Party Board players for online play. It never runs game code:
each frame it collects every human player's controller state, then sends the bundle to everyone
in the room (lockstep). It also compares periodic checksums from each player and ends the game if
anyone drifts out of sync.

- Protocol: [`include/netplay/protocol.h`](../include/netplay/protocol.h), shared with the game
- Transport: [ENet](http://enet.bespin.org/) over UDP, default port **7845**
- Rooms: 4-letter codes, up to 4 players, all on the same Party Board build
- A player who drops is replaced by a CPU. If they join the same code again, the server seats them
  on a CPU's seat (their own, matched by name) and flags the frames; at the next save point every player's game sends
  its board state and restarts, rejoins the room by name, and the server starts the game again from
  that state by itself (or after 60 seconds with whoever is back). Rooms survive that restart.

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

## Docker Swarm / Portainer

[`portainer-stack.yml`](portainer-stack.yml) runs one instance pinned to a labelled node, with the
UDP port published in host mode.

1. Label the node players will connect to (from a manager):
   `docker node update --label-add partyboard=true <node-name>`
2. Portainer: **Stacks > Add stack**, paste the file (or point **Repository** at
   `server/portainer-stack.yml` on the `netplay` branch), **Deploy the stack**.
3. Open UDP 7845 on that node. Players connect to that node's address.

To update: open the stack in Portainer, **Update the stack** with **Re-pull image** enabled.
Check it from the node: `docker exec $(docker ps -qf name=partyboard_relay) partyboard-server-test 127.0.0.1 7845`
(replace `partyboard` with your stack name).

Keep `replicas: 1`: rooms live in memory, so a second instance would split players between them.

## Build the image yourself

From the repository root:
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
