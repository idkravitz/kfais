BEGIN TRANSACTION;

/************************************ clubs ************************************/

insert into clubs(name, address) values ('Бастион', 'г. Владивосток, ул. Никифорова, д. 43');
insert into clubs(name, address) values ('Восход', 'г. Владивосток, ул. Русская, д. 74а');
insert into clubs(name, address) values ('Олимпиец', 'г. Владивосток, ул. Батарейная, д. 2');

/************************************ coaches ************************************/

insert into coaches(name, phone, club_id) values ('Ковалёв Владимир Сергеевич', '8-924-675-85-92', (select id from clubs where name = 'Восход'));
insert into coaches(name, phone, club_id) values ('Леоновец М.С.', '8-924-675-85-91', (select id from clubs where name = 'Олимпиец'));
insert into coaches(name, phone, club_id) values ('Петров В.В.', '8-924-675-85-93', (select id from clubs where name = 'Бастион'));

/************************************ ranks ************************************/

insert into ranks(name) values ('10 кю');
insert into ranks(name) values ('9 кю');
insert into ranks(name) values ('8 кю');
insert into ranks(name) values ('10 дан');
insert into ranks(name) values ('9 дан');

/************************************ sportsmen ************************************/

insert into sportsmen(name, birthday, rank_id, reg_number, coach_id, address, phone, workplace, job) values (
	'Дрёмин Николай Иванович',
	'1965-10-10',
	(select id from ranks where name = '9 кю'),
	12345,
	(select id from coaches where name = 'Ковалёв Владимир Сергеевич'), 
	'г. Владивосток, ул. Батарейная, д. 2',
	'8-924-675-85-93',
	'ООО "Nokia"',
	'Инженер'); 
	
insert into sportsmen(name, birthday, rank_id, reg_number, coach_id, address, phone, workplace, job) values (
	'Сидоров Федор Иванович',
	'1990-10-10',
	(select id from ranks where name = '9 дан'),
	123456,
	(select id from coaches where name = 'Ковалёв Владимир Сергеевич'), 
	'г. Владивосток, ул. Батарейная, д. 2',
	'8-924-675-85-93',
	'ООО "Nokia"',
	'Директор');
	
insert into sportsmen(name, birthday, rank_id, reg_number, coach_id, address, phone, workplace, job) values (
	'Крылов Август Измаилович',
	'1990-01-01',
	(select id from ranks where name = '9 дан'),
	1234567,
	(select id from coaches where name = 'Ковалёв Владимир Сергеевич'), 
	'г. Владивосток, ул. Батарейная, д. 2',
	'8-924-675-85-93',
	'ООО "Nokia"',
	'Генеральный директор');

/************************************ fee ************************************/

insert into fee(sportsman_id, date) values ((select id from sportsmen where name = 'Дрёмин Николай Иванович'), '2010-07-01');
insert into fee(sportsman_id, date) values ((select id from sportsmen where name = 'Дрёмин Николай Иванович'), '2011-02-28');
insert into fee(sportsman_id, date) values ((select id from sportsmen where name = 'Сидоров Федор Иванович'), '2010-03-8');

/************************************ certifications ************************************/

insert into certifications(num_rec_sert, sportsman_id, date, rank_from_id, rank_to_id, result) values(
	111111,
	(select id from sportsmen where name = 'Дрёмин Николай Иванович'),
	'2000-10-01',
	(select id from ranks where name = '10 кю'), 
	(select id from ranks where name = '9 кю'), 
	'Сдал');
	
insert into certifications(num_rec_sert, sportsman_id, date, rank_from_id, rank_to_id, result) values(
	222222,
	(select id from sportsmen where name = 'Дрёмин Николай Иванович'),
	'2001-23-02', 
	(select id from ranks where name = '9 кю'), 
	(select id from ranks where name = '8 кю'), 
	'Не сдал');
	
insert into certifications(num_rec_sert, sportsman_id, date, rank_from_id, rank_to_id, result) values(
	3333333,
	(select id from sportsmen where name = 'Сидоров Федор Иванович'),
	'2010-01-04', 
	(select id from ranks where name = '10 дан'), 
	(select id from ranks where name = '9 дан'), 
	'Сдал');

/************************************ categories ************************************/

insert into categories(name) values ('Мужчины, 240-265 ед.');
insert into categories(name) values ('Мужчины, 265-190');

/************************************ competitions ************************************/

insert into competitions(name, date, location) values ('Юбилейные соревнования 09', '2009-09-09', 'г. Владивосток, ул. Батарейная, д. 2');
insert into competitions(name, date, location) values ('Юбилейные соревнования 10', '2010-10-10', 'г. Владивосток, ул. Батарейная, д. 2');

/************************************ sportsmen_competitions ************************************/

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

/*	
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Рудич Сергей Евгеньевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1987-05-07','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Авдеенко Олег Александрович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1970-01-27','г. Благовещенск'); 
/*insert into sportsmen(name, coach_id, birthday, address) values 
    ('Глобин Олег Анатольевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1980-04-17','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Назаретян Нарек Оганесович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1991-10-06','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Кривко Константин Николаевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1979-06-02','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Криворотов Андрей Павлович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1995-08-04','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Тыченко Дмитрий Александрович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1995-10-19','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Баяндин Денис Анатольевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1977-02-23','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Топоев Денис Павлович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1989-12-28','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Зверева Евгения Павловна', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1986-11-07', 'п. Чигири'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Струков Арсений Дмитриевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1992-10-17','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Попов Дмитрий Константинович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1989-08-01','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Казлаускас Ян Йонавич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1990-03-16','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Велесюк Максим Александрович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1990-08-10','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Веселов Дмитрий Юрьевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1984-10-27','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Максименко Александр Юрьевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1991-01-01','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Ефимов Вячеслав Алексеевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1990-02-11','г. Благовещенск'); 
insert into sportsmen(name, coach_id, birthday, address) values 
    ('Яковлев Алексей Андреевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1991-08-05','г. Благовещенск'); */

COMMIT;