-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `bd` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `bd` ;

-- -----------------------------------------------------
-- Table `bd`.`dev_cat`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bd`.`dev_cat` (
  `id` INT NOT NULL,
  `cat` VARCHAR(30) NULL,
  `salary` FLOAT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bd`.`developer`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bd`.`developer` (
  `id` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  `dev_cat_id` INT NOT NULL,
  PRIMARY KEY (`id`, `dev_cat_id`),
  INDEX `fk_developer_dev_cat1_idx` (`dev_cat_id` ASC),
  CONSTRAINT `fk_developer_dev_cat1`
    FOREIGN KEY (`dev_cat_id`)
    REFERENCES `bd`.`dev_cat` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bd`.`client`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bd`.`client` (
  `id` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bd`.`project`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bd`.`project` (
  `id` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  `client_id` INT NOT NULL,
  PRIMARY KEY (`id`, `client_id`),
  INDEX `fk_project_client_idx` (`client_id` ASC),
  CONSTRAINT `fk_project_client`
    FOREIGN KEY (`client_id`)
    REFERENCES `bd`.`client` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bd`.`project_has_developer`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bd`.`project_has_developer` (
  `developer_id` INT NOT NULL,
  `project_id` INT NOT NULL,
  PRIMARY KEY (`developer_id`, `project_id`),
  INDEX `fk_project_has_developer_developer1_idx` (`developer_id` ASC),
  INDEX `fk_project_has_developer_project1_idx` (`project_id` ASC),
  CONSTRAINT `fk_project_has_developer_developer1`
    FOREIGN KEY (`developer_id`)
    REFERENCES `bd`.`developer` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_project_has_developer_project1`
    FOREIGN KEY (`project_id`)
    REFERENCES `bd`.`project` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
