CREATE TABLE data (
  imm8 INT,
  compiler TEXT,
  version TEXT,
  compile_time REAL,
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

    `cr`.`uops_per_cycle` AS uops_per_cycle_clang_rosbif,
    `cs`.`uops_per_cycle` AS uops_per_cycle_clang_rosbif2,
    `cm`.`uops_per_cycle` AS uops_per_cycle_clang_mula,
    `ca`.`uops_per_cycle` AS uops_per_cycle_clang_autovec,
    `gr`.`uops_per_cycle` AS uops_per_cycle_gcc_rosbif,
    `gs`.`uops_per_cycle` AS uops_per_cycle_gcc_rosbif2,
    `gm`.`uops_per_cycle` AS uops_per_cycle_gcc_mula,
    `ga`.`uops_per_cycle` AS uops_per_cycle_gcc_autovec,
    `ir`.`uops_per_cycle` AS uops_per_cycle_icc_rosbif,
    `is`.`uops_per_cycle` AS uops_per_cycle_icc_rosbif2,
    `im`.`uops_per_cycle` AS uops_per_cycle_icc_mula,
    `ia`.`uops_per_cycle` AS uops_per_cycle_icc_autovec,

    `cr`.`ipc` AS ipc_clang_rosbif,
    `cs`.`ipc` AS ipc_clang_rosbif2,
    `cm`.`ipc` AS ipc_clang_mula,
    `ca`.`ipc` AS ipc_clang_autovec,
    `gr`.`ipc` AS ipc_gcc_rosbif,
    `gs`.`ipc` AS ipc_gcc_rosbif2,
    `gm`.`ipc` AS ipc_gcc_mula,
    `ga`.`ipc` AS ipc_gcc_autovec,
    `ir`.`ipc` AS ipc_icc_rosbif,
    `is`.`ipc` AS ipc_icc_rosbif2,
    `im`.`ipc` AS ipc_icc_mula,
    `ia`.`ipc` AS ipc_icc_autovec,

    `cr`.`block_rthroughput` AS rthroughput_clang_rosbif,
    `cs`.`block_rthroughput` AS rthroughput_clang_rosbif2,
    `cm`.`block_rthroughput` AS rthroughput_clang_mula,
    `ca`.`block_rthroughput` AS rthroughput_clang_autovec,
    `gr`.`block_rthroughput` AS rthroughput_gcc_rosbif,
    `gs`.`block_rthroughput` AS rthroughput_gcc_rosbif2,
    `gm`.`block_rthroughput` AS rthroughput_gcc_mula,
    `ga`.`block_rthroughput` AS rthroughput_gcc_autovec,
    `ir`.`block_rthroughput` AS rthroughput_icc_rosbif,
    `is`.`block_rthroughput` AS rthroughput_icc_rosbif2,
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
        `ir`.`version` = 'rosbif2'
    LEFT JOIN `data` AS `is`
      ON
        `is`.`imm8` = `data`.`imm8` AND
        `is`.`compiler` = 'icc' AND
        `is`.`version` = 'rosbif'
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
    `cm`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_mula,
    `ca`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_clang_autovec,
    `gr`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_rosbif,
    `gs`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_rosbif2,
    `gm`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_mula,
    `ga`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_gcc_autovec,
    `ir`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_rosbif,
    `is`.`block_rthroughput` - (SELECT MIN(`block_rthroughput`) FROM `data` AS `id` WHERE `id`.`imm8` = `data`.`imm8` GROUP BY `id`.`imm8`) AS rthroughput_icc_rosbif2,
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
    AVG(uops_per_cycle) AS uops_per_cycle,
    AVG(ipc) AS ipc,
    AVG(block_rthroughput) AS rthroughput
  FROM data
  GROUP BY compiler, version;
