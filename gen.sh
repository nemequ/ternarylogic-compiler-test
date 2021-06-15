#!/bin/bash

#SIMDE_HOME=/home/nemequ/local/src/simde
SIMDE_HOME=/home/cmoore/Downloads/simde

if [ -e data.db ]; then
    echo "data.db exists!"
    exit 1
fi
sqlite3 data.db < create_db.sql

function parse_mca () {
    COMPILER="$1"
    VERSION="$2"
    IMM8=$3
    COMPILE_TIME="$(cat time.res)"
    TOTAL_CYCLES="$(grep -P '^(Total Cycles:).+' llvm-mca.txt | cut -b20-)"
    DISPATCH_WIDTH="$(grep -P '^(Dispatch Width:).+' llvm-mca.txt | cut -b20-)"
    UOPS_PER_CYCLE="$(grep -P '^(uOps Per Cycle:).+' llvm-mca.txt | cut -b20-)"
    IPC="$(grep -P '^(IPC:).+' llvm-mca.txt | cut -b20-)"
    BLOCK_RTHROUGHPUT="$(grep -P '^(Block RThroughput:).+' llvm-mca.txt | cut -b20-)"

    echo "INSERT INTO data (imm8, compiler, version, compile_time, total_cycles, dispatch_width, uops_per_cycle, ipc, block_rthroughput, asm) VALUES ($IMM8, '$COMPILER', '$VERSION', $COMPILE_TIME, $TOTAL_CYCLES, $DISPATCH_WIDTH, $UOPS_PER_CYCLE, $IPC, $BLOCK_RTHROUGHPUT, readfile('result.s'));" | sqlite3 data.db
}

CLANG=clang-11
CLANGXX=clang++-11
GCC=gcc-11
GXX=g++-11

CFLAGS_COMMON="-O3 -fopenmp-simd -DSIMDE_ENABLE_OPENMP -iquote $SIMDE_HOME"
CFLAGS_CLANG="$CFLAGS_COMMON"
CFLAGS_GCC="$CFLAGS_COMMON -fcf-protection=branch -mmanual-endbr"
CFLAGS_ICC="$CFLAGS_COMMON -qoverride-limits"

x=0;
for MARCH in nehalem; do
  while [ $x -lt 256 ]; do
    echo "Generating data for -march=$MARCH #$x..."

    /usr/bin/time -o time.res -f '%U' $CLANG   -DIMM8=$x -march=$MARCH $CFLAGS_CLANG tl-rosbif.c  -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "$CLANG" "rosbif" $x

    /usr/bin/time -o time.res -f '%U' $CLANG   -DIMM8=$x -march=$MARCH $CFLAGS_CLANG tl-rosbif2.c -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "$CLANG" "rosbif2" $x

    /usr/bin/time -o time.res -f '%U' $CLANG   -DIMM8=$x -march=$MARCH $CFLAGS_CLANG tl.c         -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "$CLANG" "autovec" $x

    /usr/bin/time -o time.res -f '%U' $CLANGXX -DIMM8=$x -march=$MARCH $CFLAGS_CLANG mula.cpp     -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "$CLANGXX" "mula" $x



    /usr/bin/time -o time.res -f '%U' $GCC     -DIMM8=$x -march=$MARCH $CFLAGS_GCC tl-rosbif.c  -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "$GCC" "rosbif" $x

    /usr/bin/time -o time.res -f '%U' $GCC     -DIMM8=$x -march=$MARCH $CFLAGS_GCC tl-rosbif2.c -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "$GCC" "rosbif2" $x

    /usr/bin/time -o time.res -f '%U' $GCC     -DIMM8=$x -march=$MARCH $CFLAGS_GCC tl.c         -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "$GCC" "autovec" $x

    /usr/bin/time -o time.res -f '%U' $GXX     -DIMM8=$x -march=$MARCH $CFLAGS_GCC mula.cpp     -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "$GXX" "mula" $x



    /usr/bin/time -o time.res -f '%U' icc     -DIMM8=$x -march=$MARCH $CFLAGS_ICC tl-rosbif.c  -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "icc" "rosbif" $x

    /usr/bin/time -o time.res -f '%U' icc     -DIMM8=$x -march=$MARCH $CFLAGS_ICC tl-rosbif2.c -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "icc" "rosbif2" $x

    /usr/bin/time -o time.res -f '%U' icc     -DIMM8=$x -march=$MARCH $CFLAGS_ICC tl.c         -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "icc" "autovec" $x

    /usr/bin/time -o time.res -f '%U' icpc    -DIMM8=$x -march=$MARCH $CFLAGS_ICC mula.cpp     -S -o result.s
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "icc" "mula" $x

    x=$(expr $x + 1)
  done
done

sqlite3 data.db < gen_csv.sql
