PRAGMA foreign_keys = ON;

CREATE TABLE sportsmen(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    birthday DATE,
	rank_id INTEGER,
    reg_number TEXT,
    coach_id INTEGER,
    address TEXT,
    phone TEXT,
    workplace TEXT,
    job TEXT,
	note TEXT,
--	UNIQUE(reg_number),
	FOREIGN KEY (coach_id) REFERENCES coaches(id) ON DELETE SET NULL ON UPDATE CASCADE,
	FOREIGN KEY (rank_id) REFERENCES ranks(id) ON DELETE SET NULL ON UPDATE CASCADE);

CREATE TABLE coaches(
	id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    phone TEXT,
	club_id INTEGER,
	note TEXT,
	FOREIGN KEY (club_id) REFERENCES clubs(id) ON DELETE SET NULL ON UPDATE CASCADE);

CREATE TABLE clubs(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    address TEXT,
	note TEXT);

CREATE TABLE ranks(
	id INTEGER NOT NULL PRIMARY KEY,
	name TEXT NOT NULL,
	note TEXT);

CREATE TABLE sertifications( 
	id INTEGER NOT NULL PRIMARY KEY,
	sportsman_id INTEGER NOT NULL,
    date DATE NOT NULL,
    rank_from_id INTEGER,	--If sportsman haven't any rank
    rank_to_id INTEGER NOT NULL,
    note TEXT,
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (rank_from_id) REFERENCES ranks(id) ON DELETE SET NULL ON UPDATE CASCADE,
	FOREIGN KEY (rank_to_id) REFERENCES ranks(id) ON DELETE SET NULL ON UPDATE CASCADE);

CREATE TABLE fee(
    id INTEGER NOT NULL PRIMARY KEY,
	sportsman_id INTEGER NOT NULL,
    date DATE NOT NULL,
	note TEXT,
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE competitions(
	id INTEGER NOT NULL PRIMARY KEY,
	name TEXT NOT NULL,
	name_prot TEXT NOT NULL,
    date DATE NOT NULL,
    location TEXT,
	note TEXT,
	UNIQUE(name, date));

CREATE TABLE categories(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
	note TEXT);

CREATE TABLE sportsmen_competitions(
    id INTEGER NOT NULL PRIMARY KEY,
    sportsman_id INTEGER NOT NULL,
    competition_id INTEGER NOT NULL,
    category_id INTEGER,
    draw_number INTEGER,
    units INTEGER,
	note TEXT,
	UNIQUE(sportsman_id, competition_id),
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (competition_id) REFERENCES competitions(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (category_id) REFERENCES categories(id) ON DELETE SET NULL ON UPDATE CASCADE);

CREATE TABLE prize_winners(
	id INTEGER NOT NULL PRIMARY KEY,
	sportsman_competition_id INTEGER NOT NULL,
	fights_count INTEGER,
    fights_won INTEGER,
    place INTEGER,
    region TEXT,						--For result protocol
    city TEXT,      					--For result protocol
    note TEXT,
    UNIQUE(sportsman_competition_id),
    FOREIGN KEY (sportsman_competition_id) REFERENCES sportsmen_competitions(id) ON DELETE CASCADE ON UPDATE CASCADE);

/*
CREATE TRIGGER trigger_sc_insert AFTER INSERT ON sportsmen_competitions
	BEGIN
		UPDATE sportsmen_competitions SET name = (SELECT s.name FROM sportsmen s WHERE s.id = new.sportsman_id) || ' - ' || 
												 (SELECT c.name || ' ' || c.date FROM competitions c WHERE c.id = new.competition_id) 
			WHERE id = new.id;
	END;

CREATE TRIGGER trigger_sc_update AFTER UPDATE OF sportsman_id, competition_id ON sportsmen_competitions
	BEGIN
		UPDATE sportsmen_competitions SET name = (SELECT s.name FROM sportsmen s WHERE s.id = new.sportsman_id) || ' - ' || 
												 (SELECT c.name || ' ' || c.date FROM competitions c WHERE c.id = new.competition_id) 
			WHERE id = new.id;
	END;
*/
/*
CREATE VIEW sportsmen_competitions_view AS
	SELECT sc.id, sc.sportsman_id, c.name, c.date, sc.category_id, sc.draw_number, sc.units, sc.note 
		FROM sportsmen_competitions sc JOIN competitions c ON sc.competition_id = c.id;

CREATE VIEW prize_winners_view AS 
	SELECT pw.id, c.name, c.date, s.name, pw.fights_count, pw.fights_won, pw.place, pw.region, pw.city, pw.note FROM prize_winners pw 
		JOIN sportsmen_competitions sc, sportsmen s, competitions c ON 
		pw.sportsman_competition_id = sc.id and sc.sportsman_id = s.id and sc.competition_id = c.id;*/

--INSERT INTO clubs (id, name) VALUES (0, '');
--INSERT INTO coaches (id, name) VALUES (0, '');
--INSERT INTO ranks (id, name) VALUES (0, '');
--INSERT INTO sportsmen (id, name, birthday) VALUES (0, '', '2000-01-01');
--INSERT INTO categories (id, name) VALUES (0, '');