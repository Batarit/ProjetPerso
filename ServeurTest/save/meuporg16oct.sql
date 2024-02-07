-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le : lun. 16 oct. 2023 à 15:27
-- Version du serveur : 8.0.31
-- Version de PHP : 8.0.26

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `meuporg`
--

-- --------------------------------------------------------

--
-- Structure de la table `guildes`
--

DROP TABLE IF EXISTS `guildes`;
CREATE TABLE IF NOT EXISTS `guildes` (
  `nom` varchar(50) NOT NULL,
  `id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Structure de la table `joueurs`
--

DROP TABLE IF EXISTS `joueurs`;
CREATE TABLE IF NOT EXISTS `joueurs` (
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `password` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `adresse mail` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Structure de la table `mail`
--

DROP TABLE IF EXISTS `mail`;
CREATE TABLE IF NOT EXISTS `mail` (
  `id` int NOT NULL AUTO_INCREMENT,
  `idReception` int NOT NULL,
  `idSender` int NOT NULL,
  `Contenu` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idReception` (`idReception`,`idSender`),
  KEY `idSender` (`idSender`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Structure de la table `map`
--

DROP TABLE IF EXISTS `map`;
CREATE TABLE IF NOT EXISTS `map` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `description` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `map`
--

INSERT INTO `map` (`id`, `name`, `description`) VALUES
(0, 'begin town', 'a port city where many adventurer comme to begin their adventure.'),
(1, 'Little Forest', 'a forest where the monster are not really dangerous.'),
(2, 'col of jugement', 'a little path in the montaine where the danger is beyand every stone there is the only path to go to'),
(3, 'secound town', 'there is where the majority of adventurer say the adventur begin.'),
(4, 'graveyard', 'outside of the town you can find a graveyard it\'s not recomended to enter for letting the dead rest '),
(5, 'Crypt', 'in the graveyard you founded a vault who gave acces to an old crypt who know what you would find in '),
(6, 'Old Cave', 'an old cave with for only light source somme mushroom and the sound of water far away'),
(7, 'underground lake', 'a big lake underground emitting somme light and a stream of water liding to the outside');

-- --------------------------------------------------------

--
-- Structure de la table `mapliaison`
--

DROP TABLE IF EXISTS `mapliaison`;
CREATE TABLE IF NOT EXISTS `mapliaison` (
  `id` int NOT NULL AUTO_INCREMENT,
  `idMap1` int NOT NULL,
  `idMap2` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idMap1` (`idMap1`),
  KEY `idMap2` (`idMap2`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `mapliaison`
--

INSERT INTO `mapliaison` (`id`, `idMap1`, `idMap2`) VALUES
(1, 0, 1),
(2, 1, 2),
(3, 2, 3),
(4, 3, 4);

-- --------------------------------------------------------

--
-- Structure de la table `passif`
--

DROP TABLE IF EXISTS `passif`;
CREATE TABLE IF NOT EXISTS `passif` (
  `id` int NOT NULL AUTO_INCREMENT,
  `description` text NOT NULL,
  `Info_Prog` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Structure de la table `perso`
--

DROP TABLE IF EXISTS `perso`;
CREATE TABLE IF NOT EXISTS `perso` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `lv` int NOT NULL,
  `exp` int NOT NULL,
  `hp` int NOT NULL,
  `mana` int NOT NULL,
  `Armor` int NOT NULL,
  `logued` int NOT NULL,
  `id player` int NOT NULL,
  `id race` int NOT NULL,
  `id passif` int NOT NULL,
  `id guild` int NOT NULL,
  `id map` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id race` (`id race`),
  KEY `id player` (`id player`),
  KEY `id map` (`id map`),
  KEY `id guild` (`id guild`),
  KEY `id passif` (`id passif`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Structure de la table `race`
--

DROP TABLE IF EXISTS `race`;
CREATE TABLE IF NOT EXISTS `race` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `pv` tinyint NOT NULL,
  `mana` tinyint NOT NULL,
  `armor` tinyint NOT NULL,
  `description` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `race`
--

INSERT INTO `race` (`id`, `name`, `pv`, `mana`, `armor`, `description`) VALUES
(1, 'Nain', 3, -2, 2, 'une espece robuste mais plutôt faible en magie'),
(2, 'elf', 0, 5, -2, 'une espece forte en magie mais faible physiquement'),
(3, 'hummain', 1, 1, 1, 'l\'espece moyen en tout');

-- --------------------------------------------------------

--
-- Structure de la table `runes`
--

DROP TABLE IF EXISTS `runes`;
CREATE TABLE IF NOT EXISTS `runes` (
  `id` int NOT NULL AUTO_INCREMENT,
  `Type` tinyint NOT NULL,
  `Damage` tinyint NOT NULL,
  `Mana` tinyint NOT NULL,
  `Armor` tinyint NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=69 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Déchargement des données de la table `runes`
--

INSERT INTO `runes` (`id`, `Type`, `Damage`, `Mana`, `Armor`) VALUES
(1, 0, 1, 1, 0),
(2, 0, 2, 2, 0),
(3, 0, 0, 1, 1),
(4, 0, 0, 2, 2),
(5, 0, 2, 4, 2),
(6, 0, 2, 3, 1),
(7, 0, 1, 3, 2),
(8, 0, 1, 2, 1),
(28, 3, 2, 4, 2),
(27, 3, 2, 3, 1),
(26, 3, 1, 3, 2),
(25, 3, 1, 2, 1),
(17, 2, 1, 2, 1),
(18, 2, 1, 3, 2),
(19, 2, 2, 3, 1),
(20, 2, 2, 4, 2),
(21, 2, 0, 2, 2),
(22, 2, 0, 1, 1),
(23, 2, 2, 2, 0),
(24, 2, 1, 1, 0),
(9, 1, 1, 2, 1),
(10, 1, 1, 3, 2),
(11, 1, 2, 3, 1),
(12, 1, 2, 4, 2),
(13, 1, 0, 2, 2),
(14, 1, 0, 1, 1),
(15, 1, 2, 2, 0),
(16, 1, 1, 1, 0),
(32, 3, 1, 1, 0),
(31, 3, 2, 2, 0),
(30, 3, 0, 1, 1),
(29, 3, 0, 2, 2),
(33, 4, 1, 2, 1),
(34, 4, 1, 3, 2),
(35, 4, 2, 3, 1),
(36, 4, 2, 4, 2),
(37, 4, 0, 2, 2),
(38, 4, 0, 1, 1),
(39, 4, 2, 2, 0),
(40, 4, 1, 1, 0),
(41, 5, 1, 2, 1),
(42, 5, 1, 3, 2),
(43, 5, 2, 3, 1),
(44, 5, 2, 4, 2),
(45, 5, 0, 2, 2),
(46, 5, 0, 1, 1),
(47, 5, 2, 2, 0),
(48, 5, 1, 1, 0),
(49, 6, 1, 2, 1),
(50, 6, 1, 3, 2),
(51, 6, 2, 3, 1),
(52, 6, 2, 4, 2),
(53, 6, 0, 2, 2),
(54, 6, 0, 1, 1),
(55, 6, 2, 2, 0),
(56, 6, 1, 1, 0);

--
-- Contraintes pour les tables déchargées
--

--
-- Contraintes pour la table `mail`
--
ALTER TABLE `mail`
  ADD CONSTRAINT `mail_ibfk_1` FOREIGN KEY (`idReception`) REFERENCES `perso` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `mail_ibfk_2` FOREIGN KEY (`idSender`) REFERENCES `perso` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Contraintes pour la table `mapliaison`
--
ALTER TABLE `mapliaison`
  ADD CONSTRAINT `mapliaison_ibfk_1` FOREIGN KEY (`idMap1`) REFERENCES `map` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `mapliaison_ibfk_2` FOREIGN KEY (`idMap2`) REFERENCES `map` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Contraintes pour la table `perso`
--
ALTER TABLE `perso`
  ADD CONSTRAINT `perso_ibfk_1` FOREIGN KEY (`id race`) REFERENCES `race` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `perso_ibfk_2` FOREIGN KEY (`id player`) REFERENCES `joueurs` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `perso_ibfk_3` FOREIGN KEY (`id map`) REFERENCES `map` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `perso_ibfk_4` FOREIGN KEY (`id guild`) REFERENCES `guildes` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `perso_ibfk_5` FOREIGN KEY (`id passif`) REFERENCES `passif` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
