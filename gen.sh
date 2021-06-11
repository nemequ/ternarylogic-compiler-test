#!/bin/bash

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
    DISPATCH_WIDTH="$(grep -P '^(Dispatch Width:).+' llvm-mca.txt | cut -b20-)"
    UOPS_PER_CYCLE="$(grep -P '^(uOps Per Cycle:).+' llvm-mca.txt | cut -b20-)"
    IPC="$(grep -P '^(IPC:).+' llvm-mca.txt | cut -b20-)"
    BLOCK_RTHROUGHPUT="$(grep -P '^(Block RThroughput:).+' llvm-mca.txt | cut -b20-)"

    echo "INSERT INTO data (imm8, compiler, version, compile_time, dispatch_width, uops_per_cycle, ipc, block_rthroughput, asm) VALUES ($IMM8, '$COMPILER', '$VERSION', $COMPILE_TIME, $DISPATCH_WIDTH, $UOPS_PER_CYCLE, $IPC, $BLOCK_RTHROUGHPUT, readfile('result.s'));" | sqlite3 data.db
}

x=0;
for MARCH in tremont; do
  while [ $x -lt 256 ]; do
    echo "Generating data for -march=$MARCH #$x..."

    /usr/bin/time -o time.res -f '%U' clang   -DIMM8=$x -march=$MARCH tl-rosbif.c  -S -o result.s -O3
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "clang" "rosbif" $x

    /usr/bin/time -o time.res -f '%U' clang   -DIMM8=$x -march=$MARCH tl-rosbif2.c -S -o result.s -O3
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "clang" "rosbif2" $x

    /usr/bin/time -o time.res -f '%U' clang   -DIMM8=$x -march=$MARCH tl.c         -S -o result.s -O3
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "clang" "autovec" $x

    /usr/bin/time -o time.res -f '%U' clang++ -DIMM8=$x -march=$MARCH mula.cpp     -S -o result.s -O3
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "clang" "mula" $x



    /usr/bin/time -o time.res -f '%U' gcc     -DIMM8=$x -march=$MARCH tl-rosbif.c  -S -o result.s -O3
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "gcc" "rosbif" $x

    /usr/bin/time -o time.res -f '%U' gcc     -DIMM8=$x -march=$MARCH tl-rosbif2.c -S -o result.s -O3
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "gcc" "rosbif2" $x

    /usr/bin/time -o time.res -f '%U' gcc     -DIMM8=$x -march=$MARCH tl.c         -S -o result.s -O3
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "gcc" "autovec" $x

    /usr/bin/time -o time.res -f '%U' g++     -DIMM8=$x -march=$MARCH mula.cpp     -S -o result.s -O3
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "gcc" "mula" $x



    /usr/bin/time -o time.res -f '%U' icc     -DIMM8=$x -march=$MARCH tl-rosbif.c  -S -o result.s -O3 -qoverride-limits
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "icc" "rosbif" $x

    /usr/bin/time -o time.res -f '%U' icc     -DIMM8=$x -march=$MARCH tl-rosbif2.c -S -o result.s -O3 -qoverride-limits
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "icc" "rosbif2" $x

    /usr/bin/time -o time.res -f '%U' icc     -DIMM8=$x -march=$MARCH tl.c         -S -o result.s -O3 -qoverride-limits
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "icc" "autovec" $x

    /usr/bin/time -o time.res -f '%U' icpc    -DIMM8=$x -march=$MARCH mula.cpp     -S -o result.s -O3 -qoverride-limits
    llvm-mca -mcpu=$MARCH -o "llvm-mca.txt" result.s
    parse_mca "icc" "mula" $x

    x=$(expr $x + 1)
  done
done

sqlite3 data.db < gen_csv.sql
