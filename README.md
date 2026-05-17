# Aphids and Ladybugs

This is a small C++17 simulation of aphids and ladybugs moving around
on a board and interacting with each other.

## Layout

The `src/` folder contains the source files, the original Makefile,
and the configuration files that determine aphid, ladybug, and board
attributes. The `inc/` folder contains the header files.

## Build

Run `make` from the repository root to build the project. The build
delegates to `src/Makefile` and creates `src/aphids_and_ladybugs`.

## Run

Run `make run` from the repository root. This runs the executable from
`src/` so the simulation can find `board.conf`, `aphid.conf`, and
`ladybug.conf`.

## Clean

Run `make clean` to remove object files and the executable.
