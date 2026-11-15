# Party Board netplay relay server.
# Build from the repository root:
#   docker build -f server/Dockerfile -t partyboard-server .
# Run (UDP port 7845):
#   docker run -d --name partyboard-server --restart unless-stopped -p 7845:7845/udp partyboard-server

FROM debian:bookworm-slim AS build
RUN apt-get update \
    && apt-get install -y --no-install-recommends cmake g++ make git ca-certificates \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /src
COPY include/netplay include/netplay
COPY server server
RUN cmake -S server -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --parallel \
    && strip build/partyboard-server build/partyboard-server-test

FROM debian:bookworm-slim
# Links the ghcr.io package to the repository.
LABEL org.opencontainers.image.source="https://github.com/Jacob-Tate/partyboard" \
      org.opencontainers.image.description="Party Board netplay relay server" \
      org.opencontainers.image.licenses="CC0-1.0"
RUN useradd --system --no-create-home partyboard
COPY --from=build /src/build/partyboard-server /usr/local/bin/partyboard-server
# The integration test client ships too, so a deployment can be checked in place:
#   docker exec partyboard-server partyboard-server-test 127.0.0.1 7845
COPY --from=build /src/build/partyboard-server-test /usr/local/bin/partyboard-server-test
USER partyboard
EXPOSE 7845/udp
ENTRYPOINT ["partyboard-server"]
