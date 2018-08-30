DROP TABLE IF EXISTS categoria CASCADE;
CREATE TABLE categoria (
 codCateg  serial,
 nomeCateg  varchar(200) NOT NULL,
PRIMARY KEY ( codCateg )); 
INSERT INTO  categoria  (nomeCateg) VALUES ('Professor' ),('Motorista' ),('TA' ),('Gerente' );
DROP TABLE IF EXISTS  pessoa CASCADE;
CREATE TABLE  pessoa  (
 codPessoa  int,
 nome  char(50) NOT NULL,
 salario  real,
 codCateg  int NOT NULL,
PRIMARY KEY ( codPessoa ),
CONSTRAINT  pessoa_ibfk_1  FOREIGN KEY ( codCateg ) REFERENCES  categoria 
( codCateg ));
INSERT INTO  pessoa  VALUES (1, 'João Silva' ,1000,2),(2, 'Silva
Mello' ,1400,3),(3, 'Pedro Silva de Alcantara' ,2400,1),(4, 'Alfredo
Borba' ,800,2),(5, 'Alfonso Pena' ,800,3),(6, 'MarloX' ,1800,4),(10, 'Jorge
Campos' ,12000,1),(11, 'Jorge Campos' , null,1),(100, 'João' ,null,1);
DROP TABLE IF EXISTS  endereco CASCADE;
CREATE TABLE  endereco  (
 codPessoa  int,
 cidade  varchar(200),
 estado  char(2),
 numero  int,
 cep  varchar(9),
PRIMARY KEY ( codPessoa ),
CONSTRAINT  endereco_ibfk_1  FOREIGN KEY ( codPessoa ) REFERENCES  pessoa 
( codPessoa ));
INSERT INTO  endereco  VALUES
(1, 'Alegrete' , 'RS' ,33, '78622-863' ),(2, 'Bagé' , 'RS' ,254, '12342-863' ),(3, 'Bagé' , 'RS'
 ,1166, '99821-340' );
DROP TABLE IF EXISTS  projeto CASCADE;
CREATE TABLE  projeto (
 codProj  serial,
 nomeProj  varchar(200) NOT NULL,
PRIMARY KEY ( codProj )
) ;
INSERT INTO  projeto  (nomeProj) VALUES ('Projeto1' ),('Projeto 2' ),('Projeto 3' );
DROP TABLE IF EXISTS  participacao CASCADE;
CREATE TABLE  participacao  (
 codProj  int ,
 codPessoa  int ,
 funcao  varchar(200) NOT NULL,
PRIMARY KEY ( codProj , codPessoa ),
CONSTRAINT  participacao_ibfk_1  FOREIGN KEY ( codProj ) REFERENCES  projeto 
( codProj ),
CONSTRAINT  participacao_ibfk_2  FOREIGN KEY ( codPessoa ) REFERENCES  pessoa 
( codPessoa )
);
INSERT INTO  participacao  VALUES
(1,1, 'Colaborador' ),(1,2, 'Colaborador' ),(1,3, 'Lider'),(2,3, 'Lider'),(3,2, 'Subordinado'),(3,3, 'lider'),(3,4, 'Colaborador'),(3,6, 'Interessado');
