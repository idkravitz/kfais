-- Подумать над правильным склонением
INSERT INTO competitions (id, name, date, location) VALUES (1, 'Чемпионата и Первенства по КУДО Приморского края', '2010-12-10', 'г.Владивосток');

-- категории
INSERT INTO categories (name) VALUES ('мужчины');

-- Для жеребьёвки
INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id, units) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), 1, (select id from categories where name='мужчины'), 190);
INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id, units) VALUES ((select id from sportsmen where name='Ганжара Владимир'), 1, (select id from categories where name='мужчины'), 190);
--INSERT INTO sportsmen_competitions (sportsman_id, competition_id, category_id, units) VALUES ((select id from sportsmen where name='Ганжара Владимир'), (select id from categories where name='мужчины'), 190);
/*INSERT INTO sportsmen_competitions (sportsman_id, category_id, units) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id, units) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id, units) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id, units) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id, units) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
INSERT INTO sportsmen_competitions (sportsman_id, category_id, units) VALUES ((select id from sportsmen where name='Карпов Иван Анатольевич'), (select id from categories where name='мужчины'), 190)
  */