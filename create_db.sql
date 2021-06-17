CREATE TABLE data (
  imm8 INT,
  compiler TEXT,
  version TEXT,
  compile_time REAL,
  instructions INT,
  total_cycles INT,
  dispatch_width INT,
  uops_per_cycle REAL,
  ipc REAL,
  block_rthroughput REAL,
  asm TEXT
);

DROP VIEW IF EXISTS by_imm8;
CREATE VIEW by_imm8 AS
  SELECT DISTINCT
    `cr`.`imm8`,

    `cr`.`instructions` AS instructions_clang_rosbif,
    `cs`.`instructions` AS instructions_clang_rosbif2,
    `ct`.`instructions` AS instructions_clang_rosbif3,
    `cu`.`instructions` AS instructions_clang_rosbif4,
    `cv`.`instructions` AS instructions_clang_rosbif5,
    `cm`.`instructions` AS instructions_clang_mula,
    `ca`.`instructions` AS instructions_clang_autovec,
    `gr`.`instructions` AS instructions_gcc_rosbif,
    `gs`.`instructions` AS instructions_gcc_rosbif2,
    `gt`.`instructions` AS instructions_gcc_rosbif3,
    `gu`.`instructions` AS instructions_gcc_rosbif4,
    `gv`.`instructions` AS instructions_gcc_rosbif5,
    `gm`.`instructions` AS instructions_gcc_mula,
    `ga`.`instructions` AS instructions_gcc_autovec,
    `ir`.`instructions` AS instructions_icc_rosbif,
    `is`.`instructions` AS instructions_icc_rosbif2,
    `it`.`instructions` AS instructions_icc_rosbif3,
    `iu`.`instructions` AS instructions_icc_rosbif4,
    `iv`.`instructions` AS instructions_icc_rosbif5,
    `im`.`instructions` AS instructions_icc_mula,
    `ia`.`instructions` AS instructions_icc_autovec,

    `cr`.`total_cycles` AS total_cycles_clang_rosbif,
    `cs`.`total_cycles` AS total_cycles_clang_rosbif2,
    `ct`.`total_cycles` AS total_cycles_clang_rosbif3,
    `cu`.`total_cycles` AS total_cycles_clang_rosbif4,
    `cv`.`total_cycles` AS total_cycles_clang_rosbif5,
    `cm`.`total_cycles` AS total_cycles_clang_mula,
    `ca`.`total_cycles` AS total_cycles_clang_autovec,
    `gr`.`total_cycles` AS total_cycles_gcc_rosbif,
    `gs`.`total_cycles` AS total_cycles_gcc_rosbif2,
    `gt`.`total_cycles` AS total_cycles_gcc_rosbif3,
    `gu`.`total_cycles` AS total_cycles_gcc_rosbif4,
    `gv`.`total_cycles` AS total_cycles_gcc_rosbif5,
    `gm`.`total_cycles` AS total_cycles_gcc_mula,
    `ga`.`total_cycles` AS total_cycles_gcc_autovec,
    `ir`.`total_cycles` AS total_cycles_icc_rosbif,
    `is`.`total_cycles` AS total_cycles_icc_rosbif2,
    `it`.`total_cycles` AS total_cycles_icc_rosbif3,
    `iu`.`total_cycles` AS total_cycles_icc_rosbif4,
    `iv`.`total_cycles` AS total_cycles_icc_rosbif5,
    `im`.`total_cycles` AS total_cycles_icc_mula,
    `ia`.`total_cycles` AS total_cycles_icc_autovec,

    `cr`.`uops_per_cycle` AS uops_per_cycle_clang_rosbif,
    `cs`.`uops_per_cycle` AS uops_per_cycle_clang_rosbif2,
    `ct`.`uops_per_cycle` AS uops_per_cycle_clang_rosbif3,
    `cu`.`uops_per_cycle` AS uops_per_cycle_clang_rosbif4,
    `cv`.`uops_per_cycle` AS uops_per_cycle_clang_rosbif5,
    `cm`.`uops_per_cycle` AS uops_per_cycle_clang_mula,
    `ca`.`uops_per_cycle` AS uops_per_cycle_clang_autovec,
    `gr`.`uops_per_cycle` AS uops_per_cycle_gcc_rosbif,
    `gs`.`uops_per_cycle` AS uops_per_cycle_gcc_rosbif2,
    `gt`.`uops_per_cycle` AS uops_per_cycle_gcc_rosbif3,
    `gu`.`uops_per_cycle` AS uops_per_cycle_gcc_rosbif4,
    `gv`.`uops_per_cycle` AS uops_per_cycle_gcc_rosbif5,
    `gm`.`uops_per_cycle` AS uops_per_cycle_gcc_mula,
    `ga`.`uops_per_cycle` AS uops_per_cycle_gcc_autovec,
    `ir`.`uops_per_cycle` AS uops_per_cycle_icc_rosbif,
    `is`.`uops_per_cycle` AS uops_per_cycle_icc_rosbif2,
    `it`.`uops_per_cycle` AS uops_per_cycle_icc_rosbif3,
    `iu`.`uops_per_cycle` AS uops_per_cycle_icc_rosbif4,
    `iv`.`uops_per_cycle` AS uops_per_cycle_icc_rosbif5,
    `im`.`uops_per_cycle` AS uops_per_cycle_icc_mula,
    `ia`.`uops_per_cycle` AS uops_per_cycle_icc_autovec,

    `cr`.`ipc` AS ipc_clang_rosbif,
    `cs`.`ipc` AS ipc_clang_rosbif2,
    `ct`.`ipc` AS ipc_clang_rosbif3,
    `cu`.`ipc` AS ipc_clang_rosbif4,
    `cv`.`ipc` AS ipc_clang_rosbif5,
    `cm`.`ipc` AS ipc_clang_mula,
    `ca`.`ipc` AS ipc_clang_autovec,
    `gr`.`ipc` AS ipc_gcc_rosbif,
    `gs`.`ipc` AS ipc_gcc_rosbif2,
    `gt`.`ipc` AS ipc_gcc_rosbif3,
    `gu`.`ipc` AS ipc_gcc_rosbif4,
    `gv`.`ipc` AS ipc_gcc_rosbif5,
    `gm`.`ipc` AS ipc_gcc_mula,
    `ga`.`ipc` AS ipc_gcc_autovec,
    `ir`.`ipc` AS ipc_icc_rosbif,
    `is`.`ipc` AS ipc_icc_rosbif2,
    `it`.`ipc` AS ipc_icc_rosbif3,
    `iu`.`ipc` AS ipc_icc_rosbif4,
    `iv`.`ipc` AS ipc_icc_rosbif5,
    `im`.`ipc` AS ipc_icc_mula,
    `ia`.`ipc` AS ipc_icc_autovec,

    `cr`.`block_rthroughput` AS rthroughput_clang_rosbif,
    `cs`.`block_rthroughput` AS rthroughput_clang_rosbif2,
    `ct`.`block_rthroughput` AS rthroughput_clang_rosbif3,
    `cu`.`block_rthroughput` AS rthroughput_clang_rosbif4,
    `cv`.`block_rthroughput` AS rthroughput_clang_rosbif5,
    `cm`.`block_rthroughput` AS rthroughput_clang_mula,
    `ca`.`block_rthroughput` AS rthroughput_clang_autovec,
    `gr`.`block_rthroughput` AS rthroughput_gcc_rosbif,
    `gs`.`block_rthroughput` AS rthroughput_gcc_rosbif2,
    `gt`.`block_rthroughput` AS rthroughput_gcc_rosbif3,
    `gu`.`block_rthroughput` AS rthroughput_gcc_rosbif4,
    `gv`.`block_rthroughput` AS rthroughput_gcc_rosbif5,
    `gm`.`block_rthroughput` AS rthroughput_gcc_mula,
    `ga`.`block_rthroughput` AS rthroughput_gcc_autovec,
    `ir`.`block_rthroughput` AS rthroughput_icc_rosbif,
    `is`.`block_rthroughput` AS rthroughput_icc_rosbif2,
    `it`.`block_rthroughput` AS rthroughput_icc_rosbif3,
    `iu`.`block_rthroughput` AS rthroughput_icc_rosbif4,
    `iv`.`block_rthroughput` AS rthroughput_icc_rosbif5,
    `im`.`block_rthroughput` AS rthroughput_icc_mula,
    `ia`.`block_rthroughput` AS rthroughput_icc_autovec

    FROM `data`

    LEFT JOIN `data` AS `cr`
      ON
        `cr`.`imm8` = `data`.`imm8` AND
        `cr`.`compiler` = 'clang' AND
        `cr`.`version` = 'rosbif'
    LEFT JOIN `data` AS `cs`
      ON
        `cs`.`imm8` = `data`.`imm8` AND
        `cs`.`compiler` = 'clang' AND
        `cs`.`version` = 'rosbif2'
    LEFT JOIN `data` AS `ct`
      ON
        `ct`.`imm8` = `data`.`imm8` AND
        `ct`.`compiler` = 'clang' AND
        `ct`.`version` = 'rosbif3'
    LEFT JOIN `data` AS `cu`
      ON
        `cu`.`imm8` = `data`.`imm8` AND
        `cu`.`compiler` = 'clang' AND
        `cu`.`version` = 'rosbif4'
    LEFT JOIN `data` AS `cv`
      ON
        `cv`.`imm8` = `data`.`imm8` AND
        `cv`.`compiler` = 'clang' AND
        `cv`.`version` = 'rosbif5'
    LEFT JOIN `data` AS `cm`
      ON
        `cm`.`imm8` = `data`.`imm8` AND
        `cm`.`compiler` = 'clang' AND
        `cm`.`version` = 'mula'
    LEFT JOIN `data` AS `ca`
      ON
        `ca`.`imm8` = `data`.`imm8` AND
        `ca`.`compiler` = 'clang' AND
        `ca`.`version` = 'autovec'

    LEFT JOIN `data` AS `gr`
      ON
        `gr`.`imm8` = `data`.`imm8` AND
        `gr`.`compiler` = 'gcc' AND
        `gr`.`version` = 'rosbif'
    LEFT JOIN `data` AS `gs`
      ON
        `gs`.`imm8` = `data`.`imm8` AND
        `gs`.`compiler` = 'gcc' AND
        `gs`.`version` = 'rosbif2'
    LEFT JOIN `data` AS `gt`
      ON
        `gt`.`imm8` = `data`.`imm8` AND
        `gt`.`compiler` = 'gcc' AND
        `gt`.`version` = 'rosbif3'
    LEFT JOIN `data` AS `gu`
      ON
        `gu`.`imm8` = `data`.`imm8` AND
        `gu`.`compiler` = 'gcc' AND
        `gu`.`version` = 'rosbif4'
    LEFT JOIN `data` AS `gv`
      ON
        `gv`.`imm8` = `data`.`imm8` AND
        `gv`.`compiler` = 'gcc' AND
        `gv`.`version` = 'rosbif5'
    LEFT JOIN `data` AS `gm`
      ON
        `gm`.`imm8` = `data`.`imm8` AND
        `gm`.`compiler` = 'gcc' AND
        `gm`.`version` = 'mula'
    LEFT JOIN `data` AS `ga`
      ON
        `ga`.`imm8` = `data`.`imm8` AND
        `ga`.`compiler` = 'gcc' AND
        `ga`.`version` = 'autovec'

    LEFT JOIN `data` AS `ir`
      ON
        `ir`.`imm8` = `data`.`imm8` AND
        `ir`.`compiler` = 'icc' AND
        `ir`.`version` = 'rosbif'
    LEFT JOIN `data` AS `is`
      ON
        `is`.`imm8` = `data`.`imm8` AND
        `is`.`compiler` = 'icc' AND
        `is`.`version` = 'rosbif2'
    LEFT JOIN `data` AS `it`
      ON
        `it`.`imm8` = `data`.`imm8` AND
        `it`.`compiler` = 'icc' AND
        `it`.`version` = 'rosbif3'
    LEFT JOIN `data` AS `iu`
      ON
        `iu`.`imm8` = `data`.`imm8` AND
        `iu`.`compiler` = 'icc' AND
        `iu`.`version` = 'rosbif4'
    LEFT JOIN `data` AS `iv`
      ON
        `iv`.`imm8` = `data`.`imm8` AND
        `iv`.`compiler` = 'icc' AND
        `iv`.`version` = 'rosbif5'
    LEFT JOIN `data` AS `im`
      ON
        `im`.`imm8` = `data`.`imm8` AND
        `im`.`compiler` = 'icc' AND
        `im`.`version` = 'mula'
    LEFT JOIN `data` AS `ia`
      ON
        `ia`.`imm8` = `data`.`imm8` AND
        `ia`.`compiler` = 'icc' AND
        `ia`.`version` = 'autovec'

    GROUP BY
      `data`.`imm8`,
      `data`.`compiler`,
      `data`.`version`;


DROP VIEW IF EXISTS rel_rthroughput;
CREATE VIEW rel_rthroughput AS
  SELECT DISTINCT
    `cr`.`imm8`,

    `cr`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_rosbif,
    `cs`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_rosbif2,
    `ct`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_rosbif3,
    `cu`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_rosbif4,
    `cv`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_rosbif5,
    `cm`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_mula,
    `ca`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_autovec,
    `gr`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_rosbif,
    `gs`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_rosbif2,
    `gt`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_rosbif3,
    `gu`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_rosbif4,
    `gv`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_rosbif5,
    `gm`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_mula,
    `ga`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_autovec,
    `ir`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_rosbif,
    `is`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_rosbif2,
    `it`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_rosbif3,
    `iu`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_rosbif4,
    `iv`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_rosbif5,
    `im`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_mula,
    `ia`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_autovec

    FROM `data`

    LEFT JOIN `data` AS `cr`
      ON
        `cr`.`imm8` = `data`.`imm8` AND
        `cr`.`compiler` = 'clang' AND
        `cr`.`version` = 'rosbif'
    LEFT JOIN `data` AS `cs`
      ON
        `cs`.`imm8` = `data`.`imm8` AND
        `cs`.`compiler` = 'clang' AND
        `cs`.`version` = 'rosbif2'
    LEFT JOIN `data` AS `ct`
      ON
        `ct`.`imm8` = `data`.`imm8` AND
        `ct`.`compiler` = 'clang' AND
        `ct`.`version` = 'rosbif3'
    LEFT JOIN `data` AS `cu`
      ON
        `cu`.`imm8` = `data`.`imm8` AND
        `cu`.`compiler` = 'clang' AND
        `cu`.`version` = 'rosbif4'
    LEFT JOIN `data` AS `cv`
      ON
        `cv`.`imm8` = `data`.`imm8` AND
        `cv`.`compiler` = 'clang' AND
        `cv`.`version` = 'rosbif5'
    LEFT JOIN `data` AS `cm`
      ON
        `cm`.`imm8` = `data`.`imm8` AND
        `cm`.`compiler` = 'clang' AND
        `cm`.`version` = 'mula'
    LEFT JOIN `data` AS `ca`
      ON
        `ca`.`imm8` = `data`.`imm8` AND
        `ca`.`compiler` = 'clang' AND
        `ca`.`version` = 'autovec'

    LEFT JOIN `data` AS `gr`
      ON
        `gr`.`imm8` = `data`.`imm8` AND
        `gr`.`compiler` = 'gcc' AND
        `gr`.`version` = 'rosbif'
    LEFT JOIN `data` AS `gs`
      ON
        `gs`.`imm8` = `data`.`imm8` AND
        `gs`.`compiler` = 'gcc' AND
        `gs`.`version` = 'rosbif2'
    LEFT JOIN `data` AS `gt`
      ON
        `gt`.`imm8` = `data`.`imm8` AND
        `gt`.`compiler` = 'gcc' AND
        `gt`.`version` = 'rosbif3'
    LEFT JOIN `data` AS `gu`
      ON
        `gu`.`imm8` = `data`.`imm8` AND
        `gu`.`compiler` = 'gcc' AND
        `gu`.`version` = 'rosbif4'
    LEFT JOIN `data` AS `gv`
      ON
        `gv`.`imm8` = `data`.`imm8` AND
        `gv`.`compiler` = 'gcc' AND
        `gv`.`version` = 'rosbif5'
    LEFT JOIN `data` AS `gm`
      ON
        `gm`.`imm8` = `data`.`imm8` AND
        `gm`.`compiler` = 'gcc' AND
        `gm`.`version` = 'mula'
    LEFT JOIN `data` AS `ga`
      ON
        `ga`.`imm8` = `data`.`imm8` AND
        `ga`.`compiler` = 'gcc' AND
        `ga`.`version` = 'autovec'

    LEFT JOIN `data` AS `ir`
      ON
        `ir`.`imm8` = `data`.`imm8` AND
        `ir`.`compiler` = 'icc' AND
        `ir`.`version` = 'rosbif'
    LEFT JOIN `data` AS `is`
      ON
        `is`.`imm8` = `data`.`imm8` AND
        `is`.`compiler` = 'icc' AND
        `is`.`version` = 'rosbif2'
    LEFT JOIN `data` AS `it`
      ON
        `it`.`imm8` = `data`.`imm8` AND
        `it`.`compiler` = 'icc' AND
        `it`.`version` = 'rosbif3'
    LEFT JOIN `data` AS `iu`
      ON
        `iu`.`imm8` = `data`.`imm8` AND
        `iu`.`compiler` = 'icc' AND
        `iu`.`version` = 'rosbif4'
    LEFT JOIN `data` AS `iv`
      ON
        `iv`.`imm8` = `data`.`imm8` AND
        `iv`.`compiler` = 'icc' AND
        `iv`.`version` = 'rosbif5'
    LEFT JOIN `data` AS `im`
      ON
        `im`.`imm8` = `data`.`imm8` AND
        `im`.`compiler` = 'icc' AND
        `im`.`version` = 'mula'
    LEFT JOIN `data` AS `ia`
      ON
        `ia`.`imm8` = `data`.`imm8` AND
        `ia`.`compiler` = 'icc' AND
        `ia`.`version` = 'autovec'

    GROUP BY
      `data`.`imm8`,
      `data`.`compiler`,
      `data`.`version`;


DROP VIEW IF EXISTS avg_rthroughput;
CREATE VIEW avg_rthroughput AS
  SELECT
    compiler,
    version,
    AVG(compile_time) AS compile_time,
    AVG(instructions) AS instructions,
    AVG(total_cycles) AS total_cycles,
    AVG(uops_per_cycle) AS uops_per_cycle,
    AVG(ipc) AS ipc,
    AVG(block_rthroughput) AS rthroughput
  FROM data
  GROUP BY compiler, version;
