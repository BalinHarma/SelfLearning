-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `stocks` int(10) NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `price` decimal(65,4) NOT NULL,
  `sold` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (6,'TWTR',12,'2014-09-08 19:48:56',52.1000,0),(6,'MSFT',3,'2014-09-08 19:49:04',46.4600,1),(6,'TWTR',9,'2014-09-08 19:49:12',52.1000,1),(6,'MSFT',2,'2014-09-08 19:50:34',46.4700,1),(6,'MSFT',4,'2014-09-08 19:50:45',46.4700,0),(6,'TWTR',3,'2014-09-08 19:51:09',52.0600,0),(6,'MSFT',5,'2014-09-08 19:51:18',46.4650,0),(6,'SAFS',4,'2014-09-08 20:01:31',0.0006,0),(6,'SAFS',100,'2014-09-09 09:24:55',0.0006,0),(6,'MSFT',3,'2014-09-09 09:27:20',46.4700,0),(6,'MSFT',1,'2014-09-09 09:28:00',46.4700,0),(6,'MSFT',1,'2014-09-09 09:29:30',46.4700,0),(6,'MSFT',3,'2014-09-09 09:51:49',46.4700,0),(6,'MSFT',1,'2014-09-09 09:54:47',46.4700,0),(6,'MSFT',1,'2014-09-09 09:55:56',46.4700,0),(6,'MSFT',1,'2014-09-09 09:57:01',46.4700,0),(6,'MSFT',1,'2014-09-09 10:00:34',46.4700,0),(6,'MSFT',1,'2014-09-09 10:01:32',46.4700,0),(6,'MSFT',7,'2014-09-09 10:24:26',46.4700,0),(6,'MSFT',1,'2014-09-09 13:04:34',46.4700,0),(6,'TWTR',1,'2014-09-09 13:10:43',52.0000,0),(6,'TWTR',1,'2014-09-09 13:14:40',52.0000,1),(6,'SAFS',10,'2014-09-09 13:15:34',0.0006,1),(6,'MSFT',4,'2014-09-09 13:18:02',46.4700,1),(13,'SAFS',10000,'2014-09-09 14:05:20',0.0006,0),(13,'SAFS',10000,'2014-09-09 14:06:19',0.0006,0),(13,'SAFS',10000,'2014-09-09 14:08:01',0.0006,0),(13,'SAFS',10000,'2014-09-09 14:08:18',0.0006,0),(13,'SAFS',1,'2014-09-15 16:13:40',0.0007,1),(13,'SAFS',10,'2014-09-15 16:15:10',0.0007,1),(13,'SAFS',10,'2014-09-15 16:18:48',0.0007,0),(13,'SAFS',100,'2014-09-15 16:19:17',0.0007,1),(13,'SAFS',101,'2014-09-15 16:20:36',0.0007,0),(13,'SAFS',1,'2014-09-15 16:21:47',0.0007,1),(13,'SAFS',1,'2014-09-15 16:22:01',0.0007,0),(6,'SAFS',10,'2014-09-15 16:24:04',0.0007,1),(6,'SAFS',10,'2014-09-15 16:24:21',0.0007,0),(6,'SAFS',10,'2014-09-15 16:25:32',0.0007,1),(6,'TWTR',1,'2014-09-16 09:14:54',49.3800,1),(6,'PMC',1,'2014-09-17 19:12:25',26.4337,0),(6,'PMC',1,'2014-09-17 19:12:28',26.4337,0);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stocks`
--

DROP TABLE IF EXISTS `stocks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stocks` (
  `id` int(10) NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `stocks` int(11) NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stocks`
--

LOCK TABLES `stocks` WRITE;
/*!40000 ALTER TABLE `stocks` DISABLE KEYS */;
INSERT INTO `stocks` VALUES (6,'MSFT',39),(6,'PMC',2),(6,'SAFS',84),(6,'TERTR',1),(6,'TWTR',25),(6,'WETRETERGETW',1),(13,'SAFS',40000);
/*!40000 ALTER TABLE `stocks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  `email` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000,''),(2,'hirschhorn','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000,''),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000,''),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000,''),(5,'milo','$1$HA$6DHumQaK4GhpX8QE23C8V1',10000.0000,''),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',23479.1703,'richard19k@gmail.com'),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000,''),(8,'Balinth','$1$SIG54peV$cnc1dpNnBj/NO3gSzSplr/',10000.0000,''),(9,'csipotle','$1$SOE7cHS6$rwNpHgghWkzI4olRn5la21',10000.0000,''),(10,'maláta','$1$EUXSSudn$KLPYQhvDzUmzt/pTQ4kFk.',10000.0000,''),(11,'richard19','$1$B.jKxuwh$jXwRYWk5ixybKooDtbE17/',10000.0000,''),(12,'kapuska','$1$BkqTR/zh$KHu/NdxMXARJ2BPTJlhyG0',10000.0000,''),(13,'zanzibar','$1$EI30UiAI$hprBef4BWlfz7Si6WTXsP1',9976.0000,'richard19k@gmail.com');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-09-18  5:08:27
