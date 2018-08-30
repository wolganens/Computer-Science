/* 1)Recupere o nome dos projetos juntamente com o nome dos clientes
select project.name, client.name from project
inner join client on project.client_id = project.id*/

/*2)Recupere o nome dos desenvolvedores e o nome dos projetos
que eles trabalham
select developer.name, project.name from project_has_developer
inner join developer on project_has_developer.developer_id = developer.id
inner join project on project_has_developer.project_id = project.id;
*/

/* 3) Liste o nome dos desenvolvedores e clientes.
select developer.name from developer union select client.name from client*/

/*4) Liste todas as categorias funcionais e os empregados associados
a elas
select dev_cat.cat,developer.name from developer
inner join dev_cat on developer.dev_cat_id = dev_cat.id
*/
/*5) Recupere o número de desenvolvedores.
select count(*) from developer;
*/

/*6)Recupere o número de desenvolvedores da categoria ‘
senior
’
select count(*) from developer
inner join dev_cat on developer.dev_cat_id = dev_cat.id and dev_cat.cat like 'Pleno'*/

/*7)Selecione o total de horas trabalhadas no projeto de
codigo
?
select project.id ,sum(horas) from project_has_developer
inner join project on project_has_developer.project_id = project.id
group by project.id
*/
/*8)Selecione o total de horas trabalhadas por projeto */

/*9)Selecione o numero de desenvolvedores por projeto (o nome do
projeto deve ser listado) 
select count(*),project.name from project_has_developer
inner join project on project_has_developer.project_id = project.id group by project.name
*/
