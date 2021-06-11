This is just a quick test I threw together for testing ternarylogic
implementations for SIMDe.  I didn't really intend to publish it so
it's a complete mess, and could rather easily be *significantly*
improved (e.g., using a Makefile instead of a shell script so
compilation could be done in parallel).

I'll try to keep
[this spreadsheet](https://docs.google.com/spreadsheets/d/1yW-HyztA96har0rkFWdSAoO3IMOmgMBS5rD1vZ_wupU/edit?usp=sharing)
up to date with this repo; it's just the CSV output from these
copied and pasted into a spreadsheet.

Some of the source code contains hardcoded paths to where I have my
development version of SIMDe, so you'll have to change that.

Mula is the version from [WojciechMula/ternary-logic](https://github.com/WojciechMula/ternary-logic).
rosbif and rosbif2 are versions @rosbif is working on.  autovec
is what @simba611 has in his PR right now, which is basically a scalar
version of mula called in a loop which the compiler then
autovectorizes.

