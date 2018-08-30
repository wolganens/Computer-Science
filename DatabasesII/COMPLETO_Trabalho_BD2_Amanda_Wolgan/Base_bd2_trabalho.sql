create table table1(
	ip serial primary key,
	"is" integer not null,
	ic1 integer not null,
	ic2 integer not null,
	ni integer not null
);
create table table2(
	ip serial primary key,
	"is" integer not null,
	ic1 integer not null,
	ic2 integer not null,
	ni integer not null
);
create table table3(
	ip serial primary key,
	"is" integer not null,
	ic1 integer not null,
	ic2 integer not null,
	ni integer not null
);
create table table4(
	ip serial primary key,
	"is" integer not null,
	ic1 integer not null,
	ic2 integer not null,
	ni integer not null
);
create table table5(
	ip serial primary key,
	"is" integer not null,
	ic1 integer not null,
	ic2 integer not null,
	ni integer not null
);
create index primary_index_ip on table1 (ip);
create index secondary_index_is on table1 ("is");
create index multicolumn_index_ic1_ic2 on table1 (ic1,ic2);

create index primary_index_ip_t2 on table2 (ip);
create index secondary_index_is_t2 on table2 ("is");
create index multicolumn_index_ic1_ic2_t2 on table2 (ic1,ic2);

create index primary_index_ip_t3 on table3 (ip);
create index secondary_index_is_t3 on table3 ("is");
create index multicolumn_index_ic1_ic2_t3 on table3 (ic1,ic2);

create index primary_index_ip_t4 on table4 (ip);
create index secondary_index_is_t4 on table4 ("is");
create index multicolumn_index_ic1_ic2_t4 on table4 (ic1,ic2);

create index primary_index_ip_t5 on table5 (ip);
create index secondary_index_is_t5 on table5 ("is");
create index multicolumn_index_ic1_ic2_t5 on table5 (ic1,ic2);

insert into table1 values ( 
	generate_series(1,100),
	ceil(random() * 100),
	ceil(random() * 100),
	ceil(random() * 100),
	ceil(random() * 100)
); 	
insert into table2 values ( generate_series(1,1000),ceil(random() * 1000),ceil(random() * 1000),ceil(random() * 1000),ceil(random() * 1000));
insert into table3 values ( generate_series(1,10000),ceil(random() * 10000),ceil(random() * 10000),ceil(random() * 10000),ceil(random() * 10000)); 
insert into table4 values ( generate_series(1,100000),ceil(random() * 100000),ceil(random() * 100000),ceil(random() * 100000),ceil(random() * 100000)); 
insert into table5 values ( generate_series(1,1000000),ceil(random() * 1000000),ceil(random() * 1000000),ceil(random() * 1000000),ceil(random() * 1000000)); 