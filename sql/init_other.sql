BEGIN TRANSACTION;

/************************************ clubs ************************************/

insert into clubs(id, name, address) values (1, 'Бастион', 'г. Владивосток, ул. Никифорова, д. 43');
insert into clubs(id, name, address) values (2, 'Восход', 'г. Владивосток, ул. Русская, д. 74а');
insert into clubs(id, name, address) values (3, 'Олимпиец', 'г. Владивосток, ул. Батарейная, д. 2');

/************************************ update coaches ************************************/

update coaches set club_id = 1 where name = 'Сивопляс Денис Анатольевич';
update coaches set club_id = 1 where name = 'Иванов Вячеслав Юрьевич';
update coaches set club_id = 1 where name = 'Караульных К.А.';

update coaches set club_id = 2 where name = 'Сергеев Александр Садофович';

/***************************************************************************************************/
/************************************ Must be deleted in release ************************************/
/***************************************************************************************************/

/************************************ sertifications ************************************/

--From "Бастион"
insert into sertifications(sportsman_id, date, rank_from_id, rank_to_id) values(
	(select id from sportsmen where name = 'Цирик Сергей'), 
	'2011-04-03',
	(select id from ranks where name = '10 кю'),
	(select id from ranks where name = '7 кю'));
	
insert into sertifications(sportsman_id, date, rank_from_id, rank_to_id) values(
	(select id from sportsmen where name = 'Алексеев Михаил'), 
	'2011-04-03',
	(select id from ranks where name = '10 кю'),
	(select id from ranks where name = '9 кю'));
	
insert into sertifications(sportsman_id, date, rank_from_id, rank_to_id) values(
	(select id from sportsmen where name = 'Иванкин Виктор'), 
	'2011-04-03',
	(select id from ranks where name = '10 кю'),
	(select id from ranks where name = '9 кю'));

insert into sertifications(sportsman_id, date, rank_from_id, rank_to_id) values(
	(select id from sportsmen where name = 'Кивель Сергей Анатольевич'), 
	'2011-04-03',
	(select id from ranks where name = '9 кю'),
	(select id from ranks where name = '8 кю'));
	
insert into sertifications(sportsman_id, date, rank_from_id, rank_to_id) values(
	(select id from sportsmen where name = 'Ханин Алексей'), 
	'2011-04-03',
	(select id from ranks where name = '10 кю'),
	(select id from ranks where name = '9 кю'));

--From "Восход"	
/*
insert into sertifications(sportsman_id, date, rank_from_id, rank_to_id) values(
	(select id from sportsmen where name = 'Ханин Алексей'), 
	'2011-04-03',
	(select id from ranks where name = '10 кю'),
	(select id from ranks where name = '9 кю'));
	
insert into sertifications(sportsman_id, date, rank_from_id, rank_to_id) values(
	(select id from sportsmen where name = 'Ханин Алексей'), 
	'2011-04-03',
	(select id from ranks where name = '10 кю'),
	(select id from ranks where name = '9 кю'));
	
insert into sertifications(sportsman_id, date, rank_from_id, rank_to_id) values(
	(select id from sportsmen where name = 'Ханин Алексей'), 
	'2011-04-03',
	(select id from ranks where name = '10 кю'),
	(select id from ranks where name = '9 кю'));*/
	
/************************************ fee ************************************/
/*
insert into fee(sportsman_id, date) values ((select id from sportsmen where name = 'Дрёмин Николай Иванович'), '2010-07-01');
insert into fee(sportsman_id, date) values ((select id from sportsmen where name = 'Дрёмин Николай Иванович'), '2011-02-28');
insert into fee(sportsman_id, date) values ((select id from sportsmen where name = 'Сидоров Федор Иванович'), '2010-03-8');
*/

/************************************ sertifications ************************************/
/*
insert into sertifications(num_rec_sert, sportsman_id, date, rank_from_id, rank_to_id) values(
	'111111',
	(select id from sportsmen where name = 'Дрёмин Николай Иванович'),
	'2000-10-01',
	(select id from ranks where name = '10 кю'), 
	(select id from ranks where name = '9 кю'));

insert into sertifications(num_rec_sert, sportsman_id, date, rank_from_id, rank_to_id) values(
	'222222',
	(select id from sportsmen where name = 'Дрёмин Николай Иванович'),
	'2001-23-02', 
	(select id from ranks where name = '9 кю'), 
	(select id from ranks where name = '8 кю'));

insert into sertifications(num_rec_sert, sportsman_id, date, rank_from_id, rank_to_id) values(
	'3333333',
	(select id from sportsmen where name = 'Сидоров Федор Иванович'),
	'2010-01-04', 
	(select id from ranks where name = '10 дан'), 
	(select id from ranks where name = '9 дан'));
*/
/************************************ categories ************************************/
/*
insert into categories(name) values ('Мужчины, 240-265 ед.');
insert into categories(name) values ('Мужчины, 265-190');
*/
/************************************ competitions ************************************/
/*
insert into competitions(name, date, location) values ('Юбилейные соревнования 09', '2009-09-09', 'г. Владивосток, ул. Батарейная, д. 2');
insert into competitions(name, date, location) values ('Юбилейные соревнования 10', '2010-10-10', 'г. Владивосток, ул. Батарейная, д. 2');
*/
/************************************ sportsmen_competitions ************************************/
/*
insert into sportsmen_competitions(sportsman_id, DSO, category_id, draw_number, units, prize_place, fights_count, fights_won) values(
	(select id from sportsmen where name = 'Дрёмин Николай Иванович'),
	'КУДО',
	(select id from categories where name = 'Мужчины, 240-265 ед.'),
	1,
	250,
	1,
	2,
	2);

insert into sportsmen_competitions(sportsman_id, DSO, category_id, draw_number, units, prize_place, fights_count, fights_won) values(
	(select id from sportsmen where name = 'Сидоров Федор Иванович'),
	'КУДО',
	(select id from categories where name = 'Мужчины, 240-265 ед.'),
	2,
	260,
	3,
	2,
	1);

insert into sportsmen_competitions(sportsman_id, DSO, category_id, draw_number, units, fights_count, fights_won) values(
	(select id from sportsmen where name = 'Крылов Август Измаилович'),
	'КУДО',
	(select id from categories where name = 'Мужчины, 240-265 ед.'),
	3,
	240,
	2,
	0);

insert into sportsmen_competitions(name, DSO, category_id, draw_number, units, fights_count, fights_won) values(
	'Афанасьев Артур Васильевич',
	'Кик-боксинг',
	(select id from categories where name = 'Мужчины, 240-265 ед.'),
	4,
	265,
	2,
	1);
*/
COMMIT;