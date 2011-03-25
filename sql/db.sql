CREATE TABLE sportsmens(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    photo BLOB,
    reg_number INTEGER,
    coach_id INTEGER NOT NULL REFERENCES coaches(id),
    birthday DATE NOT NULL,
    address TEXT,
    phone TEXT,
    workplace TEXT,
    rank INTEGER,
    job TEXT);

CREATE TABLE coaches(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    phone TEXT,
    club_id INTEGER REFERENCES clubs(id));

CREATE TABLE clubs(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL,
    address TEXT);

CREATE TABLE certifications( 
    NumRecCert INTEGER NOT NULL PRIMARY KEY,
    date DATE NOT NULL,
    rankFrom INTEGER,
    rankTO INTEGER,
    result TEXT,
    note TEXT);

CREATE TABLE fee(
    id INTEGER NOT NULL PRIMARY KEY,
    date DATE,
    sportsman_id INTEGER NOT NULL REFERENCES sportsmens(id));

CREATE TABLE competitions_details(
    id INTEGER NOT NULL PRIMARY KEY,
    competitor_id INTEGER NOT NULL REFERENCES sportsmens(id),
    draw_number INTEGER NOT NULL,
    units INTEGER NOT NULL,
    category_id INTEGER NOT NULL REFERENCES categories(id),
    place INTEGER,
    fights_count INTEGER,
    fights_won INTEGER);

CREATE TABLE competitions(
    id INTEGER NOT NULL PRIMARY KEY,
    date DATE,
    location TEXT);

CREATE TABLE categories(
    id INTEGER NOT NULL PRIMARY KEY,
    name TEXT NOT NULL);
