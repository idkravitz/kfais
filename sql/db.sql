PRAGMA foreign_keys = ON;

CREATE TABLE sportsmen(
    id INTEGER NOT NULL PRIMARY KEY,
    photo BLOB,
    name TEXT NOT NULL,
    birthday DATE NOT NULL,
	rank_id INTEGER,
    reg_number TEXT,
    coach_id INTEGER,
    address TEXT,
    phone TEXT,
    workplace TEXT,
    job TEXT,
	note TEXT,
	FOREIGN KEY (coach_id) REFERENCES coaches(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (rank_id) REFERENCES ranks(id) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE coaches(
	id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    phone TEXT,
	club_id INTEGER,
	note TEXT,
	FOREIGN KEY (club_id) REFERENCES clubs(id) ON DELETE CASCADE ON UPDATE CASCADE);

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
    num_rec_sert TEXT NOT NULL PRIMARY KEY,
	sportsman_id INTEGER NOT NULL,
    date DATE NOT NULL,
    rank_from_id INTEGER,	--If sportsman haven't any rank
    rank_to_id INTEGER NOT NULL,
    result TEXT,
    note TEXT,
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (rank_from_id) REFERENCES ranks(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (rank_to_id) REFERENCES ranks(id) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE fee(
    id INTEGER NOT NULL PRIMARY KEY,
	sportsman_id INTEGER NOT NULL,
    date DATE NOT NULL,
	note TEXT,
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE sportsmen_competitions(
    id INTEGER NOT NULL PRIMARY KEY,
    sportsman_id INTEGER,
	name TEXT,
	DSO TEXT NOT NULL,
    category_id INTEGER NOT NULL,
    draw_number INTEGER NOT NULL,
    units INTEGER NOT NULL,
    prize_place INTEGER,
    fights_count INTEGER,
    fights_won INTEGER,
	note TEXT,
	FOREIGN KEY (sportsman_id) REFERENCES sportsmen(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (category_id) REFERENCES categories(id) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE competitions(
	id INTEGER NOT NULL PRIMARY KEY,
	name TEXT TEXT NOT NULL,
    date DATE,
    location TEXT,
	note TEXT);

CREATE TABLE categories(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
	note TEXT);