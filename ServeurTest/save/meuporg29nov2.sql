-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le : mer. 29 nov. 2023 à 16:58
-- Version du serveur : 5.7.36
-- Version de PHP : 7.4.26

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
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `joueurs`
--

DROP TABLE IF EXISTS `joueurs`;
CREATE TABLE IF NOT EXISTS `joueurs` (
  `name` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `adresse mail` varchar(50) NOT NULL,
  `Connected` tinyint(1) NOT NULL DEFAULT '0',
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `joueurs`
--

INSERT INTO `joueurs` (`name`, `password`, `adresse mail`, `Connected`, `id`) VALUES
('admin', 'admin', 'admin', 0, 3);

-- --------------------------------------------------------

--
-- Structure de la table `mail`
--

DROP TABLE IF EXISTS `mail`;
CREATE TABLE IF NOT EXISTS `mail` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idReception` int(11) NOT NULL,
  `idSender` int(11) NOT NULL,
  `Contenu` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idReception` (`idReception`,`idSender`),
  KEY `idSender` (`idSender`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `map`
--

DROP TABLE IF EXISTS `map`;
CREATE TABLE IF NOT EXISTS `map` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `description` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

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
(7, 'underground lake', 'a big lake underground emitting somme light and a stream of water liding to the outside'),
(8, 'glade', 'a glade'),
(9, 'Roking Pass', 'a passage to the mountain'),
(10, 'swamp', 'a place hard to navigate inside');

-- --------------------------------------------------------

--
-- Structure de la table `mapliaison`
--

DROP TABLE IF EXISTS `mapliaison`;
CREATE TABLE IF NOT EXISTS `mapliaison` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idMap1` int(11) NOT NULL,
  `idMap2` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idMap1` (`idMap1`),
  KEY `idMap2` (`idMap2`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `mapliaison`
--

INSERT INTO `mapliaison` (`id`, `idMap1`, `idMap2`) VALUES
(1, 0, 1),
(2, 1, 2),
(3, 2, 3),
(4, 3, 4),
(6, 4, 5),
(7, 4, 7),
(8, 7, 8),
(9, 3, 8),
(10, 3, 9),
(11, 3, 10);

-- --------------------------------------------------------

--
-- Structure de la table `passif`
--

DROP TABLE IF EXISTS `passif`;
CREATE TABLE IF NOT EXISTS `passif` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `description` text NOT NULL,
  `Info_Prog` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `perso`
--

DROP TABLE IF EXISTS `perso`;
CREATE TABLE IF NOT EXISTS `perso` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `lv` int(11) NOT NULL DEFAULT '1',
  `exp` int(11) NOT NULL DEFAULT '0',
  `hp` int(11) NOT NULL DEFAULT '100',
  `mana` int(11) NOT NULL DEFAULT '100',
  `Armor` int(11) NOT NULL DEFAULT '5',
  `logued` tinyint(1) NOT NULL DEFAULT '0',
  `id_player` int(11) NOT NULL,
  `id_race` int(11) NOT NULL,
  `id_passif` int(11) DEFAULT NULL,
  `id_guild` int(11) DEFAULT NULL,
  `id_map` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `id race` (`id_race`),
  KEY `id player` (`id_player`),
  KEY `id map` (`id_map`),
  KEY `id guild` (`id_guild`),
  KEY `id passif` (`id_passif`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `perso`
--

INSERT INTO `perso` (`id`, `name`, `lv`, `exp`, `hp`, `mana`, `Armor`, `logued`, `id_player`, `id_race`, `id_passif`, `id_guild`, `id_map`) VALUES
(1, 'jack', 1, 0, 100, 100, 5, 0, 3, 1, NULL, NULL, 0),
(4, 'Pedro', 1, 0, 103, 98, 7, 0, 3, 1, NULL, NULL, 3),
(5, 'd', 1, 0, 101, 101, 6, 0, 3, 3, NULL, NULL, 0),
(6, 'Salade', 1, 0, 100, 105, 3, 0, 3, 2, NULL, NULL, 0),
(7, 'Barbe', 1, 0, 103, 98, 7, 0, 3, 1, NULL, NULL, 0),
(8, 'TuPue', 1, 0, 100, 105, 3, 0, 3, 2, NULL, NULL, 0),
(9, 'last', 1, 0, 101, 101, 6, 0, 3, 3, NULL, NULL, 0),
(10, 'coucou', 1, 0, 101, 101, 6, 0, 3, 3, NULL, NULL, 0);

-- --------------------------------------------------------

--
-- Structure de la table `race`
--

DROP TABLE IF EXISTS `race`;
CREATE TABLE IF NOT EXISTS `race` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `pv` tinyint(4) NOT NULL,
  `mana` tinyint(4) NOT NULL,
  `armor` tinyint(4) NOT NULL,
  `description` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `race`
--

INSERT INTO `race` (`id`, `name`, `pv`, `mana`, `armor`, `description`) VALUES
(1, 'Nain', 103, 98, 7, 'une espece robuste mais plutÃ´t faible en magie'),
(2, 'elf', 100, 105, 3, 'une espece forte en magie mais faible physiquement'),
(3, 'hummain', 101, 101, 6, 'l\'espece moyen en tout');

-- --------------------------------------------------------

--
-- Structure de la table `runes`
--

DROP TABLE IF EXISTS `runes`;
CREATE TABLE IF NOT EXISTS `runes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Type` tinyint(4) NOT NULL,
  `Damage` tinyint(4) NOT NULL,
  `Mana` tinyint(4) NOT NULL,
  `Armor` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=69 DEFAULT CHARSET=latin1;

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
  ADD CONSTRAINT `mapliaison_ibfk_1` FOREIGN KEY (`idMap1`) REFERENCES `map` (`id`),
  ADD CONSTRAINT `mapliaison_ibfk_2` FOREIGN KEY (`idMap2`) REFERENCES `map` (`id`);

--
-- Contraintes pour la table `perso`
--
ALTER TABLE `perso`
  ADD CONSTRAINT `perso_ibfk_1` FOREIGN KEY (`id_race`) REFERENCES `race` (`id`),
  ADD CONSTRAINT `perso_ibfk_2` FOREIGN KEY (`id_player`) REFERENCES `joueurs` (`id`),
  ADD CONSTRAINT `perso_ibfk_3` FOREIGN KEY (`id_map`) REFERENCES `map` (`id`),
  ADD CONSTRAINT `perso_ibfk_4` FOREIGN KEY (`id_guild`) REFERENCES `guildes` (`id`),
  ADD CONSTRAINT `perso_ibfk_5` FOREIGN KEY (`id_passif`) REFERENCES `passif` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
