.headers on
.mode csv
.output data.csv
SELECT imm8, compiler, version, total_cycles, compile_time, dispatch_width, uops_per_cycle, ipc, block_rthroughput FROM data;
.output by_imm8.csv
SELECT * FROM by_imm8;
.output rel_rthroughput.csv
SELECT * FROM rel_rthroughput;
.output avg_rthroughput.csv
SELECT * FROM avg_rthroughput;
