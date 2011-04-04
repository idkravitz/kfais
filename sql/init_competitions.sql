-- Подумать над правильным склонением
INSERT INTO competitions (id, name, name_prot, date, location) VALUES (
	1, 'Чемпионат и Первенство по КУДО Приморского края', 'Чемпионата и Первенства по КУДО Приморского края', '2010-12-10', 'г.Владивосток');

-- категории
INSERT INTO categories (name) VALUES ('мужчины 190 ед.');
INSERT INTO categories (name) VALUES ('мужчины 200 ед.');
INSERT INTO categories (name) VALUES ('1996-1998 г.р. до 240 ед.');


-- Для жеребьёвки
INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id) VALUES (
    (select id from sportsmen where name='Карпов Иван Анатольевич'),
    1,
    (select id from categories where name='мужчины 190 ед.'));
INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id) VALUES (
    (select id from sportsmen where name='Ганжара Владимир'),
    1,
    (select id from categories where name='мужчины 190 ед.'));
INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id) VALUES (
    (select id from sportsmen where name='Васильев Артем'),
    1,
    (select id from categories where name='мужчины 190 ед.'));
INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id) VALUES (
    (select id from sportsmen where name='Шихардин Андрей'),
    1,
    (select id from categories where name='мужчины 190 ед.'));
INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id) VALUES (
    (select id from sportsmen where name='Прохоров Андрей Олегович'),
    1,
    (select id from categories where name='мужчины 200 ед.'));
INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id) VALUES (
    (select id from sportsmen where name='Глушко Никита Эдуардович'),
    1,
    (select id from categories where name='1996-1998 г.р. до 240 ед.'));

--INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id) VALUES ((select id from sportsmen where name='Ганжара Владимир'), (select id from categories where name='мужчины'), 190);
/*INSERT INTO sportsmen_competitions (sportsman_id, category_id) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
  */

INSERT INTO prize_winners (sportsman_competition_id, fights_count, fights_won, place, region, city) VALUES(
    (SELECT id FROM sportsmen_competitions WHERE sportsman_id=(SELECT id FROM sportsmen where name = 'Васильев Артем') and competition_id=1),
    2,
    2,
    1,
    'Приморский край',
    'Владивосток');
INSERT INTO prize_winners (sportsman_competition_id, fights_count, fights_won, place, region, city) VALUES(
    (SELECT id FROM sportsmen_competitions WHERE sportsman_id=(SELECT id FROM sportsmen WHERE name = 'Шихардин Андрей') and competition_id=1),
    2,
    1,
    2,
    'Приморский край',
    'Уссурийск');
