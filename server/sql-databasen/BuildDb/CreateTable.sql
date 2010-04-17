create domain type CHAR(3)
	check (value in ('DVD', 'VHS'));

create domain cat varchar(10)
	check (value in ('Horror', 'Action', 'Porn'));

create table product
	(
	id int, 
	actors text,
	category cat,
	title varchar(80),
	primary key (id)
	);

create table Rent
	(
	id int, 
	type type,
	rprice double precision,
	rcopies int,
	primary key (id, type),
	foreign key (id) references  product
	);

create table Sale
	(
	id int,
	type type, 
	sprice double precision,
	rcopies int,
	primary key (id, type),
	foreign key (id) references  product
	);

create table customer
	(
	pnr int,
	name varchar(30),
	phone varchar(15),
	primary key (pnr)
	);

create table membership
	(
	pnr int,
	expdate date,
	primary key (pnr),
	foreign key (pnr) references customer
	);

create table rents 
	(
	pnr int,
	id int,
	type type,
	rentdate date,
	retdate date,
	primary key (id, pnr, type),
	foreign key (pnr) references customer,
	foreign key (id) references product
	);

create table buys
	(
	pnr int,
	id int,
	type type,
	bdate date,
	primary key (id, pnr, type),
	foreign key (pnr) references customer,
	foreign key (id) references product
	);

create index productid on product using hash (id);
create index Rentid on Rent using hash (id);
create index Saleid on Sale using hash (id);
create index customerpnr on customer using hash (pnr);
create index membershippnr on membership using hash (pnr);
create index rentspnr on rents using hash (pnr);
create index buysprn on buys using hash (pnr);


create index producttitle on product using btree (title);
create index productcat on product using btree (category);
create index membershipexpdate on membership using btree (expdate);
create index rentsrentdate on rents using btree (rentdate);
create index rentsretdate on rents using btree (retdate);
create index buysbdate on buys using btree (bdate);


create view customerView AS
	Select actors, category, title from product;


