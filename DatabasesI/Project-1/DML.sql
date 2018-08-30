-- 1 Músicas compartilhadas por um usuario em um determinado grupo
select music.name from group_music 
inner join music on music.id = group_music.music_id
inner join `group` on `group`.`id` = group_music.group_id and `group`.`name` like 'Gr%';
inner join user on user.id = group_music.user_id

/* 2 Selecionar os nomes da música que um determinado usuario compartilhou nos grupos*/

select music.name, `group`.name from group_music
inner join music on music.id = group_music.music_id
inner join user on user.id = group_music.user_id and user.name like 'User %'
inner join `group` on `group`.id = group_music.group_id;

/* 3 Selecionar o número de músicas que um usuário compartilhou em um grupo agrupado por genero*/

select genre.name,count(*) from group_music
inner join user on user.id = group_music.user_id and user.name like 'User 1'
inner join `group` on `group`.id = group_music.group_id
inner join music on music.id = group_music.music_id
inner join genre on genre.id = music.genre_id
group by genre.name

/* 4 ORDENAR GÊNEROS POR MAIOR QUANTIDADE DE MÚSICA*/
select genre.name, count(*) as c from music 
inner join genre on genre.id = music.genre_id
group by genre.name order by c desc;

/* 5 selecionar o número de músicas de um determinado artista na playlist de um determinado usuario*/
select count(*) from playlist_music
inner join music on music.id = playlist_music.music_id
inner join playlist on playlist.id = playlist_music.playlist_id
inner join artist on artist.id = music.artist_id and artist.name like 'Zezé %'
inner join user on user.id = playlist.user_id and user.name like 'User 1';
--  6 Selecionar playlists de um determinado usuário
select * from playlist 
inner join user on user.id = playlist.user_id and user.name like 'User %';

/* 7 selecionar o nome de todos os amigos do usuario de id 1*/
select user.name from user 
inner join user_user on user_user.user_id = user.id and user_user.user_id2 = 1
union
select user.name from user 
inner join user_user on user_user.user_id2 = user.id and user_user.user_id = 1;


/* 8 selecionar musicas que um amigo do usuario de id 1 postou em grupos*/

select music.name, user.name from user
inner join user_user on user_user.user_id = user.id and user_user.user_id2 = 1
inner join group_music on group_music.user_id = user_user.user_id
inner join music on music.id = group_music.music_id
union
select music.name, user.name from user
inner join user_user on user_user.user_id2 = user.id and user_user.user_id = 1
inner join group_music on group_music.user_id = user_user.user_id2
inner join music on music.id = group_music.music_id;

--  9 selecionar musicas compartilhadas em grupos de um determinado genero
select music.name from group_music 
inner join music on music.id = group_music.music_id
inner join genre on music.genre_id = genre.id and genre.name like 'Rock'


/* 10 selecionar número de músicas existentes no sistema*/
select count (*) from music;
/* 11 selecionar número de usuários cadastrados no sistema*/
select count (*) from user;
