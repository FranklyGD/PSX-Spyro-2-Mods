# Spyro 2: Ripto's Rage
This repository is an ongoing decompilation/modding project for the PSX game Spyro 2: Ripto's Rage. To discuss about Spyro hacking, join our Discord: [![Discord](https://img.shields.io/badge/chat-Discord-blue)](https://discord.gg/6B7kGtfaaS)

## Setup
This project is meant to be used as a submodule of the psx modding toolchain. To get started, clone the [toolchain repo](https://github.com/mateusfavarin/psx-modding-toolchain), follow the instructions in their [README](https://github.com/mateusfavarin/psx-modding-toolchain/blob/main/README.md), and then go to the directory `psx-modding-toolchain/games/` and clone the `Spyro2` repo there.

## Strategy
This project will adopt the [Ship of Theseus](https://en.wikipedia.org/wiki/Ship_of_Theseus) strategy. By taking advantage of [PCSX-Redux](https://github.com/grumpycoders/pcsx-redux/) 8MB memory expansion, we can re-write game functions and load them in memory, while the original game stays intact. Then, we can force the game to call each function we re-wrote, and compare the output of the decompiled function with the original game function.