# BFME 1 Source Code
<img width="1000" height="125" alt="image" src="https://github.com/user-attachments/assets/d4ac956a-5221-42a6-aaf0-b0c0e41f6b8a" />

Reverse engineered with AI.

Goal: source code that rebuilds BFME 1's executable byte-for-byte.

## What?

* If you take a part of the BFME binary, recreate the exact source code that would make that part of the binary, then compile the source code and inject it into the binary, you get the same binary
* Doing this piece by piece will eventually give you a full, open source recreation of BFME, and enable some (insane) mods
* The goal of this project _is not_ to mod the game. The point of the project is to get source code that can be compiled into a 1:1, bit by bit replica of BFME 1's binary. This ensures 100% accuracy and will enable future (insane) modifications

## Status

We currently have C++ functions in `Code/` and a patcher which can patch same-size custom functions into `lotrbfme.exe`. This is useful for modding.

The number that matters is how much of the game we hold as source. **11.38% of the game's
real code** rebuilds from source we have and can edit: C++ we wrote from the disassembly,
plus vendored library source we compile. (A quarter of `.text` is linker padding nobody has
to write, and it is left out of that denominator.)

`reverse/functions.csv` claims a lot more than that, and the rest is not recovered source:

* **8.17%** is C++ a generator wrote — exception funclets, small thunks, template grids. It
  compiles and the bytes are exact, but a script produced it, so it is not recovery.
* **8.53%** is prebuilt libraries we attach, like `d3dx9.lib`. They link, so we never have
  to write them, but their source is not in the tree.
* **56.44%** is byte-true dumps of retail. A dump pins where a function starts and ends,
  and that is all it does. Turning one into C++ is the work.

Add those up and `python3 tools/progress.py` prints **84.53%** as *Total exact*. That is how
much of the image has a fixed boundary, not how much we recovered. Quote the first number.

Every row in `reverse/functions.csv` compiles or assembles to bytes identical to retail.
Converting a dump into real C++ is the contribution, and it is the only thing that moves
the first number.

## Roadmap

* [ ] BFME 1 Source Code (11.38% held as source; 84.53% byte-exact counting dumps and libraries)
* [ ] Network delay fix
* [ ] Memory fix
* [ ] Better crash logs
* [ ] 60/120 FPS
* [ ] Multi CPU
* [ ] AC fix
* [ ] World builder Source Code
* [ ] 16 player maps

ping `redbracket` on Discord if there's something else you want to change this roadmap

## How You Can Help

Clone the repo and give your AI agent this exact prompt — measured on six agent
sessions, a vaguer prompt reliably produces zero progress:

> Read AGENTS.md and follow it. Loop: take the served candidate's whole file,
> convert bodies to byte-exact C++, bank each verified body as its own commit,
> and before stopping run `python3 tools/progress.py origin/master` — if C++
> exact is +0 bytes, keep going. Make a PR when you have a few landed bodies.

Each commit in the PR is one verified function, and I will be able to merge it.

!! All such AI-generated PRs are appreciated !!

## Build

The MSVC 7.1 toolchain and baseline executables are committed directly (plain git, no LFS), so a normal `git clone` gets everything. Then:

```bash
./tools/setup_hooks.sh   # enable the pre-commit byte-check (git won't do this from a clone)
./build.sh               # verify every tracked function against retail   (.\build.ps1 on Windows)
```

To check a single function while iterating, pass its file or name — a few seconds instead of the full run:

```bash
./build.sh Code/Libraries/Source/WWVegas/WWMath/color.cpp
```
