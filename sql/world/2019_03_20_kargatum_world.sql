/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Licence MIT https://opensource.org/MIT
 */

INSERT INTO `version_db_world` (`sql_rev`) VALUES ('1553428344428393600');

-- ----------------------------
-- Table structure for anti_ad_message
-- ----------------------------
DROP TABLE IF EXISTS `anti_ad_message`;
CREATE TABLE `anti_ad_message`  (
  `message` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`message`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of anti_ad_message
-- ----------------------------
INSERT INTO `anti_ad_message` VALUES 
('(w)(o)(w)'),
('.com'),
('.eu'),
('.fr'),
('.info'),
('.net'),
('.org'),
('.ru'),
('.zapto'),
('.рф'),
('://'),
('http'),
('no-ip'),
('w-o-w'),
('wow'),
('www');

-- ----------------------------
-- Table structure for item_levelup
-- ----------------------------
-- DROP TABLE IF EXISTS `item_levelup`;
-- CREATE TABLE `item_levelup`  (
--   `Entry` int(10) NOT NULL,
--   `MinLevel` int(3) NULL DEFAULT 0,
--   `MaxLevel` int(3) NULL DEFAULT 0,
--   `Comment` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
--   PRIMARY KEY (`Entry`) USING BTREE
-- ) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of item_levelup
-- ----------------------------
-- INSERT INTO `item_levelup` VALUES (80000, 1, 20, '1 - 20 Уровень');
-- INSERT INTO `item_levelup` VALUES (80001, 21, 40, '21 - 40 Уровень');
-- INSERT INTO `item_levelup` VALUES (80002, 41, 60, '41 - 60 Уровень');

-- ----------------------------
-- Table structure for level_reward
-- ----------------------------
DROP TABLE IF EXISTS `level_reward`;
CREATE TABLE `level_reward`  (
  `Level` int(3) NOT NULL DEFAULT 1,
  `Money` int(20) NOT NULL DEFAULT 0,
  `ItemID` int(20) NOT NULL DEFAULT 0,
  `ItemCount` int(5) NOT NULL DEFAULT 0,
  PRIMARY KEY (`Level`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for online_reward_history
-- ----------------------------
DROP TABLE IF EXISTS `online_reward_history`;
CREATE TABLE `online_reward_history`  (
  `PlayedGuid` bigint(20) NOT NULL DEFAULT 0,
  `Rewarded` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `RewardedPerHour` int(20) NULL DEFAULT 0,
  PRIMARY KEY (`PlayedGuid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Table structure for online_reward
-- ----------------------------
DROP TABLE IF EXISTS `online_reward`;
CREATE TABLE `online_reward`  (
  `RewardPlayedTime` int(20) NOT NULL DEFAULT 0,
  `ItemID` int(11) NOT NULL DEFAULT 1,
  `Count` int(11) NOT NULL DEFAULT 1,
  PRIMARY KEY (`RewardPlayedTime`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of online_reward
-- ----------------------------
-- INSERT INTO `online_reward` VALUES (700, 49426, 5);
-- INSERT INTO `online_reward` VALUES (900, 49426, 10);
-- INSERT INTO `online_reward` VALUES (930, 49426, 20);

-- ----------------------------
-- Table structure for player_buff
-- ----------------------------
DROP TABLE IF EXISTS `player_buff`;
CREATE TABLE `player_buff`  (
  `SpellID` int(10) NOT NULL COMMENT 'Spell ID',
  `Comment` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`spellid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- Class buff
INSERT INTO `player_buff` VALUES (25898, '');
INSERT INTO `player_buff` VALUES (48074, '');
INSERT INTO `player_buff` VALUES (48162, '');
INSERT INTO `player_buff` VALUES (48470, '');
INSERT INTO `player_buff` VALUES (57623, '');
INSERT INTO `player_buff` VALUES (61316, '');
-- INSERT INTO `player_buff` VALUES (62276, 'Покров молний (тест)');

-- ----------------------------
-- Table structure for spell_duration
-- ----------------------------
DROP TABLE IF EXISTS `spell_duration`;
CREATE TABLE `spell_duration`  (
  `SpellID` int(11) NOT NULL COMMENT 'Айди спелла',
  `MaxDuration` int(11) NULL DEFAULT NULL COMMENT 'Время в секундах',
  PRIMARY KEY (`SpellID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- Class buff
INSERT INTO `spell_duration` VALUES (25898, -1);
INSERT INTO `spell_duration` VALUES (48074, -1);
INSERT INTO `spell_duration` VALUES (48162, -1);
INSERT INTO `spell_duration` VALUES (48470, -1);
INSERT INTO `spell_duration` VALUES (57623, -1);
INSERT INTO `spell_duration` VALUES (61316, -1);

-- Add trinity_string
DELETE FROM `trinity_string` WHERE `entry` IN (50000, 50001, 50002, 50003);
INSERT INTO `trinity_string`(`entry`, `content_default`, `content_loc8`) VALUES 
(50000, '|cFFFF0000[AntiAD]:|r %s |cff6C8CD5said a bad word:|r %s', '|cFFFF0000[Антиреклама]:|r %s |cff6C8CD5сказал запрещённое слово:|r %s'),
(50001, '|cFFFF0000[AntiAD]:|cff6C8CD5 You chat muted on |r %u |cff6C8CD5minutes.', '|cFFFF0000[Антиреклама]:|cff6C8CD5 Ваш чат заблокирован на|r %u |cff6C8CD5минут.'),
(50002, '|cFFFF0000[AntiAD]:|r %s |cff6C8CD5wanted to say:|r %s', '|cFFFF0000[Антиреклама]:|r %s |cff6C8CD5хотел сказать:|r %s'),
(50003, '|cffff0000# |cff00ff00Player|r %s |cff00ff00will not be able to speak yet:|r |cffff0000%s|r', '|cffff0000# |cff00ff00Игрок|r %s |cff00ff00не сможет говорить ещё: |cffff0000%s');
