-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Versión del servidor:         10.6.4-MariaDB - Arch Linux
-- SO del servidor:              Linux
-- HeidiSQL Versión:             11.3.0.6295
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

-- Volcando datos para la tabla consulta.configuracion: ~1 rows (aproximadamente)
/*!40000 ALTER TABLE `configuracion` DISABLE KEYS */;
INSERT INTO `configuracion` (`id`, `directorio`, `pdf`, `web`, `imagen`, `video`) VALUES
	(0, '/home/ladis/Programacion/builds/Consulta/Consultas', 'okular', 'firefox', 'gwenview', 'vlc');
/*!40000 ALTER TABLE `configuracion` ENABLE KEYS */;

-- Volcando datos para la tabla consulta.pacientes: ~3 rows (aproximadamente)
/*!40000 ALTER TABLE `pacientes` DISABLE KEYS */;
INSERT INTO `pacientes` (`idPaciente`, `nombre`, `apellido1`, `apellido2`, `dni`, `localidad`, `provincia`, `cp`, `telefono`, `correo`, `profesion`, `nacimiento`, `sexo`, `eCivil`, `hijos`, `grupoS`, `rh`, `notas`) VALUES
	(1, 'Ladislao', 'Pascual', 'Bonilla', '20196639V', 'Santander', 'Cantabria', '39007', '655827262', 'Ladispascual@gmail.com', 'Naturista', '1972-08-07', 'M', 'P', 2, 'AB', '-', ''),
	(2, 'Sonia', 'Torre', 'Teran', '', '', '', '', '657-82-97-72', '', '', '2000-01-01', 'F', 'S', 0, 'NS', 'NS', ''),
	(3, 'Carmen', 'Gutierrez', 'Hernandez', '12687281K', 'Palencia', 'Palencia', '', '677824933', '', 'Administrativo', '1949-06-15', 'F', 'S', 0, 'NS', 'NS', ''),
	(4, 'Banesa', '', '', '', 'Colindres', 'Cantabria', '', '', '', '', '1978-03-01', 'F', 'S', 0, 'NS', 'NS', '');
/*!40000 ALTER TABLE `pacientes` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
