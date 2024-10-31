This is a sinple exaple that uses [minifb](https://github.com/emoon/minifb), [miniaudio](https://miniaud.io/), and [pntr](https://github.com/RobLoach/pntr).

The idea here is a very small app-frame that is cross-platform, and works on web, that uses streaming audio (with a callback.)

I am using [xmake](https://xmake.io/).

```
# set platform to wasm
xmake config -p wasm

# set platform to native (if you build for wasm)
xmake config -p macosx/windows/linux

# build for current platform
xmake
```