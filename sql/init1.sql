insert into coaches(name, phone) values ('Ковалёв Владимир Сергеевич', '8-924-675-85-92');

insert into sportsmens(name, coach_id, birthday, address) values 
    ('Дрёмин Николай Иванович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1965-10-10','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Рудич Сергей Евгеньевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1987-05-07','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Авдеенко Олег Александрович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1970-01-27','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Глобин Олег Анатольевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1980-04-17','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Назаретян Нарек Оганесович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1991-10-06','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Кривко Константин Николаевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1979-06-02','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Криворотов Андрей Павлович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1995-08-04','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Тыченко Дмитрий Александрович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1995-10-19','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Баяндин Денис Анатольевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1977-02-23','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Топоев Денис Павлович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1989-12-28','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Зверева Евгения Павловна', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1986-11-07', 'п. Чигири'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Струков Арсений Дмитриевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1992-10-17','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Попов Дмитрий Константинович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1989-08-01','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Казлаускас Ян Йонавич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1990-03-16','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Велесюк Максим Александрович', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1990-08-10','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Веселов Дмитрий Юрьевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1984-10-27','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Максименко Александр Юрьевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1991-01-01','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Ефимов Вячеслав Алексеевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1990-02-11','г. Благовещенск'); 
insert into sportsmens(name, coach_id, birthday, address) values 
    ('Яковлев Алексей Андреевич', (select id from coaches where name='Ковалёв Владимир Сергеевич'), '1991-08-05','г. Благовещенск'); 
