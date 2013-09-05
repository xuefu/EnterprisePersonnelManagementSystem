-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Sep 05, 2013 at 09:59 PM
-- Server version: 5.5.32
-- PHP Version: 5.3.10-1ubuntu3.7

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `EnterprisePersonnelManagementSystem`
--

-- --------------------------------------------------------

--
-- Table structure for table `managers`
--

CREATE TABLE IF NOT EXISTS `managers` (
  `managers_id` varchar(20) NOT NULL,
  `managers_passwd` varchar(20) NOT NULL,
  PRIMARY KEY (`managers_id`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

--
-- Dumping data for table `managers`
--

INSERT INTO `managers` (`managers_id`, `managers_passwd`) VALUES
('20111602310029', 'xtiprfw');

-- --------------------------------------------------------

--
-- Table structure for table `workers`
--

CREATE TABLE IF NOT EXISTS `workers` (
  `workers_id` varchar(20) NOT NULL,
  `workers_passwd` varchar(20) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`workers_id`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

--
-- Dumping data for table `workers`
--

INSERT INTO `workers` (`workers_id`, `workers_passwd`) VALUES
('20111602310000', 'xtiprfw'),
('20111602310004', 'xtiprfw'),
('20111602310016', 'xtiprfw'),
('20111602310022', 'xtiprfw'),
('20111602310027', 'xtiprfw'),
('20111602310029', 'xtiprfw');

-- --------------------------------------------------------

--
-- Table structure for table `workers_attendinfo`
--

CREATE TABLE IF NOT EXISTS `workers_attendinfo` (
  `attendinfo_id` int(5) NOT NULL AUTO_INCREMENT,
  `workers_id` varchar(20) NOT NULL,
  `attendinfo_date` char(10) NOT NULL,
  `attendinfo_absencetimes` int(5) DEFAULT '0',
  `attendinfo_latetimes` int(5) DEFAULT '0',
  `attendinfo_leavetimes` int(5) DEFAULT '0',
  PRIMARY KEY (`attendinfo_id`),
  KEY `workers_id` (`workers_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=gb2312 AUTO_INCREMENT=6 ;

--
-- Dumping data for table `workers_attendinfo`
--

INSERT INTO `workers_attendinfo` (`attendinfo_id`, `workers_id`, `attendinfo_date`, `attendinfo_absencetimes`, `attendinfo_latetimes`, `attendinfo_leavetimes`) VALUES
(1, '20111602310004', '2013-05', 0, 2, 2),
(2, '20111602310016', '2013-05', 0, 0, 0),
(3, '20111602310027', '2013-05', 2, 0, 4),
(4, '20111602310022', '2013-05', 3, 2, 5),
(5, '20111602310000', '2013-05', 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `workers_basicinfo`
--

CREATE TABLE IF NOT EXISTS `workers_basicinfo` (
  `basicinfo_id` int(5) NOT NULL AUTO_INCREMENT,
  `workers_id` varchar(20) NOT NULL,
  `workers_name` varchar(5) DEFAULT NULL,
  `workers_sex` char(2) DEFAULT NULL,
  `workers_age` int(3) DEFAULT NULL,
  `workers_idcard` varchar(18) NOT NULL,
  `workers_address` varchar(20) DEFAULT NULL,
  `workers_birthdate` char(10) DEFAULT NULL,
  `workers_telephone` char(11) NOT NULL,
  `workers_personnel` varchar(10) NOT NULL,
  `workers_position` varchar(10) DEFAULT NULL,
  `workers_passwd` varchar(20) NOT NULL,
  PRIMARY KEY (`basicinfo_id`),
  KEY `workers_id` (`workers_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=gb2312 AUTO_INCREMENT=6 ;

--
-- Dumping data for table `workers_basicinfo`
--

INSERT INTO `workers_basicinfo` (`basicinfo_id`, `workers_id`, `workers_name`, `workers_sex`, `workers_age`, `workers_idcard`, `workers_address`, `workers_birthdate`, `workers_telephone`, `workers_personnel`, `workers_position`, `workers_passwd`) VALUES
(1, '20111602310000', '李土迪', '女', 18, '124124312341312112', '山东', '1989-06-04', '18789347321', '宣传部', 'CEO', 'xtiprfw'),
(2, '20111602310004', '胡升', '男', 18, '1234143254325221', '山东', '1989-06-04', '18789347321', '人事部', 'CEO', 'xtiprfw'),
(3, '20111602310016', '汪鼎力', '男', 18, '234235324132412543', '浙江杭州', '1989-06-04', '18789347321', '广告部', 'CTO', 'xtiprfw'),
(4, '20111602310027', '张学扶', '男', 18, '362426199204067718', '江西泰和苑前', '1989-06-04', '18789347643', '财政部', 'CTO', 'xtiprfw'),
(5, '20111602310022', '吴育辉', '男', 18, '123412341423423421', '海南海口', '1989-06-04', '18789347614', '人事部', 'CTO', 'xtiprfw');

-- --------------------------------------------------------

--
-- Table structure for table `workers_payinfo`
--

CREATE TABLE IF NOT EXISTS `workers_payinfo` (
  `payinfo_id` int(5) NOT NULL AUTO_INCREMENT,
  `workers_id` varchar(20) NOT NULL,
  `payinfo_date` char(10) NOT NULL,
  `payinfo_total` int(10) NOT NULL,
  `payinfo_tax` int(10) NOT NULL,
  `payinfo_income` int(10) NOT NULL,
  PRIMARY KEY (`payinfo_id`),
  KEY `workers_id` (`workers_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=gb2312 AUTO_INCREMENT=6 ;

--
-- Dumping data for table `workers_payinfo`
--

INSERT INTO `workers_payinfo` (`payinfo_id`, `workers_id`, `payinfo_date`, `payinfo_total`, `payinfo_tax`, `payinfo_income`) VALUES
(1, '20111602310004', '2013-06', 6000, 200, 5800),
(2, '20111602310016', '2013-06', 6000, 200, 5800),
(3, '20111602310027', '2013-06', 6000, 200, 5800),
(4, '20111602310022', '2013-06', 6000, 200, 5800),
(5, '20111602310000', '2013-06', 6000, 200, 5800);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `workers_attendinfo`
--
ALTER TABLE `workers_attendinfo`
  ADD CONSTRAINT `workers_attendinfo_ibfk_1` FOREIGN KEY (`workers_id`) REFERENCES `workers` (`workers_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `workers_basicinfo`
--
ALTER TABLE `workers_basicinfo`
  ADD CONSTRAINT `workers_basicinfo_ibfk_1` FOREIGN KEY (`workers_id`) REFERENCES `workers` (`workers_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `workers_payinfo`
--
ALTER TABLE `workers_payinfo`
  ADD CONSTRAINT `workers_payinfo_ibfk_1` FOREIGN KEY (`workers_id`) REFERENCES `workers` (`workers_id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
