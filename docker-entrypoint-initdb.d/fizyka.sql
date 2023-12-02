-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: db
-- Generation Time: Nov 11, 2023 at 03:59 PM
-- Server version: 8.2.0
-- PHP Version: 8.2.11

CREATE DATABASE IF NOT EXISTS `fizyka`;
USE `fizyka`;

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

USE `fizyka`;

CREATE TABLE `dzialy` (
  `id` int NOT NULL,
  `nazwa` varchar(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_polish_ci;

--
-- Dumping data for table `dzialy`
--

INSERT INTO `dzialy` (`id`, `nazwa`) VALUES
(1, 'Mechanika'),
(2, 'Elektryczność i magnetyzm'),
(3, 'Optyka'),
(4, 'Termodynamika');

-- --------------------------------------------------------

--
-- Table structure for table `odpowiedzi`
--

USE `fizyka`;

CREATE TABLE `odpowiedzi` (
  `id` int NOT NULL,
  `pytanie_id` int NOT NULL,
  `poprawna` varchar(512) CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL,
  `bledna_1` varchar(512) CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL,
  `bledna_2` varchar(512) CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL,
  `bledna_3` varchar(512) CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_polish_ci;

--
-- Dumping data for table `odpowiedzi`
--

INSERT INTO `odpowiedzi` (`id`, `pytanie_id`, `poprawna`, `bledna_1`, `bledna_2`, `bledna_3`) VALUES
(1, 1, '18 Nm', '0 Nm', '7 Nm', '9 Nm'),
(2, 2, '49,35 J', '1800 J', '900 J', '16,2 J'),
(3, 3, '0,2 km', '1000 m', '2 km', 'żadna odpowiedź nie jest poprawna'),
(4, 4, '[0, 0, 7] kg m^2/s', '[0, 0, 3.5] kg m^2/s', '[1, 2, 3.5] kg m^2/s', '3.5 kg m^2/s'),
(5, 5, '20,39 m', '41,00 m', '20,30 m', 'żadna odpowiedź nie jest prawdziwa'),
(6, 6, '0,375', '0,3', '0,15', '0,5'),
(7, 7, '1/2 f', '2f', 'f', '1/4 f'),
(8, 8, '0.46 K/s', '4.6 K/s', '46 K/min', '4.6 K/min'),
(9, 9, 'Odległość maleje', 'Odległość wzrasta', 'Odległość się nie zmienia', 'Za mało informacji'),
(10, 10, 'P = 574 W, P_wyp = 72 W', 'P = 626 W, P_wyp = 94 W', 'P = 437 W, P_wyp = 125 W', 'P = 385 W, P_wyp = 63 W'),
(11, 11, 'Ugnie się w kierunku do normalnej', 'Ugnie się w kierunku od normalnej', 'Będzie biegł bez zmian', 'Różnie się zachowa w zależności od długości fali światła ');

-- --------------------------------------------------------

--
-- Table structure for table `pytania`
--

USE `fizyka`;

CREATE TABLE `pytania` (
  `id` int NOT NULL,
  `dzial_id` int NOT NULL,
  `rozdzial_id` int NOT NULL,
  `pytanie` varchar(8192) CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_polish_ci;

--
-- Dumping data for table `pytania`
--

INSERT INTO `pytania` (`id`, `dzial_id`, `rozdzial_id`, `pytanie`) VALUES
(1, 1, 1, 'Wektor siły jest równy [2;1;2] N, wektor ramienia, za pomocą którego działamy na ciało, ma współrzędne [2;4;-4] m. Ile wynosi wartość momentu siły, jaki zadziała na ciało?'),
(2, 1, 2, 'Bryła sztywna w kształcie jednorodnej kuli o promieniu 1 m oraz masie 100 kg obraca się wokół osi przechodzącej przez jej środek z prędkością kątową 90 stopni/sekundę. Energia ruchu obrotowego tej kuli wynosi:'),
(3, 1, 3, 'Samochód jadący jednostajnie prostym odcinkiem drogi z prędkością 36 km/h nagle zaczyna przyśpieszać z przyspieszeniem 2 m/s^2.  Jaką drogę przebędzie w czasie 10 sekund od momentu, kiedy zaczął przyśpieszać?'),
(4, 1, 4, 'Ciało o masie 2 kg porusza się ruchem jednostajnym po okręgu o promieniu 1 m. Płaszczyzna w której odbywa się ruch zawarta jest w płaszczyźnie XY, a początek układu odniesienia jest w środku okręgu. Wartość prędkości liniowej ciała wynosi 3,5 m/s. Moment pędu tego ciała liczony względem środka okręgu, po którym się porusza wynosi:'),
(5, 1, 3, 'Na jaką maksymalną wysokość (z dokładnością do drugiego miejsca po przecinku) wzniesie się kulka wystrzelona pionowo w górę z prędkością 72 km/h (przyjmij przyspieszenie ziemskie równe 9,81 m/s^2)?'),
(6, 1, 5, 'Powierzchnia równi tworzy z poziomem kąt równy 15 stopni. Klocek możemy przesuwać po równi ruchem jednostajnym z dołu do góry używając siły F1, zaś z góry na dół używając siły F2. Ile wynosi współczynnik tarcia klocka o równię, jeśli F1=6F2, a obie siły są równoległe do powierzchni równi?'),
(7, 1, 4, 'Siła tarcia f jest siłą dośrodkową dla samochodu pokonującego zakręt o promieniu R z prędkością V. Dalej samochód pokonuje podobny zakręt, ale o promieniu 2R z tą samą prędkością V. Aby przejechać drugi zakręt siła tarcia musi wynosić: '),
(8, 4, 6, 'Element projektowanego układu elektronicznego składa się z 23 mg krzemu. Płynący prąd dodaje energię w tempie 7.4 mW = 7.4 * 10^(-3) J/s. Jeśli nie można w żaden sposób odprowadzać ciepła z elementu, z jaką prędkością rośnie jego temperatura? Ciepło właściwe krzemu to 705 J/kg*K'),
(9, 3, 7, 'Oświetlasz laserem, którego długość fali świetlnej można płynnie zmieniać, parę blisko siebie położonych szczelin. Na ekranie za szczelinami widać układ prążków interferencyjnych. Jeśli zmieniasz długość światła od czerwonego do niebieskiego, jak będzie się zmieniała odległość między prążkami?'),
(10, 4, 8, 'Jaką całkowitą moc wypromieniowuje ciało ludzkie o powierzchni 1.2 m^2 i temperaturze powierzchni 30°C = 303 K? Jeśli otoczenie ma temperaturę 20°C, jaka jest wypadkowa strata ciepła? Emisyjność ludzkiego ciała jest bliska 1, stała Boltzmanna δ = 5.67 * 10^(-8) W/(m^2 * K^4)'),
(11, 3, 10, 'Jeśli światło biegnie z ośrodka o większym współczynniku załamania do ośrodka o mniejszym współczynniku załamania, to po minięciu granicy ośrodków promień:');

-- --------------------------------------------------------

--
-- Table structure for table `rozdzialy`
--

USE `fizyka`;

CREATE TABLE `rozdzialy` (
  `id` int NOT NULL,
  `dzial_id` int NOT NULL,
  `nazwa` varchar(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_polish_ci;

--
-- Dumping data for table `rozdzialy`
--

INSERT INTO `rozdzialy` (`id`, `dzial_id`, `nazwa`) VALUES
(1, 1, 'Zasady dynamiki Newtona'),
(2, 1, 'Obroty wokół stałej osi'),
(3, 1, 'Ruch prostoliniowy'),
(4, 1, 'Ruch po okręgu'),
(5, 1, 'Równia pochyła'),
(6, 4, 'Temperatura i ciepło'),
(7, 3, 'Interferencja'),
(8, 4, 'Zasady termodynamiki'),
(10, 3, 'Natura światła');

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
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `pytania`
--
ALTER TABLE `pytania`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `rozdzialy`
--
ALTER TABLE `rozdzialy`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

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
