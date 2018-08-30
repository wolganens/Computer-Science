/*1. Selecionar todos registros de pessoa 

select count(*) from pessoa;

*/

/* 2. Selecionar somente o nome das pessoas 

select nome from pessoa

*/

/* 3. Selecionar nome e salário das pessoas cujo salário seja superior a 1000 reais 

select pessoa.nome, pessoa.salario from pessoa where salario > 1000

*/


/* 4.Selecionar nome e salário das pessoas cujo salário fique entre 500 e 1000 reais :

select pessoa.nome from pessoa where salario between 500 and 1000

*/

/* 5.Selecionar nome das pessoas que não tenham salário definido :

select pessoa.nome from pessoa where salario isnull

*/

/* 6. Selecionar nome das pessoas que tenham salário definido 

select pessoa.nome from pessoa where salario is not null

*/

/* 7. Selecionar nome das pessoas que tenham Silva como parte do nome 

select pessoa.nome from pessoa where pessoa.nome like '%Silva%'

*/

/* 8.Selecionar nome e salário d as pessoas que tenham Silva como parte do nome e recebem mais do que 1500 reais:

select pessoa.nome, pessoa.salario from pessoa where pessoa.nome like '%Silva%'

*/

/*10.Selecionar nome e salário das pessoas cujo salário seja superior a 1000 reais, e ordenar o resultado por salário 

select pessoa.nome,pessoa.salario from pessoa where salario > 1000 order by pessoa.salario

*/

/* 11. Agrupar os resultados, exibindo número de pessoas com salarios iguais

select count(*) from pessoa group by pessoa.salario

*/

/* 12. Agrupar os resultados, exibindo número de pessoas por código da categoria:

select categoria.codcateg , count(*) from pessoa inner join categoria on pessoa.codcateg = categoria.codcateg group by categoria.codcateg order by categoria.codcateg

*/

/* 13. Selecionar nome das pessoas e nome da categoria que elas pertence

select pessoa.nome, categoria.nomecateg from pessoa inner join categoria on pessoa.codcateg = categoria.codcateg

*/

/* 14. Agrupar os resultados, exibindo número de pessoas por nome da categoria

select categoria.nomecateg, count(*) from pessoa inner join categoria on pessoa.codcateg = categoria.codcateg group by categoria.nomecateg order by categoria.nomecateg

*/

/* 15. Selecione todos os registros de categoria 

select * from categoria

*/

/* 16. Exiba o número de registros de categoria 

select count(*) from categoria

*/

/* 17. Selecionar nome de pessoas da categoria TA 

select pessoa.nome from pessoa inner join categoria on pessoa.codcateg = categoria.codcateg and categoria.nomecateg like 'TA'

*/


/* 18. Selecionar nomes de todas categorias e nome das pessoas relacionadas a essas categoria 

select pessoa.nome, categoria.nomecateg from pessoa inner join categoria on pessoa.codcateg = categoria.codcateg

*/

/* 19. Selecionar nome das pessoas e nome dos projetos em que elas atuam

select pessoa.nome, projeto.nomeproj from participacao inner join projeto on participacao.codproj = projeto.codproj inner join pessoa on pessoa.codpessoa = participacao.codpessoa

*/

/* 20. Selecionar quantas pessoas trabalham no projeto de código 1

select count(*) from participacao inner join projeto on participacao.codproj = projeto.codproj and participacao.codproj = 3

*/

/* 21. Selecionar nome da pessoa, projeto onde atua e sua função.

select pessoa.nome, projeto.nomeproj, participacao.funcao from participacao inner join pessoa on participacao.codpessoa = pessoa.codpessoa
inner join projeto on participacao.codproj = projeto.codproj

*/

/*22. Selecionar pessoas e seus endereços 

select pessoa.nome, endereco.cidade,endereco.estado,endereco.numero,endereco.cep from endereco inner join pessoa on endereco.codpessoa = pessoa.codpessoa

*/

/* 23. Agrupar cidades iguais, exibindo a cidade e o maior salário pago naquela cidade 

select endereco.cidade, max(pessoa.salario) from endereco inner join pessoa on endereco.codpessoa = pessoa.codpessoa group by endereco.cidade

*/

/*24. Selecionar pessoas e seus endereços, mesmo pessoas que não possuam endereços

select pessoa.nome, endereco.* from endereco right join pessoa on endereco.codpessoa = pessoa.codpessoa

*/

/*25. Selecionar pessoas e projetos onde trabalharam. Exibir também pessoas que não atuaram em nenhum projeto

select pessoa.nome , projeto.nomeproj from pessoa left join participacao on pessoa.codpessoa = participacao.codpessoa left join projeto on participacao.codproj = projeto.codproj

*/ 
/*26. Selecionar pessoas de Bagé que atuaram como líderes de projetos 

select pessoa.nome, endereco.cidade,projeto.nomeproj from endereco inner join pessoa on endereco.codpessoa = pessoa.codpessoa and endereco.cidade = 'Bagé'
inner join participacao on pessoa.codpessoa = participacao.codpessoa and participacao.funcao = 'Lider'
inner join projeto on participacao.codproj = projeto.codproj

*/

/* 27. Exibir o número de pessoas de Bagé que já atuaram em pelo menos algum projeto 

select count(*) , projeto.nomeproj from endereco inner join pessoa on endereco.codpessoa = pessoa.codpessoa and endereco.cidade = 'Bagé'
inner join participacao on participacao.codpessoa = pessoa.codpessoa
inner join projeto on participacao.codproj = projeto.codproj group by projeto.nomeproj

*/

/* 28. Selecionar cidades e o número de pessoas daquela cidade que já atuaram em projetos em posições que não fossem de Líder

select count(*), endereco.cidade from endereco inner join pessoa on endereco.codpessoa = pessoa.codpessoa 
inner join participacao on participacao.codpessoa = pessoa.codpessoa and participacao.funcao != 'Lider'
inner join projeto on participacao.codproj = projeto.codproj group by endereco.cidade

*/
