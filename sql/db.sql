PRAGMA foreign_keys = ON;

CREATE TABLE sportsmen(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    photo BLOB,
    reg_number INTEGER,
    coach_id INTEGER NOT NULL,
    birthday DATE NOT NULL,
    address TEXT,
    phone TEXT,
    workplace TEXT,
    rank INTEGER,
    job TEXT,
	note TEXT,
	FOREIGN KEY (coach_id) REFERENCES coaches(id) ON DELETE CASCADE ON UPDATE CASCADE);

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

CREATE TABLE certifications( 
    NumRecCert INTEGER NOT NULL PRIMARY KEY,
    date DATE NOT NULL,
    rankFrom INTEGER NOT NULL,
    rankTo INTEGER NOT NULL,
    result TEXT,
    note TEXT);

CREATE TABLE fee(
    id INTEGER NOT NULL PRIMARY KEY,
	sportsmen_id INTEGER NOT NULL,
    date DATE NOT NULL,
	note TEXT,
	FOREIGN KEY (sportsmen_id) REFERENCES sportsmens(id) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE sportsmen_competitions(
    id INTEGER NOT NULL PRIMARY KEY,
    sportsmen_id INTEGER,
	name TEXT,
	DSO TEXT NOT NULL,
    category_id INTEGER NOT NULL,
    draw_number INTEGER NOT NULL,
    units INTEGER NOT NULL,
    prize_place INTEGER,
    fights_count INTEGER,
    fights_won INTEGER,
	note TEXT,
	FOREIGN KEY (sportsmen_id) REFERENCES sportsmens(id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (category_id) REFERENCES categories(id) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE competitions(
    id INTEGER NOT NULL PRIMARY KEY,
    date DATE,
    location TEXT,
	note TEXT);

CREATE TABLE categories(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
	note TEXT);
