PRAGMA foreign_keys = ON;

CREATE TABLE sportsmen(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    birthday DATE,
	rank_id INTEGER DEFAULT 0,
    reg_number TEXT,
    coach_id INTEGER DEFAULT 0,
    address TEXT,
    phone TEXT,
    workplace TEXT,
    job TEXT,
	note TEXT,
	FOREIGN KEY (coach_id) REFERENCES coaches(id) ON DELETE SET DEFAULT ON UPDATE CASCADE,
	FOREIGN KEY (rank_id) REFERENCES ranks(id) ON DELETE SET DEFAULT ON UPDATE CASCADE);

CREATE TABLE coaches(
	id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    phone TEXT,
	club_id INTEGER DEFAULT 0,
	note TEXT,
	FOREIGN KEY (club_id) REFERENCES clubs(id) ON DELETE SET DEFAULT ON UPDATE CASCADE);

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
    rank_from_id INTEGER DEFAULT 0,	--If sportsman haven't any rank
    rank_to_id INTEGER NOT NULL,
    note TEXT,
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (rank_from_id) REFERENCES ranks(id) ON DELETE SET DEFAULT ON UPDATE CASCADE,
	FOREIGN KEY (rank_to_id) REFERENCES ranks(id) ON DELETE SET DEFAULT ON UPDATE CASCADE);

CREATE TABLE fee(
    id INTEGER NOT NULL PRIMARY KEY,
	sportsman_id INTEGER NOT NULL,
    date DATE NOT NULL,
	note TEXT,
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE sportsmen_competitions(
    id INTEGER NOT NULL PRIMARY KEY,
    sportsman_id INTEGER DEFAULT 0,
	name TEXT,
	DSO TEXT,
    category_id INTEGER NOT NULL,
    draw_number INTEGER,
    units INTEGER NOT NULL,
    prize_place INTEGER,
    fights_count INTEGER,
    fights_won INTEGER,
	note TEXT,
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (category_id) REFERENCES categories(id) ON DELETE SET NULL ON UPDATE CASCADE);

CREATE TABLE competitions(
	id INTEGER NOT NULL PRIMARY KEY,
	name TEXT NOT NULL,
    date DATE,
    location TEXT,
	note TEXT);

CREATE TABLE categories(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
	note TEXT);

CREATE VIEW sportsmen_competitions_view as 
		select sc.id, s.name, sc.DSO, sc.category_id, sc.draw_number, sc.units, sc.prize_place, sc.fights_count, sc.fights_won, sc.note 
		from sportsmen_competitions sc inner join sportsmen s on sc.sportsman_id=s.id where sc.sportsman_id <> 0
	UNION
		select id, name, DSO, category_id, draw_number, units, prize_place, fights_count, fights_won, note from sportsmen_competitions where sportsman_id=0; 

INSERT INTO clubs (id, name) VALUES (0, '');
INSERT INTO coaches (id, name) VALUES (0, '');
INSERT INTO ranks (id, name) VALUES (0, '');
INSERT INTO sportsmen (id, name, birthday) VALUES (0, '', '2000-01-01');
