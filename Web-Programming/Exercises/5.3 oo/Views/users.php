<h3 class="page-header">Lista de usuários</h3>
<a href="index.php?controller=Pages&action=home" title="Novo usuário" class="btn btn-primary">Novo usuário</a>
<table class="table">
	<thead>
		<tr>
			<th>Nome</th>
			<th>Email</th>
			<th>CPF</th>
			<th>Data</th>
			<th>Senha</th>
		</tr>
	</thead>
	<tbody>
		<?php for ($i = 0 ; $i < count($users) ; $i++ ): ?>
			<tr>
				<td><?php echo $users[$i]->getName(); ?></td>
				<td><?php echo $users[$i]->getEmail(); ?></td>
				<td><?php echo $users[$i]->getCpf(); ?></td>
				<td><?php echo $users[$i]->getDate(); ?></td>
				<td><?php echo $users[$i]->getPassword(); ?></td>
			</tr>
		<?php endfor ?>
	</tbody>
</table>
