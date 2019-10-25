
# The Earth Light

Decompilation of KCE Japan West's "High Speed Robot Action" title *Zone of the Enders*.

## Overview

This project aims to construct a C/C++ language codebase that will compile working replacement code for PlayStation 2 and, if possible, match the original binary exactly.

New content not representative of the base games such as ports to new systems, enhancements, translations, etc. most likely will not be merged while the initial decompilation is ongoing. Please create a new fork of the project to do so. (This policy may be changed in the future.)

## Contributing

* Play Zone of the Enders.
* Have knowledge of C, C++, and MIPS assembly programming.
* Follow the style guide (after it's been written).
* Always restore original symbols wherever possible.

## List of Builds

See [docs/disc_id.md](docs/disc_id.md) for a list of commercially released builds.

See [docs/symtable.xlsx](docs/symtable.xlsx) for information on builds with debug symbols.

## Tools & Software

The following tools should prove useful.

#### Disassemblers

* IDA Pro 7.0
* [Ghidra](https://ghidra-sre.org/)

#### Toolchains & Libraries

PlayStation 2 Programmer Tool:
* [DTL-S12010] Runtime Library Release 2.0
* [DTL-S13010] SCE Development Tool Chain Release 2.0

All known builds of the game were created using Release 2.0.

#### Custom Tools

See: [Vivid Transparency (Factory)](https://github.com/Joy-Division/VividTransparency)

## Links & Discussion

* [Joy Division on GitHub](https://github.com/Joy-Division)
* [Joy Division on Discord](https://discord.gg/UtNEjtg)
