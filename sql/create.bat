SET DB=base.db
DEL /P /F %DB%
sqlite3 -batch %DB% < db.sql
sqlite3 -batch %DB% < init_coaches.sql
sqlite3 -batch %DB% < init_sportsmen.sql
sqlite3 -batch %DB% < init_other.sql
