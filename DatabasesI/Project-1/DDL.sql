CREATE TABLE `group`(
	id integer primary key auto_increment,
	name varchar(100) not null
	owner integer not null,
	foreign key (owner) references user(id)
);
CREATE TABLE user(
	id integer primary key auto_increment,
	name varchar(100) not null,
	email varchar(150) not null,
	password varchar(8)
);
CREATE TABLE playlist(
	id integer primary key auto_increment,
	name varchar(100) not null,
	user_id integer not null,
	foreign key(user_id) references user(id)
);
CREATE TABLE user_group(
	user_id integer not null,
	group_id integer not null,
	created_at date,
	updated_at date,
	primary key(user_id,group_id),
	foreign key (user_id) references user(id),
	foreign key (group_id) references `group`(id)
);
CREATE TABLE  user_user(
	user_id integer not null,
	user_id2 integer not null,
	created_at date,
	updated_at date,
	primary key(user_id,user_id2),
	foreign key (user_id) references user(id),
	foreign key (user_id2) references user(id)
);
CREATE TABLE genre(
	id integer primary key not null,
	name varchar(40) not null
);
CREATE TABLE artist(
	id integer primary key not null,
	name varchar(40) not null
);
CREATE TABLE music(
	id integer primary key not null,
	name varchar(100) not null,
	size integer,
	duration time,
	genre_id integer,
	artist_id integer,
	foreign key(genre_id) references genre(id),
	foreign key (artist_id) references artist(id)
);
CREATE TABLE playlist_music(
	music_id integer not null,
	playlist_id integer not null,
	primary key(music_id,playlist_id),
	foreign key (music_id) references music(id),
	foreign key (playlist_id) references playlist(id)
);
CREATE TABLE group_music(
	group_id integer not null,
	music_id integer not null,
	user_id integer not null,
	created_at date,
	deleted_at date,
	primary key(group_id,music_id),
	foreign key (group_id) references `group`(id),
	foreign key (music_id) references music(id),
	foreign key (user_id) references user(id)
);
INSERT INTO user values 
	(1,'User 1', 'user1@email.com',123),
	(2,'User 2', 'user2@email.com',123),
	(3,'User 3', 'user3@email.com',123),
	(4,'User 4', 'user4@email.com',123),
	(5,'User 5', 'user5@email.com',123),
	(6,'User 6', 'user6@email.com',123),
	(7,'User 7', 'user7@email.com',123);
INSERT INTO `group` values
	(1, 'Group 1'),
	(2, 'Group 2'),
	(3, 'Group 3'),
	(4, 'Group 4'),
	(5, 'Group 5'),
	(6, 'Group 6'),
	(7, 'Group 7');
INSERT INTO playlist values
	-- (PLAYLIST,NOME,USUARIO)
	(1, 'Playlist 1',1),
	(2, 'Playlist 2',1),
	(3, 'Playlist 3',2),
	(4, 'Playlist 4',2),
	(5, 'Playlist 5',3),
	(6, 'Playlist 6',4),
	(7, 'Playlist 7',5);
INSERT INTO user_group values
	(1,1,'2015-01-25',null),
	(1,2,'2015-01-25',null),
	(2,1,'2015-01-25',null),
	(2,2,'2015-01-25',null),
	(3,1,'2015-01-25',null),
	(3,2,'2015-01-25',null),
	(4,1,'2015-01-25',null);
INSERT INTO user_user values
/*(USUARIO 1, USUARIO 2, QUANDO COMEÇOU, QUANDO TERMINOU)*/
	(1,1,'2015-01-25',null),
	(1,2,'2015-01-25',null),
	(2,1,'2015-01-25',null),
	(2,2,'2015-01-25',null),
	(3,1,'2015-01-25',null),
	(4,2,'2015-01-25',null),
	(7,1,'2015-01-25',null);
INSERT INTO genre values
	(1,'Rock'),
	(2,'Sertanejo'),
	(3,'Samba'),
	(4,'Blues'),
	(5,'Eletrônica'),
	(6,'Pop'),
	(7,'Hip Hop');
INSERT INTO artist values
	(1,'Oasis'),
	(2,'Zezé di Camargo & Luciano'),
	(3,'Zeca Pagodinho'),
	(4,'Blind Willie Johnson'),
	(5,'David Guetta'),
	(6,'Madonna'),
	(7,'Ace Hood');
INSERT INTO music values
	(1,'Supersonic',2000,'03:51:00',1,1),
	(2,'No dia em que eu sai de casa',1500,'03:16:00',2,2),
	(3,'Deixa a vida me levar',2500,'03:38:00',3,3),
	(4,'Dark Was the Night - Cold Was the Ground',4500,'03:21:00',4,4),
	(5,'Titanium',4500,'03:57:00',5,5);
INSERT INTO playlist_music values
/*(MUSICA,PLAYLIST)*/
 	(1,1),
 	(2,1),
 	(3,1),
 	(4,1),
 	(5,1),
 	(1,2),
 	(2,2),
 	(3,3),
 	(1,4),
 	(2,4),
 	(3,4);
INSERT INTO group_music values
 	(1,1,1,'2015-01-25',null),
 	(1,2,1,'2015-01-25',null),
 	(1,3,2,'2015-01-25',null),
 	(1,4,2,'2015-01-25',null),
 	(1,5,2,'2015-01-25',null),
 	(2,2,3,'2015-01-25',null),
 	(2,3,3,'2015-01-25',null),
 	(2,4,4,'2015-01-25',null),
 	(3,1,5,'2015-01-25',null),
 	(2,5,4,'2015-01-25',null),
 	(3,4,4,'2015-01-25',null);