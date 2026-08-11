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

The number that matters is **byte-exact C++**: about **13.5% of `.text`**, which is
**~18% of the game's real code** (a quarter of `.text` is linker `int3` padding that
needs no source and is excluded from the honest denominator). A further ~6% is
byte-verified assembly awaiting conversion. Every row in `reverse/functions.csv`
compiles or assembles to bytes identical to retail; `python3 tools/progress.py <ref>`
prints the current split. The pipeline: scripts claim unidentified functions as
byte-true ASM dumps, and agents convert ASM to exact C++ — conversion is the
contribution.

## Roadmap

* [ ] BFME 1 Source Code (~8% done)
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

Baseline executables and the MSVC 7.1 toolchain are committed directly in the repo (plain git, no LFS) — a normal `git clone` gets everything. After cloning, run:

```bash
./tools/setup_hooks.sh
```

Git does not auto-enable versioned hooks from a clone. `setup_hooks.sh` points this checkout at the
tracked pre-commit hook, which rejects new source functions unless they are listed in
`reverse/functions.csv` and pass the byte comparison.

```bash
./build.sh
# (or on Windows)
# .\build.ps1
```

The build verifies the baseline, byte-compares tracked source against the original executable, and checks that a no-op patched copy hashes identically. While iterating on one function, verify just its source in a few seconds by passing in the path:

```bash
./build.sh Code/Libraries/Source/WWVegas/WWMath/color.cpp   # or a function name
```
