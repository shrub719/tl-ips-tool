# Tomodachi Life (3DS) IPS Tool

A command line tool for inspecting IPS files for Tomodachi Life 3DS.

## Usage

```tl-ips-tool code.ips```

It's as easy as that! The tool will output each hunk with its offset, length
and payload. Write to a file with `>`, and then copy/paste it into 
[your favourite ARM32 disassembler](https://ret.futo.org/arm32/), 
making sure that the start of the instructions are aligned with a multiple of 4.

