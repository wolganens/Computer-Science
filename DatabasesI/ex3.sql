ALTER TABLE `gol_marcado`.`group`
ADD COLUMN user_id int not null,
ADD CONSTRAINT  fk_user_id FOREIGN KEY (user_id) references `gol_marcado`.`user` (`id`)