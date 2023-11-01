-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: db
-- Generation Time: Nov 01, 2023 at 06:55 PM
-- Server version: 8.2.0
-- PHP Version: 8.2.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `fizyka`
--

-- --------------------------------------------------------

--
-- Table structure for table `dzialy`
--

CREATE TABLE `dzialy` (
  `id` int NOT NULL,
  `nazwa` varchar(128) COLLATE utf8mb4_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_polish_ci;

--
-- Dumping data for table `dzialy`
--

INSERT INTO `dzialy` (`id`, `nazwa`) VALUES
(1, 'Mechanika');

-- --------------------------------------------------------

--
-- Table structure for table `odpowiedzi`
--

CREATE TABLE `odpowiedzi` (
  `id` int NOT NULL,
  `pytanie_id` int NOT NULL,
  `poprawna` varchar(512) COLLATE utf8mb4_polish_ci NOT NULL,
  `bledna_1` varchar(512) COLLATE utf8mb4_polish_ci NOT NULL,
  `bledna_2` varchar(512) COLLATE utf8mb4_polish_ci NOT NULL,
  `bledna_3` varchar(512) COLLATE utf8mb4_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_polish_ci;

--
-- Dumping data for table `odpowiedzi`
--

INSERT INTO `odpowiedzi` (`id`, `pytanie_id`, `poprawna`, `bledna_1`, `bledna_2`, `bledna_3`) VALUES
(1, 1, '18 Nm', '0 Nm', '7 Nm', '9 Nm');

-- --------------------------------------------------------

--
-- Table structure for table `pytania`
--

CREATE TABLE `pytania` (
  `id` int NOT NULL,
  `dzial_id` int NOT NULL,
  `rozdzial_id` int NOT NULL,
  `pytanie` varchar(8192) COLLATE utf8mb4_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_polish_ci;

--
-- Dumping data for table `pytania`
--

INSERT INTO `pytania` (`id`, `dzial_id`, `rozdzial_id`, `pytanie`) VALUES
(1, 1, 1, 'Wektor siły jest równy [2;1;2] N, wektor ramienia, za pomocą którego działamy na ciało, ma współrzędne [2;4;-4] m. Ile wynosi wartość momentu siły, jaki zadziała na ciało?');

-- --------------------------------------------------------

--
-- Table structure for table `rozdzialy`
--

CREATE TABLE `rozdzialy` (
  `id` int NOT NULL,
  `dzial_id` int NOT NULL,
  `nazwa` varchar(128) COLLATE utf8mb4_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_polish_ci;

--
-- Dumping data for table `rozdzialy`
--

INSERT INTO `rozdzialy` (`id`, `dzial_id`, `nazwa`) VALUES
(1, 1, 'Zasady dynamiki Newtona');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `dzialy`
--
ALTER TABLE `dzialy`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `odpowiedzi`
--
ALTER TABLE `odpowiedzi`
  ADD PRIMARY KEY (`id`),
  ADD KEY `pytanie_id` (`pytanie_id`);

--
-- Indexes for table `pytania`
--
ALTER TABLE `pytania`
  ADD PRIMARY KEY (`id`),
  ADD KEY `dzial_id` (`dzial_id`),
  ADD KEY `rozdzial_id` (`rozdzial_id`);

--
-- Indexes for table `rozdzialy`
--
ALTER TABLE `rozdzialy`
  ADD PRIMARY KEY (`id`),
  ADD KEY `dzial_id` (`dzial_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `dzialy`
--
ALTER TABLE `dzialy`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `odpowiedzi`
--
ALTER TABLE `odpowiedzi`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `pytania`
--
ALTER TABLE `pytania`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `rozdzialy`
--
ALTER TABLE `rozdzialy`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `odpowiedzi`
--
ALTER TABLE `odpowiedzi`
  ADD CONSTRAINT `odpowiedzi_ibfk_1` FOREIGN KEY (`pytanie_id`) REFERENCES `pytania` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Constraints for table `pytania`
--
ALTER TABLE `pytania`
  ADD CONSTRAINT `pytania_ibfk_1` FOREIGN KEY (`dzial_id`) REFERENCES `dzialy` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `pytania_ibfk_2` FOREIGN KEY (`rozdzial_id`) REFERENCES `rozdzialy` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Constraints for table `rozdzialy`
--
ALTER TABLE `rozdzialy`
  ADD CONSTRAINT `rozdzialy_ibfk_1` FOREIGN KEY (`dzial_id`) REFERENCES `dzialy` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
